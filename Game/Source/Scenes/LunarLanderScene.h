#pragma once
#include "CoreHeaders.h"
#include "DataTypes.h"
#include "Scenes/Scene.h"



class GameObject;
class Game;
class Lander;

class LunarLanderScene : public fw::Scene
{
public:
	LunarLanderScene(Game* game);
	virtual ~LunarLanderScene();

	virtual void Update(float DeltaTime) override;
	virtual void Draw() override;

	void DebugDraw(fw::GameObject* object) override;

protected:
	Lander* m_pLander;

	Game* m_game;

};

