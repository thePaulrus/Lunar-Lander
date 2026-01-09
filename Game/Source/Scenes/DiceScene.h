#pragma once
#include "CoreHeaders.h"
#include "DataTypes.h"
#include "Scenes/Scene.h"



	class GameObject;
	class Game;
	class Camera;
	class Player;

	class DiceScene : public fw::Scene {
	public:
		DiceScene(Game* game);
		virtual ~DiceScene();

		virtual void Update(float DeltaTime) override;
		virtual void Draw() override;

	protected:
		Player* m_pPlayer;
	};
