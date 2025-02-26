#pragma once
#include "Quayside/Core.h"
#include "Quayside/Events/Event.h"

namespace Quayside
{
    class QUAYSIDE_API Layer
    {
    public:
        Layer(const std::string& Name = "Layer");
        virtual ~Layer();

        virtual void OnAttach() {};
        virtual void OnDetach() {};
        virtual void OnUpdate() {};
        virtual void OnEvent(Event& Event) {};
        virtual void OnImGuiRender() {};
        inline const std::string& GetName() { return DebugName; }

    protected:
        std::string DebugName;
    };
}

