#include "Game.h"
#include "raylib.h"
#include "Paddle.h"
#include "Ball.h"
#include <sstream>

#include <iostream>


void Game::Initalisation()
{

    //Ball and Paddle setup
    PaddleRadius = SCREENSIZE / 2 - PADDLEPOSOFFSET;
    double random = rand() % MAXRANDOMSTARTPOSTION;
    playerPaddle.Init(PADDLESPEED, PADDLEWIDTH, PADDLEHEIGHT, PaddleRadius, random);
    gameBall.Init(INITIALBALLSPEED, BALLSIZE, random);

    //Scoring and game logic 
    score = 0;
    gameOver = false;

    //Used for seeing the number of frames since a given action
    deltaFrames = 0;
}

void Game::Update()
{
    if (!gameOver)
    {
        //Player input checks
        if (IsKeyDown(MOVEPADDLERIGHT))
            playerPaddle.MovePaddle(0);
        if (IsKeyDown(MOVEPADDLELEFT))
            playerPaddle.MovePaddle(1);

        //Moving the ball
        gameBall.MoveBall();

        //Close game upon ball hiting wall
        //Scales with ball size
        if (gameBall.position.x <= 0 + gameBall.size || gameBall.position.x >= SCREENSIZE - gameBall.size || gameBall.position.y <= 0 + gameBall.size || gameBall.position.y >= SCREENSIZE - gameBall.size)
            gameOver = true;
    }
}

void Game::Draw()
{
    //Draw score
    string s = to_string(score);
    if (score < 10)
    {
        s = "0" + s;
    }
    const char* pchar = s.c_str();
    DrawText(pchar, SCORETEXTOFFSETX, SCORETEXTOFFSETY, SCORETEXTSIZE, NOTEXACTLYBLACK);
    if (!gameOver)
    {

        //Draw player paddle
        DrawTriangle(playerPaddle.corners.second.second, playerPaddle.corners.first.second, playerPaddle.corners.first.first, WHITE);
        DrawTriangle(playerPaddle.corners.first.first, playerPaddle.corners.second.first, playerPaddle.corners.second.second, LIGHTGRAY);

        //Ball and paddle collision check
        if (gameBall.collidable)
        {
            //Check if the ball passed either of the triangles
            if (CheckCollisionPointTriangle(gameBall.position, playerPaddle.corners.second.second, playerPaddle.corners.first.second, playerPaddle.corners.first.first) || CheckCollisionPointTriangle(gameBall.position, playerPaddle.corners.first.first, playerPaddle.corners.second.first, playerPaddle.corners.second.second))
            {
                //Disable ball collisions
                gameBall.collidable = false;
                //Increase ball speed and score
                gameBall.speed += BALLSPEEDINCREASE;
                score++;
                //Update the displayed score

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
    }
    else
    {
        DrawText("YOU LOSE", GOTEXTOFFSETX, GOTEXTOFFSETY, GOTEXTSIZE, WHITE);
        if (IsKeyDown(KEY_ENTER))
        {
            gameOver = false;
            Initalisation();
        }
    }
}