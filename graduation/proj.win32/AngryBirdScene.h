#ifndef __ANGRY_BIRD_SCENE__
#define __ANGRY_BIRD_SCENE__

#include "cocos2d.h"
#include "Box2D/Box2D.h"
#include "SimpleAudioEngine.h"

#include "BirdSprite.h"
#include "SlingSprite.h"
#include "PhysicsWorld.h"

using namespace  cocos2d;

class AngryBirdScene : public CCLayer
{
public:
	AngryBirdScene():
		birdClicked(false),
		slingClicked(false),
		isCreateBird(false)
	{
	}
	virtual bool init();
	CREATE_FUNC(AngryBirdScene);
	static cocos2d::CCScene* scene();

private:
	BirdSprite* bird;
	SlingSprite* sling;

	bool birdClicked;
	bool slingClicked;
	bool isCreateBird;
	b2Vec2 newBirdVelocity;
	CCPoint clickedInBird;
	CCPoint clickedInSling;

	PhysicsWorld* physicsWorld;
	void draw();
	void updateWorld(float deltaTime);
	void createMap();

public:
	virtual void onEnter();
	virtual void onExit();

	virtual bool ccTouchBegan(CCTouch* pTouch ,CCEvent* pEvent);
	virtual void ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent);
	virtual void ccTouchEnded (CCTouch *pTouch, CCEvent *pEvent);
};

#endif  // __ANGRY_BIRD_CENE__