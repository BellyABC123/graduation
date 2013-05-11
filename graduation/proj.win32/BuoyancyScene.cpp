
#include "BuoyancyScene.h"
#include "ReturnMainMenuScene.h"


CCScene* BuoyancyScene::scene()
{
	CCScene * scene = NULL;
	do 
	{
		// 'scene' is an autorelease object
		scene = ReturnMainMenuScene::create();
		CC_BREAK_IF(! scene);

		// 'layer' is an autorelease object
		BuoyancyScene *layer = BuoyancyScene::create();
		CC_BREAK_IF(! layer);

		// add layer as a child to scene
		scene->addChild(layer);
	} while (0);

	// return the scene
	return scene;
}



bool BuoyancyScene::init()
{
	bool bRet = false;
	do 
	{
		// Initiate CCLayer
		CC_BREAK_IF(! CCLayer::init());

		// Initiate Physics
		physics = Physics::create();
		if(NULL == physics) return false;

		createMap();
		schedule(schedule_selector(BuoyancyScene::updateWorld), physics->getUpdateTime());

		setTouchEnabled(true);

		bRet = true;
	} while (0);

	return bRet;
}

void BuoyancyScene::createMap()
{
	//physics->createCircle(400,300,25,"circle");

	physics->setDensity(1);
	physics->createBrick(400,200,50,50,"brick1");
	physics->setDensity(2);
	physics->createBrick(450,200,50,50,"brick2");
	physics->setDensity(3);
	physics->createBrick(500,200,50,50,"brick3");

	physics->createWaterPool(200,100,200,200,"water");
}

void BuoyancyScene::updateWorld(float deltaTime)
{
	physics->updateWorld();
	draw();
}

void BuoyancyScene::onEnter()
{
	CCLayer::onEnter();
	CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this,0,true);
}

bool BuoyancyScene::ccTouchBegan (CCTouch *pTouch, CCEvent *pEvent)
{
	//physics->updateWorld();
	physics->touchBegin(pTouch,pEvent);
	return true;
}

void BuoyancyScene::ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent)
{
	physics->touchMoved(pTouch,pEvent);
}
void BuoyancyScene::ccTouchEnded (CCTouch *pTouch, CCEvent *pEvent)
{
	physics->touchEnded(pTouch,pEvent);
}

void BuoyancyScene::draw()
{
	CCLayer::draw();
	ccGLEnableVertexAttribs( kCCVertexAttribFlag_Position );
	kmGLPushMatrix();
	physics->drawDebugData();
	kmGLPopMatrix();
	CHECK_GL_ERROR_DEBUG();
}