#pragma once

#include "CoreHeaders.h"
#include "EventSystem/EventManager.h"

namespace fw {
    class Event;

    class VirtualController : public EventListener
    {
    protected:
        unsigned int m_LastActions = 0;
        unsigned int m_Actions = 0;
    public:
        enum Actions {
            Up =        1 << 0,
            Down =      1 << 1,
            Left =      1 << 2,
            Right =     1 << 3,
            Teleport =  1 << 4,
            Jump =      1 << 5,
            Reset =     1 << 6,
            AddRotY =   1 << 7,
            LessRotY =  1 << 8,
            LessRotX =  1 << 9,
            AddRotX =   1 << 10,
            Closer =    1 << 11,
            Further =   1 << 12,
        };
        VirtualController();
        VirtualController(EventManager* manager);
        virtual ~VirtualController();
        void StartFrame();

        //event managment
        void ReceiveEvents(Event* pEvent);

        //getters
        bool IsPressed(Actions action);
        bool WasJustPressed(Actions action);
        bool WasJustReleased(Actions action);
    protected:
        bool WasPressed(Actions action);
    };
}