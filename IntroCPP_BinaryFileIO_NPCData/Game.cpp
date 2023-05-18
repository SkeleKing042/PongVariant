#include "Game.h"
#include "raylib.h"
#include <sstream>

#include <iostream>

Game::Game()
{
    angle = 0;
    MenuInitalisation();
}
void Game::MenuInitalisation()
{
    state = startMenu;

    // LOAD BUTTONS
    startButton.Init(BUTTONWIDTH, BUTTONHEIGHT, STARTBUTTONX, STARTBUTTONY);
    quitButton.Init(BUTTONWIDTH, BUTTONHEIGHT, QUITBUTTONX, QUITBUTTONY);
}

void Game::GameInitalisation()
{
    //Scoring and game logic 
    state = playing;
    score = 0;

    //Ball and Paddle setup
    double random = rand() % MAXRANDOMSTARTPOSTION;
    playerPaddle.Init(PADDLESPEED, PADDLEWIDTH, PADDLEHEIGHT, SCREENSIZE / 2 - PADDLEPOSOFFSET, random);
    gameBall.Init(INITIALBALLSPEED, BALLSIZE, random);

    //Used for seeing the number of frames since a given action
    deltaFrames = 0;
}

void Game::Update()
{
    //Check what the game's current state is and calls the approprate update function
    switch (state)
    {
    case startMenu:
        MenuStateUpdate();
        break;
    case playing:
        GameUpdate();
        break;
    case gameOver:
        EndGameUpdate();
        break;
    }

    angle += 0.04;
    //Resets angle when reaching 0 or 360 degrees 
    if (angle > PI * 2)
        angle -= PI * 2;
    if (angle < 0)
        angle += PI * 2;
}

// IN MENUS //
void Game::MenuStateUpdate()
{
    //Check to see if player presses either button
    //If so, call approprate functions
    if (IsMouseButtonPressed(0))
    {
        if (startButton.Clicked(GetMousePosition()))
        {
            GameInitalisation();
            return;
        }
        if (quitButton.Clicked(GetMousePosition()))
        {
            exit(0);
            return;
        }
    }
    //An input (ENTER) may be used to start the game also
    if (IsKeyReleased(STARTINPUT))
    {
        GameInitalisation();
        return;
    }
    MenuDraw();
}
void Game::MenuDraw()
{
    BeginDrawing();

    ClearBackground(BLACK);

    //The title moves slowly up and down
    DrawText(TITLETEXT, TITLEXPOS, TITLEYPOS + sin(angle) * TITLEMOVEMENTSCALE, TITLESIZE, RAYWHITE);

    DrawRectangleRec(startButton.rec, RAYWHITE);
    DrawRectangleLinesEx(startButton.rec, 2, GRAY);
    DrawText(STARTBUTTONTEXT, startButton.rec.x + startButton.rec.width / 2 - MENUTEXTSIZE / 2.0 * STARTBUTTONCHARS / 2.0, startButton.rec.y + startButton.rec.height / 2.0 - MENUTEXTSIZE / 2.0, MENUTEXTSIZE, BLACK);

    DrawRectangleRec(quitButton.rec, RAYWHITE);
    DrawRectangleLinesEx(quitButton.rec, 2, GRAY);
    DrawText(QUITBUTTONTEXT, quitButton.rec.x + quitButton.rec.width / 2 - MENUTEXTSIZE / 2.0 * QUITBUTTONCHARS / 2.0, quitButton.rec.y + quitButton.rec.height / 2.0 - MENUTEXTSIZE / 2.0, MENUTEXTSIZE, BLACK);

    EndDrawing();
}

// PLAYING GAME
void Game::GameUpdate()
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
    {
        angle = 0; 
        state = gameOver;
        return;
    }

    GameDraw();
}
void Game::GameDraw()
{
    BeginDrawing();

    ClearBackground(BLACK);

    //Draw score
    string s = to_string(score);
    if (score < 10)
    {
        s = "0" + s;
    }
    const char* pchar = s.c_str();
    DrawText(pchar, SCORETEXTOFFSETX, SCORETEXTOFFSETY, SCORETEXTSIZE, NOTEXACTLYBLACK);

    //Draw player paddle
    DrawTriangle(playerPaddle.corners.second.second, playerPaddle.corners.first.second, playerPaddle.corners.first.first, WHITE);
    DrawTriangle(playerPaddle.corners.first.first, playerPaddle.corners.second.first, playerPaddle.corners.second.second, LIGHTGRAY);

    //Draw the ball
    DrawCircleV(gameBall.position, gameBall.size, WHITE);

    //Ball and paddle collision check
    if (gameBall.collidable)
    {
        //Check if the ball passed either of the triangles
        if (CheckCollisionPointTriangle(gameBall.position, playerPaddle.corners.second.second, playerPaddle.corners.first.second, playerPaddle.corners.first.first) || CheckCollisionPointTriangle(gameBall.position, playerPaddle.corners.first.first, playerPaddle.corners.second.first, playerPaddle.corners.second.second))
        {
            //Disable ball collisions
            gameBall.collidable = false;
            //Increase ball speed and score
            score++;
            if (score <= BALLSCORELIMIT)
            {
                gameBall.speed = BALLSPEEDSCALAR * score + INITIALBALLSPEED;
            }
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

    EndDrawing();
}

//END GAME
void Game::EndGameUpdate()
{
    //Check to see if player wants to continue
    if (IsKeyReleased(NEXTKEY))
    {
        MenuInitalisation();
    }

    EndGameDraw();
}
void Game::EndGameDraw()
{
    BeginDrawing();

    ClearBackground(BLACK);

    //Draw score
    string s = to_string(score);
    if (score < 10)
    {
        s = "0" + s;
    }
    const char* pchar = s.c_str();

    //Creates a grid of the player's score which moves in and out from the center in a sort of
    //breathing motion
    for (int y = -3; y <= 3; y++)
    {
        for (int x = -2; x <= 2; x++)
        {
            DrawText(pchar, (SCREENSIZE / 2 - GOTEXTSIZE / 2) + (GOTEXTSIZE + GOSCORESPACING) * x + cos(angle) * x, GOTEXTOFFSETY + (GOTEXTSIZE - GOSCORESPACING) * y + sin(angle) * y, GOTEXTSIZE, DEEPERRED);
            DrawText(pchar, (SCREENSIZE / 2 - GOTEXTSIZE / 2) + (GOTEXTSIZE + GOSCORESPACING) * x + cos(angle) * x * GOSCOREMOVEMENTMULTIPLIER, GOTEXTOFFSETY + (GOTEXTSIZE - GOSCORESPACING)* y + sin(angle) * y * GOSCOREMOVEMENTMULTIPLIER, GOTEXTSIZE, DEEPRED);
        }
    }
    //Display losing text over this grid
    DrawText("YOU LOSE", GOTEXTOFFSETX, GOTEXTOFFSETY, GOTEXTSIZE, RAYWHITE);

    EndDrawing();
}
