#include "HelloWorldScene.h"
#include "GLES-Render.h"
#include "BodyUserData.h"

using namespace cocos2d;

CCScene* HelloWorld::scene()
{
    CCScene * scene = NULL;
    do 
    {
        // 'scene' is an autorelease object
        scene = CCScene::create();
        CC_BREAK_IF(! scene);

        // 'layer' is an autorelease object
        HelloWorld *layer = HelloWorld::create();
        CC_BREAK_IF(! layer);

        // add layer as a child to scene
        scene->addChild(layer);
    } while (0);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    bool bRet = false;
    do 
    {
        //////////////////////////////////////////////////////////////////////////
        // super init first
        //////////////////////////////////////////////////////////////////////////

        CC_BREAK_IF(! CCLayer::init());

        //////////////////////////////////////////////////////////////////////////
        // add your codes below...
        //////////////////////////////////////////////////////////////////////////

        bRet = true;
    } while (0);

	initBox2D();

	//createBrick(100,100,10,20);
	createBrick(275,15,30,28,"brick1");
	createBrick(365,15,30,28,"brick2");
	createBrick(320,46,120,28,"brick3");
	createBrick(320,72,60,28,"brick4");
	createBrick(305,108,90,28,"brick5");
	createBrick(320,154,120,48,"brick6");
	createIdol(340,225,"idol");

    return bRet;
}

void HelloWorld::menuCloseCallback(CCObject* pSender)
{
    // "close" menu item clicked
    CCDirector::sharedDirector()->end();
}

HelloWorld::HelloWorld():gravity(0,-19.18) ,
										sleep(true),
										stepTime(1.0 / 30),
										velocityIterations(10),
										positionIterations(10),
										worldScale(30)
{
}

void HelloWorld::initBox2D()
{
	world = new b2World(gravity);
	schedule(schedule_selector(HelloWorld::updateWorld), 1.0 / 60);

	// Create Body
	createStaticBrick(400,-1,800,6,"platform");
	createCircle(400,300,10,"circle");

	// Set Debug Draw
	GLESDebugDraw* draw = new GLESDebugDraw();
	world->SetDebugDraw(draw);
	draw->SetFlags(b2Draw::e_shapeBit);  
}

void HelloWorld::updateWorld(float deltaTime)
{
	//cout<<"update world"<<endl;
	world->Step(stepTime,velocityIterations,positionIterations);
	world->ClearForces();
	draw();
}

void HelloWorld::draw()
{
	CCLayer::draw();
	ccGLEnableVertexAttribs( kCCVertexAttribFlag_Position );
	kmGLPushMatrix();
	world->DrawDebugData();
	kmGLPopMatrix();
	CHECK_GL_ERROR_DEBUG();
}

b2Body* HelloWorld::createCircle(int x, int y, float radius, char* name)
{	
	b2BodyDef bodyDefinition;
	b2CircleShape circleShape;
	b2FixtureDef fixtureDefinition;
	fixtureDefinition.shape = &circleShape;

	// Body
	bodyDefinition.type = b2BodyType::b2_dynamicBody;
	bodyDefinition.position.Set(x,y);
	b2Body* body = world->CreateBody(&bodyDefinition);

	body->SetUserData(new BodyUserData(name));

	// Fixture
	fixtureDefinition.restitution = 0.4;
	fixtureDefinition.friction = 0.5;
	// Shape
	circleShape.m_radius = 10;

	body->CreateFixture(&fixtureDefinition);
	return body;
}

b2Body* HelloWorld::createStaticBrick(int x, int y, int width, int height,char* name)
{
	b2BodyDef bodyDef;
	b2PolygonShape polygonShape;
	b2FixtureDef fixtureDef;
	fixtureDef.shape = &polygonShape;

	fixtureDef.density = 1;
	fixtureDef.restitution = 0.4;
	fixtureDef.friction = 0.5;

	bodyDef.position.Set(x,y);
	b2Body* body = world->CreateBody(&bodyDef);

	body->SetUserData(new BodyUserData(name));

	polygonShape.SetAsBox(width/2,height/2);
	body->CreateFixture(&fixtureDef);
	return body;
}

b2Body* HelloWorld::createBrick(int x, int y, int width, int height,char* name)
{
	b2BodyDef bodyDef;
	b2PolygonShape polygonShape;
	b2FixtureDef fixtureDef;
	fixtureDef.shape = &polygonShape;

	fixtureDef.density = 1;
	fixtureDef.restitution = 0.4;
	fixtureDef.friction = 0.5;

	bodyDef.position.Set(x,y);
	bodyDef.type = b2BodyType::b2_dynamicBody;
	b2Body* body = world->CreateBody(&bodyDef);

	body->SetUserData(new BodyUserData(name));

	polygonShape.SetAsBox(width/2,height/2);
	body->CreateFixture(&fixtureDef);
	return body;
}

b2Body* HelloWorld::createIdol(int x, int y,char* name)
{
	int width = 5;
	int height = 20;
	b2Vec2 center1(0,-height);
	float angle = 3.14 / 4;

	b2BodyDef bodyDef;
	b2PolygonShape polygonShape;
	b2FixtureDef fixtureDef;

	bodyDef.position.Set(x,y);
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
	vector[0].Set(0,10);
	vector[1].Set(15,25);
	vector[2].Set(0,40);
	vector[3].Set(-15,25);
	polygonShape.Set(vector,4);
	body->CreateFixture(&fixtureDef);

	return body;
}


void HelloWorld::onEnter()
{
	CCLayer::onEnter();
	CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this,0,true);
}

void HelloWorld::onExit()
{
	CCLayer::onExit();
	CCDirector::sharedDirector()->getTouchDispatcher()->removeDelegate(this);
}

void 	HelloWorld::ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent)
{
}

void 	HelloWorld::ccTouchEnded (CCTouch *pTouch, CCEvent *pEvent)
{
}

void 	HelloWorld::ccTouchCancelled (CCTouch *pTouch, CCEvent *pEvent)
{
}

class ClickCallback :public b2QueryCallback
{
public:
 bool 	ReportFixture (b2Fixture *fixture)
	{
		b2Body* body							= fixture->GetBody();
		BodyUserData* bodyUserData	= (BodyUserData*)body->GetUserData();
		b2World* world						= body->GetWorld();

		world->DestroyBody(body);

		cout<<"Click On Body : ";
		cout<<bodyUserData->getName()<<endl;
		return false;
	}
};

bool HelloWorld::ccTouchBegan(CCTouch* pTouch ,CCEvent* pEvent)
{
	CCPoint point = pTouch->getLocation();
	cout<<"x:"<<point.x<<"\t"<<"y£º"<<point.y<<endl;

	b2AABB aabb;
	aabb.lowerBound = b2Vec2(point.x,point.y);
	aabb.upperBound = b2Vec2(point.x,point.y);

	ClickCallback clickCallBack;

	world->QueryAABB(&clickCallBack,aabb);
	return true;
}






