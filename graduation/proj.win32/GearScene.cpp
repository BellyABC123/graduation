
#include "GearScene.h"


CCScene* GearScene::scene()
{
	CCScene * scene = NULL;
	do 
	{
		// 'scene' is an autorelease object
		scene = CCScene::create();
		CC_BREAK_IF(! scene);

		// 'layer' is an autorelease object
		GearScene *layer = GearScene::create();
		CC_BREAK_IF(! layer);

		// add layer as a child to scene
		scene->addChild(layer);
	} while (0);

	// return the scene
	return scene;
}



bool GearScene::init()
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
		schedule(schedule_selector(GearScene::updateWorld), physics->getUpdateTime());

		setTouchEnabled(true);

		bRet = true;
	} while (0);

	return bRet;
}

void GearScene::createMap()
{
	// 通过相互接触
	// 实现的齿轮效果
	b2Body* circle1 = physics->createCircle(100,200,50,"circle1");
	b2Body* circle2 = physics->createCircle(200,200,50,"circle2");
	b2Body* bar		= physics->createBrick(400,200,300,10,"bar");

	b2RevoluteJointDef revoluteJointDef;

	revoluteJointDef.bodyA = physics->getBackgroundBody();
	revoluteJointDef.bodyB = circle1;
	revoluteJointDef.localAnchorA = circle1->GetWorldCenter();
	revoluteJointDef.localAnchorB = b2Vec2(0,0);
	revoluteJointDef.enableMotor = true;
	revoluteJointDef.maxMotorTorque = 200;
	revoluteJointDef.motorSpeed = 3.14;
	physics->getWorld()->CreateJoint(&revoluteJointDef);


	revoluteJointDef.bodyB = circle2;
	revoluteJointDef.localAnchorA = circle2->GetWorldCenter();
	revoluteJointDef.enableMotor = false;
	physics->getWorld()->CreateJoint(&revoluteJointDef);

	// 通过GearJoint
	// 实现齿轮效果
	b2Body* circle3 = physics->createCircle(400,200,50,"circle3");
	b2Body* circle4 = physics->createCircle(500,200,50,"circle4");

	revoluteJointDef.bodyA = physics->getBackgroundBody();
	revoluteJointDef.bodyB = circle3;
	revoluteJointDef.collideConnected = false;
	revoluteJointDef.localAnchorA = circle3->GetWorldCenter();
	revoluteJointDef.localAnchorB = b2Vec2(0,0);
	b2Joint* revolute3 = physics->getWorld()->CreateJoint(&revoluteJointDef);

	revoluteJointDef.bodyB = circle4;
	revoluteJointDef.localAnchorA = circle4->GetWorldCenter();
	b2Joint* revolute4 = physics->getWorld()->CreateJoint(&revoluteJointDef);

	b2GearJointDef gearJointDef;
	gearJointDef.bodyA = circle3;
	gearJointDef.bodyB = circle4;
	gearJointDef.joint1 = revolute3;
	gearJointDef.joint2 = revolute4;
	gearJointDef.ratio	= 1;
	physics->getWorld()->CreateJoint(&gearJointDef);

	// Gear Joint 链接
	// Revolute Joint 和 Prisimatic Joint
	b2Body* circle5 = physics->createCircle(300,400,50,"circle5");
	b2Body* bar6	= physics->createBrick(355,450,10,200,"bar6");
	b2Body* circle7	= physics->createCircle(410,500,50,"circle7");

	// Revolute
	revoluteJointDef.bodyA = physics->getBackgroundBody();
	revoluteJointDef.bodyB = circle5;
	revoluteJointDef.localAnchorA = circle5->GetWorldCenter();
	revoluteJointDef.localAnchorB = b2Vec2(0,0);
	b2Joint* joint5 = physics->getWorld()->CreateJoint(&revoluteJointDef);
	// Prismatic
	b2PrismaticJointDef prismaticJointDef;
	prismaticJointDef.bodyA = physics->getBackgroundBody();
	prismaticJointDef.bodyB = bar6;
	prismaticJointDef.collideConnected = false;
	prismaticJointDef.localAnchorA = b2Vec2(355 * physics->getMeterPerPixel(),0);
	prismaticJointDef.localAnchorB = b2Vec2(0,0);
	prismaticJointDef.localAxisA = b2Vec2(0,1);
	b2Joint* joint6 = physics->getWorld()->CreateJoint(&prismaticJointDef);
	// Revolute
	revoluteJointDef.bodyB = circle7;
	revoluteJointDef.localAnchorA = circle7->GetWorldCenter();
	b2Joint* joint7 = physics->getWorld()->CreateJoint(&revoluteJointDef);

	// Gear Joint A
	gearJointDef.bodyA = circle5;
	gearJointDef.bodyB = bar6;
	gearJointDef.joint1 = joint5;
	gearJointDef.joint2 = joint6;
	gearJointDef.ratio	= -1;
	physics->getWorld()->CreateJoint(&gearJointDef);
	// Gear Joint B
	gearJointDef.bodyA = bar6;
	gearJointDef.bodyB = circle7;
	gearJointDef.joint1 = joint6;
	gearJointDef.joint2 = joint7;
	gearJointDef.ratio = 1;
	physics->getWorld()->CreateJoint(&gearJointDef);
}

void GearScene::updateWorld(float deltaTime)
{
	physics->updateWorld();
	draw();
}

void GearScene::onEnter()
{
	CCLayer::onEnter();
	CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this,0,true);
}

bool GearScene::ccTouchBegan (CCTouch *pTouch, CCEvent *pEvent)
{
	//physics->updateWorld();
	physics->touchBegin(pTouch,pEvent);
	return true;
}

void GearScene::ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent)
{
	physics->touchMoved(pTouch,pEvent);
}
void GearScene::ccTouchEnded (CCTouch *pTouch, CCEvent *pEvent)
{
	physics->touchEnded(pTouch,pEvent);
}

void GearScene::draw()
{
	CCLayer::draw();
	ccGLEnableVertexAttribs( kCCVertexAttribFlag_Position );
	kmGLPushMatrix();
	physics->drawDebugData();
	kmGLPopMatrix();
	CHECK_GL_ERROR_DEBUG();
}