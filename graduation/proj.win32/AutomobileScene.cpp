#include "AutomobileScene.h"
#include "GLES-Render.h"
#include "BodyUserData.h"

using namespace cocos2d;

CCScene* AutomobileScene::scene()
{
	CCScene * scene = NULL;
	do 
	{
		// 'scene' is an autorelease object
		scene = CCScene::create();
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

// on "init" you need to initialize your instance
bool AutomobileScene::init()
{
	bool bRet = false;
	do 
	{
		CC_BREAK_IF(! CCLayer::init());

		initBox2D();

		bRet = true;
	} while (0);

	return bRet;
}

void AutomobileScene::menuCloseCallback(CCObject* pSender)
{
	// "close" menu item clicked
	CCDirector::sharedDirector()->end();
}


void AutomobileScene::initBox2D()
{
	world = new b2World(gravity);

	b2BodyDef bodyDef;
	backgroundBody = world->CreateBody(&bodyDef);

	createStaticBrick(400,-1,800,6,"platform");

	//  Create The Distance Joint
	b2Body* body1 = createBrick(400,300,50,50,"brick1");
	b2Body* body2 = createBrick(600,300,50,50,"brick2");

	b2DistanceJointDef distanceJoint;
	distanceJoint.Initialize(body1,
										body2,
										body1->GetWorldCenter(),
										body2->GetWorldCenter()
										);

	world->CreateJoint(&distanceJoint);

	// Create The Revolute Joint
	b2Body* body3 = createStaticBrick(300,500,10,100,"brick3");
	b2Body* body4 = createBrick(400,400,100,10,"brick4");

	createString(body3, body4, 200);

	//b2RevoluteJointDef revoluteJointDef;
	//revoluteJointDef.Initialize(body3,
	//										body4,
	//										body3->GetWorldCenter()
	//										);

	//b2RevoluteJoint* revoluteJoint = (b2RevoluteJoint*)world->CreateJoint(&revoluteJointDef);
	//revoluteJoint->EnableMotor(true);
	//revoluteJoint->SetMaxMotorTorque(999);
	//revoluteJoint->SetMotorSpeed(12);

	// Create Prismatic Joint
	b2Body* body5 = createBrick(400,100,100,50,"brick5");
	b2Body* body6 = createBrick(600,200,100,50,"brick6");

	b2PrismaticJointDef prismaticJointDef;
	prismaticJointDef.Initialize(
												body5,
												body6,
												b2Vec2(body5->GetWorldCenter().x + 100 * meterPerPixel ,
															body5->GetWorldCenter().y),
												b2Vec2(0,1));
	prismaticJointDef.collideConnected = true;
	world->CreateJoint(&prismaticJointDef);





	schedule(schedule_selector(AutomobileScene::updateWorld), updateTime);

	// Set Debug Draw
	GLESDebugDraw* draw = new GLESDebugDraw(1.0 / meterPerPixel);
	world->SetDebugDraw(draw);
	draw->SetFlags(b2Draw::e_shapeBit | b2Draw::e_jointBit);
}

void AutomobileScene::updateWorld(float deltaTime)
{
	world->Step(stepTime,velocityIterations,positionIterations);
	world->ClearForces();
	draw();
}

void AutomobileScene::draw()
{
	CCLayer::draw();
	ccGLEnableVertexAttribs( kCCVertexAttribFlag_Position );
	kmGLPushMatrix();
	world->DrawDebugData();
	kmGLPopMatrix();
	CHECK_GL_ERROR_DEBUG();
}

b2Body* AutomobileScene::createCircle(int x, int y, float radius, char* name)
{	
	b2BodyDef bodyDefinition;
	b2CircleShape circleShape;
	b2FixtureDef fixtureDefinition;
	fixtureDefinition.shape = &circleShape;

	// Body
	bodyDefinition.type = b2BodyType::b2_dynamicBody;
	bodyDefinition.position.Set( x * meterPerPixel, y * meterPerPixel);
	b2Body* body = world->CreateBody(&bodyDefinition);

	body->SetUserData(new BodyUserData(name));

	// Fixture
	fixtureDefinition.density		= 2;
	fixtureDefinition.restitution	= 0.4;
	fixtureDefinition.friction		= 0.5;
	// Shape
	circleShape.m_radius = radius * meterPerPixel;

	body->CreateFixture(&fixtureDefinition);
	return body;
}

b2Body* AutomobileScene::createStaticBrick(int x, int y, int width, int height,char* name)
{
	b2BodyDef bodyDef;
	b2PolygonShape polygonShape;
	b2FixtureDef fixtureDef;
	fixtureDef.shape = &polygonShape;

	fixtureDef.density = 2;
	fixtureDef.restitution = 0.4;
	fixtureDef.friction = 0.5;

	bodyDef.position.Set(x * meterPerPixel, y * meterPerPixel);
	b2Body* body = world->CreateBody(&bodyDef);

	body->SetUserData(new BodyUserData(name));

	polygonShape.SetAsBox(width*meterPerPixel/ 2, height*meterPerPixel/2);
	body->CreateFixture(&fixtureDef);
	return body;
}

b2Body* AutomobileScene::createBrick(int x, int y, int width, int height,char* name)
{
	b2BodyDef bodyDef;
	b2PolygonShape polygonShape;
	b2FixtureDef fixtureDef;
	fixtureDef.shape = &polygonShape;

	fixtureDef.density = 1;
	fixtureDef.restitution = 0.4;
	fixtureDef.friction = 0.5;

	bodyDef.position.Set(x*meterPerPixel,y*meterPerPixel);
	bodyDef.type = b2BodyType::b2_dynamicBody;
	b2Body* body = world->CreateBody(&bodyDef);

	body->SetUserData(new BodyUserData(name));

	polygonShape.SetAsBox(width*meterPerPixel/2,height*meterPerPixel/2);
	body->CreateFixture(&fixtureDef);
	return body;
}

b2Body* AutomobileScene::createIdol(int x, int y,char* name)
{
	int width = 5 * meterPerPixel;
	int height = 20 * meterPerPixel;
	b2Vec2 center1(0,-height);
	float angle = 3.14 / 4;

	b2BodyDef bodyDef;
	b2PolygonShape polygonShape;
	b2FixtureDef fixtureDef;

	bodyDef.position.Set(x*meterPerPixel,y*meterPerPixel);
	bodyDef.type = b2BodyType::b2_dynamicBody;
	b2Body* body = world->CreateBody(&bodyDef);
	fixtureDef.shape = &polygonShape;

	body->SetUserData(new BodyUserData(name));

	fixtureDef.density = 1;
	fixtureDef.restitution = 0.4;
	fixtureDef.friction = 0.5;

	polygonShape.SetAsBox(width, height);

	body->CreateFixture(&fixtureDef);

	polygonShape.SetAsBox(width, height, center1, -angle);
	body->CreateFixture(&fixtureDef);

	polygonShape.SetAsBox(width, height, center1, angle);
	body->CreateFixture(&fixtureDef);

	b2Vec2 vector[4];
	vector[0].Set(0 * meterPerPixel,10 * meterPerPixel);
	vector[1].Set(15 * meterPerPixel,25 * meterPerPixel);
	vector[2].Set(0 * meterPerPixel,40 * meterPerPixel);
	vector[3].Set(-15 * meterPerPixel,25 * meterPerPixel);
	polygonShape.Set(vector,4);
	body->CreateFixture(&fixtureDef);

	return body;
}

void AutomobileScene::createString(b2Body* bodyA, b2Body* bodyB,float distance)
{
	b2RopeJointDef ropeJointDef;

	//ropeJointDef.bodyA = bodyA;
	ropeJointDef.bodyA = bodyA;
	ropeJointDef.bodyB = bodyB;
	ropeJointDef.localAnchorA.SetZero();
	ropeJointDef.localAnchorB.SetZero();
	ropeJointDef.maxLength = distance * meterPerPixel;

	world->CreateJoint(&ropeJointDef);
}


void AutomobileScene::onEnter()
{
	CCLayer::onEnter();
	CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this,0,true);
}

void AutomobileScene::onExit()
{
	CCLayer::onExit();
	CCDirector::sharedDirector()->getTouchDispatcher()->removeDelegate(this);
}



//class GetClickFixtureCallback :public b2QueryCallback
//{
//private:
//	AutomobileScene* automobileScene;
//	CCPoint	clickPoint;
//
//
//public:
//	GetClickFixtureCallback(AutomobileScene* automobilScene,CCPoint& clickPoint)
//	{
//		this->automobileScene = automobilScene;
//		this->clickPoint = clickPoint;
//	}
//
//	bool 	ReportFixture (b2Fixture *fixture)
//	{
//		b2Body* clickedBody							= fixture->GetBody();
//		BodyUserData* bodyUserData	= (BodyUserData*)clickedBody->GetUserData();
//		b2World* world = clickedBody->GetWorld();
//
//		if(clickedBody->GetType() == b2BodyType::b2_dynamicBody)
//		{
//			b2MouseJointDef mouseJointDef;
//			mouseJointDef.bodyA = automobileScene->getBackgroundBody();
//			mouseJointDef.bodyB = clickedBody;
//			mouseJointDef.target = b2Vec2(
//																clickPoint.x * automobileScene->getMeterPerPixel(),
//																clickPoint.y * automobileScene->getMeterPerPixel()
//																);
//			mouseJointDef.maxForce = 1000 * clickedBody->GetMass();
//
//			automobileScene->setMouseJoint((b2MouseJoint*)world->CreateJoint(&mouseJointDef));
//		}
//
//		return false;
//	}
//};

bool AutomobileScene::ccTouchBegan(CCTouch* pTouch ,CCEvent* pEvent)
{
	//CCPoint point = pTouch->getLocation();

	//b2AABB aabb;
	//aabb.lowerBound = b2Vec2(point.x * meterPerPixel ,point.y * meterPerPixel);
	//aabb.upperBound = b2Vec2(point.x * meterPerPixel,point.y * meterPerPixel);

	//GetClickFixtureCallback getClickFixtureCallback(this,point);
	//world->QueryAABB(&getClickFixtureCallback,aabb);
	
	return true;
}

void 	AutomobileScene::ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent)
{
	if(mouseJoint != 0)
	{
		mouseJoint->SetTarget(b2Vec2(
															pTouch->getLocation().x * meterPerPixel,
															pTouch->getLocation().y * meterPerPixel
															)
											);
	}

}

void 	AutomobileScene::ccTouchEnded (CCTouch *pTouch, CCEvent *pEvent)
{
	if(mouseJoint != 0)
	{
		world->DestroyJoint(mouseJoint);
		mouseJoint = 0;
	}
}







