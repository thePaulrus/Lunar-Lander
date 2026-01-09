#include "ContactListener.h"
#include "Objects/GameObject.h"

namespace fw {
	ContactListener::ContactListener()
	{

	}

	ContactListener::~ContactListener()
	{

	}

	void ContactListener::BeginContact(b2Contact* contact)
	{
		
		GameObject* pObjA = contact->GetFixtureA()->GetBody()->GetUserData().Object;
		
		GameObject* pObjB = contact->GetFixtureB()->GetBody()->GetUserData().Object;
		
		//if one of them is a Lander1, and the other is NOT LandingPad1, explode the lander
		//if one of the objects is a lander, and the lander is going too fast or at a bad angle explode it
		if (pObjA->GetName() == "Lander1") {
			if (pObjB->GetName() != "LandingPad1") {
				pObjA->Explode();
			}
			else if(pObjA->GetBody()->GetLinearVelocity().y < -3.0f){
				pObjA->Explode();
			}
			else if (radsToDegrees(pObjA->GetBody()->GetAngle()) > 10.0f && radsToDegrees(pObjA->GetBody()->GetAngle()) < 350.0f) {
				pObjA->Explode();
			}
			
		}
		else if (pObjB->GetName() == "Lander1") {
			if (pObjA->GetName() != "LandingPad1") {
				pObjB->Explode();
			}
			else if (pObjB->GetBody()->GetLinearVelocity().y < -3.0f) {
				pObjB->Explode();
			}
			else if (radsToDegrees(pObjB->GetBody()->GetAngle()) > 10.0f && radsToDegrees(pObjB->GetBody()->GetAngle()) < 350.0f) {
				pObjB->Explode();
			}



		}
		
		pObjA->SetCanJump(true);
		pObjB->SetCanJump(true);
	}
	void ContactListener::EndContact(b2Contact* contact)
	{
		GameObject* pObjA = contact->GetFixtureA()->GetBody()->GetUserData().Object;
		GameObject* pObjB = contact->GetFixtureB()->GetBody()->GetUserData().Object;
	}
}


