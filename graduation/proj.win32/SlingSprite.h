
#ifndef __SLING_SPRITE__
#define __SLING_SPRITE__

#include "cocos2d.h"

using namespace cocos2d;

class SlingSprite : public CCSprite
{
public:
	SlingSprite(int x = 0, int y = 0):
		_radius(50)
	{
		init();
		setPosition(CCPoint(x,y));
	}
	~SlingSprite();

private:
	int _radius;

public:
	int getRadius(){ return _radius;}
	virtual void draw();
};


#endif // !__BIRD_SPRITE__
