#pragma once
#include "CoreHeaders.h"
#include "DataTypes.h"
#include "Scenes/Scene.h"



	class GameObject;
	class Game;
	class Camera;
	class Player;

	class LightScene : public fw::Scene {
	public:
		LightScene(Game* game);
		virtual ~LightScene();

		virtual void Update(float DeltaTime) override;
		virtual void Draw() override;

	protected:
		Player* m_pPlayer;
	};
