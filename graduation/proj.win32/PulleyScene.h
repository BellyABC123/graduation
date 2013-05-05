
#ifndef __PULLEY_SCENE__
#define __PULLEY_SCENE__

#include "cocos2d.h"
#include "Physics.h"

using namespace cocos2d;

class PulleyScene: public CCLayer
{
public:
	virtual bool init();
	CREATE_FUNC(PulleyScene);
	static CCScene* scene();

	void onEnter();

public:
	virtual bool ccTouchBegan (CCTouch *pTouch, CCEvent *pEvent);
	virtual void ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent);
	virtual void ccTouchEnded (CCTouch *pTouch, CCEvent *pEvent);

private:
	Physics* physics;
	void draw();
	void updateWorld(float deltaTime);

private:
	void createMap();
};



#endif // !__PULLEY__
