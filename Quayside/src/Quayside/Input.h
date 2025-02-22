#pragma once
#include "Quayside/Core.h"

namespace Quayside
{
    class QUAYSIDE_API Input
    {
    public:
        static bool IsKeyPressed(int Keycode) { return Instance->IsKeyPressedImpl(Keycode); }

    protected:
        virtual bool IsKeyPressedImpl(int Keycode) = 0;
        
    private:
        static Input* Instance;
    };
}
