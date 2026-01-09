#pragma once
#include "CoreHeaders.h"
#include "DataTypes.h"



//box2d stuff
#define B2_USER_SETTINGS
#include "box2d/include/box2D/box2d.h"

class PhysDebugDraw;
namespace fw {
	class GameObject;
	class Camera;
	class GameCore;
	class ContactListener;

	class Scene {
	public:
		Scene(GameCore* game);
		virtual ~Scene();

		virtual void Update(float DeltaTime);
		virtual void Draw();

		Camera* GetCamera();
		GameCore* GetGameCore();
		b2World* GetWorld();


		
		virtual void DebugDraw(GameObject* object);


	protected:
		GameCore* m_game;
		std::vector<GameObject*> m_pObjects;
		Camera* m_pCamera;

		b2World* m_pWorld = nullptr;
		ContactListener* m_pContactListener = nullptr;

		virtual void CreateWorld();
		virtual void PhysicsUpdate(float DeltaTime);
	};
}