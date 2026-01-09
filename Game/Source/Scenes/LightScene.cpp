#include "LightScene.h"
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


LightScene::LightScene(Game* game):
	Scene(game)
{

    // Create some gameObjects.
    m_pCamera = new fw::Camera(this, vec3(0, 10, -50));
	
#define getMesh game->GetResources()->Get<fw::Mesh>
#define getMaterial game->GetResources()->Get<fw::Material>

    m_pObjects.push_back(new fw::GameObject(this, "Box1", vec3(0, 0, 0), getMesh("RectC"), getMaterial("ColourLight")));

    m_pObjects[0]->SetScale(vec3(100,0,100));

}

LightScene::~LightScene()
{
}

void LightScene::Update(float DeltaTime)
{

    for (int i = 0; i < m_pObjects.size(); i++) {
        m_pObjects[i]->Update(DeltaTime);
    }

    for (int i = 0; i < m_pObjects.size(); i++) {
        if (m_pObjects[i]->GetName() == "Box1") {
            m_pObjects[i]->RotationGUI();
        }
    }

    m_pCamera->SetPosition(vec3(sin((float)fw::GetSystemTimeSinceGameStart()*0.5)* 50, m_pCamera->GetPosition().y, m_pCamera->GetPosition().z));
}

void LightScene::Draw()
{
    // Program the view and proj uniforms from the camera.
    m_pCamera->Enable(EditorViews::EditorView_Game);

    // Draw all objects.
    for (fw::GameObject* pObject : m_pObjects)
    {
        pObject->Draw();
    }
}

