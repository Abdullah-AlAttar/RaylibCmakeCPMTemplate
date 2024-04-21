#pragma once 

#include <raylib.h>
#include <vector>
#include <iostream>
#include <control_point.hpp>

namespace ser
{
    
    struct Rectangle
    {
        Vector2 ul ;
        Vector2 lr;
        Vector2 ur;
        Vector2 ll;
        Color color;
        float thickness;
        ControlPoint ulcp; // upper_left
        ControlPoint lrcp; // lower_right
        ControlPoint urcp; // upper_right
        ControlPoint llcp; // lower_left
    };
    Rectangle CreateRectangle(Vector2 ul, Vector2 lr, Color color, float thickness)
    {
        // Contrl pointers slightly offset from the start and end points
        ControlPoint ulcp = {ul, BLACK, 15.0f};
        ControlPoint lrcp = {lr, BLACK, 15.0f};
        ControlPoint urcp = {Vector2{lr.x, ul.y}, BLACK, 15.0f};
        ControlPoint llcp = {Vector2{ul.x, lr.y}, BLACK, 15.0f};
        Rectangle rectangle = {ul, lr, urcp.position, llcp.position, color, thickness, ulcp, lrcp, urcp, llcp};
        return rectangle;
    }
    void DrawRectangle(const Rectangle &rectangle)
    {
        DrawLineEx(rectangle.ul, rectangle.ur, rectangle.thickness, rectangle.color);
        DrawLineEx(rectangle.ur, rectangle.lr, rectangle.thickness, rectangle.color);
        DrawLineEx(rectangle.lr, rectangle.ll, rectangle.thickness, rectangle.color);
        DrawLineEx(rectangle.ll, rectangle.ul, rectangle.thickness, rectangle.color);
        // draw control points
        DrawCircleV(rectangle.ulcp.position, rectangle.ulcp.radius, rectangle.ulcp.color);
        DrawCircleV(rectangle.lrcp.position, rectangle.lrcp.radius, rectangle.lrcp.color);
        DrawCircleV(rectangle.urcp.position, rectangle.urcp.radius, rectangle.urcp.color);
        DrawCircleV(rectangle.llcp.position, rectangle.llcp.radius, rectangle.llcp.color);
    }
    bool IsRectangleSelected(const Rectangle &rectangle)
    {
        return rectangle.ulcp.selected || rectangle.lrcp.selected || rectangle.urcp.selected || rectangle.llcp.selected;
    }
    void UpdateRectangle(Rectangle &rectangle)
    {
        // Update control points
        if (IsMouseButtonDown(MOUSE_LEFT_BUTTON))
        {
            if (!IsRectangleSelected(rectangle)
                && CheckCollisionPointCircle(GetMousePosition(), rectangle.ulcp.position, rectangle.ulcp.radius))
            {
                rectangle.ulcp.selected = true;
            }
            else if  (!IsRectangleSelected(rectangle)
                && CheckCollisionPointCircle(GetMousePosition(), rectangle.lrcp.position, rectangle.lrcp.radius))
            {
                rectangle.lrcp.selected = true;
            }
            else if  (!IsRectangleSelected(rectangle)
                && CheckCollisionPointCircle(GetMousePosition(), rectangle.urcp.position, rectangle.urcp.radius))
            {
                rectangle.urcp.selected = true;
            }
            else if  (!IsRectangleSelected(rectangle)
                && CheckCollisionPointCircle(GetMousePosition(), rectangle.llcp.position, rectangle.llcp.radius))
            {
                rectangle.llcp.selected = true;
            }
        }
        // if mouse is released, unselect all control points
        if (IsMouseButtonReleased(MOUSE_LEFT_BUTTON))
        {
            rectangle.ulcp.selected = false;
            rectangle.lrcp.selected = false;
            rectangle.urcp.selected = false;
            rectangle.llcp.selected = false;
        }
        // Update control points, resizing the rectangle 
        if (rectangle.ulcp.selected)
        {
            rectangle.ulcp.position = GetMousePosition();
            rectangle.llcp.position = Vector2{rectangle.ulcp.position.x, rectangle.llcp.position.y};
            rectangle.urcp.position = Vector2{rectangle.urcp.position.x, rectangle.ulcp.position.y};
            
        }
        if (rectangle.lrcp.selected)
        {
            rectangle.lrcp.position = GetMousePosition();
            rectangle.urcp.position = Vector2{rectangle.lrcp.position.x, rectangle.urcp.position.y};
            rectangle.llcp.position = Vector2{rectangle.llcp.position.x, rectangle.lrcp.position.y};

        }
        if (rectangle.urcp.selected)
        {
            rectangle.urcp.position = GetMousePosition();
            rectangle.lrcp.position = Vector2{rectangle.urcp.position.x, rectangle.lrcp.position.y};
            rectangle.ulcp.position = Vector2{rectangle.ulcp.position.x, rectangle.urcp.position.y};
        }
        if (rectangle.llcp.selected)
        {
            rectangle.llcp.position = GetMousePosition();
            rectangle.ulcp.position = Vector2{rectangle.llcp.position.x, rectangle.ulcp.position.y};
            rectangle.lrcp.position = Vector2{rectangle.lrcp.position.x, rectangle.llcp.position.y};
        }

        // update rectangle
        rectangle.ul = rectangle.ulcp.position;
        rectangle.lr = rectangle.lrcp.position;
        rectangle.ur = rectangle.urcp.position;
        rectangle.ll = rectangle.llcp.position;
    }

} // namespace ser