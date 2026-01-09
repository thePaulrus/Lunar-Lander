//
// Copyright (c) 2022-2023 Jimmy Lord
//
// This software is provided 'as-is', without any express or implied warranty.  In no event will the authors be held liable for any damages arising from the use of this software.
// Permission is granted to anyone to use this software for any purpose, including commercial applications, and to alter it and redistribute it freely, subject to the following restrictions:
// 1. The origin of this software must not be misrepresented; you must not claim that you wrote the original software. If you use this software in a product, an acknowledgment in the product documentation would be appreciated but is not required.
// 2. Altered source versions must be plainly marked as such, and must not be misrepresented as being the original software.
// 3. This notice may not be removed or altered from any source distribution.

#include "Framework.h"

#include "Game.h"
#include "GameCore.h"
#include "Objects/Player.h"
#include "Scenes/Scene.h"


Player::Player(fw::Scene* scene, std::string name, vec3 pos, fw::Mesh* pMesh, fw::Material* pMaterial, fw::EventManager* EventManager, fw::VirtualController* controller)
    : fw::GameObject(scene, name, pos, pMesh, pMaterial)
{
    //event managment
    m_pEventMan = EventManager;
    m_pEventMan->AddListener(fw::CharEvent::GetStaticEventType(), this);

    //controller
    m_Controller = controller;
}

Player::~Player()
{
}

void Player::Update(float deltaTime)
{
    float speed = 4.0f;

    vec2 dir;
    if (m_Controller->IsPressed(fw::VirtualController::Actions::Up)) {
        dir.y++;
    }
    if (m_Controller->IsPressed(fw::VirtualController::Actions::Down)) { 
        dir.y--; 
    }
    if (m_Controller->IsPressed(fw::VirtualController::Actions::Left)) { 
        dir.x--; 
    }
    if (m_Controller->IsPressed(fw::VirtualController::Actions::Right)) {
        dir.x++; 
    }
    if (m_Controller->IsPressed(fw::VirtualController::Actions::Jump)) {
        if (m_CanJump == true) {
            m_pPhysicsBody->ApplyLinearImpulse(b2Vec2(0, 10), m_pPhysicsBody->GetWorldCenter(), true);
            m_CanJump = false;
        }
    }
    dir.Normalize();


    //if there's a physics body move that instead
    if (m_pPhysicsBody) {
        m_pPhysicsBody->ApplyForce(b2Vec2(dir.x* 1000 * deltaTime,0), m_pPhysicsBody->GetWorldCenter(), true);
    }
    else {
        m_Position += dir * speed * deltaTime;
    }

    if (m_Controller->WasJustPressed(fw::VirtualController::Actions::Teleport)) {
        m_Position = vec2(fw::Random::Float(0, 10), fw::Random::Float(0, 10));
    }
}

void Player::ReceiveEvents(fw::Event* pEvent)
{
}

void Player::SetCanJump(bool jump)
{
    m_CanJump = jump;
}


