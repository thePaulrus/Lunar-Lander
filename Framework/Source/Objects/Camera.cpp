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
#include "FWCore.h"
#include "GameCore.h"
#include "Utility/Uniforms.h"
#include "Resources/Mesh.h"
#include "Scenes/Scene.h"

namespace fw {

    Camera::Camera(Scene* scene, vec3 pos)
        : GameObject( scene, "Camera", pos, nullptr, nullptr)
    {
        FWCore* pFW = m_Scene->GetGameCore()->GetFramework();
        SetAspectRatio( (float)pFW->GetWindowClientWidth()/pFW->GetWindowClientHeight() );
    }

    Camera::~Camera()
    {
    }

    void Camera::Update(float32 deltaTime)
    {

    }

    void Camera::Update(float32 deltaTime, std::vector<fw::GameObject*> TrackObj)
    {
    }

    void Camera::Enable(int viewID)
    {
        Uniforms* pUniforms = m_Scene->GetGameCore()->GetUniforms();
        vec2 scaleWithAspectRatio = m_ProjectionScale * vec2( 1.0f/m_AspectRatio, 1 );
    
        mat4 worldToVeiw;
       
        worldToVeiw.CreateLookAtView(m_Position + vec3(0,0,-25), vec3(0, 1, 0), m_Position);


      
        vec4 pos = vec4(m_Position, 0);
       

        mat4 projMatrix;
        // Orthographic matrix that shows vertices between (-5,-5,0) and (5,5,100).
        //projMatrix.CreateOrtho(-5, 5, -5, 5, 0, 100);
        // Perspective matrix that shows things up to 100 units in front of the camera and within 45 degrees vertically above and below where the camera is looking.  Aspect ratio is set to 1 for our square screen.
        projMatrix.CreatePerspectiveVFoV(45, m_AspectRatio, 0.01, 1000);


        // Setup uniforms.
        bgfx::setUniform( pUniforms->GetUniform("u_WorldToVeiw"), &worldToVeiw, 1 );
        bgfx::setUniform( pUniforms->GetUniform("u_MatProj"), &projMatrix, 1 );
        bgfx::setUniform(pUniforms->GetUniform("u_camPos"),  &pos);
    }

    void Camera::LanderZoom(GameObject* Lander, GameObject* Pad)
    {
        m_Position.z = -(Lander->GetPosition().DistanceFrom(Pad->GetPosition()));
    }

} // namespace fw
