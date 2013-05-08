
#include "CustomContactListener.h"


void CustomContactListener::setBuoyancyEnable(bool enable)
{
	_isBuoyancyEnable = enable;
}

void CustomContactListener::setOneSidedPlatformEanble(bool enable)
{
	_isOneSidePlatfomEanble = enable;
}

void CustomContactListener::addOneSidedPlatform(b2Body* body)
{
	if(!isContainOneSidedPlatform(body))
	{
		oneSidedPlatforms.push_back(body);

		BodyUserData* userData = (BodyUserData*)body->GetUserData();
		cout<<"Add OneSidedPlatform "<<userData->getName()<<endl;
	}
}

bool CustomContactListener::isContainOneSidedPlatform(b2Body* body)
{
	bool result = false;

	for(list<b2Body*>::iterator iterator = oneSidedPlatforms.begin();iterator != oneSidedPlatforms.end(); iterator++)
	{
		if(*iterator == body)
		{
			result = true;
			break;
		}
	}

	return result;
}


void CustomContactListener::BeginContact (b2Contact *contact)
{
	b2Fixture* fixtureA = contact->GetFixtureA();
	b2Fixture* fixtureB = contact->GetFixtureB();

	if(_isBuoyancyEnable)
	{
		if (fixtureA->IsSensor() && fixtureB->GetBody()->GetType() == b2_dynamicBody)
		{
			fixturePairs.insert( make_pair(fixtureA, fixtureB) );
		}
		else if (fixtureB->IsSensor() && fixtureA->GetBody()->GetType() == b2_dynamicBody)
		{
			fixturePairs.insert( make_pair(fixtureB, fixtureA) );
		}
	}
}

void CustomContactListener::EndContact (b2Contact *contact)
{
	b2Fixture* fixtureA = contact->GetFixtureA();
	b2Fixture* fixtureB = contact->GetFixtureB();

	if(_isBuoyancyEnable)
	{
		if ( fixtureA->IsSensor() && fixtureB->GetBody()->GetType() == b2_dynamicBody )
			fixturePairs.erase( make_pair(fixtureA, fixtureB) );
		else if ( fixtureB->IsSensor() && fixtureA->GetBody()->GetType() == b2_dynamicBody )
			fixturePairs.erase( make_pair(fixtureB, fixtureA) );
	}
}


void CustomContactListener::PreSolve (b2Contact *contact, const b2Manifold *oldManifold)
{
	b2ContactListener::PreSolve(contact,oldManifold);

	b2Fixture* fixtureA = contact->GetFixtureA();
	b2Fixture* fixtureB = contact->GetFixtureB();

	b2Body* bodyA = fixtureA->GetBody();
	b2Body* bodyB = fixtureB->GetBody();

	BodyUserData* userDataA = (BodyUserData*)bodyA->GetUserData();
	BodyUserData* userDataB = (BodyUserData*)bodyB->GetUserData();

	if(_isOneSidePlatfomEanble)
	{
		if(isContainOneSidedPlatform(bodyA))
		{
			cout<<"ContactListener PreSolve:"<<endl;
			cout<<"BodyA: "<<userDataA->getName()<<endl;
			cout<<"BodyB: "<<userDataB->getName()<<endl;
			cout<<"BodyA "<<userDataA->getName()<<"Is In OneSidedPlatform !"<<endl;
			if(bodyB->GetPosition().y < bodyA->GetPosition().y)
			{
				contact->SetEnabled(false);
				cout<<"Contact Disable !!"<<endl;
			}
		}

		if(isContainOneSidedPlatform(bodyB))
		{
			cout<<"ContactListener PreSolve:"<<endl;
			cout<<"BodyA: "<<userDataA->getName()<<endl;
			cout<<"BodyB: "<<userDataB->getName()<<endl;
			cout<<"BodyB "<<userDataB->getName()<<"Is In OneSidedPlatform !"<<endl;

			if(bodyA->GetPosition().y < bodyB->GetPosition().y)
			{
				contact->SetEnabled(false);
				cout<<"Contact Disable !!"<<endl;
			}
		}
	}
}

bool CustomContactListener::inside(b2Vec2 cp1, b2Vec2 cp2, b2Vec2 p)
{
	return (cp2.x-cp1.x)*(p.y-cp1.y) > (cp2.y-cp1.y)*(p.x-cp1.x);
}

b2Vec2 CustomContactListener::intersection(b2Vec2 cp1, b2Vec2 cp2, b2Vec2 s, b2Vec2 e)
{
	b2Vec2 dc( cp1.x - cp2.x, cp1.y - cp2.y );
	b2Vec2 dp( s.x - e.x, s.y - e.y );
	float n1 = cp1.x * cp2.y - cp1.y * cp2.x;
	float n2 = s.x * e.y - s.y * e.x;
	float n3 = 1.0 / (dc.x * dp.y - dc.y * dp.x);
	return b2Vec2( (n1*dp.x - n2*dc.x) * n3, (n1*dp.y - n2*dc.y) * n3);
}

