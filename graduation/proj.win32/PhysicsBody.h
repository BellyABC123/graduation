#ifndef __PHYSICS_BODY__
#define __PHYSICS_BODY__

#include "Box2D/Box2D.h"

#include <iostream>
using namespace std;

class PhysicsBody
{
private:
	b2World* world;

	b2BodyDef* bodyDef;
	b2Body* body;

	b2FixtureDef* fixtureDef;

	b2ChainShape*		chainShape;
	b2CircleShape*		circleShape;
	b2EdgeShape*		edgeShape;
	b2PolygonShape* polygonShape;

public:
	PhysicsBody(b2World* world);

private:
	bool isBodyExistence(char* functionName);
	void resetAllShape();
	void resetFixture();
	void resetBody();

public:
	// 操作 Body
	PhysicsBody* newBody();
	PhysicsBody* setBodyPosition(b2Vec2 position);
	PhysicsBody* setBodyType(b2BodyType type);

	// 操作 Shape
	// polygonShape
	PhysicsBody* setPolygonShapeASBox(float hx, float hy);

	// 操作 Fixture
private:
	bool _setFixtureSensorFlag;
public:
	PhysicsBody* setFixtureSensor(bool sensor);
	PhysicsBody* setFixtureDensity(float density);
	PhysicsBody* setFixtureRestitution(float restitution);
	PhysicsBody* setFixtureFriction(float friction);
	PhysicsBody* setFixtureGroupIndex(int groupIndex);
	PhysicsBody* setFixtureCategoryBits(int categoryBits);
	PhysicsBody* setFixtureMaskBits(int maskBits);
	PhysicsBody* createFixture();

	// 结束 流语法
	b2Body* createBody();
};

#endif // !__PHYSICS_BODY__
