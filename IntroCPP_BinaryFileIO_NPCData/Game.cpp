#include "Game.h"
#include "raylib.h"
#include <sstream>

#include <iostream>

Game::Game()
{
    scalePointer = &scalesSaved[0];
    angle = 0;
    MenuInitalisation();
}
void Game::MenuInitalisation()
{
    state = startMenu;
    menuState = 0;
    activePaddleCount = 0;
    activeBallCount = 0;
    // LOAD BUTTONS
    startButton.Init(BUTTONWIDTH, BUTTONHEIGHT, STARTBUTTONX, STARTBUTTONY, STARTBUTTONTEXT);
    quitButton.Init(BUTTONWIDTH, BUTTONHEIGHT, QUITBUTTONX, QUITBUTTONY, QUITBUTTONTEXT);
}
void Game::ModeMenuInitalisation()
{
    menuState = 1;

    //Loading Buttons
    for(int y = 0; y < (double)MODEMENUEXTRAMODES / (double)MODEMENUBUTTONSPERROW; y++)
        for (int x = 0; x <MODEMENUBUTTONSPERROW; x++)
        {
            if (y * MODEMENUBUTTONSPERROW + x >= MODEMENUEXTRAMODES)
                break;
            modeButtons[y * MODEMENUBUTTONSPERROW + x].rec.width = (MODEMENUSIDESPACING - ((MODEMENUBUTTONSPERROW - 1.0) * BUTTONSPACING)) / (double)MODEMENUBUTTONSPERROW;
            modeButtons[y *MODEMENUBUTTONSPERROW + x].rec.height = MODEMENUBUTTONHEIGHT;
            modeButtons[y *MODEMENUBUTTONSPERROW + x].rec.x = MODEMENUBUTTONXOFFSET + x * (modeButtons[y * MODEMENUBUTTONSPERROW + x].rec.width + MODEMENUBUTTONSPACING);
            modeButtons[y *MODEMENUBUTTONSPERROW + x].rec.y = MODEMENUBUTTONYOFFSET + y * (modeButtons[y * MODEMENUBUTTONSPERROW + x].rec.height + MODEMENUBUTTONSPACING);
            if (y *MODEMENUBUTTONSPERROW + x >= modeNameCount)
                modeButtons[y *MODEMENUBUTTONSPERROW + x].name = "TBD";
            else
                modeButtons[y *MODEMENUBUTTONSPERROW + x].name = modeNames[y *MODEMENUBUTTONSPERROW + x];

            modeButtons[y *MODEMENUBUTTONSPERROW + x].nameLength = strlen(modeButtons[y *MODEMENUBUTTONSPERROW + x].name);
        }
}

void Game::GameInitalisation(int mode)
{
    //Scoring and game logic 
    state = playing;
    score = 0;

    //Ball and Paddle setup
    double random = rand() % MAXRANDOMSTARTPOSTION;
    playerPaddle[0].Init(PADDLESPEED, PADDLEWIDTH, PADDLEHEIGHT, SCREENSIZE / 2 - PADDLEPOSOFFSET, random);
    gameBall[0].Init(INITIALBALLSPEED, BALLSIZE, random);

    switch (mode)
    {
    case 1:
        //Small objects
        playerPaddle[0].rec.width /= 2;
        playerPaddle[0].rec.height /= 2;
        gameBall[0].size /= 2;
        playerPaddle[0].SetCorners();
        break;
    case 2:
        //Ring
        for (int i = 1; i < 20; i++)
        {
            playerPaddle[i].Init(playerPaddle[0].speed, playerPaddle[0].rec.width, playerPaddle[0].rec.height, playerPaddle[0].distanceFromCenter, random);
            playerPaddle[i].angle[1] = (18 * i) * DEG2RAD;
            playerPaddle[i].SetCorners();
            activePaddleCount++;
        }
        break;
    case 3:
        //Random ball speed
        randomBallSpeed = true;
        break;
    case 4:
        //Long and close paddles
        playerPaddle[1].Init(playerPaddle[0].speed, playerPaddle[0].rec.width, playerPaddle[0].rec.height, playerPaddle[0].distanceFromCenter, random);
        playerPaddle[1].angle[1] = 180 * DEG2RAD;
        playerPaddle[1].SetCorners();
        activePaddleCount+=1;
        break;
    }

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
    switch (menuState)
    {
    case 0:
        MainMenuUpdate();
        break;
    case 1:
        ModeSelectMenuUpdate();
        break;
    }
}

