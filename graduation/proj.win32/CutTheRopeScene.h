
#ifndef __CUT_THE_ROPE__
#define __CUT_THE_ROPE__

#include "cocos2d.h"
#include "Physics.h"

using namespace cocos2d;

class CutTheRopeScene: public CCLayer
{
public:
	virtual bool init();
	CREATE_FUNC(CutTheRopeScene);
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
};

#endif // !1
