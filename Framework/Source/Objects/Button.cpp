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
#include "Button.h"
#include "Resources/Mesh.h"
#include "Utility/Uniforms.h"
#include "Imgui/ImGuiManager.h"
#include "Scenes/Scene.h"
//#include "Objects/PhysDebugDraw.h"

//box2d stuff
#define B2_USER_SETTINGS
#include "box2d/include/box2D/box2d.h"

namespace fw {

    Button::Button(Scene* scene, std::string name, vec3 pos, Mesh* pMesh, Material* pMaterial)
        : GameObject(scene, name, pos, pMesh, pMaterial)
    {
       
    }

    Button::~Button()
    {
    }

    void Button::Update(float DeltaTime) {

    }

} // namespace fw
