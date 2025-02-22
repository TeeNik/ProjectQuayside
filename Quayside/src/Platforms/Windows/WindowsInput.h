#pragma once
#include "Quayside/Input.h"

namespace Quayside
{
    class WindowsInput : public Input
    {
    protected:
        virtual bool IsKeyPressedImpl(int Keycode) override;
    };
}
