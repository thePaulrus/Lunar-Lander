#include "PinBallScene.h"
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
#include "Objects/PhysDebugDraw.h"

//box2d stuff
#define B2_USER_SETTINGS
#include "box2d/include/box2D/box2d.h"

PinBallScene::PinBallScene(Game* game):
	Scene(game)
{
    CreateWorld();

    // Create some GameObjects.
    m_pCamera = new fw::Camera(this, vec3(0, 1, 0));
    m_pCamera->SetRotation(20);

#define getMesh game->GetResources()->Get<fw::Mesh>
#define getMaterial game->GetResources()->Get<fw::Material>

    m_pPlayer = new Player(this, "Player", vec3(1, 7, 0), getMesh("Sprite"), getMaterial("MegaMan"), game->GetEventManager(), game->GetController());
    //m_pPlayer->CreateSquareBody(true, 0.1);
    m_pObjects.push_back(m_pPlayer);

    fw::GameObject* pObject;

    pObject = new fw::GameObject(this, "low blue square", vec3(1, 1, 0), getMesh("Square"), getMaterial("Blue"));
    pObject->SetRotation(vec3(0,0,30));
    pObject->SetScale(vec3(5,2,1));
    //pObject->CreateSquareBody(false, 0.1);
    m_pObjects.push_back(pObject);

    pObject = new fw::GameObject(this, "high blue square", vec3(2, 0, 0), getMesh("Square"), getMaterial("Blue"));
    pObject->SetRotation(vec3(0,0,30));
    //pObject->CreateSquareBody(false, 0.1);
    m_pObjects.push_back(pObject);

    //m_pObjects.push_back(new fw::GameObject(this, "green square", vec3(7, 7, 0), getMesh("Square"), getMaterial("VertexColor")));
    //m_pObjects.push_back(new fw::GameObject(this, "ball", vec3(1, 9, 0), getMesh("Circle"), getMaterial("Blue")));


    //m_pObjects[3]->CreateSquareBody(false, 0.9);
   // m_pObjects[4]->CreateCircleBody(true, 0.7);
    //m_pObjects[2]->SetRotation(vec3(0,0,20));

    m_pDebugDraw = new PhysDebugDraw();
    m_pDebugDraw->SetFlags(b2Draw::e_shapeBit | b2Draw::e_aabbBit);
    m_pDebugDraw->m_ShaderHandle = getMaterial("VertexColor")->GetShader()->GetProgram();
    m_pDebugDraw->m_pUniforms = game->GetUniforms();

    m_pWorld->SetDebugDraw(m_pDebugDraw);
}

PinBallScene::~PinBallScene()
{

}

void PinBallScene::Update(float DeltaTime)
{
    PhysicsUpdate(DeltaTime);



    for (int i = 0; i < m_pObjects.size(); i++) {
        m_pObjects[i]->Update(DeltaTime);
    }

    for (int i = 0; i < m_pObjects.size(); i++) {
        if (m_pObjects[i]->GetName() == "Box1") {
            m_pObjects[i]->RotationGUI();
        }
    }
    m_pWorld->DebugDraw();
}

void PinBallScene::Draw()
{
    // Program the view and proj uniforms from the camera.
    m_pCamera->Enable(EditorViews::EditorView_Game);

    // Draw all objects.
    for (fw::GameObject* pObject : m_pObjects)
    {
        pObject->Draw();
    }
}
