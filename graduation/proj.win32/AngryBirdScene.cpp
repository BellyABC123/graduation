#include "AngryBirdScene.h"
#include "GLES-Render.h"
#include "BodyUserData.h"

#include "ReturnMainMenuScene.h"

using namespace cocos2d;

CCScene* AngryBirdScene::scene()
{
	CCScene * scene = NULL;
	do 
	{
		// 'scene' is an autorelease object
		scene = ReturnMainMenuScene::create();
		CC_BREAK_IF(! scene);

		// 'layer' is an autorelease object
		AngryBirdScene *layer = AngryBirdScene::create();
		CC_BREAK_IF(! layer);

		// add layer as a child to scene
		scene->addChild(layer);
	} while (0);

	// return the scene
	return scene;
}

// on "init" you need to initialize your instance
bool AngryBirdScene::init()
{
	bool bRet = false;
	do 
	{
		CC_BREAK_IF(! CCLayer::init());

		// Sling
		sling = new SlingSprite(200,300);
		addChild(sling);

		// Bird
		CCPoint slingPosition = sling->getPosition();
		bird = new BirdSprite(slingPosition.x, slingPosition.y);
		addChild(bird);

		// Initiate Physics
		physicsWorld = PhysicsWorld::create();
		if(NULL == physicsWorld) return false;

		createMap();
		schedule(schedule_selector(AngryBirdScene::updateWorld), physicsWorld->getUpdateTime());

		setTouchEnabled(true);

		bRet = true;
	} while (0);

	return bRet;
}

void AngryBirdScene::updateWorld(float deltaTime)
{
	physicsWorld->updateWorld();
	draw();
}

void AngryBirdScene::draw()
{
	CCLayer::draw();
	ccGLEnableVertexAttribs( kCCVertexAttribFlag_Position );
	kmGLPushMatrix();
	physicsWorld->drawDebugData();
	kmGLPopMatrix();
	CHECK_GL_ERROR_DEBUG();
}

void AngryBirdScene::onEnter()
{
	CCLayer::onEnter();
	CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this,0,true);
}

void AngryBirdScene::onExit()
{
	CCLayer::onExit();
	CCDirector::sharedDirector()->getTouchDispatcher()->removeDelegate(this);
}

bool AngryBirdScene::ccTouchBegan(CCTouch* pTouch ,CCEvent* pEvent)
{
	physicsWorld->touchBegin(pTouch,pEvent);


	// Check Whether Clicked The Bird
	float distance = ccpDistance(pTouch->getLocation(),bird->getPosition());

	clickedInBird		= ccpSub(pTouch->getLocation(),bird->getPosition());
	clickedInSling	= ccpSub(pTouch->getLocation(),sling->getPosition());

	if(distance < bird->getRadius())
	{
		birdClicked = true;
		return true;
	}

	if(distance < sling->getRadius())
	{
		slingClicked = true;
		return true;
	}

	return true;
}

void AngryBirdScene::ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent)
{
	physicsWorld->touchMoved(pTouch,pEvent);


	float distance = ccpDistance(pTouch->getLocation(),sling->getPosition());

	if(birdClicked)
	{
		if(distance < sling->getRadius())
		{
			bird->setPosition(pTouch->getLocation());
		}
		else
		{
			float ratio = sling->getRadius() / distance;
			CCPoint birdPosition((pTouch->getLocation().x - sling->getPosition().x) * ratio + sling->getPosition().x,
								 (pTouch->getLocation().y - sling->getPosition().y) * ratio + sling->getPosition().y);
			bird->setPosition(birdPosition);
		}
	}
	else if(slingClicked)
	{
		sling->setPosition(ccpSub(pTouch->getLocation(),clickedInSling));
		bird->setPosition(sling->getPosition());
	}
}

void 	AngryBirdScene::ccTouchEnded (CCTouch *pTouch, CCEvent *pEvent)
{
	physicsWorld->touchEnded(pTouch,pEvent);


	// Bird Release
	float maxSpeedAllowed =  (1 / physicsWorld->getStepTime() * 2);

	if(true == birdClicked)
	{
		birdClicked = false;

		newBirdVelocity = b2Vec2(
			(sling->getPosition().x - bird->getPosition().x) / (sling->getRadius()) * maxSpeedAllowed,
			(sling->getPosition().y - bird->getPosition().y) / (sling->getRadius()) * maxSpeedAllowed
			);

		b2Body* physicsBird = physicsWorld->createCircle(bird->getPosition().x,bird->getPosition().y,bird->getRadius(),"bird");
		physicsBird->SetLinearVelocity(newBirdVelocity);

		bird->setPosition(sling->getPosition());
	}

	slingClicked = false;
}

void AngryBirdScene::createMap()
{
	// Floor 1
	physicsWorld->createStaticBrick(475,10,150,20,"castle");
	physicsWorld->createStaticBrick(625,10,150,20,"castle");
	// Floor 2
	physicsWorld->createBrick(405,30,10,20,"wood");
	physicsWorld->createBrick(480,95,10,150,"wood");
	physicsWorld->createBrick(550,25,70,10,"wood");
	// Middel Line  x = 550;
	physicsWorld->createBrick(620,95,10,150,"wood");
	physicsWorld->createBrick(695,30,10,20,"wood");

	// Floor 3
	physicsWorld->createBrick(520,70,10,80,"glass");
	physicsWorld->createBrick(580,70,10,80,"glass");

	// Floor 4
	physicsWorld->createBrick(550,115,70,10,"wood");

	// Floor 5
	physicsWorld->createBrick(550,175,150,10,"wood");

	// Floor 6
	physicsWorld->createBrick(500,255,10,150,"wood");
	physicsWorld->createBrick(550,185,80,10,"wood");
	physicsWorld->createBrick(600,255,10,150,"wood");

	// Floor 7
	physicsWorld->createBrick(550,335,110,10,"wood");
	// Floor 8
	physicsWorld->createBrick(550,350,20,20,"wood");
	// Floor 9
	physicsWorld->createBrick(550,370,10,20,"wood");

	// Pig
	physicsWorld->createCircle(550,210,20,"pig");
}