#include "AngryBirdScene.h"
#include "GLES-Render.h"
#include "BodyUserData.h"

using namespace cocos2d;

CCScene* AngryBirdScene::scene()
{
	CCScene * scene = NULL;
	do 
	{
		// 'scene' is an autorelease object
		scene = CCScene::create();
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

		//
		initBox2D();

		bRet = true;
	} while (0);

	return bRet;
}

void AngryBirdScene::menuCloseCallback(CCObject* pSender)
{
	// "close" menu item clicked
	CCDirector::sharedDirector()->end();
}



void AngryBirdScene::initBox2D()
{
	world = new b2World(gravity);
	world->SetAllowSleeping(false);
	createStaticBrick(400,-1,800,6,"platform");

	// Map
	createMap();

	schedule(schedule_selector(AngryBirdScene::updateWorld), updateTime);

	// Set Debug Draw
	GLESDebugDraw* draw = new GLESDebugDraw(1.0 / meterPerPixel);
	world->SetDebugDraw(draw);
	draw->SetFlags(b2Draw::e_shapeBit);  
}

void AngryBirdScene::updateWorld(float deltaTime)
{
	world->Step(stepTime,velocityIterations,positionIterations);
	world->ClearForces();
	draw();
}

void AngryBirdScene::draw()
{
	CCLayer::draw();
	ccGLEnableVertexAttribs( kCCVertexAttribFlag_Position );
	kmGLPushMatrix();
	world->DrawDebugData();
	kmGLPopMatrix();
	CHECK_GL_ERROR_DEBUG();
}

b2Body* AngryBirdScene::createCircle(int x, int y, float radius, char* name)
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

b2Body* AngryBirdScene::createStaticBrick(int x, int y, int width, int height,char* name)
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

b2Body* AngryBirdScene::createBrick(int x, int y, int width, int height,char* name)
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

b2Body* AngryBirdScene::createIdol(int x, int y,char* name)
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

bool AngryBirdScene::ccTouchBegan(CCTouch* pTouch ,CCEvent* pEvent)
{
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

void 	AngryBirdScene::ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent)
{
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
	// Bird Release

	float maxSpeedAllowed =  (1 / stepTime * 2);

	if(true == birdClicked)
	{
		birdClicked = false;

		newBirdVelocity = b2Vec2(
			(sling->getPosition().x - bird->getPosition().x) / (sling->getRadius()) * maxSpeedAllowed,
			(sling->getPosition().y - bird->getPosition().y) / (sling->getRadius()) * maxSpeedAllowed
			);

		b2Body* physicsBird = createCircle(bird->getPosition().x,bird->getPosition().y,bird->getRadius(),"bird");
		physicsBird->SetLinearVelocity(newBirdVelocity);

		bird->setPosition(sling->getPosition());
	}

	slingClicked = false;
}

void 	AngryBirdScene::ccTouchCancelled (CCTouch *pTouch, CCEvent *pEvent)
{
}

void AngryBirdScene::createMap()
{
	// Floor 1
	createStaticBrick(475,10,150,20,"castle");
	createStaticBrick(625,10,150,20,"castle");
	// Floor 2
	createBrick(405,30,10,20,"wood");
	createBrick(480,95,10,150,"wood");
	createBrick(550,25,70,10,"wood");
	// Middel Line  x = 550;
	createBrick(620,95,10,150,"wood");
	createBrick(695,30,10,20,"wood");

	// Floor 3
	createBrick(520,70,10,80,"glass");
	createBrick(580,70,10,80,"glass");

	// Floor 4
	createBrick(550,115,70,10,"wood");

	// Floor 5
	createBrick(550,175,150,10,"wood");

	// Floor 6
	createBrick(500,255,10,150,"wood");
	createBrick(550,185,80,10,"wood");
	createBrick(600,255,10,150,"wood");

	// Floor 7
	createBrick(550,335,110,10,"wood");
	// Floor 8
	createBrick(550,350,20,20,"wood");
	// Floor 9
	createBrick(550,370,10,20,"wood");

	// Pig
	createCircle(550,210,20,"pig");
}






