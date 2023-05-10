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
    Paddle playerPaddle(0.1, 10, 50, PaddleRadius);
    vector<double> momentum;
    momentum.push_back(0.5);
    momentum.push_back(0.5);
    Ball gameBall(10, 5, rand() % 360);

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

        DrawRectanglePro(playerPaddle.rec, playerPaddle.recCenter, RAD2DEG * playerPaddle.angle, GREEN);
        Vector2 ballPos;
        ballPos.x = gameBall.position.x;
        ballPos.y = gameBall.position.y;
        Rectangle rec = playerPaddle.rec;
        rec.x = playerPaddle.rec.x - playerPaddle.rec.width / 2;
        rec.y = playerPaddle.rec.y - playerPaddle.rec.height / 2;
        if (CheckCollisionCircleRec(ballPos, gameBall.size, rec))
        {

            // https://answers.unity.com/questions/880103/vector-based-pong-ball-bounce-calculations.html
            Vector2 ballVelocity = gameBall.velocity;
            ballVelocity = NormaliseVector(ballVelocity);
            Vector2 playerNormalAsVector;
            playerNormalAsVector.x = cos(playerPaddle.GetPaddleNormal());
            playerNormalAsVector.y = sin(playerPaddle.GetPaddleNormal());
            double dotProd = DotVectors(gameBall.velocity, playerNormalAsVector);

            //double tmpAngle = gameBall.moveDir;
            //tmpAngle = tmpAngle * RAD2DEG;
            //tmpAngle = tmpAngle - 180;
            //if (tmpAngle < 0) tmpAngle += 360;
            //double angleDiff = abs(tmpAngle - playerPaddle.angle);
            //tmpAngle = tmpAngle + angleDiff * 2;
            //gameBall.UpdateMoveDir(tmpAngle);


            DrawRectangle(rec.x, rec.y, rec.width, rec.height, RED);
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

double DotVectors(Vector2 lhs, Vector2 rhs)
{
    return lhs.x * rhs.x + lhs.y * rhs.y;
}
Vector2 NormaliseVector(Vector2 v)
{
    Vector2 v2;
    v2.x = v.x / Magnitude(v);
    v2.y = v.y / Magnitude(v);
    return v2;
}
double Magnitude(Vector2 v)
{
    return sqrt(v.x * v.x + v.y * v.y);
}