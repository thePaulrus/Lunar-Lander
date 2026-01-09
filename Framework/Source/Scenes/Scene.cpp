#include "Scene.h"
#include "GameCore.h"
#include "Objects/GameObject.h"
#include "EventSystem/ContactListener.h"




namespace fw {


	fw::Scene::Scene(GameCore* game)
	{
		m_game = game;

	
	}
	Scene::~Scene()
	{
		for (GameObject* pObj : m_pObjects) {
			delete pObj;
		}
		delete m_pCamera;
		delete m_pWorld;
	}
	void Scene::Update(float DeltaTime)
	{
		for (GameObject* pObj : m_pObjects) {
			pObj->Update(DeltaTime);
		}
	}
	void Scene::Draw()
	{
		for (GameObject* pObj : m_pObjects) {
			pObj->Draw();
		}
	}
	Camera* Scene::GetCamera() {
		return m_pCamera;
	}
	GameCore* Scene::GetGameCore()
	{
		return m_game;
	}
	b2World* Scene::GetWorld()
	{
		return m_pWorld;
	}
	void Scene::DebugDraw(GameObject* object)
	{
	}
	void Scene::CreateWorld()
	{
		// physics handling
		b2Vec2 gravity = b2Vec2(0, -10);
		m_pWorld = new b2World(gravity);

		//make a contectlistener and send it into that method
		m_pContactListener = new ContactListener();
		m_pWorld->SetContactListener(m_pContactListener);

	}
	void Scene::PhysicsUpdate(float DeltaTime)
	{
		float timeStep = DeltaTime;
		int velocityIterations = 8;
		int positionIterations = 3;

		m_pWorld->Step(timeStep, velocityIterations, positionIterations);

		for (GameObject* pObj : m_pObjects) {
			pObj->PhysicsUpdate();
		}

		
	}
}
