
#pragma once


#include <control_point.hpp>

#include <vector>
#include <iostream>
namespace ser
{
    



struct Line
{
    Vector2 start;
    Vector2 end;
    Color color;
    float thickness;
    ControlPoint cp1;
    ControlPoint cp2;
};

Line CreateLine(Vector2 start, Vector2 end, Color color, float thickness)
{  
    // Contrl pointers slightly offset from the start and end points
    ControlPoint cp1 = {start, BLACK, 15.0f};
    ControlPoint cp2 = {end, BLACK, 15.0f};
    Line line = {start, end, color, thickness, cp1, cp2};
    return line;
}


void DrawLine(const Line &line)
{
    DrawLineEx(line.start, line.end, line.thickness, line.color);

    // draw control points
    DrawCircleV(line.cp1.position, line.cp1.radius, line.cp1.color);
    DrawCircleV(line.cp2.position, line.cp2.radius, line.cp2.color);
}

void UpdateLine(Line &line)
{
    // Update control points
    if (IsMouseButtonDown(MOUSE_LEFT_BUTTON))
    {
        if (!line.cp2.selected &&
            CheckCollisionPointCircle(GetMousePosition(), line.cp1.position, line.cp1.radius))
        {
            line.cp1.selected = true;
        }
        if (!line.cp1.selected &&
            CheckCollisionPointCircle(GetMousePosition(), line.cp2.position, line.cp2.radius))
        {
            line.cp2.selected = true;
        }
    }
    // if mouse is released, unselect all control points
    if (IsMouseButtonReleased(MOUSE_LEFT_BUTTON))
    {
        line.cp1.selected = false;
        line.cp2.selected = false;
    }
    if (line.cp1.selected)
    {
        line.cp1.position = GetMousePosition();
    }
    if (line.cp2.selected)
    {
        line.cp2.position = GetMousePosition();
    }
    // Update line start and end points
    line.start = line.cp1.position;
    line.end = line.cp2.position;
}


} // namespace ser