#ifndef __ANGRY_BIRD_SCENE__
#define __ANGRY_BIRD_SCENE__

#include "cocos2d.h"
#include "Box2D/Box2D.h"
#include "SimpleAudioEngine.h"

#include "BirdSprite.h"
#include "SlingSprite.h"

using namespace  cocos2d;

class AngryBirdScene : public cocos2d::CCLayer
{
public:
	AngryBirdScene():
		meterPerPixel(0.1),
		gravity(0,-9.8) ,
		sleep(true),
		updateTime(1.0 / 30),
		stepTime(1.0 / 30),
		velocityIterations(10),
		positionIterations(10),
		birdClicked(false),
		slingClicked(false),
		isCreateBird(false)
	{
	}
	// Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
	virtual bool init();  

	// there's no 'id' in cpp, so we recommand to return the exactly class pointer
	static cocos2d::CCScene* scene();

	// a selector callback
	void menuCloseCallback(CCObject* pSender);

	// implement the "static node()" method manually
	CREATE_FUNC(AngryBirdScene);


	BirdSprite* bird;
	SlingSprite* sling;

	bool birdClicked;
	bool slingClicked;
	bool isCreateBird;
	b2Vec2 newBirdVelocity;
	CCPoint clickedInBird;
	CCPoint clickedInSling;

	
	// Box2d
private:
	float meterPerPixel;
	b2World* world;
	b2Vec2 gravity;
	bool sleep;

	float updateTime;
	float stepTime;
	int velocityIterations;
	int positionIterations;

	b2Body* bodys[3];

	void initBox2D();
	void updateWorld(float deltaTime);
	void draw();

	// Utilities
	b2Body* createCircle(int x, int y, float radius, char* name);
	b2Body* createStaticBrick(int x, int y, int width, int height,char* name);
	b2Body* createBrick(int x, int y, int width, int height,char* name);
	b2Body* createIdol(int x, int y,char* name);

	// Map
	void createMap();

public:
	virtual void onEnter();
	virtual void onExit();

	virtual bool ccTouchBegan(CCTouch* pTouch ,CCEvent* pEvent);
	virtual void ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent);
	virtual void ccTouchEnded (CCTouch *pTouch, CCEvent *pEvent);
	virtual void ccTouchCancelled (CCTouch *pTouch, CCEvent *pEvent);

};

#endif  // __ANGRY_BIRD_CENE__