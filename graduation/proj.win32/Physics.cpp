
#include "Physics.h"
#include "BodyUserData.h"
#include "GLES-Render.h"
#include "cocos2d.h"

#include "PhysicsBody.h"

Physics::Physics():
	meterPerPixel(0.1),
	gravity(0,-9.8) ,
	sleep(true),
	updateTime(1.0 / 30),
	stepTime(1.0 / 30),
	velocityIterations(10),
	positionIterations(10),
	mouseJoint(NULL)
	//customContactListener(this)
{
	customContactListener = new CustomContactListener(this);

	density = 1;
}

bool Physics::init()
{
	world = new b2World(gravity);
	if(NULL == world)	return false;

	world->SetContactListener(customContactListener);
	world->SetAllowSleeping(true);

	b2BodyDef bodyDef;
	backgroundBody = world->CreateBody(&bodyDef);

	// Static Platform
	createStaticBrick(400,-1,800,6,"platform");


	//PhysicsBody* physicsBody = new PhysicsBody(world);
	//physicsBody
	//					->setBodyPosition(b2Vec2(400 * meterPerPixel, 300 * meterPerPixel))
	//					->setBodyType(b2BodyType::b2_dynamicBody)
	//					->setPolygonShapeASBox(50*meterPerPixel, 50*meterPerPixel)
	//					->setFixtureDensity(1)
	//					->createFixture()
	//					->setBodyPosition(b2Vec2(100*meterPerPixel, 100*meterPerPixel))
	//					->setPolygonShapeASBox(50*meterPerPixel, 50*meterPerPixel)
	//					->createFixture();


	//b2DistanceJointDef distanceJointDef;
	//distanceJointDef.bodyA = brick1;
	//distanceJointDef.bodyB = brick2;
	//distanceJointDef.collideConnected = true;
	//b2Vec2 baryCenter = brick1->GetWorldCenter();
	//distanceJointDef.localAnchorA = b2Vec2(25 * meterPerPixel,0);
	//distanceJointDef.localAnchorB = b2Vec2(0,0);
	//distanceJointDef.length = 110 * meterPerPixel;

	//world->CreateJoint(&distanceJointDef);


	//b2RevoluteJointDef revoluteJointDef;
	//revoluteJointDef.Initialize(brick1, brick2 , brick1->GetWorldCenter());
	//world->CreateJoint(&revoluteJointDef);


	// Set Debug Draw
	GLESDebugDraw* draw = new GLESDebugDraw(1.0 / meterPerPixel);
	if(NULL == draw)	return false;
	world->SetDebugDraw(draw);
	draw->SetFlags(b2Draw::e_shapeBit | b2Draw::e_jointBit | b2Draw::e_pairBit);  

	return true;
}

Physics* Physics::create()
{
	Physics* instance = new Physics();
	
	if(instance && instance->init())
	{
		return instance;
	}

	delete instance;
	return NULL;
}

void Physics::updateWorld()
{
	world->Step(stepTime,velocityIterations,positionIterations);
	customContactListener->applyBuoyancyEachStep();
	//world->ClearForces();
}

void Physics::drawDebugData()
{
	world->DrawDebugData();
}

