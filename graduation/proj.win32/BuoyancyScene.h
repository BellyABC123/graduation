#ifndef __BUOYANCY_SCENE__
#define __BUOYANCY_SCENE__

#include "cocos2d.h"
#include "Box2D/Box2D.h"
#include "PhysicsWorld.h"

using namespace cocos2d;

class BuoyancyScene: public CCLayer
{
public:
	virtual bool init();
	CREATE_FUNC(BuoyancyScene);
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






#endif //
