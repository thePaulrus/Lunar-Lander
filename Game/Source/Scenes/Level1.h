#pragma once
#include "CoreHeaders.h"
#include "DataTypes.h"
#include "Scenes/Scene.h"
#include "Scenes/LunarLanderScene.h"



class GameObject;
class Game;
class Lander;

class Level1 : public LunarLanderScene
{
public:
	Level1(Game* game);
	virtual ~Level1();

};

