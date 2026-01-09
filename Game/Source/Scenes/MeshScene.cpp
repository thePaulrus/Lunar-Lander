#include "MeshScene.h"
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


MeshScene::MeshScene(Game* game) :
	Scene(game)
{

    // Create some GameObjects.
    m_pCamera = new fw::Camera(this, vec3(5, 5, 10));

#define getMesh game->GetResources()->Get<fw::Mesh>
#define getMaterial game->GetResources()->Get<fw::Material>


    //                                   Scene*  std::string name , vec3 pos, Mesh* pMesh,        Material* pMaterial,)

    fw::GameObject* pObject;


    pObject = new fw::GameObject(this, "Box1", vec3(0, 0, 10), getMesh("RectC"), getMaterial("Die1"));
    //pObject->SetScale(vec3(2, 2, 2));
    m_pObjects.push_back(pObject);

    pObject = new fw::GameObject(this, "Box2", vec3(10, 0, 10), getMesh("RectC"), getMaterial("Die1"));
    //pObject->SetScale(vec3(2, 2, 2));
    m_pObjects.push_back(pObject);

    pObject = new fw::GameObject(this, "Box3", vec3(0, 0, 0), getMesh("RectC"), getMaterial("Die1"));
    //pObject->SetScale(vec3(2, 2, 2));
    m_pObjects.push_back(pObject);

    pObject = new fw::GameObject(this, "Box4", vec3(10, 0, 0), getMesh("RectC"), getMaterial("Die1"));
    //pObject->SetScale(vec3(2, 2, 2));
    m_pObjects.push_back(pObject);

    pObject = new fw::GameObject(this, "Water", vec3(-5, 0, -5), getMesh("Plane"), getMaterial("Minecraft_Water"));
    //pObject->SetScale(vec3(1, 1, 1));
    m_pObjects.push_back(pObject);

    pObject = new fw::GameObject(this, "Island", vec3(0, 0, 0), getMesh("A4_Hight"), getMaterial("A4_Hight"));
    //pObject->SetScale(vec3(1, 1, 1));
    m_pObjects.push_back(pObject);

    for (int i = 0; i < 20; i+=2) {
        pObject = new fw::GameObject(this, "Tree1", vec3(i, 5, i), getMesh("Tree2"), getMaterial("Tree2"));
        pObject->SetScale(fw::Random::Float(0.4)+0.8);
        pObject->SetRotation(vec3(0, fw::Random::Float(360), 0));

        if (i == 0) {
           // m_pCamera = new OrbitCamera(this, vec3(5, 5, 10), pObject, game->GetController());
        }

        m_pObjects.push_back(pObject);
    }
}

MeshScene::~MeshScene()
{
}

void MeshScene::Update(float DeltaTime)
{
    for (int i = 0; i < m_pObjects.size(); i++) {
        m_pObjects[i]->Update(DeltaTime);
    }

    for (int i = 0; i < m_pObjects.size(); i++) {
        if (m_pObjects[i]->GetName() == "Tree1") {
            m_pObjects[i]->RotationGUI();
        }
    }
   
}

void MeshScene::Draw()
{
    // Program the view and proj uniforms from the camera.
    m_pCamera->Enable(EditorViews::EditorView_Game);

    
    // Draw all objects.
    for (fw::GameObject* pObject : m_pObjects)
    {
        pObject->Draw();

    }

}



void MeshScene::DebugDraw(fw::GameObject* object)
{
    b2Color colour;
    colour.Set(1, 0, 0, 1);
    
}



