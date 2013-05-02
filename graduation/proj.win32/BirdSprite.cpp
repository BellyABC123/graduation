
#include "BirdSprite.h"
#include "cocos2d.h"



BirdSprite::~BirdSprite()
{
}

void BirdSprite::draw()
{
	CCSprite::draw();
	ccDrawColor4F(1,0,0,1);
	ccDrawCircle(CCPoint(0,0),_radius, 0,_radius*2.0 , false);
}