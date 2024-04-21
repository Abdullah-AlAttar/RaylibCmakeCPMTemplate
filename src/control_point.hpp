#pragma once 

#include <raylib.h>

namespace ser
{
    
    struct ControlPoint
    {
        Vector2 position;
        Color color;
        float radius;
        bool selected = false;
    };
} // namespace ser


