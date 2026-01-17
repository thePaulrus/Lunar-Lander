#include "Objects/Lander.h"
#include "LoadResources.h"
#include "Resources/Material.h"
//#include ""

Lander::Lander(fw::Scene* scene, std::string name, vec3 pos, fw::Mesh* pMesh, fw::Material* pMaterial, fw::EventManager* EventManager, fw::VirtualController* controller)
    : fw::GameObject(scene, name, pos, pMesh, pMaterial)
{
    //controller
    m_Controller = controller;

    m_State = LanderStates::Off;

    //set start pos
    m_StartPos = vec2(pos.x,pos.y);
}

Lander::~Lander()
{
}

void Lander::Update(float deltaTime)
{ 

    UpdateTexture();

    if (m_Controller->IsPressed(fw::VirtualController::Actions::Reset)) {
        Reset();
    }

    //if the ship exploded no need to update it
    if (m_State == LanderStates::Explode) {

        m_pPhysicsBody->SetType(b2_staticBody);
        return;
    }

    float force = 13;
    vec2 forceDir(0, force);
    mat4 rotMatrix;
    rotMatrix.CreateRotation(m_Rotation);


    vec2 rotatedOffsetLeft = rotMatrix * vec2(-1, -1);
    vec2 rotatedOffsetRight = rotMatrix * vec2(1, -1);
    vec2 rotatedForce = rotMatrix * forceDir;

    vec2 worldPointLeft = m_Position.XY() + rotatedOffsetLeft;
    vec2 worldPointRight = m_Position.XY() + rotatedOffsetRight;

    m_pPhysicsBody->SetAngularDamping(10);
    m_pPhysicsBody->SetGravityScale(0.2);


    if (m_Controller->IsPressed(fw::VirtualController::Actions::Left)) {
        m_pPhysicsBody->ApplyForce(b2Vec2(rotatedForce.x, rotatedForce.y), b2Vec2(worldPointLeft.x, worldPointLeft.y), true);
        m_State = LanderStates::LeftOn;
    }
    if (m_Controller->IsPressed(fw::VirtualController::Actions::Right)) {
        m_pPhysicsBody->ApplyForce(b2Vec2(rotatedForce.x, rotatedForce.y), b2Vec2(worldPointRight.x, worldPointRight.y), true);
        m_State = LanderStates::RightOn;
    }

    if (m_Controller->IsPressed(fw::VirtualController::Actions::Left) && m_Controller->IsPressed(fw::VirtualController::Actions::Right)) {
        m_State = LanderStates::BothOn;
    }
    else if (!(m_Controller->IsPressed(fw::VirtualController::Actions::Left) || m_Controller->IsPressed(fw::VirtualController::Actions::Right)) && m_State != LanderStates::Explode) {
        m_State = LanderStates::Off;

    }

   

    

}

void Lander::Explode()
{
    m_State = LanderStates::Explode;

   
}

void Lander::ReceiveEvents(fw::Event* pEvent)
{
}

void Lander::UpdateTexture()
{
    //change the texture depending on the state
    switch (m_State) {
    case LanderStates::Off:
        m_pMaterial = m_Scene->GetGameCore()->GetResources()->Get<fw::Material>("LanderOff");
        break;
    case LanderStates::BothOn:
        m_pMaterial = m_Scene->GetGameCore()->GetResources()->Get<fw::Material>("LanderBoth");
        // code block
        break;
    case LanderStates::LeftOn:
        m_pMaterial = m_Scene->GetGameCore()->GetResources()->Get<fw::Material>("LanderLeft");
        // code block
        break;
    case LanderStates::RightOn:
        m_pMaterial = m_Scene->GetGameCore()->GetResources()->Get<fw::Material>("LanderRight");
        // code block
        break;
    case LanderStates::Explode:
        m_pMaterial = m_Scene->GetGameCore()->GetResources()->Get<fw::Material>("LanderExplode");
        // code block
        break;
    default:
        // code block
        break;
    }
}

//vec2 Lander::GetStartPos()
//{
//    return m_StartPos;
//}
//
//void Lander::SetStartPos(vec2 startPos)
//{
//    m_StartPos = startPos;
//}

void Lander::Reset()
{
    m_State = LanderStates::Off;
    m_pPhysicsBody->SetAngularVelocity(0.0);
    m_pPhysicsBody->SetLinearVelocity(b2Vec2(0,0));
    m_pPhysicsBody->SetTransform(b2Vec2(m_StartPos.x, m_StartPos.y), 0);

    m_pPhysicsBody->SetType(b2_dynamicBody);

}