//http://rosettacode.org/wiki/Sutherland-Hodgman_polygon_clipping#JavaScript
//Note that this only works when fB is a convex polygon, but we know all 
//fixtures in Box2D are convex, so that will not be a problem
bool CustomContactListener::findIntersectionOfFixtures(b2Fixture* fA, b2Fixture* fB, vector<b2Vec2>& outputVertices)
{
	//currently this only handles polygon vs polygon
	if ( fA->GetShape()->GetType() != b2Shape::e_polygon ||
		fB->GetShape()->GetType() != b2Shape::e_polygon )
		return false;

	b2PolygonShape* polyA = (b2PolygonShape*)fA->GetShape();
	b2PolygonShape* polyB = (b2PolygonShape*)fB->GetShape();

	//fill subject polygon from fixtureA polygon
	for (int i = 0; i < polyA->GetVertexCount(); i++)
		outputVertices.push_back( fA->GetBody()->GetWorldPoint( polyA->GetVertex(i) ) );

	//fill clip polygon from fixtureB polygon
	vector<b2Vec2> clipPolygon;
	for (int i = 0; i < polyB->GetVertexCount(); i++)
		clipPolygon.push_back( fB->GetBody()->GetWorldPoint( polyB->GetVertex(i) ) );

	b2Vec2 cp1 = clipPolygon[clipPolygon.size()-1];
	for (int j = 0; j < clipPolygon.size(); j++) {
		b2Vec2 cp2 = clipPolygon[j];
		if ( outputVertices.empty() )
			return false;
		vector<b2Vec2> inputList = outputVertices;
		outputVertices.clear();
		b2Vec2 s = inputList[inputList.size() - 1]; //last on the input list
		for (int i = 0; i < inputList.size(); i++) {
			b2Vec2 e = inputList[i];
			if (inside(cp1, cp2, e)) {
				if (!inside(cp1, cp2, s)) {
					outputVertices.push_back( intersection(cp1, cp2, s, e) );
				}
				outputVertices.push_back(e);
			}
			else if (inside(cp1, cp2, s)) {
				outputVertices.push_back( intersection(cp1, cp2, s, e) );
			}
			s = e;
		}
		cp1 = cp2;
	}

	return !outputVertices.empty();
}

//Taken from b2PolygonShape.cpp
b2Vec2 CustomContactListener::ComputeCentroid(vector<b2Vec2> vs, float& area)
{
	int count = (int)vs.size();
	b2Assert(count >= 3);

	b2Vec2 c;
	c.Set(0.0f, 0.0f);
	area = 0.0f;

	// pRef is the reference point for forming triangles.
	// Its location doesnt change the result (except for rounding error).
	b2Vec2 pRef(0.0f, 0.0f);

	const float32 inv3 = 1.0f / 3.0f;

	for (int32 i = 0; i < count; ++i)
	{
		// Triangle vertices.
		b2Vec2 p1 = pRef;
		b2Vec2 p2 = vs[i];
		b2Vec2 p3 = i + 1 < count ? vs[i+1] : vs[0];

		b2Vec2 e1 = p2 - p1;
		b2Vec2 e2 = p3 - p1;

		float32 D = b2Cross(e1, e2);

		float32 triangleArea = 0.5f * D;
		area += triangleArea;

		// Area weighted centroid
		c += triangleArea * inv3 * (p1 + p2 + p3);
	}

	// Centroid
	if (area > b2_epsilon)
		c *= 1.0f / area;
	else
		area = 0;
	return c;
}

void CustomContactListener::applyBuoyancyEachStep()
{
	if(!_isBuoyancyEnable) return;

	set<fixturePair>::iterator it = fixturePairs.begin();
	set<fixturePair>::iterator end = fixturePairs.end();
	while (it != end) {

		//fixtureA is the fluid
		b2Fixture* fixtureA = it->first;
		b2Fixture* fixtureB = it->second;

		float density = fixtureA->GetDensity();

		vector<b2Vec2> intersectionPoints;
		if ( findIntersectionOfFixtures(fixtureA, fixtureB, intersectionPoints) ) {

			//find centroid
			float area = 0;
			b2Vec2 centroid = ComputeCentroid( intersectionPoints, area);

			//apply buoyancy stuff here...
			b2Vec2 gravity = physics->getWorld()->GetGravity();
			//apply buoyancy force (fixtureA is the fluid)
			float displacedMass = fixtureA->GetDensity() * area;

			b2Vec2 buoyancyForce = displacedMass * - gravity;
			fixtureB->GetBody()->ApplyForce( buoyancyForce, centroid );

			//
			//find relative velocity between object and fluid
			b2Vec2 velDir = fixtureB->GetBody()->GetLinearVelocityFromWorldPoint( centroid ) -
				fixtureA->GetBody()->GetLinearVelocityFromWorldPoint( centroid );
			float vel = velDir.Normalize();
			//apply simple linear drag
			float dragMag = fixtureA->GetDensity() * vel * vel;
			b2Vec2 dragForce = dragMag * -velDir;
			fixtureB->GetBody()->ApplyForce( dragForce, centroid );

			//apply simple angular drag
			float angularDrag = area * -fixtureB->GetBody()->GetAngularVelocity();
			fixtureB->GetBody()->ApplyTorque( angularDrag );

			cout<<"apply buoyancy ..."<<endl;
			cout<<"density: "<<fixtureA->GetDensity()<<endl;
			cout<<"area: "<<area<<endl;
			cout<<"displaceMass: "<<displacedMass<<endl;
			cout<<"centroid: "<<centroid.x<<" "<<centroid.y<<endl;
			cout<<"buoyancyForce: "<<buoyancyForce.x<<" "<<buoyancyForce.y<<endl;
		}

		++it;
	}
}