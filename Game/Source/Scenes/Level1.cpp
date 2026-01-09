#include "LunarLanderScene.h"
#include "Level1.h"
#include "GameCore.h"
#include "Objects/GameObject.h"
#include "Objects/Camera.h"
#include "Objects/Lander.h"
#include "Meshes/Shapes.h"
#include "Meshes/VertexFormats.h"
#include "DataTypes.h"
#include "Game.h"
#include "Resources/Mesh.h"
#include "Resources/Material.h"
#include "Objects/PhysDebugDraw.h"

//box2d stuff
#define B2_USER_SETTINGS
#include "box2d/include/box2D/box2d.h"

Level1::Level1(Game* game) :
    LunarLanderScene(game)
{
    CreateWorld();

  
    // Create some GameObjects.
    m_pCamera = new fw::Camera(this, vec3(0, 0, 0));
    m_pCamera->SetRotation(20);

#define getMesh game->GetResources()->Get<fw::Mesh>
#define getMaterial game->GetResources()->Get<fw::Material>

    m_pLander = new Lander(this, "Lander1", vec3(0, 8, 0), getMesh("Sprite"), getMaterial("LanderBoth"), game->GetEventManager(), game->GetController());
    m_pLander->SetScale(vec3(2, 2, 1));
    m_pLander->CreateSquareBody(true, 0.0, false);
    m_pObjects.push_back(m_pLander);

    fw::GameObject* pObject;

    pObject = new fw::GameObject(this, "LandingPad1", vec3(0, -10, 0), getMesh("Square"), getMaterial("Blue"));
    pObject->SetScale(vec3(5, 2, 1));
    pObject->CreateSquareBody(false, 0.0, false);
    m_pObjects.push_back(pObject);

}

Level1::~Level1()
{
   
}
