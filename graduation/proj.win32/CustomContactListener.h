



#ifndef __CUSTOM_CONTACT_LISTENER__
#define __CUSTOM_CONTACT_LISTENER__

#include "Physics.h"
#include "Box2D/Box2D.h"
#include <list>
#include <set>
#include <vector>
#include <iostream>
#include <BodyUserData.h>

using namespace std;

class Physics;

class CustomContactListener:public b2ContactListener
{
private:
	Physics* physics;

	// OneSidedPlatform
	bool _isOneSidePlatfomEanble;
	list<b2Body*> oneSidedPlatforms;

	// Buoyancy
	typedef pair<b2Fixture*, b2Fixture*> fixturePair;
	bool _isBuoyancyEnable;
	set<fixturePair> fixturePairs;

public:
	CustomContactListener(Physics* physics)
	{
		this->physics = physics;
		_isOneSidePlatfomEanble = false;
		_isBuoyancyEnable		= false;
	}

	// Buoyancy
	void setBuoyancyEnable(bool enable = true);
	void applyBuoyancyEachStep();
private:
	bool	inside(b2Vec2 cp1, b2Vec2 cp2, b2Vec2 p);
	b2Vec2	intersection(b2Vec2 cp1, b2Vec2 cp2, b2Vec2 s, b2Vec2 e);
	bool	findIntersectionOfFixtures(b2Fixture* fA, b2Fixture* fB, vector<b2Vec2>& outputVertices);
	b2Vec2	ComputeCentroid(vector<b2Vec2> vs, float& area);


	// OneSidedPlatform
public:
	void setOneSidedPlatformEanble(bool enable = true);
	void addOneSidedPlatform(b2Body* body);
	bool isContainOneSidedPlatform(b2Body* body);

	void BeginContact (b2Contact *contact);
	void EndContact (b2Contact *contact);
	void PreSolve (b2Contact *contact, const b2Manifold *oldManifold);
};

#endif // !__CUSTOM_CONTACT_LISTENER__