#ifndef __MENU_SCENE__
#define __MENU_SCENE__

#include "cocos2d.h"
#include "Box2D/Box2D.h"
#include "SimpleAudioEngine.h"

using namespace  cocos2d;

class MainMenuScene:public cocos2d::CCLayer
{
public:
	virtual bool init();  
	static CCScene* scene();
	CREATE_FUNC(MainMenuScene);

public:
	MainMenuScene();

	void menuCallback(CCObject * pSender);
	void closeCallback(CCObject * pSender);

private:
	CCScene* createScene(int index);
};

#endif  //