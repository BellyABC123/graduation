
#include "OneSidedPlatformScene.h"
#include "ReturnMainMenuScene.h"


CCScene* OneSidedPlatformScene::scene()
{
	CCScene * scene = NULL;
	do 
	{
		// 'scene' is an autorelease object
		scene = ReturnMainMenuScene::create();
		CC_BREAK_IF(! scene);

		// 'layer' is an autorelease object
		OneSidedPlatformScene *layer = OneSidedPlatformScene::create();
		CC_BREAK_IF(! layer);

		// add layer as a child to scene
		scene->addChild(layer);
	} while (0);

	// return the scene
	return scene;
}



bool OneSidedPlatformScene::init()
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
		schedule(schedule_selector(OneSidedPlatformScene::updateWorld), physics->getUpdateTime());

		setTouchEnabled(true);

		bRet = true;
	} while (0);

	return bRet;
}

void OneSidedPlatformScene::createMap()
{
	physics->createCircle(400,300,25,"circle");
	physics->createOneWayPlatform(200,400,200,10,"OneSidedPlatform_2");
	physics->createOneWayPlatform(400,200,200,10,"OneSidedPlatform_1");
	physics->createStaticBrick(600,400,200,10,"Platform");
}

void OneSidedPlatformScene::updateWorld(float deltaTime)
{
	physics->updateWorld();
	draw();
}

void OneSidedPlatformScene::onEnter()
{
	CCLayer::onEnter();
	CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this,0,true);
}

bool OneSidedPlatformScene::ccTouchBegan (CCTouch *pTouch, CCEvent *pEvent)
{
	//physics->updateWorld();
	physics->touchBegin(pTouch,pEvent);
	return true;
}

void OneSidedPlatformScene::ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent)
{
	physics->touchMoved(pTouch,pEvent);
}
void OneSidedPlatformScene::ccTouchEnded (CCTouch *pTouch, CCEvent *pEvent)
{
	physics->touchEnded(pTouch,pEvent);
}

void OneSidedPlatformScene::draw()
{
	CCLayer::draw();
	ccGLEnableVertexAttribs( kCCVertexAttribFlag_Position );
	kmGLPushMatrix();
	physics->drawDebugData();
	kmGLPopMatrix();
	CHECK_GL_ERROR_DEBUG();
}