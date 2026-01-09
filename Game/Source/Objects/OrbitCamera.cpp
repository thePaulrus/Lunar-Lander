#include "OrbitCamera.h"


#include "CoreHeaders.h"

#include "LoadResources.h"

#include "Objects/Camera.h"
#include "FWCore.h"
#include "GameCore.h"
#include "Utility/Uniforms.h"
#include "Resources/Mesh.h"
#include "Scenes/Scene.h"


OrbitCamera::OrbitCamera(fw::Scene* scene, vec3 pos, fw::GameObject* track, fw::VirtualController* controller):
	fw::Camera(scene, pos)
{
	m_tracked = track;
	m_Controller = controller;
}

OrbitCamera::~OrbitCamera()
{
}

void OrbitCamera::Enable(int viewID)
{
	fw::Uniforms* pUniforms = m_Scene->GetGameCore()->GetUniforms();
	vec2 scaleWithAspectRatio = m_ProjectionScale * vec2(1.0f / m_AspectRatio, 1);

	mat4 worldToVeiw;

	//worldToVeiw.CreateLookAtView(m_Position + vec3(0, 0, -25), vec3(0, 1, 0), m_Position);
	worldToVeiw.CreateLookAtView(m_Eye, m_Up, m_At);



	vec4 pos = vec4(m_Position, 0);


	mat4 projMatrix;
	// Orthographic matrix that shows vertices between (-5,-5,0) and (5,5,100).
	//projMatrix.CreateOrtho(-5, 5, -5, 5, 0, 100);
	// Perspective matrix that shows things up to 100 units in front of the camera and within 45 degrees vertically above and below where the camera is looking.  Aspect ratio is set to 1 for our square screen.
	projMatrix.CreatePerspectiveVFoV(45, m_AspectRatio, 0.01, 1000);


	// Setup uniforms.
	bgfx::setUniform(pUniforms->GetUniform("u_WorldToVeiw"), &worldToVeiw, 1);
	bgfx::setUniform(pUniforms->GetUniform("u_MatProj"), &projMatrix, 1);
	bgfx::setUniform(pUniforms->GetUniform("u_camPos"), &pos);
}

void OrbitCamera::Update(float32 deltaTime)
{
	//m_Controller->IsPressed(fw::VirtualController::Actions::Up)
	vec2 rotationSpeed = vec2(1.0f, 0.4f);

	if (m_Controller->IsPressed(fw::VirtualController::Actions::AddRotY)) {
		m_Rotation.y += 90 * deltaTime * rotationSpeed.x;
	}
	if (m_Controller->IsPressed(fw::VirtualController::Actions::LessRotY)) {
		m_Rotation.y -= 90 * deltaTime * rotationSpeed.x;
	}
	if (m_Controller->IsPressed(fw::VirtualController::Actions::LessRotX)) {
		m_Rotation.x -= 90 * deltaTime * rotationSpeed.y;
	}
	if (m_Controller->IsPressed(fw::VirtualController::Actions::AddRotX)) {
		m_Rotation.x += 90 * deltaTime * rotationSpeed.y;
	}

	if (m_Controller->IsPressed(fw::VirtualController::Actions::Closer)) {
		m_Distance -= 10 * deltaTime;
	}
	if (m_Controller->IsPressed(fw::VirtualController::Actions::Further)) {
		m_Distance += 10 * deltaTime;
	}

	fw::MyClamp(m_Distance, 0.1f, 100.0f);
	fw::MyClamp(m_Rotation.x, -89.9f, 89.9f);

	// Calculate eye offset.
	// Method 1.
	float sx = sin(m_Rotation.x / 180 * PI);
	float sy = sin(m_Rotation.y / 180 * PI);
	float cx = cos(m_Rotation.x / 180 * PI);
	float cy = cos(m_Rotation.y / 180 * PI);
	vec3 offset = vec3(cx * sy * m_Distance, -sx * m_Distance, -1 * cx * cy * m_Distance);

	// Method 2.
	//mat4 rot;
	//rot.SetIdentity();
	//rot.Rotate( m_Rotation.x, 1, 0, 0 );
	//rot.Rotate( m_Rotation.y, 0, 1, 0 );
	//offset = rot * vec3(0,0,-m_Distance);

	m_Eye = m_tracked->GetPosition() + offset;
	m_At = m_tracked->GetPosition();
	m_Up = vec3(0, 1, 0);


}
