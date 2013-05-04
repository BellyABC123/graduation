
#include "CutTheRope.h"


CCScene* CutTheRopeScene::scene()
{
	CCScene * scene = NULL;
	do 
	{
		// 'scene' is an autorelease object
		scene = CCScene::create();
		CC_BREAK_IF(! scene);

		// 'layer' is an autorelease object
		CutTheRopeScene *layer = CutTheRopeScene::create();
		CC_BREAK_IF(! layer);

		// add layer as a child to scene
		scene->addChild(layer);
	} while (0);

	// return the scene
	return scene;
}

bool CutTheRopeScene::init()
{
	bool bRet = false;
	do 
	{
		// Initiate CCLayer
		CC_BREAK_IF(! CCLayer::init());

		// Initiate Physics
		physics = Physics::create();
		if(NULL == physics) return false;

		b2Body* brick1 = physics->createBrick(100,100,100,100,"brick1");
		b2Body* brick2 = physics->createBrick(300,100,100,100,"brick2");
		physics->createRope(brick1, brick2, 200 );

		schedule(schedule_selector(CutTheRopeScene::updateWorld), physics->getUpdateTime());

		setTouchEnabled(true);

		bRet = true;
	} while (0);

	return bRet;
}

void CutTheRopeScene::updateWorld(float deltaTime)
{
	physics->updateWorld();
	draw();
}

void CutTheRopeScene::onEnter()
{
	CCLayer::onEnter();
	CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this,0,true);
}

 bool 	CutTheRopeScene::ccTouchBegan (CCTouch *pTouch, CCEvent *pEvent)
{
	//physics->updateWorld();
	physics->touchBegin(pTouch,pEvent);
	return true;
}

void CutTheRopeScene::ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent)
{
	physics->touchMoved(pTouch,pEvent);
}
 void CutTheRopeScene::ccTouchEnded (CCTouch *pTouch, CCEvent *pEvent)
 {
	 physics->touchEnded(pTouch,pEvent);
 }

void CutTheRopeScene::draw()
{
	CCLayer::draw();
	ccGLEnableVertexAttribs( kCCVertexAttribFlag_Position );
	kmGLPushMatrix();
	physics->drawDebugData();
	kmGLPopMatrix();
	CHECK_GL_ERROR_DEBUG();
}