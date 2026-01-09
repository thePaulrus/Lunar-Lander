#pragma once
#include "CoreHeaders.h"
#include "DataTypes.h"
#include "Scenes/Scene.h"
#include "Scenes/LunarLanderScene.h"



class GameObject;
class Game;
class Lander;

class TestLevel: public LunarLanderScene
{
public:
	TestLevel(Game* game);
	virtual ~TestLevel();

};