void Game::MainMenuUpdate()
{
    //Check to see if player presses either button
    //If so, call approprate functions
    if (IsMouseButtonPressed(0))
    {
        if (startButton.Clicked(GetMousePosition()))
        {
            ModeMenuInitalisation();
            return;
        }
        if (quitButton.Clicked(GetMousePosition()))
        {
            exit(0);
            return;
        }
    }
    //Player can change the difficulty by pressing 1 - 5
    if (IsKeyPressed(KEY_ONE))
        scalePointer = &scalesSaved[0];
    if (IsKeyPressed(KEY_TWO))
        scalePointer = &scalesSaved[1];
    if (IsKeyPressed(KEY_THREE))
        scalePointer = &scalesSaved[2];
    if (IsKeyPressed(KEY_FOUR))
        scalePointer = &scalesSaved[3];
    if (IsKeyPressed(KEY_FIVE))
        scalePointer = &scalesSaved[4];

    //An input (ENTER) may be used to start the game also
    if (IsKeyReleased(STARTINPUT))
    {
        GameInitalisation(0);
        return;
    }
    MainMenuDraw();
}
void Game::MainMenuDraw()
{
    BeginDrawing();

    ClearBackground(BLACK);

    //The title moves slowly up and down
        DrawText(TITLETEXT, TITLEXPOS, TITLEYPOS + sin(angle) * TITLEMOVEMENTSCALE, TITLESIZE, RAYWHITE);

    //A red gradient gets more intense as the difficulty increases
    if(*scalePointer == TIER5)
        DrawRectangleGradientV(0, 0, SCREENSIZE, SCREENSIZE, BLANK, DIFF5);
    else if(*scalePointer == TIER4)
        DrawRectangleGradientV(0, 0, SCREENSIZE, SCREENSIZE, BLANK, DIFF4);
    else if (*scalePointer == TIER3)
        DrawRectangleGradientV(0, 0, SCREENSIZE, SCREENSIZE, BLANK, DIFF3);
    else if (*scalePointer == TIER2)
        DrawRectangleGradientV(0, 0, SCREENSIZE, SCREENSIZE, BLANK, DIFF2);
    else
        DrawRectangleGradientV(0, 0, SCREENSIZE, SCREENSIZE, BLANK, BLANK);

    for (int i = 0; i <= 4; i++)
    {
        if (abs(i < *scalePointer))
            DrawRectangle(STARTBUTTONX + i * DIFFTABXMULTIPLIER + DIFFTABXOFFSET, DIFFTABYOFFSET, DIFFTABWIDTH, DIFFTABHEIGHT, WHITE);
        else
            DrawRectangle(STARTBUTTONX + i * DIFFTABXMULTIPLIER + DIFFTABXOFFSET, DIFFTABYOFFSET, DIFFTABWIDTH, DIFFTABHEIGHT, GRAY);
    }

    startButton.Draw();
    quitButton.Draw();

    EndDrawing();
}

void Game::ModeSelectMenuUpdate()
{
    for(int i = 0; i < MODEMENUEXTRAMODES; i++)
        if(IsMouseButtonPressed(0) && modeButtons[i].Clicked(GetMousePosition()))
            GameInitalisation(i);
    ModeSelectMenuDraw();
}
void Game::ModeSelectMenuDraw()
{
    BeginDrawing();

    ClearBackground(BLACK);

    DrawText("CHOOSE A MODE...", SCREENSIZE * 0.034, SCREENSIZE * 0.033, SCREENSIZE * 0.0534, WHITE);

    for (int i = 0; i < MODEMENUEXTRAMODES; i++)
    {
        modeButtons[i].Draw();
    }

    EndDrawing();
}

