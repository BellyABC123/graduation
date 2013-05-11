#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include "Box2D/Box2D.h"
#include "SimpleAudioEngine.h"
#include "PhysicsWorld.h"

using namespace  cocos2d;

class TotemScene : public CCLayer
{
private:
	PhysicsWorld* physicsWorld;
	void draw();
	void updateWorld(float deltaTime);
	void createMap();

public:
    virtual bool init();  
	CREATE_FUNC(TotemScene);
    static cocos2d::CCScene* scene();

	virtual void onEnter();
	virtual void onExit();
	
	virtual void ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent);
	virtual void ccTouchEnded (CCTouch *pTouch, CCEvent *pEvent);
	virtual bool ccTouchBegan(CCTouch* pTouch ,CCEvent* pEvent);
};

#endif  // __HELLOWORLD_SCENE_H__