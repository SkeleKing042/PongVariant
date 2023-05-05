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
#include "Paddle.h"
#include "Ball.h"
#include <iostream>
#include <string.h>

int main(int argc, char* argv[])
{
    // Initialization
    //--------------------------------------------------------------------------------------
    int screenWidth = 800;
    int screenHeight = 450;

    InitWindow(screenWidth, screenHeight, "raylib [core] example - basic window");

    Paddle playerPaddle(0.1, 10, 50);
    int PaddleRadius = 200;
    vector<double> momentum;
    momentum.push_back(0.5);
    momentum.push_back(0.5);
    Ball gameBall(10, 5, momentum);   

    SetTargetFPS(60);
    //--------------------------------------------------------------------------------------
    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        if (IsKeyDown(KEY_UP))
            playerPaddle.MovePaddle(0);
        if (IsKeyDown(KEY_DOWN))
            playerPaddle.MovePaddle(1);

        gameBall.MoveBall();
        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

        ClearBackground(BLACK);

        //cout << "ANGLE: " << playerPaddle.angle << endl;
        Rectangle rec;
        Vector2 recPos;
        rec.x = screenWidth / 2 + cos(playerPaddle.angle) * PaddleRadius;
        rec.y = screenHeight / 2 + sin(playerPaddle.angle) * PaddleRadius;
        rec.width = playerPaddle.size.first;
        rec.height = playerPaddle.size.second;
        recPos.x = playerPaddle.size.first / 2;
        recPos.y = playerPaddle.size.second / 2;
        DrawRectanglePro(rec, recPos, RAD2DEG * playerPaddle.angle, GREEN);
        /*DrawLine(playerPaddle.corners[0].first + screenWidth / 2 + cos(playerPaddle.angle) * PaddleRadius,
            playerPaddle.corners[0].second + screenHeight / 2 + sin(playerPaddle.angle) * PaddleRadius,
            playerPaddle.corners[1].first + screenWidth / 2 + cos(playerPaddle.angle) * PaddleRadius,
            playerPaddle.corners[1].second + screenHeight / 2 + sin(playerPaddle.angle) * PaddleRadius, RED);
        //DrawCircle(, 1, RED);
        DrawRectangleLines(screenWidth / 2 + cos(playerPaddle.angle) * PaddleRadius, screenHeight / 2 + sin(playerPaddle.angle) * PaddleRadius, 10, 50, WHITE);*/
        DrawCircle(gameBall.position[0], gameBall.position[1], gameBall.size, BLUE);

        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------   
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}