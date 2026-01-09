#pragma once

#include "CoreHeaders.h"
#include "DataTypes.h"
#include "Scenes/Scene.h"

//networking
#include <winsock.h>



class GameObject;
class Game;
class Camera;
class Player;
class Lander;




class MidtermScene : public fw::Scene {
public:
	MidtermScene(Game* game);
	virtual ~MidtermScene();

	virtual void Update(float DeltaTime) override;
	virtual void Draw() override;

protected:
	void InitNetwork();
	void SendToNetwork();
	void ReciveFromNetwork();

	struct packet {
		char command;
		unsigned char r;
		unsigned char g;
		unsigned char b;
		int playerNum;
		vec3 pos;
		float rot;
	};

protected:
	Lander* m_pLander;
	Player* m_pPlayer;

	class PhysDebugDraw* m_pDebugDraw;

	//networking
	int m_socketHandle = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
	sockaddr_in m_serverAddr;


};