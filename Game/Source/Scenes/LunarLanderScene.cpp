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
