
#ifndef __BIRD_SPRITE__
#define __BIRD_SPRITE__

#include "cocos2d.h"

using namespace cocos2d;

class BirdSprite : public CCSprite
{
public:
	BirdSprite(int x = 0, int y = 0):
		_radius(10)
	{
		init();
		setPosition(CCPoint(x,y));
	}
	~BirdSprite();

private:
	int _radius;

public:
	virtual void draw();
	int getRadius(){ return _radius;}
};


#endif // !__BIRD_SPRITE__
