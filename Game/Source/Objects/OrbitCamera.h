#pragma once

#include "Objects/Camera.h"
#include <DataTypes.h>

	class Scene;

class OrbitCamera: public fw::Camera
{
public:
	OrbitCamera() = default;
	OrbitCamera(fw::Scene* scene, vec3 pos, fw::GameObject* track, fw::VirtualController* controller);
	virtual ~OrbitCamera();

	void Enable(int viewID) override;


	virtual void Update(float32 deltaTime) override;

protected:
	fw::GameObject* m_tracked = nullptr;
	float m_Distance;
	fw::VirtualController* m_Controller;

	vec3 m_Eye = vec3(0, 0, 0);
	vec3 m_Up = vec3(0, 0, 0);
	vec3 m_At = vec3(0, 0, 0);


};

