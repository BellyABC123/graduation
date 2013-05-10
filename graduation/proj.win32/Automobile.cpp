
#include "Automobile.h"


Automobile::Automobile(Physics* physics, float x, float y)
{
	this->physics = physics;

	motorSpeed = 2 * 3.1425 * 2;
	maxMotorTorque = 999;

	createAutomobile(x,y);
}

void Automobile::createAutomobile(float x, float y)
{
	float meterPerPixel = physics->getMeterPerPixel();
	b2World* world = physics->getWorld();

	x *= meterPerPixel;
	y *= meterPerPixel;
	
	float carBodyWidth = 150 * meterPerPixel;
	float carBodyHeight = 10 * meterPerPixel;
	float wheelRadius	= 25 * meterPerPixel;

	b2Vec2 localAnchorFixWheel1	= b2Vec2(-60*meterPerPixel,0);
	b2Vec2 localAnchorFixWheel2 = b2Vec2(+60*meterPerPixel,0);

	PhysicsBody physicsBody(world);
	b2Body* carBody = physicsBody.newBody()
								->setBodyPosition(b2Vec2(x, y))
								->setBodyType(b2BodyType::b2_dynamicBody)
								->setPolygonShapeASBox(carBodyWidth/2,carBodyHeight/2)
								->setFixtureDensity(1)
								->createFixture()
								->createBody();

	b2Body* wheel1	= physicsBody.newBody()
								->newBody()
								->setBodyType(b2BodyType::b2_dynamicBody)
								->setBodyPosition(b2Vec2(x,y))
								->setCircleShape(wheelRadius)
								->setFixtureDensity(1)
								->setFixtureFriction(1)
								->createFixture()
								->createBody();

	b2Body* wheel2	= physicsBody.newBody()
								->newBody()
								->setBodyType(b2BodyType::b2_dynamicBody)
								->setBodyPosition(b2Vec2(x,y))
								->setCircleShape(wheelRadius)
								->setFixtureDensity(1)
								->setFixtureFriction(1)
								->createFixture()
								->createBody();

	b2RevoluteJointDef revoluteJointDef;
	revoluteJointDef.collideConnected = false;
	revoluteJointDef.bodyA = carBody;
	revoluteJointDef.bodyB = wheel1;
	revoluteJointDef.localAnchorA = localAnchorFixWheel1;
	revoluteJointDef.localAnchorB = b2Vec2(0,0);
	revoluteJoints[0] = (b2RevoluteJoint*)world->CreateJoint(&revoluteJointDef);

	revoluteJointDef.bodyB = wheel2;
	revoluteJointDef.localAnchorA = localAnchorFixWheel2;
	revoluteJoints[1] = (b2RevoluteJoint*)world->CreateJoint(&revoluteJointDef);
}

void Automobile::forward()
{
	for(int i=0;i<2;i++)
	{
		revoluteJoints[i]->EnableMotor(true);
		revoluteJoints[i]->SetMotorSpeed(motorSpeed);
		revoluteJoints[i]->SetMaxMotorTorque(maxMotorTorque);
	}
}
void Automobile::backward()
{
	for(int i=0;i<2;i++)
	{
		revoluteJoints[i]->EnableMotor(true);
		revoluteJoints[i]->SetMotorSpeed(-motorSpeed);
		revoluteJoints[i]->SetMaxMotorTorque(maxMotorTorque);
	}
}
void Automobile::stop()
{
	for(int i=0;i<2;i++)
	{
		revoluteJoints[i]->EnableMotor(false);
	}
}
