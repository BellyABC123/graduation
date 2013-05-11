
#include "PulleyScene.h"
#include "ReturnMainMenuScene.h"


CCScene* PulleyScene::scene()
{
	CCScene * scene = NULL;
	do 
	{
		// 'scene' is an autorelease object
		scene = ReturnMainMenuScene::create();
		CC_BREAK_IF(! scene);

		// 'layer' is an autorelease object
		PulleyScene *layer = PulleyScene::create();
		CC_BREAK_IF(! layer);

		// add layer as a child to scene
		scene->addChild(layer);
	} while (0);

	// return the scene
	return scene;
}



bool PulleyScene::init()
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
		schedule(schedule_selector(PulleyScene::updateWorld), physics->getUpdateTime());

		setTouchEnabled(true);

		bRet = true;
	} while (0);

	return bRet;
}

void PulleyScene::createMap()
{
	//physics->createBrick(400,300,50,50,"brick");

	b2Body* body1 = physics->createCircle(300,200,25,"body1");
	b2Body* body2 = physics->createBrick(400,200,50,50,"body2");

	b2PulleyJointDef pulleyJointDef;
	pulleyJointDef.bodyA = body1;
	pulleyJointDef.bodyB = body2;
	pulleyJointDef.localAnchorA = b2Vec2(0,0);
	pulleyJointDef.localAnchorB = b2Vec2(0,0);
	pulleyJointDef.lengthA = 200 * physics->getMeterPerPixel();
	pulleyJointDef.lengthB = 200 * physics->getMeterPerPixel();
	pulleyJointDef.groundAnchorA = b2Vec2(300 * physics->getMeterPerPixel(),400 * physics->getMeterPerPixel());
	pulleyJointDef.groundAnchorB = b2Vec2(400 * physics->getMeterPerPixel(),400 * physics->getMeterPerPixel());
	pulleyJointDef.ratio = 1;

	physics->getWorld()->CreateJoint(&pulleyJointDef);
}

void PulleyScene::updateWorld(float deltaTime)
{
	physics->updateWorld();
	draw();
}

void PulleyScene::onEnter()
{
	CCLayer::onEnter();
	CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this,0,true);
}

bool PulleyScene::ccTouchBegan (CCTouch *pTouch, CCEvent *pEvent)
{
	//physics->updateWorld();
	physics->touchBegin(pTouch,pEvent);
	return true;
}

void PulleyScene::ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent)
{
	physics->touchMoved(pTouch,pEvent);
}
void PulleyScene::ccTouchEnded (CCTouch *pTouch, CCEvent *pEvent)
{
	physics->touchEnded(pTouch,pEvent);
}

void PulleyScene::draw()
{
	CCLayer::draw();
	ccGLEnableVertexAttribs( kCCVertexAttribFlag_Position );
	kmGLPushMatrix();
	physics->drawDebugData();
	kmGLPopMatrix();
	CHECK_GL_ERROR_DEBUG();
}