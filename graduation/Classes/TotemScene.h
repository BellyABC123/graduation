#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include "Box2D/Box2D.h"
#include "SimpleAudioEngine.h"

using namespace  cocos2d;

class TotemScene : public CCLayer
{
public:
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();  

    // there's no 'id' in cpp, so we recommand to return the exactly class pointer
    static cocos2d::CCScene* scene();
    
    // a selector callback
    void menuCloseCallback(CCObject* pSender);

    // implement the "static node()" method manually
    CREATE_FUNC(TotemScene);

	// Box2d
public:
	TotemScene();
private:
	b2World* world;
	b2Vec2 gravity;
	bool sleep;

	float stepTime;
	int velocityIterations;
	int positionIterations;
	float worldScale;

	// Body
	void initBox2D();
	void updateWorld(float deltaTime);
	void draw();

	// Utilities
	b2Body* createCircle(int x, int y, float radius, char* name);
	b2Body* createStaticBrick(int x, int y, int width, int height,char* name);
	b2Body* createBrick(int x, int y, int width, int height,char* name);
	b2Body* createIdol(int x, int y,char* name);

public:
	virtual void onEnter();
	virtual void onExit();
	
	virtual void ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent);
	virtual void ccTouchEnded (CCTouch *pTouch, CCEvent *pEvent);
	virtual void ccTouchCancelled (CCTouch *pTouch, CCEvent *pEvent);
	virtual bool ccTouchBegan(CCTouch* pTouch ,CCEvent* pEvent);
};

#endif  // __HELLOWORLD_SCENE_H__