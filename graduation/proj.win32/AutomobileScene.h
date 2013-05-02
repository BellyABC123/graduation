#ifndef __AUTOMOBILE_SCENE__
#define __AUTOMOBILE_SCENE__

#include "cocos2d.h"
#include "Box2D/Box2D.h"
#include "SimpleAudioEngine.h"

#include "BirdSprite.h"
#include "SlingSprite.h"

using namespace  cocos2d;

class AutomobileScene : public cocos2d::CCLayer
{
public:
	AutomobileScene():
		meterPerPixel(0.1),
		gravity(0,-9.8) ,
		sleep(true),
		updateTime(1.0 / 30),
		stepTime(1.0 / 30),
		velocityIterations(10),
		positionIterations(10),
		mouseJoint(0)
	{
	}
	// Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
	virtual bool init();  

	// there's no 'id' in cpp, so we recommand to return the exactly class pointer
	static cocos2d::CCScene* scene();

	// a selector callback
	void menuCloseCallback(CCObject* pSender);

	// implement the "static node()" method manually
	CREATE_FUNC(AutomobileScene);



	// Box2d
private:
	float meterPerPixel;
public:
	float getMeterPerPixel(){ return meterPerPixel;}

private:
	b2World* world;
	b2Body* backgroundBody;
public:
	b2Body* getBackgroundBody() { return backgroundBody;}
private:
	b2Vec2 gravity;
	bool sleep;

	float updateTime;
	float stepTime;
	int velocityIterations;
	int positionIterations;


	// Mouse Joint
	b2MouseJoint* mouseJoint;
public:
	void setMouseJoint(b2MouseJoint* mouseJoint) { this->mouseJoint = mouseJoint;}

private:
	void initBox2D();
	void updateWorld(float deltaTime);
	void draw();

	// Utilities
	b2Body* createCircle(int x, int y, float radius, char* name);
	b2Body* createStaticBrick(int x, int y, int width, int height,char* name);
	b2Body* createBrick(int x, int y, int width, int height,char* name);

	b2Body* createIdol(int x, int y,char* name);

	void createString(b2Body* bodyA, b2Body* bodyB,float distance);


public:
	virtual void onEnter();
	virtual void onExit();

	virtual bool ccTouchBegan(CCTouch* pTouch ,CCEvent* pEvent);
	virtual void ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent);
	virtual void ccTouchEnded (CCTouch *pTouch, CCEvent *pEvent);

};

#endif  // __ANGRY_BIRD_CENE__