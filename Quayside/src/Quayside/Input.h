#pragma once
#include "Quayside/Core.h"

namespace Quayside
{
    class QUAYSIDE_API Input
    {
    public:
        virtual ~Input() = default;
        
        inline static bool IsKeyPressed(int Keycode) { return Instance->IsKeyPressedImpl(Keycode); }
        inline static bool IsMouseButtonPressed(int Button) { return Instance->IsMouseButtonPressedImpl(Button); } 
        inline static std::pair<float, float> GetMousePosition() { return Instance->GetMousePositionImpl(); } 
        inline static float GetMouseX() { return Instance->GetMouseXImpl(); } 
        inline static float GetMouseY() { return Instance->GetMouseYImpl(); } 

    protected:
        virtual bool IsKeyPressedImpl(int Keycode) = 0;
        virtual bool IsMouseButtonPressedImpl(int Button) = 0;
        virtual std::pair<float, float> GetMousePositionImpl() = 0;
        virtual float GetMouseXImpl() = 0;
        virtual float GetMouseYImpl() = 0;
        
    private:
        static Input* Instance;
    };
}
