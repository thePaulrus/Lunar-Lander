#pragma once

//box2d stuff
#define B2_USER_SETTINGS
#include "box2d/include/box2D/box2d.h"

namespace fw {
	class ContactListener : public b2ContactListener {
	public:
		ContactListener();
		virtual ~ContactListener();
		void BeginContact(b2Contact* contact) override;
		void EndContact(b2Contact* contact) override;

	protected:


	};
}

