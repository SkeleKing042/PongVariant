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
#include "GameDefines.h"
#include <iostream>
#include <string.h>
#include <sstream>

int main(int argc, char* argv[])
{
    //Initialization
    //Display window setup
    int screenWidth = SCREENSIZE;
    int screenHeight = screenWidth;
    InitWindow(screenWidth, screenHeight, "raylib [core] example - basic window");
    SetTargetFPS(FPS);
    int deltaFrames = 0;

    //Ball and Paddle setup
    double PaddleRadius = screenWidth / 2 - PADDLEPOSOFFSET;
    double random = rand() % MAXRANDOMSTARTPOSTION;
    Paddle playerPaddle(PADDLESPEED, PADDLEWIDTH, PADDLEHEIGHT, PaddleRadius, random);
    Ball gameBall(INITIALBALLSPEED, BALLSIZE, random);

    //score
    int score = 0;

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        //Player input checks
        if (IsKeyDown(KEY_UP) || GetMouseWheelMove() > 0 || IsKeyDown(KEY_RIGHT))
            playerPaddle.MovePaddle(0);
        if (IsKeyDown(KEY_DOWN) || GetMouseWheelMove() < 0 || IsKeyDown(KEY_LEFT))
            playerPaddle.MovePaddle(1);

        //Moving the ball
        gameBall.MoveBall();


        // Draw
        BeginDrawing();


        ClearBackground(BLACK);

        //Draw the score
        string s = to_string(score);
        char const* pchar = s.c_str();
        DrawText(pchar, TEXTOFFSETX, TEXTOFFSETY, TEXTSIZE, DARKGRAY);

        //Draw player paddle
        DrawRectanglePro(playerPaddle.rec, playerPaddle.recCenter, RAD2DEG * playerPaddle.angle, WHITE);

        //Finding player center
        Vector2 playerCenter;
        playerCenter.x = screenWidth / 2 + cos(playerPaddle.angle) * PaddleRadius;
        playerCenter.y = screenHeight / 2 + sin(playerPaddle.angle) * PaddleRadius;

        //Ball and paddle collision check
        if (gameBall.collidable)
        {
            if (CheckCollisionCircles(gameBall.position, gameBall.size, playerCenter, playerPaddle.size.second / 3))
            {
                //Disable ball collisions
                gameBall.collidable = false;
                //Increase ball speed and score
                gameBall.speed += BALLSPEEDINCREASE;
                score++;

                //Get ball movement direction
                double ballDir = gameBall.moveDir * RAD2DEG;
                //Reduce the ball movement angle by the player paddle angle
                //This is done to achieve a neutral calculation start for the ball's new movement
                //direction.
                //Basically, we always calculate the next ball position as though the paddle is at
                //0 degrees.
                //180 is added to flip the ball's movement angle
                double newAngle = 180 + (ballDir - playerPaddle.angle * RAD2DEG);
                //Angles shouldn't be below 0, so we add 360
                //^ -135 = 225
                if (newAngle < 0) newAngle += 360;
                //Generating a random offset
                int randomOffset = rand() % RANDOMANGLEADDITION;
                if ((randomOffset % 2) == 0) randomOffset *= -1;
                //We take is new angle and reduce 360 by it then add back the player angle from
                //before, before added the random offset
                newAngle = 360 - newAngle + (playerPaddle.angle * RAD2DEG) + randomOffset;
                //Update the ball's movement direction
                gameBall.UpdateMoveDir(newAngle * DEG2RAD);
            }
        }
        else
        {
            //After a collision, wait a certain number of frames, then enable collisions
            deltaFrames++;
            if (deltaFrames >= BALLCOLISIONCHECKCOOLDOWN)
            {
                deltaFrames = 0;
                gameBall.collidable = true;
            }
        }
        
        //Draw the ball
        DrawCircleV(gameBall.position, gameBall.size, WHITE);


        EndDrawing();
    }

    CloseWindow();        // Close window and OpenGL context

    return 0;
}