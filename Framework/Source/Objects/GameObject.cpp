//
// Copyright (c) 2022-2023 Jimmy Lord
//
// This software is provided 'as-is', without any express or implied warranty.  In no event will the authors be held liable for any damages arising from the use of this software.
// Permission is granted to anyone to use this software for any purpose, including commercial applications, and to alter it and redistribute it freely, subject to the following restrictions:
// 1. The origin of this software must not be misrepresented; you must not claim that you wrote the original software. If you use this software in a product, an acknowledgment in the product documentation would be appreciated but is not required.
// 2. Altered source versions must be plainly marked as such, and must not be misrepresented as being the original software.
// 3. This notice may not be removed or altered from any source distribution.

#include "CoreHeaders.h"

#include "Camera.h"
#include "GameCore.h"
#include "GameObject.h"
#include "Resources/Mesh.h"
#include "Utility/Uniforms.h"
#include "Imgui/ImGuiManager.h"
#include "Scenes/Scene.h"
//#include "Objects/PhysDebugDraw.h"

//box2d stuff
#define B2_USER_SETTINGS
#include "box2d/include/box2D/box2d.h"

namespace fw {

    GameObject::GameObject(Scene* scene, std::string name, vec3 pos, Mesh* pMesh, Material* pMaterial)
        : m_Scene(scene)
        , m_Name(name)
        , m_Position(pos)
        , m_pMesh(pMesh)
        , m_pMaterial(pMaterial)
    {
       
    }

    GameObject::~GameObject()
    {
    }


    

    void GameObject::Update(float deltaTime)
    {
        if (m_IsRotating == true) {
            CoolRotation(deltaTime);

        }
        if (m_pPhysicsBody){
            if (m_dynamicBody == true) {
                m_pPhysicsBody->SetType(b2_dynamicBody);
            }
            else {
                m_pPhysicsBody->SetType(b2_staticBody);
            }
        }

    }

    void GameObject::PhysicsUpdate()
    {
        if (m_pPhysicsBody) {
            m_Position = vec3(m_pPhysicsBody->GetPosition().x, m_pPhysicsBody->GetPosition().y, 0);
            
            //the physics world's z rotation is backwards
            m_Rotation = vec3(0, 0, radsToDegrees(m_pPhysicsBody->GetAngle()) * -1);
        }
    }

    void GameObject::Draw()
    {
       
        Uniforms* pUniforms = m_Scene->GetGameCore()->GetUniforms();

        mat4 transform;
        transform.CreateSRT(m_Scale,m_Rotation,m_Position);
        
        bgfx::setUniform( pUniforms->GetUniform("u_OBJtoWorld"), &transform);

        mat4 rotation;
        rotation.SetIdentity();
        rotation.CreateRotation(m_Rotation);
        bgfx::setUniform(pUniforms->GetUniform("u_MatWorldRotation"), &rotation);


        //b2Color colour;
        //colour.Set(1, 0, 0, 1);
        m_Scene->DebugDraw(this);

        m_pMesh->Draw( 0, pUniforms, m_pMaterial );
    }

    b2Body* GameObject::GetBody()
    {
        return m_pPhysicsBody;
    }

   

    void GameObject::SetBodyType(bool dynamic)
    {
        if (dynamic == true) {
            m_dynamicBody = true;
        }
        else {
            m_dynamicBody = false;
        }
    }

    void GameObject::CoolRotation(float deltaTime)
    {
        m_Rotation.x = 45.0f;
        m_Rotation.y += COOL_ROTATION_SPEED * deltaTime;
        
    }

    void GameObject::SetCanJump(bool jump)
    {
    }

    void GameObject::Explode()
    {
    }

    void GameObject::RotationGUI()
    {
        ImGui::Begin("Die Rotation");

       
        
        float x[3];
        x[0] = m_Rotation.x;
        x[1] = m_Rotation.y;
        x[2] = m_Rotation.z;

        ImGui::DragFloat3("Rotation", x);

        m_Rotation.x = x[0];
        m_Rotation.y = x[1];
        m_Rotation.z = x[2];
     

        ImGui::End(); // "Object List"
    }

    void GameObject::CreateCircleBody(bool nonStatic, float bounce)
    {

        b2BodyDef bodyDef;
        bodyDef.userData.Object = this;
        if (nonStatic == true) {
            bodyDef.type = b2_dynamicBody;
            m_dynamicBody = true;

        }
        else {
            bodyDef.type = b2_staticBody;
            m_dynamicBody = false;

        }
        bodyDef.position = b2Vec2(m_Position.x, m_Position.y);
        
        b2FixtureDef fd;

       
        b2CircleShape circle;
        circle.m_radius = m_Scale.x/2;
       // circle.m_p = b2Vec2(m_Position.x, m_Position.y);
        fd.shape = &circle;
        
   
      
        fd.density = 1.0f;
        fd.restitution = bounce; //bounciness
        


        m_pPhysicsBody = m_Scene->GetWorld()->CreateBody(&bodyDef);
        m_pPhysicsBody->CreateFixture(&fd);
        m_pPhysicsBody->SetTransform(bodyDef.position, fw::degreesToRads(-m_Rotation.z));
        bodyDef.userData.Object = this;
    }

    void GameObject::CreateSquareBody(bool nonStatic, float bounce, bool sensor)
    {
        b2BodyDef bodyDef;
        bodyDef.userData.Object = this;
        if (nonStatic == true) {
            bodyDef.type = b2_dynamicBody;
            m_dynamicBody = true;

        }
        else {
            bodyDef.type = b2_staticBody;
            m_dynamicBody = false;

        }
        bodyDef.position = b2Vec2(m_Position.x, m_Position.y);
        bodyDef.angle = fw::degreesToRads(-m_Rotation.z);



        b2FixtureDef fd;
        
        if (sensor == true) {
            fd.isSensor = true;
        }

   //collision thing. dont rotate this, because this is off from the mesh
        b2PolygonShape square;
        square.SetAsBox(m_Scale.x/2, m_Scale.y/2);
        fd.shape = &square;

        fd.density = 1.0f;
        fd.restitution = bounce; //bounciness



        m_pPhysicsBody = m_Scene->GetWorld()->CreateBody(&bodyDef);
        m_pPhysicsBody->CreateFixture(&fd);
        bodyDef.userData.Object = this;
        // m_pPhysicsBody->
    }

} // namespace fw
