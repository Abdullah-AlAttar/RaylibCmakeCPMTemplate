#include "ser.hpp"


int main(void)
{
    // Initialization
    //--------------------------------------------------------------------------------------
    const int screenWidth = 800;
    const int screenHeight = 800;

    InitWindow(screenWidth, screenHeight, "raylib [core] example - basic window");

    SetTargetFPS(120);               // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------
    ser::Line line = ser::CreateLine({100, 100}, {200, 200}, RED, 5.0f);
    // Main game loop
    ser::Rectangle rectangle = ser::CreateRectangle({300, 300}, {400, 400}, RED, 5.0f);
    ser::Circle circle = ser::CreateCircle({500, 500}, 50, RED, 5.0f);
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        // Update
        //----------------------------------------------------------------------------------
        // TODO: Update your variables here
        //----------------------------------------------------------------------------------
        ser::UpdateLine(line);
        ser::UpdateRectangle(rectangle);
        ser::UpdateCircle(circle);
        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

            ClearBackground(RAYWHITE);
            ser::DrawLine(line);
            ser::DrawRectangle(rectangle);
            ser::DrawCircle(circle);
        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}