//
// Copyright (c) 2022-2023 Jimmy Lord
//
// This software is provided 'as-is', without any express or implied warranty.  In no event will the authors be held liable for any damages arising from the use of this software.
// Permission is granted to anyone to use this software for any purpose, including commercial applications, and to alter it and redistribute it freely, subject to the following restrictions:
// 1. The origin of this software must not be misrepresented; you must not claim that you wrote the original software. If you use this software in a product, an acknowledgment in the product documentation would be appreciated but is not required.
// 2. Altered source versions must be plainly marked as such, and must not be misrepresented as being the original software.
// 3. This notice may not be removed or altered from any source distribution.

#pragma once

#include "Math/Vector.h"

//box2d stuff
#define B2_USER_SETTINGS
#include "box2d/include/box2D/box2d.h"

enum class Shapes {
    circle,
    square
};

namespace fw {

    class Camera;
    class GameCore;
    class Material;
    class Mesh;
    class Uniforms;
    class EventManager;
    class Scene;

    class GameObject
    {
    public:
        GameObject(Scene* scene, std::string name, vec3 pos, Mesh* pMesh, Material* pMaterial);
        virtual ~GameObject();
        virtual void CreateCircleBody(bool nonStatic, float bounce);
        virtual void CreateSquareBody(bool nonStatic, float bounce, bool sensor);

        virtual void Update(float deltaTime);
        virtual void PhysicsUpdate();
        virtual void Draw();

        // Getters.
        std::string GetName() { return m_Name; }
        EventManager* GetEventManager() { return m_pEventMan; }

        Mesh* GetMesh() { return m_pMesh; }
        Material* GetMaterial() { return m_pMaterial; }
        b2Body* GetBody();
        vec3 GetPosition() { return m_Position; }
        vec3 GetRotation() { return m_Rotation; }
        vec3 GetScale() { return m_Scale; }

        // Setters.
        void SetPosition(vec3 pos) { m_Position = pos; }
        void SetRotation(vec3 rot) { m_Rotation = rot; }
        void SetScale(vec3 scale) { m_Scale = scale; }
        void SetBodyType(bool dynamic);
        void CoolRotation(float deltaTime);
        virtual void SetCanJump(bool jump);

        //for the lander
        virtual void Explode();


        void RotationGUI();


    protected:
        Scene* m_Scene = nullptr;

        std::string m_Name;
        bool m_isPhisicsMove = false;
        bool m_simulatePhysics = false;

        Mesh* m_pMesh = nullptr;
        Material* m_pMaterial = nullptr;

        vec3 m_Position = vec3(0, 0, 0);
        vec3 m_Rotation = vec3(0, 0, 0);
        vec3 m_Scale = vec3(1, 1, 1);

        //event managment
        EventManager* m_pEventMan;

        b2Body* m_pPhysicsBody = nullptr;
        bool m_dynamicBody;



    public:
        //this will probably be ipped out at some point
        bool m_IsRotating = false;

    };

} // namespace fw
