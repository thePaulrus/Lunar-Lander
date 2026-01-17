#include "DayOneScene.h"
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
#include "Objects/Lander.h"

//box2d stuff
#define B2_USER_SETTINGS
#include "box2d/include/box2D/box2d.h"


DayOneScene::DayOneScene(Game* game) :
	Scene(game)
{
    CreateWorld();

    // Create some GameObjects.
    m_pCamera = new fw::Camera(this, vec3(5, 5, 0));

#define getMesh game->GetResources()->Get<fw::Mesh>
#define getMaterial game->GetResources()->Get<fw::Material>

    /*m_pPlayer = new Player(this, "Player", vec3(1, 7, 0), getMesh("Sprite"), getMaterial("MegaMan"), game->GetEventManager(), game->GetController());
    m_pObjects.push_back(m_pPlayer);*/

    m_pLander = new Lander(this, "Player", vec3(1, 7, 0), getMesh("Sprite"), getMaterial("LanderOff"), game->GetEventManager(), game->GetController());
    m_pObjects.push_back(m_pLander); 
    m_pObjects[0]->CreateSquareBody(true, 0.0, true);

    //                                   Scene*  std::string name , vec3 pos, Mesh* pMesh,        Material* pMaterial,)
    m_pObjects.push_back(new fw::GameObject(this, "Object 1", vec3(0, 0, 0), getMesh("Triangle"), getMaterial("VertexColor")));
    m_pObjects.push_back(new fw::GameObject(this, "Object 2", vec3(10, 10, 0), getMesh("Triangle"), getMaterial("Blue")));
    m_pObjects.push_back(new fw::GameObject(this, "Object 3", vec3(5, 5, 0), getMesh("Square"), getMaterial("VertexColor")));
    m_pObjects.push_back(new fw::GameObject(this, "Object 4", vec3(1, 1, 0), getMesh("Square"), getMaterial("VertexColor")));
    m_pObjects.push_back(new fw::GameObject(this, "Object 5", vec3(1, 9, 0), getMesh("OBJ"), getMaterial("Red")));
    m_pObjects.push_back(new fw::GameObject(this, "Object 6", vec3(1, 7, 0), getMesh("Circle"), getMaterial("Blue")));
    m_pObjects.push_back(new fw::GameObject(this, "Box1", vec3(0, 0, 10), getMesh("RectC"), getMaterial("DebugNormals")));
    m_pObjects.push_back(new fw::GameObject(this, "MouseCircle", vec3(0, 0, 0), getMesh("Circle"), getMaterial("Green")));


    //m_pObjects[4]->CreateSquareBody(false, 0);
    //m_pObjects[6]->CreateCircleBody(true, 1);
    m_pObjects[7]->SetScale(10);
    
    m_pDebugDraw = new PhysDebugDraw();
    m_pDebugDraw->SetFlags(b2Draw::e_shapeBit | b2Draw::e_aabbBit);
    m_pDebugDraw->m_ShaderHandle = getMaterial("Blue")->GetShader()->GetProgram();
    m_pDebugDraw->m_pUniforms = game->GetUniforms();

    m_pWorld->SetDebugDraw(m_pDebugDraw);
    //debug controller. 
    ptempcontroller = new fw::VirtualController();
}

DayOneScene::~DayOneScene()
{
    delete ptempcontroller;
}


void DayOneScene::Update(float DeltaTime)
{

    PhysicsUpdate(DeltaTime);

    //mouse test
    
    m_pObjects[8]->SetPosition(ptempcontroller->GetMousePos() /5 );
 

    for (int i = 0; i < m_pObjects.size(); i++) {
        m_pObjects[i]->Update(DeltaTime);
    }

    for (int i = 0; i < m_pObjects.size(); i++) {
        if (m_pObjects[i]->GetName() == "Box1") {
            m_pObjects[i]->RotationGUI();
        }
    }
}

void DayOneScene::Draw()
{
    // Program the view and proj uniforms from the camera.
    m_pCamera->Enable(EditorViews::EditorView_Game);

    
    // Draw all objects.
    for (fw::GameObject* pObject : m_pObjects)
    {
        pObject->Draw();

    }

    m_pWorld->DebugDraw();
}



void DayOneScene::DebugDraw(fw::GameObject* object)
{
    b2Color colour;
    colour.Set(1, 0, 0, 1);
    m_pDebugDraw->DrawCircle(b2Vec2(object->GetPosition().x, object->GetPosition().y), object->GetScale().x / 2.0, colour);
    
}



