#include "DiceScene.h"
#include "GameCore.h"
#include "Objects/GameObject.h"
#include "Objects/Camera.h"
#include "Objects/Player.h"
#include "Meshes/Shapes.h"
#include "Meshes/VertexFormats.h"
#include "DataTypes.h"
#include "Game.h"
#include "Resources/Mesh.h"
#include "Resources/Material.h"
#include "FWCore.h"


DiceScene::DiceScene(Game* game):
	Scene(game)
{

    // Create some gameObjects.
    m_pCamera = new fw::Camera(this, vec3(0, 0, 0));
	
#define getMesh game->GetResources()->Get<fw::Mesh>
#define getMaterial game->GetResources()->Get<fw::Material>

    m_pObjects.push_back(new fw::GameObject(this, "Box1", vec3(0, 0, 10), getMesh("RectC"), getMaterial("Die1")));
    m_pObjects.push_back(new fw::GameObject(this, "Box2", vec3(10, 5, 10), getMesh("RectT"), getMaterial("Die1")));
    m_pObjects.push_back(new fw::GameObject(this, "Box3", vec3(-10, -5, 10), getMesh("RectW"), getMaterial("Die1")));

    m_pObjects[0]->SetScale(10);
    m_pObjects[1]->SetScale(5);
    m_pObjects[2]->SetScale(5);
    m_pObjects[1]->m_IsRotating = true;
    m_pObjects[2]->m_IsRotating = true;

    
}

DiceScene::~DiceScene()
{
}

void DiceScene::Update(float DeltaTime)
{

    for (int i = 0; i < m_pObjects.size(); i++) {
        m_pObjects[i]->Update(DeltaTime);
    }

    for (int i = 0; i < m_pObjects.size(); i++) {
        if (m_pObjects[i]->GetName() == "Box1") {
            m_pObjects[i]->RotationGUI();
        }
    }
}

void DiceScene::Draw()
{
    // Program the view and proj uniforms from the camera.
    m_pCamera->Enable(EditorViews::EditorView_Game);

    // Draw all objects.
    for (fw::GameObject* pObject : m_pObjects)
    {
        pObject->Draw();
    }
}

