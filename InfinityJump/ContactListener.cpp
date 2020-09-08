#include "stdafx.h"
#include "ContactListener.h"


void ContactListener::PreSolve(b2Contact* contact, const b2Manifold* oldManifold)
{
	b2Fixture* fixtureA = contact->GetFixtureA();
	b2Fixture* fixtureB = contact->GetFixtureB();

	//check if one of the fixtures is the platform
	b2Fixture* padFixture = NULL;
	b2Fixture* characterFixture = NULL;
	if (fixtureA->GetBody()->GetType() == b2_kinematicBody && fixtureB->GetBody()->GetType() == b2_dynamicBody) {
		padFixture = fixtureA;
		characterFixture = fixtureB;
	}
	else if (fixtureB->GetBody()->GetType() == b2_kinematicBody && fixtureA->GetBody()->GetType() == b2_dynamicBody) {
		padFixture = fixtureB;
		characterFixture = fixtureA;
	}

	if (!padFixture) {
		b2Fixture* groundFixture = NULL;
		if (fixtureA->GetBody()->GetType() == b2_staticBody && fixtureB->GetBody()->GetType() == b2_dynamicBody) {
			groundFixture = fixtureA;
			characterFixture = fixtureB;
		}
		else if (fixtureB->GetBody()->GetType() == b2_staticBody && fixtureA->GetBody()->GetType() == b2_dynamicBody) {
			groundFixture = fixtureB;
			characterFixture = fixtureA;
		}
		if (!groundFixture) return;

		b2Body* characterBody = characterFixture->GetBody();
		auto character = static_cast<Character*>(characterBody->GetUserData());
		character->setIsOnTheGround(true);
		return;
	}

	b2Body* padBody = padFixture->GetBody();
	b2Body* characterBody = characterFixture->GetBody();
	auto character = static_cast<Character*>(characterBody->GetUserData());
	auto pad = static_cast<Pad*>(padBody->GetUserData());
	
	b2Vec2 posCharacter = characterBody->GetPosition();
	b2Vec2 posPad = padBody->GetPosition();
	float width = (pad)->getWidth() / 200.0f;
	float height = (pad)->getHeight() / 200.f;

	if (characterBody->GetLinearVelocity().y > EPSILON || 
		posCharacter.x < posPad.x - width || 
		posCharacter.x > posPad.x + width || 
		posCharacter.y < posPad.y - height) {
		//contact->SetEnabled(false);
		character->setCurrentPad(NULL);
	}
	else {
		character->setCurrentPad(pad);
	}
}
