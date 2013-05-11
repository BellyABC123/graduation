

#ifndef __RETURN_MAIN_MENU_SCENE__
#define __RETURN_MAIN_MENU_SCENE__

#include "cocos2d.h"

USING_NS_CC;

class ReturnMainMenuScene:public CCScene
{
public:
	static CCScene* create();
	void menuCallback(CCObject* pSender);
};

#endif // !__RETURN_MAIN_MENU_SCENE__
