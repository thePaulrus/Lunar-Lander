#include "LunarLanderScene.h"
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

LunarLanderScene::LunarLanderScene(Game* game) :
    Scene(game)
{
    CreateWorld();

  
    // Create some GameObjects.
    m_pCamera = new fw::Camera(this, vec3(0, 0, 0));
    m_pCamera->SetRotation(20);

#define getMesh game->GetResources()->Get<fw::Mesh>
#define getMaterial game->GetResources()->Get<fw::Material>

    m_pLander = new Lander(this, "Lander1", vec3(5, 8, 0), getMesh("Sprite"), getMaterial("LanderBoth"), game->GetEventManager(), game->GetController());
    m_pLander->SetScale(vec3(2, 2, 1));
    m_pLander->CreateSquareBody(true, 0.0, false);
    m_pObjects.push_back(m_pLander);

    fw::GameObject* pObject;

    pObject = new fw::GameObject(this, "LandingPad1", vec3(-5, -10, 0), getMesh("Square"), getMaterial("Blue"));
    pObject->SetScale(vec3(5, 2, 1));
    pObject->CreateSquareBody(false, 0.0, false);
    m_pObjects.push_back(pObject);

    pObject = new fw::GameObject(this, "Death1", vec3(2, -5, 0), getMesh("Square"), getMaterial("Red"));
    pObject->SetScale(vec3(1, 1, 1));
    pObject->CreateSquareBody(false, 0.0, false);
    m_pObjects.push_back(pObject);
    pObject = new fw::GameObject(this, "Death2", vec3(-2, 3, 0), getMesh("Square"), getMaterial("Red"));
    pObject->SetScale(vec3(1, 1, 1));
    pObject->CreateSquareBody(false, 0.0, false);
    m_pObjects.push_back(pObject);
    pObject = new fw::GameObject(this, "Death3", vec3(8, 0, 0), getMesh("Square"), getMaterial("Red"));
    pObject->SetScale(vec3(1, 1, 1));
    pObject->CreateSquareBody(false, 0.0, false);
    m_pObjects.push_back(pObject);
    pObject = new fw::GameObject(this, "Death4", vec3(0, 7, 0), getMesh("Square"), getMaterial("Red"));
    pObject->SetScale(vec3(1, 1, 1));
    pObject->CreateSquareBody(false, 0.0, false);
    m_pObjects.push_back(pObject);
    pObject = new fw::GameObject(this, "Death5", vec3(-8, -7, 0), getMesh("Square"), getMaterial("Red"));
    pObject->SetScale(vec3(1, 1, 1));
    pObject->CreateSquareBody(false, 0.0, false);
    m_pObjects.push_back(pObject);
    pObject = new fw::GameObject(this, "Death6", vec3(-2, -2, 0), getMesh("Square"), getMaterial("Red"));
    pObject->SetScale(vec3(1, 1, 1));
    pObject->CreateSquareBody(false, 0.0, false);
    m_pObjects.push_back(pObject);
    pObject = new fw::GameObject(this, "Death7", vec3(-8, 0, 0), getMesh("Square"), getMaterial("Red"));
    pObject->SetScale(vec3(1, 1, 1));
    pObject->CreateSquareBody(false, 0.0, false);
    m_pObjects.push_back(pObject);
    pObject = new fw::GameObject(this, "Death8", vec3(-10, 7, 0), getMesh("Square"), getMaterial("Red"));
    pObject->SetScale(vec3(1, 1, 1));
    pObject->CreateSquareBody(false, 0.0, false);
    m_pObjects.push_back(pObject);
}

LunarLanderScene::~LunarLanderScene()
{
   
}

void LunarLanderScene::Update(float DeltaTime)
{

    PhysicsUpdate(DeltaTime);

    m_pCamera->LanderZoom(m_pLander, m_pObjects[1]);

    for (int i = 0; i < m_pObjects.size(); i++) {
        m_pObjects[i]->Update(DeltaTime);
    }

}

void LunarLanderScene::Draw()
{
    // Program the view and proj uniforms from the camera.
    m_pCamera->Enable(EditorViews::EditorView_Game);


    // Draw all objects.
    for (fw::GameObject* pObject : m_pObjects)
    {
        pObject->Draw();

    }
}

void LunarLanderScene::DebugDraw(fw::GameObject* object)
{
}
