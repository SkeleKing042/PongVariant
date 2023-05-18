/*******************************************************************************************
*
*   raylib [core] example - Basic window
*
*   Welcome to raylib!
*
*   To test examples, just press F6 and execute raylib_compile_execute script
*   Note that compiled executable is placed in the same folder as .c file
*
*   You can find all basic examples on C:\raylib\raylib\examples folder or
*   raylib official webpage: www.raylib.com
*
*   Enjoy using raylib. :)
*
*   This example has been created using raylib 1.0 (www.raylib.com)
*   raylib is licensed under an unmodified zlib/libpng license (View raylib.h for details)
*
*   Copyright (c) 2014 Ramon Santamaria (@raysan5)
*
********************************************************************************************/

#include "raylib.h"
#include "GameDefines.h"
#include "Game.h"

int main(int argc, char* argv[])
{
    Game mainGame;

    //Initialization
    //Display window setup
    InitWindow(SCREENSIZE, SCREENSIZE, "raylib [core] example - basic window");
    SetTargetFPS(FPS);

    //mainGame.GameInitalisation();

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        // Draw
        BeginDrawing();

        ClearBackground(BLACK);

        mainGame.Update();

        EndDrawing();
    }

    CloseWindow();        // Close window and OpenGL context

    return 0;
}