
#include "SlingSprite.h"
#include "cocos2d.h"



SlingSprite::~SlingSprite()
{
}

void SlingSprite::draw()
{
	CCSprite::draw();
	ccDrawColor4F(1,1,1,1);
	ccDrawCircle(CCPoint(0,0),_radius, 0,_radius*2.0 , false);
	ccDrawCircle(CCPoint(0,0),1,0,_radius*2.0,false);
}