#include "GolfScene.h"
#include "GameCore.h"
#include "Objects/GameObject.h"
#include "Objects/Camera.h"
#include "Objects/OrbitCamera.h"
#include "Objects/Player.h"
#include "Meshes/Shapes.h"
#include "Meshes/VertexFormats.h"
#include "DataTypes.h"
#include "Game.h"
#include "Resources/Mesh.h"
#include "Resources/Material.h"
#include "Objects/PhysDebugDraw.h"
#include "Objects/Lander.h"

//box2d stuff
#define B2_USER_SETTINGS
#include "box2d/include/box2D/box2d.h"


GolfScene::GolfScene(Game* game) :
	Scene(game)
{

   

#define getMesh game->GetResources()->Get<fw::Mesh>
#define getMaterial game->GetResources()->Get<fw::Material>


    //                                   Scene*  std::string name , vec3 pos, Mesh* pMesh,        Material* pMaterial,)

    fw::GameObject* pObject;




    pObject = new fw::GameObject(this, "Water", vec3(-5, 0, -5), getMesh("BigPlane"), getMaterial("Minecraft_Water"));
    m_pObjects.push_back(pObject);

    pObject = new fw::GameObject(this, "Island", vec3(0, 0, 0), getMesh("AF_Hight"), getMaterial("AF_HightLight"));
    m_pObjects.push_back(pObject);

    pObject = new fw::GameObject(this, "Tree1", vec3(0, 5, 0), getMesh("Tree2"), getMaterial("Tree2"));
    pObject->SetScale(fw::Random::Float(0.4)+0.8);
    pObject->SetRotation(vec3(0, fw::Random::Float(360), 0));
    m_pCamera = new OrbitCamera(this, vec3(0, 5, 0), pObject, game->GetController());
    m_pObjects.push_back(pObject);

   
}

GolfScene::~GolfScene()
{
}

void GolfScene::Update(float DeltaTime)
{
    for (int i = 0; i < m_pObjects.size(); i++) {
        m_pObjects[i]->Update(DeltaTime);
    }

    for (int i = 0; i < m_pObjects.size(); i++) {
        if (m_pObjects[i]->GetName() == "Tree1") {
            m_pObjects[i]->RotationGUI();
        }
    }


    m_pCamera->Update(DeltaTime);
   
}

void GolfScene::Draw()
{
    // Program the view and proj uniforms from the camera.
    m_pCamera->Enable(EditorViews::EditorView_Game);

    
    // Draw all objects.
    for (fw::GameObject* pObject : m_pObjects)
    {
        pObject->Draw();

    }

}



void GolfScene::DebugDraw(fw::GameObject* object)
{
    b2Color colour;
    colour.Set(1, 0, 0, 1);
    
}



