#include "TotemScene.h"
#include "GLES-Render.h"
#include "BodyUserData.h"

#include "ReturnMainMenuScene.h"

using namespace cocos2d;

CCScene* TotemScene::scene()
{
    CCScene * scene = NULL;
    do 
    {
        // 'scene' is an autorelease object
        scene = ReturnMainMenuScene::create();
        CC_BREAK_IF(! scene);

        // 'layer' is an autorelease object
        TotemScene *layer = TotemScene::create();
        CC_BREAK_IF(! layer);

        // add layer as a child to scene
        scene->addChild(layer);
    } while (0);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool TotemScene::init()
{
    bool bRet = false;
    do 
    {
        CC_BREAK_IF(! CCLayer::init());

		// Initiate Physics
		physicsWorld = PhysicsWorld::create();
		if(NULL == physicsWorld) return false;

		createMap();
		schedule(schedule_selector(TotemScene::updateWorld), physicsWorld->getUpdateTime());

		setTouchEnabled(true);

        bRet = true;
    } while (0);

    return bRet;
}

void TotemScene::createMap()
{
	//createBrick(100,100,10,20);
	physicsWorld->createBrick(275,15,30,28,"brick1");
	physicsWorld->createBrick(365,15,30,28,"brick2");
	physicsWorld->createBrick(320,46,120,28,"brick3");
	physicsWorld->createBrick(320,72,60,28,"brick4");
	physicsWorld->createBrick(305,108,90,28,"brick5");
	physicsWorld->createBrick(320,154,120,48,"brick6");
	physicsWorld->createIdol(340,225,"idol");
}

void TotemScene::updateWorld(float deltaTime)
{
	physicsWorld->updateWorld();
	draw();
}

void TotemScene::draw()
{
	CCLayer::draw();
	ccGLEnableVertexAttribs( kCCVertexAttribFlag_Position );
	kmGLPushMatrix();
	physicsWorld->drawDebugData();
	kmGLPopMatrix();
	CHECK_GL_ERROR_DEBUG();
}

void TotemScene::onEnter()
{
	CCLayer::onEnter();
	CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this,0,true);
}

void TotemScene::onExit()
{
	CCLayer::onExit();
	CCDirector::sharedDirector()->getTouchDispatcher()->removeDelegate(this);
}

class ClickCallback :public b2QueryCallback
{
public:
	bool 	ReportFixture (b2Fixture *fixture)
	{
		b2Body* body				= fixture->GetBody();
		BodyUserData* bodyUserData	= (BodyUserData*)body->GetUserData();
		b2World* world				= body->GetWorld();

		world->DestroyBody(body);

		cout<<"Click On Body : ";
		cout<<bodyUserData->getName()<<endl;
		return false;
	}
};

bool TotemScene::ccTouchBegan(CCTouch* pTouch ,CCEvent* pEvent)
{
	float meterPerPixel = physicsWorld->getMeterPerPixel();

	CCPoint point = pTouch->getLocation();
	cout<<"x:"<<point.x<<"\t"<<"y£º"<<point.y<<endl;

	b2AABB aabb;
	aabb.lowerBound = b2Vec2(point.x*meterPerPixel ,point.y*meterPerPixel);
	aabb.upperBound = b2Vec2(point.x*meterPerPixel,point.y*meterPerPixel);

	ClickCallback clickCallBack;
	physicsWorld->getWorld()->QueryAABB(&clickCallBack,aabb);

	return true;
}

void TotemScene::ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent)
{
}

void TotemScene::ccTouchEnded (CCTouch *pTouch, CCEvent *pEvent)
{
}



