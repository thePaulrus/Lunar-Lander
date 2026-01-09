//
// Copyright (c) 2022-2023 Jimmy Lord
//
// This software is provided 'as-is', without any express or implied warranty.  In no event will the authors be held liable for any damages arising from the use of this software.
// Permission is granted to anyone to use this software for any purpose, including commercial applications, and to alter it and redistribute it freely, subject to the following restrictions:
// 1. The origin of this software must not be misrepresented; you must not claim that you wrote the original software. If you use this software in a product, an acknowledgment in the product documentation would be appreciated but is not required.
// 2. Altered source versions must be plainly marked as such, and must not be misrepresented as being the original software.
// 3. This notice may not be removed or altered from any source distribution.

#include "Framework.h"

#include "DataTypes.h"
#include "Game.h"
#include "Objects/Player.h"
#include "Meshes/Shapes.h"
#include "Meshes/VertexFormats.h"

#define getMesh pResources->Get<fw::Mesh>
#define getShader pResources->Get<fw::ShaderProgram>
#define getTexture pResources->Get<fw::Texture>
#define getMaterial pResources->Get<fw::Material>

void LoadResources(fw::ResourceManager* pResources)
{
    // Create some meshes.
    pResources->Add<fw::Mesh>( "Triangle", CreateTriangleMesh() );
    pResources->Add<fw::Mesh>( "Square", CreateSquareMesh() );
    pResources->Add<fw::Mesh>( "Sprite", CreateSpriteMesh() );
    pResources->Add<fw::Mesh>( "Circle", CreateCircleMesh(32) );
    pResources->Add<fw::Mesh>( "RectC", CreateBoxMesh(vec3(1,1,1))); //cube
    pResources->Add<fw::Mesh>( "RectT", CreateBoxMesh(vec3(1, 2, 1)) ); // rectangular prism that is twice the hight as the lenght and width
    pResources->Add<fw::Mesh>( "RectW", CreateBoxMesh(vec3(2, 1, 2)) );// rectangular prism that is twice the lenght and width  as the hight
    pResources->Add<fw::Mesh>( "Plane", CreatePlaneMesh(vec2(32,32),vec2(20,20)));
    pResources->Add<fw::Mesh>( "BigPlane", CreatePlaneMesh(vec2(32,32),vec2(200,200)));
    pResources->Add<fw::Mesh>( "A4_Hight", CreateHightMap( vec2(10,10), "Data/Textures/A4_HightMap.png"));
    pResources->Add<fw::Mesh>( "AF_Hight", CreateHightMap( vec2(100,100), "Data/Textures/AF_HightMap.png"));
    pResources->Add<fw::Mesh>( "OBJ", ImportOBJMesh("Data/OBJs/WorstCubeEver.obj"));// 
    pResources->Add<fw::Mesh>( "Tree1", ImportOBJMesh("Data/OBJs/A4Tree.obj"));// 
    pResources->Add<fw::Mesh>( "Tree2", ImportOBJMesh("Data/OBJs/A4Tree3.obj"));// 

    // Load some shaders.
    pResources->Add<fw::ShaderProgram>( "SolidColor", new fw::ShaderProgram( "Data/Shaders/", "SolidColor.vert.bin", "SolidColor.frag.bin" ) );
    pResources->Add<fw::ShaderProgram>( "VertexColor", new fw::ShaderProgram( "Data/Shaders/", "VertexColor.vert.bin", "VertexColor.frag.bin" ) );
    pResources->Add<fw::ShaderProgram>( "Texture", new fw::ShaderProgram( "Data/Shaders/", "Texture.vert.bin", "Texture.frag.bin" ) );
    pResources->Add<fw::ShaderProgram>( "Water", new fw::ShaderProgram( "Data/Shaders/", "Water.vert.bin", "Water.frag.bin" ) );
    pResources->Add<fw::ShaderProgram>( "DebugNormals", new fw::ShaderProgram( "Data/Shaders/", "DebugNormals.vert.bin", "DebugNormals.frag.bin" ) );
    pResources->Add<fw::ShaderProgram>( "ColourLight", new fw::ShaderProgram( "Data/Shaders/", "ColourLight.vert.bin", "ColourLight.frag.bin" ) );

    // Load some textures.
    pResources->Add<fw::Texture>( "MegaMan", new fw::Texture( "Data/Textures/MegaMan.png" ) );
    pResources->Add<fw::Texture>( "Die1", new fw::Texture( "Data/Textures/DieTex1.png" ) );
    pResources->Add<fw::Texture>( "LanderOff", new fw::Texture( "Data/Textures/LunarLander_ForceOff.png" ) );
    pResources->Add<fw::Texture>( "LanderRight", new fw::Texture( "Data/Textures/LunarLander_ForceRight.png" ) );
    pResources->Add<fw::Texture>( "LanderLeft", new fw::Texture( "Data/Textures/LunarLander_ForceLeft.png" ) );
    pResources->Add<fw::Texture>( "LanderExplode", new fw::Texture( "Data/Textures/LunarLander_Explode.png" ) );
    pResources->Add<fw::Texture>( "LanderBoth", new fw::Texture( "Data/Textures/LunarLanderForceBoth.png" ) );
    pResources->Add<fw::Texture>( "Minecraft_Water", new fw::Texture( "Data/Textures/Minecraft_Water.png" ) );
    pResources->Add<fw::Texture>( "A4_Hight", new fw::Texture( "Data/Textures/A4_HightMap.png" ) );
    pResources->Add<fw::Texture>( "AF_Hight", new fw::Texture( "Data/Textures/AF_HightMap.png" ) );
    pResources->Add<fw::Texture>( "Tree2", new fw::Texture( "Data/Textures/Tree2.png" ) );

    // Create some materials.
    pResources->Add<fw::Material>( "Red", new fw::Material( getShader("SolidColor"), nullptr, fw::color4f::Red(), false ) );
    pResources->Add<fw::Material>( "Blue", new fw::Material( getShader("SolidColor"), nullptr, fw::color4f::Blue(), false ) );
    pResources->Add<fw::Material>( "Green", new fw::Material( getShader("SolidColor"), nullptr, fw::color4f::Green(), false ) );
    pResources->Add<fw::Material>( "VertexColor", new fw::Material( getShader("VertexColor"), nullptr, fw::color4f::White(), false ) );
    pResources->Add<fw::Material>( "MegaMan", new fw::Material( getShader("Texture"), getTexture("MegaMan"), fw::color4f::White(), true ) );
    pResources->Add<fw::Material>( "Die1", new fw::Material( getShader("Texture"), getTexture("Die1"), fw::color4f::White(), false ) );
    pResources->Add<fw::Material>( "LanderOff", new fw::Material( getShader("Texture"), getTexture("LanderOff"), fw::color4f::White(), false ) );
    pResources->Add<fw::Material>( "LanderRight", new fw::Material( getShader("Texture"), getTexture("LanderRight"), fw::color4f::White(), false ) );
    pResources->Add<fw::Material>( "LanderLeft", new fw::Material( getShader("Texture"), getTexture("LanderLeft"), fw::color4f::White(), false ) );
    pResources->Add<fw::Material>( "LanderExplode", new fw::Material( getShader("Texture"), getTexture("LanderExplode"), fw::color4f::White(), false ) );
    pResources->Add<fw::Material>( "LanderBoth", new fw::Material( getShader("Texture"), getTexture("LanderBoth"), fw::color4f::White(), false ) );
    pResources->Add<fw::Material>( "Tree2", new fw::Material( getShader("Texture"), getTexture("Tree2"), fw::color4f::White(), false ) );
    pResources->Add<fw::Material>( "Minecraft_Water", new fw::Material( getShader("Water"), getTexture("Minecraft_Water"), fw::color4f::White(), false ) );
    pResources->Add<fw::Material>( "A4_Hight", new fw::Material( getShader("Texture"), getTexture("A4_Hight"), fw::color4f::White(), false ) );
    pResources->Add<fw::Material>( "A4_HightLight", new fw::Material( getShader("ColourLight"), getTexture("A4_Hight"), fw::color4f::White(), false ) );
    pResources->Add<fw::Material>( "AF_Hight", new fw::Material( getShader("Texture"), getTexture("AF_Hight"), fw::color4f::White(), false ) );
    pResources->Add<fw::Material>( "AF_HightLight", new fw::Material( getShader("ColourLight"), getTexture("AF_Hight"), fw::color4f::White(), false ) );
    pResources->Add<fw::Material>( "DebugNormals", new fw::Material( getShader("DebugNormals"),nullptr, fw::color4f::White(), false ) );
    pResources->Add<fw::Material>( "ColourLight", new fw::Material( getShader("ColourLight"),nullptr, fw::color4f::White(), false ) );
    pResources->Add<fw::Material>( "ColourLightgreen", new fw::Material( getShader("ColourLight"),nullptr, fw::color4f::Green(), false ) );
    

}
