
#include "ReturnMainMenuScene.h"

CCScene* ReturnMainMenuScene::create()
{
	CCScene* scene = CCScene::create();

	if(NULL != scene)
	{
		CCLabelTTF* label = CCLabelTTF::create("Main Menu", "Arial", 24);
		CCMenuItemLabel* menuItem = CCMenuItemLabel::create(label, scene, menu_selector(ReturnMainMenuScene::menuCallback));
		CCMenu* menu = CCMenu::createWithItem(menuItem);
		scene->addChild(menu);

		menu->setPosition(700,550);
	}

	return scene;
}

void ReturnMainMenuScene::menuCallback(CCObject* pSender)
{
	CCDirector::sharedDirector()->popScene();
}