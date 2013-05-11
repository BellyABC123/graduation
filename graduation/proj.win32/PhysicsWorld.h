
#ifndef __PHYSICS_WORLD__
#define __PHYSICS_WORLD__

#include "Box2D/Box2D.h"
#include "cocos2d.h"
#include "CustomContactListener.h"
#include "Automobile.h"

using namespace cocos2d;

class CustomContactListener;
class Automobile;

class PhysicsWorld
{
private:

	float meterPerPixel;
	b2Vec2 gravity;
	bool sleep;

	b2World* world;
	b2Body* backgroundBody;

	// Joint
	b2MouseJoint* mouseJoint;

	float updateTime;
	float stepTime;
	int velocityIterations;
	int positionIterations;

	// Parameter For Creating Body
	float density;

public:
	PhysicsWorld();


	bool init();
	static PhysicsWorld* create();
	void updateWorld();
	void drawDebugData();

	void touchBegin(CCTouch *pTouch, CCEvent *pEvent);
	void touchMoved(CCTouch *pTouch, CCEvent *pEvent);
	void touchEnded (CCTouch *pTouch, CCEvent *pEvent);

	float		getMeterPerPixel(){ return meterPerPixel;}
	float		getUpdateTime(){ return updateTime;}
	float		getStepTime(){return stepTime;}
	b2World*	getWorld(){ return world;}
	b2Body*		getBackgroundBody() { return backgroundBody;}

	// Utilities

	float	getDensity(){return density;}
	void	setDensity(float density){ this->density = density; }




	b2Body* createCircle(int x, int y, float radius, char* name);
	b2Body* createStaticBrick(int x, int y, int width, int height, char* name, float angle = 0);
	b2Body* createBrick(int x, int y, int width, int height,char* name, float angle = 0, int group = 0);
	b2Body* createIdol(int x, int y,char* name);
	void	createRope(b2Body* bodyA, b2Body* bodyB,int length);
	void	createMouseJoint(b2MouseJointDef* jointDef){ mouseJoint = (b2MouseJoint*)world->CreateJoint(jointDef);}
	b2Body*	createOneWayPlatform(int x, int y, int width, int height, char* name);
	b2Body*	createWaterPool(int x, int y, int width, int height, char* name);
	Automobile*	createAutomobile(int x, int y);

private:

	CustomContactListener* customContactListener;
	// Utilites
	float	getRectangleInRadian(b2Body* bodyA, b2Body* bodyB);
};

#endif // !__PHYSICS_WORLD__
