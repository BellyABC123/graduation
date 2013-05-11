

#ifndef __AUTOMOBILE__
#define __AUTOMOBILE__

#include "Box2D/Box2D.h"
#include "PhysicsBody.h"

#include "PhysicsWorld.h"

class PhysicsWorld;

class Automobile
{
private:
	PhysicsWorld* physics;
	float motorSpeed;	// radian per second
	float maxMotorTorque;
	b2RevoluteJoint* revoluteJoints[2];

public:
	Automobile(PhysicsWorld* physics, float x, float y);
	void createAutomobile(float x, float y);

	void forward();
	void backward();
	void stop();
};

#endif // !__AUTOMOBILE__