// Utilities
b2Body* Physics::createCircle(int x, int y, float radius, char* name)
{	
	b2BodyDef bodyDefinition;
	b2CircleShape circleShape;
	b2FixtureDef fixtureDefinition;
	fixtureDefinition.shape = &circleShape;

	// Body
	bodyDefinition.type = b2BodyType::b2_dynamicBody;
	bodyDefinition.position.Set( x * meterPerPixel, y * meterPerPixel);
	b2Body* body = world->CreateBody(&bodyDefinition);

	body->SetUserData(new BodyUserData(name));

	// Fixture
	fixtureDefinition.density		= 2;
	fixtureDefinition.restitution	= 0.4;
	fixtureDefinition.friction		= 0.5;
	// Shape
	circleShape.m_radius = radius * meterPerPixel;

	body->CreateFixture(&fixtureDefinition);
	return body;
}
b2Body* Physics::createStaticBrick(int x, int y, int width, int height,char* name, float angle )
{
	b2BodyDef bodyDef;
	b2PolygonShape polygonShape;
	b2FixtureDef fixtureDef;
	fixtureDef.shape = &polygonShape;

	fixtureDef.density = density;
	fixtureDef.restitution = 0.4;
	fixtureDef.friction = 0.5;

	bodyDef.position.Set(x * meterPerPixel, y * meterPerPixel);
	b2Body* body = world->CreateBody(&bodyDef);

	body->SetUserData(new BodyUserData(name));

	polygonShape.SetAsBox(width*meterPerPixel/ 2, height*meterPerPixel/2, b2Vec2(0,0), angle);

	//polygonShape
	body->CreateFixture(&fixtureDef);
	return body;
}
b2Body* Physics::createBrick(int x, int y, int width, int height,char* name, float angle, int group)
{
	b2BodyDef bodyDef;
	b2PolygonShape polygonShape;
	b2FixtureDef fixtureDef;
	fixtureDef.shape = &polygonShape;

	fixtureDef.density = density;
	fixtureDef.restitution = 0.4;
	fixtureDef.friction = 0.5;
	fixtureDef.filter.groupIndex = group;

	bodyDef.position.Set(x*meterPerPixel,y*meterPerPixel);
	bodyDef.type = b2BodyType::b2_dynamicBody;
	b2Body* body = world->CreateBody(&bodyDef);

	body->SetUserData(new BodyUserData(name));

	polygonShape.SetAsBox(width*meterPerPixel/2,height*meterPerPixel/2, b2Vec2(0,0), angle);
	body->CreateFixture(&fixtureDef);
	return body;
}
b2Body* Physics::createIdol(int x, int y,char* name)
{
	int width = 5 * meterPerPixel;
	int height = 20 * meterPerPixel;
	b2Vec2 center1(0,-height);
	float angle = 3.14 / 4;

	b2BodyDef bodyDef;
	b2PolygonShape polygonShape;
	b2FixtureDef fixtureDef;

	bodyDef.position.Set(x*meterPerPixel,y*meterPerPixel);
	bodyDef.type = b2BodyType::b2_dynamicBody;
	b2Body* body = world->CreateBody(&bodyDef);
	fixtureDef.shape = &polygonShape;

	body->SetUserData(new BodyUserData(name));

	fixtureDef.density = 1;
	fixtureDef.restitution = 0.4;
	fixtureDef.friction = 0.5;

	polygonShape.SetAsBox(width, height);

	body->CreateFixture(&fixtureDef);

	polygonShape.SetAsBox(width, height, center1, -angle);
	body->CreateFixture(&fixtureDef);

	polygonShape.SetAsBox(width, height, center1, angle);
	body->CreateFixture(&fixtureDef);

	b2Vec2 vector[4];
	vector[0].Set(0 * meterPerPixel,10 * meterPerPixel);
	vector[1].Set(15 * meterPerPixel,25 * meterPerPixel);
	vector[2].Set(0 * meterPerPixel,40 * meterPerPixel);
	vector[3].Set(-15 * meterPerPixel,25 * meterPerPixel);
	polygonShape.Set(vector,4);
	body->CreateFixture(&fixtureDef);

	return body;
}

class GetClickFixtureCallback :public b2QueryCallback
{
private:
	CCPoint	clickPoint;
	Physics* physics;


public:
	GetClickFixtureCallback(Physics* physics,CCPoint& clickPoint)
	{
		this->physics = physics;
		this->clickPoint = clickPoint;
	}

	bool 	ReportFixture (b2Fixture *fixture)
	{
		b2Body* clickedBody = fixture->GetBody();
		BodyUserData* bodyUserData	= (BodyUserData*)clickedBody->GetUserData();

		if(clickedBody->GetType() == b2BodyType::b2_dynamicBody)
		{
			cout<<"click dynamic body:"<<bodyUserData->getName()<<endl;
			b2MouseJointDef mouseJointDef;
			mouseJointDef.bodyA = physics->getBackgroundBody();
			mouseJointDef.bodyB = clickedBody;
			mouseJointDef.target = b2Vec2(clickPoint.x * physics->getMeterPerPixel() ,
																clickPoint.y * physics->getMeterPerPixel());

			mouseJointDef.maxForce = 1000 * clickedBody->GetMass();

			physics->createMouseJoint(&mouseJointDef);
		}

		return false;
	}
};

void Physics::touchBegin(CCTouch *pTouch, CCEvent *pEvent)
{
	CCPoint point = pTouch->getLocation();

	b2AABB aabb;
	aabb.lowerBound = b2Vec2(point.x * meterPerPixel ,point.y * meterPerPixel);
	aabb.upperBound = b2Vec2(point.x * meterPerPixel,point.y * meterPerPixel);

	GetClickFixtureCallback getClickFixtureCallback(this,point);
	world->QueryAABB(&getClickFixtureCallback,aabb);
}

void Physics::touchMoved(CCTouch *pTouch, CCEvent *pEvent)
{
	if(NULL != mouseJoint)
	{
		mouseJoint->SetTarget(b2Vec2(
															pTouch->getLocation().x * meterPerPixel,
															pTouch->getLocation().y * meterPerPixel
															)
											);
	}
}
void Physics::touchEnded (CCTouch *pTouch, CCEvent *pEvent)
{
	if(NULL != mouseJoint)
	{
			world->DestroyJoint(mouseJoint);
			mouseJoint = NULL;
	}
}

float Physics::getRectangleInRadian(b2Body* bodyA, b2Body* bodyB)
{
	b2Body* leftBody;
	b2Body* rightBody;

	if(bodyA->GetPosition().x < bodyB->GetPosition().x)
	{
		leftBody = bodyA;
		rightBody = bodyB;
	}
	else
	{
		leftBody = bodyB;
		rightBody = bodyA;
	}

	float dy = rightBody->GetPosition().y - leftBody->GetPosition().y;
	float dx = rightBody->GetPosition().x - leftBody->GetPosition().x;

	return atan(dy / dx);
}


