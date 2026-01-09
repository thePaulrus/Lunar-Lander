#pragma once
#include "Objects\GameObject.h"
#include "DataTypes.h"
#include "Utility/VirtualController.h"
#include "Scenes/Scene.h"

enum LanderStates {
    Off
    ,BothOn
    ,RightOn
    ,LeftOn
    ,Explode
};

class Lander : public fw::GameObject, public fw::EventListener
{
public:
    Lander(fw::Scene* scene, std::string name, vec3 pos, fw::Mesh* pMesh, fw::Material* pMaterial, fw::EventManager* EventManager, fw::VirtualController* controller);
    virtual ~Lander();

    virtual void Update(float deltaTime) override;

    virtual void Explode() override;

    //event managment
    virtual void ReceiveEvents(fw::Event* pEvent) override;

protected:
    void UpdateTexture();

    void Reset();

protected:

    vec2 m_Controls = 0;
    fw::VirtualController* m_Controller;

    int m_State;

};

