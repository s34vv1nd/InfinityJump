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

	assert(padFixture != NULL);
	assert(characterFixture != NULL);
	
	b2Body* padBody = padFixture->GetBody();
	b2Body* characterBody = characterFixture->GetBody();

	assert(padBody != NULL);
	assert(characterBody != NULL);

	auto character = static_cast<Character*>(characterBody->GetUserData());
	auto pad = static_cast<Pad*>(padBody->GetUserData());
	
	b2Vec2 posCharacter = characterBody->GetPosition();
	b2Vec2 posPad = padBody->GetPosition();
	float characterHalfWidth = character->getHitbox().x / 200.f;
	float padHalfWidth = (pad)->getHitbox().x / 200.0f;

	if (//abs(characterBody->GetLinearVelocity().y - padBody->GetLinearVelocity().y) < EPSILON &&
		//posCharacter.x + characterHalfWidth >= posPad.x - padHalfWidth &&
		//posCharacter.x - characterHalfWidth <= posPad.x + padHalfWidth &&
		posCharacter.y > posPad.y) {
		character->setCurrentPad(pad);
	}
	else {
		character->setCurrentPad(NULL);
		/*if (posCharacter.x + characterHalfWidth < posPad.x - padHalfWidth ||
			posCharacter.x - characterHalfWidth > posPad.x + padHalfWidth) {
			contact->SetEnabled(false);
		}
		else if (posCharacter.y > posPad.y) {
			esLogMessage("Character velocity: %6f , Pad velocity: %6f\n", characterBody->GetLinearVelocity().y, padBody->GetLinearVelocity().y);
		}*/
	}
}
