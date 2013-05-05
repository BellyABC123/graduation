
#ifndef __CUSTOM_CONTACT_LISTENER__
#define __CUSTOM_CONTACT_LISTENER__

#include "Box2D/Box2D.h"
#include <list>
#include <iostream>
#include <BodyUserData.h>

using namespace std;

class CustomContactListener:public b2ContactListener
{
private:
	list<b2Body*> oneSidedPlatforms;
	bool _isOneSidePlatfomEanble;
public:
	CustomContactListener():_isOneSidePlatfomEanble(false)
	{}
	void setOneSidedPlatformEanble(bool enable = true);
	void addOneSidedPlatform(b2Body* body);
	bool isContainOneSidedPlatform(b2Body* body);
	void PreSolve (b2Contact *contact, const b2Manifold *oldManifold);
};

#endif // !__CUSTOM_CONTACT_LISTENER__