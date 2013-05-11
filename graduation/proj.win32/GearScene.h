
#ifndef __GEAR_SCENE__
#define __GEAR_SCENE__

#include "cocos2d.h"
#include "PhysicsWorld.h"

using namespace cocos2d;

class GearScene: public CCLayer
{
public:
	virtual bool init();
	CREATE_FUNC(GearScene);
	static CCScene* scene();

	void onEnter();

public:
	virtual bool ccTouchBegan (CCTouch *pTouch, CCEvent *pEvent);
	virtual void ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent);
	virtual void ccTouchEnded (CCTouch *pTouch, CCEvent *pEvent);

private:
	PhysicsWorld* physics;
	void draw();
	void updateWorld(float deltaTime);

private:
	void createMap();
};



#endif