void Physics::createRope(b2Body* bodyA, b2Body* bodyB,int length)
{
	// About The Small Rectangles
	// Constructing A Rope
	float smallRectWidth	= 1;
	float smallRectHeight	= 2;
	float anchorMargin = 0.25;
	int needSmallRectNumber = length * meterPerPixel / (smallRectHeight - 2*anchorMargin) - 1;

	cout<<"length: "<<length * meterPerPixel<<endl;
	cout<<"need small rect number: "<<needSmallRectNumber<<endl;
	cout<<"smallRectHeight - 2*anchorMargin = "<<smallRectHeight - 2*anchorMargin<<endl;

	//float angle = -getRectangleInRadian(bodyA, bodyB);
	b2Body* leftBody;
	b2Body* rightBody;
	if(bodyA->GetPosition().x < bodyB->GetPosition().x)
	{
		leftBody = bodyA;
		rightBody = bodyB;
	}
	else
	{
		leftBody = bodyB;
		rightBody = bodyA;
	}

	b2Body* aboveBody;
	b2Body* belowBody;
	if(bodyA->GetPosition().y > bodyB->GetPosition().y)
	{
		aboveBody = bodyA;
		belowBody = bodyB;
	}else
	{
		aboveBody = bodyB;
		belowBody = bodyA;
	}

	float dx = rightBody->GetPosition().x - leftBody->GetPosition().x;
	float dy = aboveBody->GetPosition().y - belowBody->GetPosition().y;
	float dLong;
	float dShort;
	b2Body* startBody;
	b2Body* endBody;

	if(dx > dy)
	{
		dLong = dx / needSmallRectNumber;
		dShort = dy / needSmallRectNumber;
		startBody = leftBody;
		endBody = rightBody;
	}
	else
	{
		// dy >= dx
		dLong = dy / needSmallRectNumber;
		dShort = dx / needSmallRectNumber;
		startBody = belowBody;
		endBody = aboveBody;
	}

	b2RevoluteJointDef revoluteJointDef;
	revoluteJointDef.collideConnected = false;
	b2Body* previousBody = startBody;

	b2Vec2 startPoint = startBody->GetPosition();
	b2Body* smallRect;
	for(int i=0;i<needSmallRectNumber;i++)
	{
		PhysicsBody physicsBody(world);
		smallRect = physicsBody.newBody()
												->setBodyPosition(b2Vec2(startPoint.x,startPoint.y))
												->setBodyType(b2BodyType::b2_dynamicBody)
												->setPolygonShapeASBox(smallRectWidth/2,smallRectHeight/2)
												->setFixtureDensity(0.1)
												->setFixtureGroupIndex(-2)
												->setFixtureMaskBits(0)
												->createFixture()
												->createBody();

		revoluteJointDef.bodyA = previousBody;
		revoluteJointDef.bodyB = smallRect;

		if(previousBody == startBody)
			revoluteJointDef.localAnchorA = b2Vec2(0, 0);
		else
			revoluteJointDef.localAnchorA = b2Vec2(0, (-smallRectHeight/2 + anchorMargin));

		revoluteJointDef.localAnchorB = b2Vec2(0, (+smallRectHeight/2 - anchorMargin) );
		world->CreateJoint(&revoluteJointDef);

		previousBody = revoluteJointDef.bodyB;

		if(dx > dy)
		{
			startPoint.x += dLong;
			startPoint.y += dShort;
		}else
		{
			startPoint.x += dShort;
			startPoint.y += dLong;
		}
	} // end for

	revoluteJointDef.bodyA = previousBody;
	revoluteJointDef.bodyB = bodyB;
	world->CreateJoint(&revoluteJointDef);


	b2RopeJointDef ropeJointDef;
	ropeJointDef.collideConnected = true;
	ropeJointDef.bodyA = bodyA;
	ropeJointDef.bodyB = bodyB;
	ropeJointDef.maxLength = length * meterPerPixel;
	cout<<"Rope Length: "<<ropeJointDef.maxLength<<endl;
	world->CreateJoint(&ropeJointDef);
}

b2Body*	Physics::createOneWayPlatform(int x, int y, int width, int height, char* name)
{
	b2Body* body = createStaticBrick(x,y,width,height,name);
	customContactListener->setOneSidedPlatformEanble();
	customContactListener->addOneSidedPlatform(body);
	return NULL;
}

b2Body*	Physics::createWaterPool(int x, int y, int width, int height, char* name)
{
	PhysicsBody body(world);

	customContactListener->setBuoyancyEnable(true);

	return body.newBody()
		->setBodyPosition(b2Vec2(x*getMeterPerPixel(),y*getMeterPerPixel()))
		->setPolygonShapeASBox(width*getMeterPerPixel()/2, height*getMeterPerPixel()/2)
		->setFixtureSensor(true)
		->setFixtureDensity(2)
		->createFixture()
		->createBody();
}

Automobile* Physics::createAutomobile(int x, int y)
{
	return new Automobile(this,x,y);
}