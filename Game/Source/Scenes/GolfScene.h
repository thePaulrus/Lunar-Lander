#pragma once
#include "CoreHeaders.h"
#include "DataTypes.h"
#include "Scenes/Scene.h"



class GameObject;
class Game;
class Camera;
class Player;
class Lander;

class GolfScene : public fw::Scene {
public:
	GolfScene(Game* game);
	virtual ~GolfScene();

	virtual void Update(float DeltaTime) override;
	virtual void Draw() override;

	void DebugDraw(fw::GameObject* object) override;

protected:
	Player* m_pPlayer;
	Lander* m_pLander;
	class PhysDebugDraw* m_pDebugDraw;
	
};