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
    int screenWidth = 300;
    int screenHeight = screenWidth;

    InitWindow(screenWidth, screenHeight, "raylib [core] example - basic window");

    double PaddleRadius = screenWidth / 2 - 10;
    double random = rand() % 1;
    Paddle playerPaddle(0.05, 10, 50, PaddleRadius, random);
    Ball gameBall(2, 5, random);

    SetTargetFPS(60);
    int deltaFrames = 0;
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

        DrawRectanglePro(playerPaddle.rec, playerPaddle.recCenter, RAD2DEG * playerPaddle.angle, GREEN);
        Vector2 ballPos;
        ballPos.x = gameBall.position.x;
        ballPos.y = gameBall.position.y;
        Rectangle rec = playerPaddle.rec;
        rec.x = playerPaddle.rec.x - playerPaddle.rec.width / 2;
        rec.y = playerPaddle.rec.y - playerPaddle.rec.height / 2;
        if (gameBall.collidable)
        {
            if (CheckCollisionCircleRec(ballPos, gameBall.size, rec))
            {
                gameBall.collidable = false;
                gameBall.speed += 0.05;
                double ballDir = gameBall.moveDir;
                ballDir = ballDir * RAD2DEG;
                ballDir -= 180;
                if (ballDir < 0) ballDir += 360;
                double angleDiff = abs(ballDir - playerPaddle.GetPaddleNormal() * RAD2DEG);
                ballDir = ballDir + angleDiff * 2;
                gameBall.UpdateMoveDir(ballDir * DEG2RAD);

                DrawRectangle(rec.x, rec.y, rec.width, rec.height, RED);
            }
        }
        else
        {
            deltaFrames++;
            if (deltaFrames >= 15)
            {
                deltaFrames = 0;
                gameBall.collidable = true;
            }
        }
        DrawCircle(gameBall.position.x, gameBall.position.y, gameBall.size, BLUE);

        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------   
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}