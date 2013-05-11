
#include "MainMenuScene.h"
#include "TotemScene.h"
#include "AngryBirdScene.h"
#include "AutomobileScene.h"
#include "CutTheRopeScene.h"
#include "PulleyScene.h"
#include "GearScene.h"
#include "OneSidedPlatformScene.h"
#include "BuoyancyScene.h"

using namespace cocos2d;

#define SCENE_TOTEM						0
#define SCENE_ANGRY_BIRD				1
#define SCENE_AUTOMOBILE				2
#define SCENE_CUT_THE_ROPE				3
#define SCENE_PULLEY					4
#define SCENE_GEAR						5
#define SCENE_ONE_SIDED_PLATFORM		6
#define SCENE_BUOYANCY					7

CCScene* MainMenuScene::scene()
{
	CCScene * scene = NULL;
	do 
	{
		// 'scene' is an autorelease object
		scene = CCScene::create();
		CC_BREAK_IF(! scene);

		// 'layer' is an autorelease object
		MainMenuScene *layer = MainMenuScene::create();
		CC_BREAK_IF(! layer);

		// add layer as a child to scene
		scene->addChild(layer);
	} while (0);

	// return the scene
	return scene;
}

// on "init" you need to initialize your instance
bool MainMenuScene::init()
{
	bool bRet = false;
	do 
	{
		CC_BREAK_IF(! CCLayer::init());
		bRet = true;
	} while (0);

	return bRet;
}

MainMenuScene::MainMenuScene()
{
	int menuItemNumber = 8;
	char** sceneNames = new char*[menuItemNumber];
	sceneNames[SCENE_TOTEM]					= "Totem Scene";
	sceneNames[SCENE_ANGRY_BIRD]			= "Angry Bird Scene";
	sceneNames[SCENE_AUTOMOBILE]			= "Automobile Scene";
	sceneNames[SCENE_CUT_THE_ROPE]			= "Cut The Rope Scene";
	sceneNames[SCENE_GEAR]					= "Gear Scene";
	sceneNames[SCENE_ONE_SIDED_PLATFORM]	= "One Sided Platform Scene";
	sceneNames[SCENE_PULLEY]				= "Pulley Scene";
	sceneNames[SCENE_BUOYANCY]				= "Buoyancy Scene";


	int menuItemSpace = 35;

	CCMenu* selectSceneMenu = CCMenu::create();

	CCMenuItemImage* closeMenuItem = CCMenuItemImage::create("CloseNormal.png","CloseSelected.png" , this, menu_selector(MainMenuScene::closeCallback) );
	selectSceneMenu->addChild(closeMenuItem);

	for(int i=0;i<menuItemNumber;i++)
	{
		CCLabelTTF* label = CCLabelTTF::create(sceneNames[i], "Arial", 24);
		CCMenuItemLabel* pMenuItem = CCMenuItemLabel::create(label, this, menu_selector(MainMenuScene::menuCallback));
		selectSceneMenu->addChild(pMenuItem, i + 10000);
	}

	selectSceneMenu->alignItemsVertically();
	addChild(selectSceneMenu);

}

void MainMenuScene::closeCallback(CCObject * pSender)
{
	 CCDirector::sharedDirector()->end();
}


void MainMenuScene::menuCallback(CCObject * pSender)
{
	CCMenuItem* menuItem = (CCMenuItem *)(pSender);
	int index = menuItem->getZOrder() - 10000;

	cout<<"Selected Menu Item: "<<index<<endl;

	//create the test scene and run it
	CCScene* pScene = createScene(index);
	if (pScene)
	{
		CCDirector::sharedDirector()->pushScene(pScene);
	}
}

CCScene* MainMenuScene::createScene(int index)
{
	//#define SCENE_HELLO_WORLD				0
	//#define SCENE_ANGRY_BIRD				1
	//#define SCENE_AUTOMOBILE				2
	//#define SCENE_CUT_THE_ROPE			3
	//#define SCENE_PULLEY					4
	//#define SCENE_GEAR					5
	//#define SCENE_ONE_SIDED_PLATFORM		6
	//#define SCENE_BUOYANCY				7
	CCScene* result;
	switch(index)
	{
	case SCENE_TOTEM:
		result = TotemScene::scene();
		break;
	case SCENE_ANGRY_BIRD:
		result = AngryBirdScene::scene();
		break;
	case SCENE_AUTOMOBILE:
		result = AutomobileScene::scene();
		break;
	case SCENE_CUT_THE_ROPE:
		result = CutTheRopeScene::scene();
		break;
	case SCENE_PULLEY:
		result = PulleyScene::scene();
		break;
	case SCENE_GEAR:
		result = GearScene::scene();
		break;
	case SCENE_ONE_SIDED_PLATFORM:
		result = OneSidedPlatformScene::scene();
		break;
	case SCENE_BUOYANCY:
		result = BuoyancyScene::scene();
		break;
	default:
		result = NULL;
	}

	return result;
}