// PLAYING GAME
void Game::GameUpdate()
{

    for (int p = 0; p <= activePaddleCount; p++)
    {
        //Player input checks
        if (IsKeyDown(MOVEPADDLERIGHT))
            playerPaddle[p].MovePaddle(1, *scalePointer);
        if (IsKeyDown(MOVEPADDLELEFT))
            playerPaddle[p].MovePaddle(0, *scalePointer);
    }

    for (int b = 0; b <= activeBallCount; b++)
    {
        //Moving the ball
        gameBall[b].MoveBall(*scalePointer);

        //Close game upon ball hiting wall
        //Scales with ball size
        if (gameBall[b].position.x <= 0 + gameBall[b].size || gameBall[b].position.x >= SCREENSIZE - gameBall[b].size || gameBall[b].position.y <= 0 + gameBall[b].size || gameBall[b].position.y >= SCREENSIZE - gameBall[b].size)
        {
            angle = 0;
            randomBallSpeed = false;
            state = gameOver;
            return;
        }

        //Ball and paddle collision check
        if (gameBall[b].collidable)
        {
            //Check if the ball passed either of the triangles
            for (int p = 0; p <= activePaddleCount; p++)
                if (CheckCollisionPointTriangle(gameBall[b].position, playerPaddle[p].corners.second.second, playerPaddle[p].corners.first.second, playerPaddle[p].corners.first.first) || CheckCollisionPointTriangle(gameBall[b].position, playerPaddle[p].corners.first.first, playerPaddle[p].corners.second.first, playerPaddle[p].corners.second.second))
                {
                    //Disable ball collisions
                    gameBall[b].collidable = false;
                    //Increase ball speed and score
                    score++;
                    if (score <= BALLSCORELIMIT)
                    {
                        if (!randomBallSpeed)
                            gameBall[b].speed = BALLSPEEDSCALAR * score + INITIALBALLSPEED;
                        else
                            gameBall[b].speed = rand() % BALLMAXSPEED;
                    }
                    //Update the displayed score

                    //Get ball movement direction
                    double ballDir = gameBall[b].moveDir * RAD2DEG;
                    //Reduce the ball movement angle by the player paddle angle
                    //This is done to achieve a neutral calculation start for the ball's new movement
                    //direction.
                    //Basically, we always calculate the next ball position as though the paddle is at
                    //0 degrees.
                    //180 is added to flip the ball's movement angle
                    double newAngle = 180 + (ballDir - (playerPaddle[p].angle[0] + playerPaddle[p].angle[1]) * RAD2DEG);
                    //Angles shouldn't be below 0, so we add 360
                    //^ -135 = 225
                    if (newAngle < 0) newAngle += 360;
                    //Generating a random offset
                    int randomOffset = rand() % RANDOMANGLEADDITION;
                    if ((randomOffset % 2) == 0) randomOffset *= -1;
                    //We take is new angle and reduce 360 by it then add back the player angle from
                    //before, before added the random offset
                    newAngle = 360 - newAngle + ((playerPaddle[p].angle[0] + playerPaddle[p].angle[1]) * RAD2DEG) + randomOffset;
                    //Update the ball's movement direction
                    gameBall[b].UpdateMoveDir(newAngle * DEG2RAD);
                }
        }
        else
        {
            //After a collision, wait a certain number of frames, then enable collisions
            deltaFrames++;
            if (deltaFrames >= BALLCOLISIONCHECKCOOLDOWN)
            {
                deltaFrames = 0;
                gameBall[b].collidable = true;
            }
        }
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
        s = "0" + s;

    const char* pchar = s.c_str();
    DrawText(pchar, SCORETEXTOFFSETX, SCORETEXTOFFSETY, SCORETEXTSIZE, NOTEXACTLYBLACK);

    //Draw player paddles
    for (int p = 0; p <= activePaddleCount; p++)
        playerPaddle[p].Draw();

    //Draw the balls
    for (int b = 0; b <= activeBallCount; b++)
        gameBall[b].Draw();

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
