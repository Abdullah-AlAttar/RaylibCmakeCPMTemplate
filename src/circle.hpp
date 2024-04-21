#pragma once

#include <raylib.h>
#include <raymath.h>

#include <control_point.hpp>


namespace ser
{
    struct Circle
    {
        Vector2 center;
        float radius_h;
        float radius_v;
        Color color;
        float thickness;
        // circle control points
        ControlPoint ulcp; // upper_left
        ControlPoint lrcp; // lower_right
        ControlPoint urcp; // upper_right
        ControlPoint llcp; // lower_left
    };

    Circle CreateCircle(Vector2 center, float radius, Color color, float thickness)
    {
        // Contrl pointers slightly offset from the start and end points
        ControlPoint ulcp = {Vector2{center.x - radius, center.y - radius}, BLACK, 5.0f};
        ControlPoint lrcp = {Vector2{center.x + radius, center.y + radius}, BLACK, 5.0f};
        ControlPoint urcp = {Vector2{center.x + radius, center.y - radius}, BLACK, 5.0f};
        ControlPoint llcp = {Vector2{center.x - radius, center.y + radius}, BLACK, 5.0f};
        Circle circle = {center, radius, radius, color, thickness, ulcp, lrcp, urcp, llcp};
        return circle;
    }

    void DrawCircle(const Circle &circle)
    {
        // draw circle outline, with thickness
        DrawEllipseLines(circle.center.x, circle.center.y, circle.radius_h, circle.radius_v, circle.color);
        // draw control points
        DrawCircleV(circle.ulcp.position, circle.ulcp.radius, circle.ulcp.color);
        DrawCircleV(circle.lrcp.position, circle.lrcp.radius, circle.lrcp.color);
        DrawCircleV(circle.urcp.position, circle.urcp.radius, circle.urcp.color);
        DrawCircleV(circle.llcp.position, circle.llcp.radius, circle.llcp.color);
    }
    bool IsCircleSelected(const Circle &circle)
    {
        return circle.ulcp.selected || circle.lrcp.selected || circle.urcp.selected || circle.llcp.selected;
    }
    void UpdateCircle(Circle &circle)
    {
        // Update control points
        if (IsMouseButtonDown(MOUSE_LEFT_BUTTON))
        {
            if (!IsCircleSelected(circle)
                && CheckCollisionPointCircle(GetMousePosition(), circle.ulcp.position, circle.ulcp.radius))
            {
                circle.ulcp.selected = true;
            }
            else if  (!IsCircleSelected(circle)
                && CheckCollisionPointCircle(GetMousePosition(), circle.lrcp.position, circle.lrcp.radius))
            {
                circle.lrcp.selected = true;
            }
            else if  (!IsCircleSelected(circle)
                && CheckCollisionPointCircle(GetMousePosition(), circle.urcp.position, circle.urcp.radius))
            {
                circle.urcp.selected = true;
            }
            else if  (!IsCircleSelected(circle)
                && CheckCollisionPointCircle(GetMousePosition(), circle.llcp.position, circle.llcp.radius))
            {
                circle.llcp.selected = true;
            }
        }

        if (IsMouseButtonReleased(MOUSE_LEFT_BUTTON))
        {
            circle.ulcp.selected = false;
            circle.lrcp.selected = false;
            circle.urcp.selected = false;
            circle.llcp.selected = false;
        }
        // Update control points
        if (circle.ulcp.selected)
        {
            circle.ulcp.position = GetMousePosition();
        }
        else if (circle.lrcp.selected)
        {
            circle.lrcp.position = GetMousePosition();
        }
        else if (circle.urcp.selected)
        {
            circle.urcp.position = GetMousePosition();
        }
        else if (circle.llcp.selected)
        {
            circle.llcp.position = GetMousePosition();
        }

       if (circle.ulcp.selected)
        {
            circle.ulcp.position = GetMousePosition();
            circle.llcp.position = Vector2{circle.ulcp.position.x, circle.llcp.position.y};
            circle.urcp.position = Vector2{circle.urcp.position.x, circle.ulcp.position.y};
            
        }
        if (circle.lrcp.selected)
        {
            circle.lrcp.position = GetMousePosition();
            circle.urcp.position = Vector2{circle.lrcp.position.x, circle.urcp.position.y};
            circle.llcp.position = Vector2{circle.llcp.position.x, circle.lrcp.position.y};

        }
        if (circle.urcp.selected)
        {
            circle.urcp.position = GetMousePosition();
            circle.lrcp.position = Vector2{circle.urcp.position.x, circle.lrcp.position.y};
            circle.ulcp.position = Vector2{circle.ulcp.position.x, circle.urcp.position.y};
        }
        if (circle.llcp.selected)
        {
            circle.llcp.position = GetMousePosition();
            circle.ulcp.position = Vector2{circle.llcp.position.x, circle.ulcp.position.y};
            circle.lrcp.position = Vector2{circle.lrcp.position.x, circle.llcp.position.y};
        }

        if (IsCircleSelected(circle))
        {
            // center should be the rectangle center
            Vector2 center;
            center.x = (circle.ulcp.position.x + circle.lrcp.position.x) / 2.f;
            center.y = (circle.ulcp.position.y + circle.lrcp.position.y) / 2.f;
            circle.center = center;
            // circle radius should be the distance from the center to the center point of the line segment
            Vector2 center_of_left_segment = Vector2{(circle.ulcp.position.x + circle.llcp.position.x) / 2.f, (circle.ulcp.position.y + circle.llcp.position.y) / 2.f};
            circle.radius_h = Vector2Distance(center, center_of_left_segment);
            Vector2 center_of_top_segment = Vector2{(circle.ulcp.position.x + circle.urcp.position.x) / 2.f, (circle.ulcp.position.y + circle.urcp.position.y) / 2.f};
            circle.radius_v = Vector2Distance(center, center_of_top_segment);

        }

    }
} // namespace ser