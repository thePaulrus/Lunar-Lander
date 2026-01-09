//
// Copyright (c) 2022-2023 Jimmy Lord
//
// this software is provided 'as-is', without any express or implied warranty.  In no event will the authors be held liable for any damages arising from the use of this software.
// Permission is granted to anyone to use this software for any purpose, including commercial applications, and to alter it and redistribute it freely, subject to the following restrictions:
// 1. The origin of this software must not be misrepresented; you must not claim that you wrote the original software. If you use this software in a product, an acknowledgment in the product documentation would be appreciated but is not required.
// 2. Altered source versions must be plainly marked as such, and must not be misrepresented as being the original software.
// 3. this notice may not be removed or altered from any source distribution.

#include "Framework.h"

#include "DataTypes.h"
#include "Game.h"
#include "LoadResources.h"
#include "Objects/Player.h"
#include "Events/GameEvents.h"
#include "Meshes/Shapes.h"
#include "Meshes/VertexFormats.h"

#include "Scenes/Scene.h"
#include "Scenes/DayOneScene.h"
#include "Scenes/DiceScene.h"
#include "Scenes/PinBallScene.h"
#include "Scenes/MidtermScene.h"
#include "Scenes/LunarLanderScene.h"
#include "Scenes/MeshScene.h"
#include "Scenes/LightScene.h"
#include "Scenes/GolfScene.h"


//box2d stuff
#define B2_USER_SETTINGS
#include "box2d/include/box2D/box2d.h"




Game::Game(fw::FWCore& fwCore)
    : GameCore( fwCore )
{
    
 


    bgfx::setViewClear(EditorViews::EditorView_Game, BGFX_CLEAR_COLOR | BGFX_CLEAR_DEPTH, 0x000030ff, 1.0f, 0);
    bgfx::setViewRect(EditorViews::EditorView_Game, 0, 0, m_FWCore.GetWindowClientWidth(), m_FWCore.GetWindowClientHeight());

    // Create some manager objects.
    m_pImGuiManager = new fw::ImGuiManager( &m_FWCore, 1 );
    m_pResources = new fw::ResourceManager();
    m_pEventMan = new fw::EventManager(this);
    m_pEventMan->AddListener(RemoveFromGameEvent::GetStaticEventType(),this);
    m_pEventMan->AddListener(fw::CharEvent::GetStaticEventType(), this);

    

    //controller
    m_Controller = new fw::VirtualController(m_pEventMan);

    // Create uniforms.
    CreateUniforms();

    // Create vertex formats.
    InitVertexFormats();

    // Load Resources.
    LoadResources( m_pResources );


  
    m_pScenes.push_back(new DayOneScene(this));
    m_pScenes.push_back(new DiceScene(this));
    m_pScenes.push_back(new PinBallScene(this));
    m_pScenes.push_back(new LunarLanderScene(this));
    m_pScenes.push_back(new MeshScene(this));
    m_pScenes.push_back(new LightScene(this));
    m_pScenes.push_back(new GolfScene(this));
    m_CurrentScene = 3;
}

Game::~Game()
{
    for( fw::Scene* pScene : m_pScenes )
    {
        delete pScene;
    }
   

    delete m_pResources;
    delete m_pUniforms;

    delete m_pImGuiManager;
    delete m_pEventMan;

    delete m_Controller;
}

void Game::CreateUniforms()
{
    assert( m_pUniforms == nullptr );

    m_pUniforms = new fw::Uniforms();
   

    m_pUniforms->CreateUniform( "u_OBJtoWorld", bgfx::UniformType::Mat4 );
    m_pUniforms->CreateUniform( "u_MatWorldRotation", bgfx::UniformType::Mat4 );
    m_pUniforms->CreateUniform( "u_camPos", bgfx::UniformType::Vec4 );


    m_pUniforms->CreateUniform( "u_WorldToVeiw", bgfx::UniformType::Mat4 );
    m_pUniforms->CreateUniform( "u_MatProj", bgfx::UniformType::Mat4 );

    m_pUniforms->CreateUniform( "u_DiffuseColor", bgfx::UniformType::Vec4 );
    m_pUniforms->CreateUniform( "u_TextureColor", bgfx::UniformType::Sampler );
    m_pUniforms->CreateUniform( "u_UVScale", bgfx::UniformType::Vec4 );
    m_pUniforms->CreateUniform( "u_UVOffset", bgfx::UniformType::Vec4 );

  

    m_pUniforms->CreateUniform( "u_Time", bgfx::UniformType::Vec4 );
}

