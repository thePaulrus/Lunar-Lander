#include "MidtermScene.h"
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

MidtermScene::MidtermScene(Game* game):
	Scene(game)
{

    CreateWorld();

   
    // Create some GameObjects.
    m_pCamera = new fw::Camera(this, vec3(0, 1, 0));
    m_pCamera->SetRotation(20);

#define getMesh game->GetResources()->Get<fw::Mesh>
#define getMaterial game->GetResources()->Get<fw::Material>


    m_pLander = new Lander(this, "Player", vec3(5, 8, 0), getMesh("Sprite"), getMaterial("LanderBoth"), game->GetEventManager(), game->GetController());
    m_pLander->SetScale(vec3(2, 2, 1));
    m_pObjects.push_back(m_pLander);

    fw::GameObject* pObject;

    pObject = new fw::GameObject(this, "ground", vec3(1, -8, 0), getMesh("Square"), getMaterial("Blue"));
    pObject->SetScale(vec3(100,2,1));
    m_pObjects.push_back(pObject);

    pObject = new fw::GameObject(this, "otherPalyer1", vec3(1, -8, 0), getMesh("Square"), getMaterial("Blue"));
    pObject->SetScale(vec3(1, 1, 1));
    m_pObjects.push_back(pObject);

    pObject = new fw::GameObject(this, "otherPalyer1", vec3(1, -8, 0), getMesh("Square"), getMaterial("Blue"));
    pObject->SetScale(vec3(1, 1, 1));
    pObject->CreateSquareBody(false, 0.0, false);
    m_pObjects.push_back(pObject);

    pObject = new fw::GameObject(this, "otherPalyer1", vec3(1, -8, 0), getMesh("Square"), getMaterial("Blue"));
    pObject->SetScale(vec3(1, 1, 1));
    pObject->CreateSquareBody(false, 0.0, false);
    m_pObjects.push_back(pObject);

    

    

    m_pDebugDraw = new PhysDebugDraw();
    m_pDebugDraw->SetFlags(b2Draw::e_shapeBit | b2Draw::e_aabbBit);
    m_pDebugDraw->m_ShaderHandle = getMaterial("VertexColor")->GetShader()->GetProgram();
    m_pDebugDraw->m_pUniforms = game->GetUniforms();

   // m_pWorld->SetDebugDraw(m_pDebugDraw);

    //network
    InitNetwork();
   

}

MidtermScene::~MidtermScene()
{

}

void MidtermScene::Update(float DeltaTime)
{
    PhysicsUpdate(DeltaTime);

    SendToNetwork();
    ReciveFromNetwork();


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

void MidtermScene::Draw()
{
    // Program the view and proj uniforms from the camera.
    m_pCamera->Enable(EditorViews::EditorView_Game);

    // Draw all objects.
    for (fw::GameObject* pObject : m_pObjects)
    {
        pObject->Draw();
    }
}

void MidtermScene::InitNetwork()
{



    sockaddr_in localaddr;
    localaddr.sin_family = AF_INET;
    localaddr.sin_addr.s_addr = INADDR_ANY;
    localaddr.sin_port = htons(12345);

    bind(m_socketHandle, (const sockaddr*)&localaddr, sizeof(sockaddr_in));

    DWORD value = 1;
    ioctlsocket(m_socketHandle, FIONBIO, &value);

    hostent* host = gethostbyname("10.50.35.181");
    in_addr serverInAddr = *(in_addr*)host->h_addr_list[0];

    
    m_serverAddr.sin_family = AF_INET;
    m_serverAddr.sin_addr = serverInAddr;
    m_serverAddr.sin_port = htons(12345);

  
   
}

void MidtermScene::SendToNetwork()
{
    //networking
 
    //240, 141, 177
    packet sendThis;
    sendThis.command = 'P';
    sendThis.r = 240;
    sendThis.g = 141;
    sendThis.b = 177;
    sendThis.playerNum = 2123869703;
    sendThis.pos = m_pLander->GetPosition();
    sendThis.rot = m_pLander->GetRotation().z;

    int flags = 0;
    sendto(m_socketHandle, (const char*)&sendThis, sizeof(sendThis),
        flags, (sockaddr*)&m_serverAddr, sizeof(sockaddr_in));
}

void MidtermScene::ReciveFromNetwork()
{
    char buffer[1000];
    int bufferSize = 1000;
    sockaddr_in address;
    int addrLength = sizeof(sockaddr_in);

    int bytes = -500;
    while (bytes != -1)
    {
        int flags = 0;
        bytes = (int)recvfrom(m_socketHandle, buffer, bufferSize,
            flags, (sockaddr*)&address, &addrLength);

        if (bytes != -1)
        {
            // Process packets here.

            packet* Packet = reinterpret_cast<packet*>(buffer);
            m_pObjects[2]->SetPosition(Packet->pos);

        }
    }
}
