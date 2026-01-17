#include "VirtualController.h"
#include <imgui/imgui.h>
//#include "Math/Vector.h"

//#include <SFML>

namespace fw {
	VirtualController::VirtualController()
	{
	}
	VirtualController::VirtualController(EventManager* manager)
	{
		manager->AddListener(InputEvent::GetStaticEventType(), this);
	}
	VirtualController::~VirtualController()
	{
	}
	void fw::VirtualController::ReceiveEvents(Event* pEvent)
	{
		if (pEvent->GetType() == InputEvent::GetStaticEventType())
		{
			InputEvent* pInputEvent = static_cast<InputEvent*>(pEvent);

			if (pInputEvent->GetDeviceType() == fw::InputEvent::DeviceType::Keyboard)
			{
				if (pInputEvent->GetDeviceState() == fw::InputEvent::DeviceState::Pressed)
				{
					switch (pInputEvent->GetKeyCode()) {
					case 'W': case VK_UP: {m_Actions = m_Actions | Actions::Up; }		break;
					case 'A': case VK_LEFT: {m_Actions = m_Actions | Actions::Left; }	break;
					case 'S': case VK_DOWN: {m_Actions = m_Actions | Actions::Down; }	break;
					case 'D': case VK_RIGHT: {m_Actions = m_Actions | Actions::Right; }		break;
					case 'J': {m_Actions = m_Actions | Actions::AddRotY; }		break;
					case 'L': {m_Actions = m_Actions | Actions::LessRotY; }		break;
					case 'I': {m_Actions = m_Actions | Actions::LessRotX; }		break;
					case 'K': {m_Actions = m_Actions | Actions::AddRotX; }		break;
					case 'U': {m_Actions = m_Actions | Actions::Closer; }		break;
					case 'M': {m_Actions = m_Actions | Actions::Further; }		break;
					case VK_SPACE: {m_Actions = m_Actions | Actions::Jump; }		break;
					case 'Z': {m_Actions = m_Actions | Actions::Teleport; }		break;
					case 'R': {m_Actions = m_Actions | Actions::Reset; }		break;
					}
				}
				if (pInputEvent->GetDeviceState() == fw::InputEvent::DeviceState::Released) {
					switch (pInputEvent->GetKeyCode()) {
					case 'W': case VK_UP: {m_Actions = m_Actions & ~Actions::Up; }		break;
					case 'A': case VK_LEFT: {m_Actions = m_Actions & ~Actions::Left; }		break;
					case 'S': case VK_DOWN: {m_Actions = m_Actions & ~Actions::Down; }		break;
					case 'D': case VK_RIGHT: {m_Actions = m_Actions & ~Actions::Right; }		break;
					case 'J':  {m_Actions = m_Actions & ~Actions::AddRotY; }		break;
					case 'L':  {m_Actions = m_Actions & ~Actions::LessRotY; }		break;
					case 'I':  {m_Actions = m_Actions & ~Actions::LessRotX; }		break;
					case 'K':  {m_Actions = m_Actions & ~Actions::AddRotX; }		break;
					case 'U':  {m_Actions = m_Actions & ~Actions::Closer; }		break;
					case 'M':  {m_Actions = m_Actions & ~Actions::Further; }		break;
					case VK_SPACE: {m_Actions = m_Actions & ~Actions::Jump; }		break;
					case 'Z': {m_Actions = m_Actions & ~Actions::Teleport; }	break;
					case 'R': {m_Actions = m_Actions & ~Actions::Reset; }	break;
					}
				}
			}
		}
	}

	void VirtualController::UpdateMousePos()
	{
		ImVec2 ImPos = ImGui::GetCursorPos();

		m_MousePos = vec2(ImPos.x, ImPos.y);
			
	}

	vec2 VirtualController::GetMousePos()
	{
		UpdateMousePos();
		return m_MousePos;
	}

	bool VirtualController::IsPressed(Actions action)
	{
		return ((m_Actions & action)!=0);
	}

	void VirtualController::StartFrame()
	{
		m_LastActions = m_Actions;
	}

	bool VirtualController::WasPressed(Actions action)
	{
		return (m_LastActions & action);
	}

	bool VirtualController::WasJustPressed(Actions action)
	{
		//if the lastAction is 0, and the new action is 1
		return(!WasPressed(action) && IsPressed(action));
	}

	bool VirtualController::WasJustReleased(Actions action)
	{
		//if the lastAction was 1, and the new action is 0
		return(WasPressed(action) && !IsPressed(action));
	}


}