void Game::StartFrame(float deltaTime)
{
    m_pImGuiManager->StartFrame( deltaTime );
    m_Controller->StartFrame();

    m_pEventMan->ProcessEvents();
}

void Game::OnEvent(fw::Event* pEvent)
{
}

void Game::Update(float deltaTime)
{
    
    


    m_pScenes[m_CurrentScene]->Update(deltaTime);
    

  

    Editor_DisplayObjectList();
    Editor_DisplayResources();


}

void Game::Draw()
{
    

    // Setup time uniforms.
    float time = (float)fw::GetSystemTimeSinceGameStart();
    bgfx::setUniform( m_pUniforms->GetUniform("u_Time"), &time );

    
    m_pScenes[m_CurrentScene]->Draw();

    m_pImGuiManager->EndFrame();
}

fw::EventManager* Game::GetEventManager()
{
    return m_pEventMan; 
}

void Game::ReceiveEvents(fw::Event* pEvent)
{

    // Process events.

    

    // Set the new aspect ratio in the camera.
    if( pEvent->GetType() == fw::WindowResizeEvent::GetStaticEventType() )
    {
        int width = m_FWCore.GetWindowClientWidth();
        int height = m_FWCore.GetWindowClientHeight();

        m_pScenes[m_CurrentScene]->GetCamera()->SetAspectRatio( (float)width/height );
    }

    // Pass "WM_CHAR" events to imgui to handle text input.
    if( pEvent->GetType() == fw::CharEvent::GetStaticEventType() )
    {
        int character = static_cast<fw::CharEvent*>(pEvent)->GetValue();
        m_pImGuiManager->AddInputCharacter( character );
    }
}

fw::ResourceManager* Game::GetResources()
{
    return m_pResources;
}

fw::VirtualController* Game::GetController()
{
    return m_Controller;
}



void Game::Editor_DisplayObjectList()
{
  
}

void Game::Editor_DisplayResources()
{
    ImGui::Begin("Resources");

    m_pResources->Editor_DisplayResourceLists();

    ImGui::End(); // "Resources"

    ImGui::Begin("Scenes");

    if (ImGui::Button("level 1")) {
        m_CurrentScene = 0;   
    }
    if (ImGui::Button("2")) {
        m_CurrentScene = 1;   
    }
    if (ImGui::Button("3")) {
        m_CurrentScene = 2;
    }
    if (ImGui::Button("4")) {
        m_CurrentScene = 3;
    }
    if (ImGui::Button("5")) {
        m_CurrentScene = 4;
    }
    if (ImGui::Button("6")) {
        m_CurrentScene = 5;
    }
    if (ImGui::Button("7")) {
        m_CurrentScene = 6;
    }
    

    ImGui::End(); // "Scenes"
}

void Game::Editor_CreateMainFrame()
{
    // Setup a main window with no frame and a dockspace that covers the entire viewport.
    ImGuiWindowFlags flags = ImGuiWindowFlags_NoDocking | ImGuiWindowFlags_NoTitleBar
        | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove
        | ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;

    ImGuiViewport* viewport = ImGui::GetMainViewport();
    ImGui::SetNextWindowPos(viewport->WorkPos);
    ImGui::SetNextWindowSize(viewport->WorkSize);

    if (ImGui::Begin("Main Dock", nullptr, flags))
    {
        ImGuiID dockspaceID = ImGui::GetID("My Dockspace");
        ImGui::DockSpace(dockspaceID);
    }
    ImGui::End();
}
