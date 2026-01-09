#pragma once

#include "CoreHeaders.h"
#include "DataTypes.h"
#include "Scenes/Scene.h"



class GameObject;
class Game;
class Camera;
class Player;

class PinBallScene : public fw::Scene {
public:
	PinBallScene(Game* game);
	virtual ~PinBallScene();

	virtual void Update(float DeltaTime) override;
	virtual void Draw() override;

protected:
	Player* m_pPlayer;

	class PhysDebugDraw* m_pDebugDraw;

};