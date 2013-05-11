
#include "AutomobileScene.h"
#include "ReturnMainMenuScene.h"


CCScene* AutomobileScene::scene()
{
	CCScene * scene = NULL;
	do 
	{
		// 'scene' is an autorelease object
		scene = ReturnMainMenuScene::create();
		CC_BREAK_IF(! scene);

		// 'layer' is an autorelease object
		AutomobileScene *layer = AutomobileScene::create();
		CC_BREAK_IF(! layer);

		// add layer as a child to scene
		scene->addChild(layer);
	} while (0);

	// return the scene
	return scene;
}



bool AutomobileScene::init()
{
	bool bRet = false;
	do 
	{
		// Initiate CCLayer
		CC_BREAK_IF(! CCLayer::init());

		// Initiate Physics
		physics = PhysicsWorld::create();
		if(NULL == physics) return false;

		createMap();
		schedule(schedule_selector(AutomobileScene::updateWorld), physics->getUpdateTime());

		setTouchEnabled(true);

		bRet = true;
	} while (0);

	return bRet;
}

void AutomobileScene::createMap()
{
	physics->createBrick(400,300,50,50,"brick");
	physics->createBrick(400,300,25,25,"brick");
	physics->createBrick(400,300,25,50,"brick");

	Automobile* automobile = physics->createAutomobile(300,100);
	automobile->forward();
}

void AutomobileScene::updateWorld(float deltaTime)
{
	physics->updateWorld();
	draw();
}

void AutomobileScene::onEnter()
{
	CCLayer::onEnter();
	CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this,0,true);
}

bool AutomobileScene::ccTouchBegan (CCTouch *pTouch, CCEvent *pEvent)
{
	//physics->updateWorld();
	physics->touchBegin(pTouch,pEvent);
	return true;
}

void AutomobileScene::ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent)
{
	physics->touchMoved(pTouch,pEvent);
}
void AutomobileScene::ccTouchEnded (CCTouch *pTouch, CCEvent *pEvent)
{
	physics->touchEnded(pTouch,pEvent);
}

void AutomobileScene::draw()
{
	CCLayer::draw();
	ccGLEnableVertexAttribs( kCCVertexAttribFlag_Position );
	kmGLPushMatrix();
	physics->drawDebugData();
	kmGLPopMatrix();
	CHECK_GL_ERROR_DEBUG();
}