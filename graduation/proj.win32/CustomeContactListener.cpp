
#include "CustomContactListener.h"

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