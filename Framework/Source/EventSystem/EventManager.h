#pragma once
#include "CoreHeaders.h"
#include "Events.h"


namespace fw {
	//forward declarations

	class GameCore;
	
	class EventListener
	{
	public:
		virtual void ReceiveEvents(Event* pEvent) = 0;
		virtual ~EventListener();
	}; //eventlist class

	class EventManager {
	using EventListnerList = std::vector<EventListener*>;
	
	protected:

		//the queue of events
		std::queue<Event*> m_Queue; 
		
		//vector of event listeners
		//std::vector<EventListener*> m_Listener;

		std::unordered_map<EventType, EventListnerList> m_Listeners; // this is unordered cause it doesn't need to be alphabetical
		
		GameCore* m_pGame;

	public:
		//constructor and destructor
		EventManager(GameCore* core);
		virtual ~EventManager();

		void AddEvent(Event* event);
		void ProcessEvents();

		void AddListener(EventType type, EventListener* pListener);
		void RemoveListener();
	};
}