#include "EventManager.h"
#include "GameCore.h"

namespace fw {
	EventManager::EventManager(GameCore* core)
	{
		m_pGame = core;

	}

	EventManager::~EventManager()
	{
		for (int i = 0; i < m_Queue.size(); i++) {
			delete m_Queue.front();
			m_Queue.pop();
		}
	}

	void EventManager::AddEvent(Event* event)
	{
		m_Queue.push(event);
	}

	void EventManager::ProcessEvents()
	{
		

		while(!m_Queue.empty()) {

			//send events to listeners
		m_pGame->OnEvent(m_Queue.front());

		EventListnerList& list = m_Listeners[m_Queue.front()->GetType()];
		for (EventListener* pListener : list) {
			pListener->ReceiveEvents(m_Queue.front());
		}
		delete m_Queue.front();
		m_Queue.pop();
		}
	}
	void EventManager::AddListener(EventType type, EventListener* pListener)
	{
		m_Listeners[type].push_back(pListener);
	}
	void EventManager::RemoveListener()
	{
	}
	EventListener::~EventListener()
	{
	}
}