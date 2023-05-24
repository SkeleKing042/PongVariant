#include "Game.h"
#include "raylib.h"
#include <sstream>

#include <iostream>

Game::Game()
{
    _scalePointer = &_scalesSaved[0];
    _angle = 0;
    MenuInitalisation();
}
void Game::MenuInitalisation()
{
    _state = startMenu;
    _menuState = 0;
    _activePaddleCount = 0;
    _activeBallCount = 0;
    // LOAD BUTTONS
    _startButton.Init(BUTTONWIDTH, BUTTONHEIGHT, STARTBUTTONX, STARTBUTTONY, STARTBUTTONTEXT);
    _quitButton.Init(BUTTONWIDTH, BUTTONHEIGHT, QUITBUTTONX, QUITBUTTONY, QUITBUTTONTEXT);
}
void Game::ModeMenuInitalisation()
{
    _menuState = 1;

    //Loading Buttons
    for(int y = 0; y < (double)MODEMENUEXTRAMODES / (double)MODEMENUBUTTONSPERROW; y++)
        for (int x = 0; x <MODEMENUBUTTONSPERROW; x++)
        {
            if (y * MODEMENUBUTTONSPERROW + x >= MODEMENUEXTRAMODES)
                break;
            _modeButtons[y * MODEMENUBUTTONSPERROW + x]._rec.width = (MODEMENUSIDESPACING - ((MODEMENUBUTTONSPERROW - 1.0) * BUTTONSPACING)) / (double)MODEMENUBUTTONSPERROW;
            _modeButtons[y *MODEMENUBUTTONSPERROW + x]._rec.height = MODEMENUBUTTONHEIGHT;
            _modeButtons[y *MODEMENUBUTTONSPERROW + x]._rec.x = MODEMENUBUTTONXOFFSET + x * (_modeButtons[y * MODEMENUBUTTONSPERROW + x]._rec.width + MODEMENUBUTTONSPACING);
            _modeButtons[y *MODEMENUBUTTONSPERROW + x]._rec.y = MODEMENUBUTTONYOFFSET + y * (_modeButtons[y * MODEMENUBUTTONSPERROW + x]._rec.height + MODEMENUBUTTONSPACING);
            if (y *MODEMENUBUTTONSPERROW + x >= _modeNameCount)
                _modeButtons[y *MODEMENUBUTTONSPERROW + x]._name = "TBD";
            else
                _modeButtons[y *MODEMENUBUTTONSPERROW + x]._name = _modeNames[y *MODEMENUBUTTONSPERROW + x];

            _modeButtons[y *MODEMENUBUTTONSPERROW + x]._nameLength = strlen(_modeButtons[y *MODEMENUBUTTONSPERROW + x]._name);
        }
    _returnButton.Init(BUTTONWIDTH, BUTTONHEIGHT, SCREENSIZE - BUTTONWIDTH - BUTTONSPACING, SCREENSIZE - BUTTONHEIGHT - BUTTONSPACING, "RETURN");
}

void Game::GameInitalisation(int mode)
{
    //Scoring and game logic 
    _state = playing;
    _score = 0;

    //Ball and Paddle setup
    double random = rand() % MAXRANDOMSTARTPOSTION;
    _playerPaddle[0].Init(PADDLESPEED, PADDLEWIDTH, PADDLEHEIGHT, SCREENSIZE / 2 - PADDLEPOSOFFSET, random);
    _gameBall[0].Init(INITIALBALLSPEED, BALLSIZE, random);

    switch (mode)
    {
    case 1:
        //Small objects
        _playerPaddle[0]._rec.width /= 2;
        _playerPaddle[0]._rec.height /= 2;
        _gameBall[0]._size /= 2;
        _playerPaddle[0].SetCorners();
        break;
    case 2:
        //Ring
        for (int i = 1; i < 20; i++)
        {
            _playerPaddle[i].Init(_playerPaddle[0]._speed, _playerPaddle[0]._rec.width, _playerPaddle[0]._rec.height, _playerPaddle[0]._distanceFromCenter, random);
            _playerPaddle[i]._angle[1] = (18 * i) * DEG2RAD;
            _playerPaddle[i].SetCorners();
            _activePaddleCount++;
        }
        break;
    case 3:
        //Random ball speed
        _randomBallSpeed = true;
        break;
    case 4:
        //Long and close paddles
        _playerPaddle[1].Init(_playerPaddle[0]._speed, _playerPaddle[0]._rec.width, _playerPaddle[0]._rec.height, _playerPaddle[0]._distanceFromCenter, random);
        _playerPaddle[1]._angle[1] = 180 * DEG2RAD;
        _playerPaddle[1].SetCorners();
        _activePaddleCount+=1;
        break;
    case 5:
        //PowerUps
        _spawnPowerUps = true;
        _setPower = new PowerUp{};
        break;
    }

    //Used for seeing the number of frames since a given action
    _deltaFrames = 0;
}

void Game::Update()
{
    //Check what the game's current state is and calls the approprate update function
    switch (_state)
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

    _angle += 0.04;
    //Resets angle when reaching 0 or 360 degrees 
    if (_angle > PI * 2)
        _angle -= PI * 2;
    if (_angle < 0)
        _angle += PI * 2;
}

// IN MENUS //
void Game::MenuStateUpdate()
{
    switch (_menuState)
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
        if (_startButton.Clicked(GetMousePosition()))
        {
            ModeMenuInitalisation();
            return;
        }
        if (_quitButton.Clicked(GetMousePosition()))
        {
            exit(0);
            return;
        }
    }
    //Player can change the difficulty by pressing 1 - 5
    if (IsKeyPressed(KEY_ONE))
        _scalePointer = &_scalesSaved[0];
    else if (IsKeyPressed(KEY_TWO))
        _scalePointer = &_scalesSaved[1];
    else if (IsKeyPressed(KEY_THREE))
        _scalePointer = &_scalesSaved[2];
    else if (IsKeyPressed(KEY_FOUR))
        _scalePointer = &_scalesSaved[3];
    else if (IsKeyPressed(KEY_FIVE))
        _scalePointer = &_scalesSaved[4];

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
        DrawText(TITLETEXT, TITLEXPOS, TITLEYPOS + sin(_angle) * TITLEMOVEMENTSCALE, TITLESIZE, RAYWHITE);

    //A red gradient gets more intense as the difficulty increases
    if(*_scalePointer == TIER5)
        DrawRectangleGradientV(0, 0, SCREENSIZE, SCREENSIZE, BLANK, DIFF5);
    else if(*_scalePointer == TIER4)
        DrawRectangleGradientV(0, 0, SCREENSIZE, SCREENSIZE, BLANK, DIFF4);
    else if (*_scalePointer == TIER3)
        DrawRectangleGradientV(0, 0, SCREENSIZE, SCREENSIZE, BLANK, DIFF3);
    else if (*_scalePointer == TIER2)
        DrawRectangleGradientV(0, 0, SCREENSIZE, SCREENSIZE, BLANK, DIFF2);
    else
        DrawRectangleGradientV(0, 0, SCREENSIZE, SCREENSIZE, BLANK, BLANK);

    for (int i = 0; i <= 4; i++)
    {
        if (abs(i < *_scalePointer))
            DrawRectangle(STARTBUTTONX + i * DIFFTABXMULTIPLIER + DIFFTABXOFFSET, DIFFTABYOFFSET, DIFFTABWIDTH, DIFFTABHEIGHT, WHITE);
        else
            DrawRectangle(STARTBUTTONX + i * DIFFTABXMULTIPLIER + DIFFTABXOFFSET, DIFFTABYOFFSET, DIFFTABWIDTH, DIFFTABHEIGHT, GRAY);
    }

    _startButton.Draw();
    _quitButton.Draw();

    EndDrawing();
}

void Game::ModeSelectMenuUpdate()
{
    if (IsMouseButtonPressed(0))
    {
        for (int i = 0; i < MODEMENUEXTRAMODES; i++)
            if (_modeButtons[i].Clicked(GetMousePosition()))
            {
                GameInitalisation(i);
            }
        if (_returnButton.Clicked(GetMousePosition()))
        {
            _menuState = 0;
        }
    }

    ModeSelectMenuDraw();
}
void Game::ModeSelectMenuDraw()
{
    BeginDrawing();

    ClearBackground(BLACK);

    DrawText("*- CHOOSE A MODE -*", SCREENSIZE * 0.034, SCREENSIZE * 0.033, SCREENSIZE * 0.0534, WHITE);

    for (int i = 0; i < MODEMENUEXTRAMODES; i++)
    {
        _modeButtons[i].Draw();
    }

    _returnButton.Draw();

    EndDrawing();
}

// PLAYING GAME
void Game::GameUpdate()
{

    for (int p = 0; p <= _activePaddleCount; p++)
    {
        //Player input checks
        if (IsKeyDown(MOVEPADDLERIGHT))
            _playerPaddle[p].MovePaddle(1, *_scalePointer);
        if (IsKeyDown(MOVEPADDLELEFT))
            _playerPaddle[p].MovePaddle(0, *_scalePointer);
    }

    for (int b = 0; b <= _activeBallCount; b++)
    {
        //Moving the ball
        _gameBall[b].MoveBall(*_scalePointer * _timeScale);

        //Close game upon ball hiting wall
        //Scales with ball size
        if (_gameBall[b]._position.x <= 0 + _gameBall[b]._size || _gameBall[b]._position.x >= SCREENSIZE - _gameBall[b]._size || _gameBall[b]._position.y <= 0 + _gameBall[b]._size || _gameBall[b]._position.y >= SCREENSIZE - _gameBall[b]._size)
        {
            _angle = 0;
            _randomBallSpeed = false;
            _state = gameOver;
            return;
        }

        //Ball and paddle collision check
        if (_gameBall[b]._collidable)
        {
            //Check if the ball passed either of the triangles
            for (int p = 0; p <= _activePaddleCount; p++)
                if (CheckCollisionPointTriangle(_gameBall[b]._position, _playerPaddle[p]._corners.second.second, _playerPaddle[p]._corners.first.second, _playerPaddle[p]._corners.first.first) || CheckCollisionPointTriangle(_gameBall[b]._position, _playerPaddle[p]._corners.first.first, _playerPaddle[p]._corners.second.first, _playerPaddle[p]._corners.second.second))
                {
                    //Disable ball collisions
                    _gameBall[b]._collidable = false;
                    //Increase ball speed and score
                    _score++;
                    if (_score <= BALLSCORELIMIT)
                    {
                        if (!_randomBallSpeed)
                            _gameBall[b]._speed = BALLSPEEDSCALAR * _score + INITIALBALLSPEED;
                        else
                            _gameBall[b]._speed = rand() % BALLMAXSPEED;
                    }
                    //Update the displayed score

                    //Get ball movement direction
                    double ballDir = _gameBall[b]._moveDir * RAD2DEG;
                    //Reduce the ball movement angle by the player paddle angle
                    //This is done to achieve a neutral calculation start for the ball's new movement
                    //direction.
                    //Basically, we always calculate the next ball position as though the paddle is at
                    //0 degrees.
                    //180 is added to flip the ball's movement angle
                    double newAngle = 180 + (ballDir - (_playerPaddle[p]._angle[0] + _playerPaddle[p]._angle[1]) * RAD2DEG);
                    //Angles shouldn't be below 0, so we add 360
                    //^ -135 = 225
                    if (newAngle < 0) newAngle += 360;
                    //Generating a random offset
                    int randomOffset = rand() % RANDOMANGLEADDITION;
                    if ((randomOffset % 2) == 0) randomOffset *= -1;
                    //We take is new angle and reduce 360 by it then add back the player angle from
                    //before, before added the random offset
                    newAngle = 360 - newAngle + ((_playerPaddle[p]._angle[0] + _playerPaddle[p]._angle[1]) * RAD2DEG) + randomOffset;
                    //Update the ball's movement direction
                    _gameBall[b].UpdateMoveDir(newAngle * DEG2RAD);
                }
        }
        else
        {
            //After a collision, wait a certain number of frames, then enable collisions
            _deltaFrames++;
            if (_deltaFrames >= BALLCOLISIONCHECKCOOLDOWN)
            {
                _deltaFrames = 0;
                _gameBall[b]._collidable = true;
            }
        }

        if (_spawnPowerUps)
        {
            if (_setPower->_active)
                if (CheckCollisionCircles(_gameBall[b]._position, _gameBall[b]._size, _setPower->_position, 50))
                {
                    _setPower->_active = false;
                    _setPower->DoEffect();
                }

        }
    }

    if (_spawnPowerUps)
    {
        if (!_setPower->_active && _powerUpSpawnCountdown <= 0)
        {
            Vector2 pos;
            pos.x = pos.y = SCREENSIZE / 2;

            int r = rand() % 2;
            switch (r)
            {
            case 0:
                _setPower = new ExtraPoint{ &_score, pos };
                _setPower->_active = true;
                break;
            case 1:
                _setPower = new TimeSlow{ &_timeScale, pos };
                _setPower->_active = true;
                break;
            default:
                break;
            }
            _powerUpSpawnCountdown = _powerUpSpawnTime;
        }
        else if (!_setPower->_active && _powerUpSpawnCountdown > 0)
            _powerUpSpawnCountdown -= 0.0167;
            }
    GameDraw();
}
void Game::GameDraw()
{
    BeginDrawing();

    ClearBackground(BLACK);

    //Draw score
    std::string s = std::to_string(_score);
    if (_score < 10)
        s = "0" + s;

    const char* pchar = s.c_str();
    DrawText(pchar, SCORETEXTOFFSETX, SCORETEXTOFFSETY, SCORETEXTSIZE, NOTEXACTLYBLACK);

    //Draw player paddles
    for (int p = 0; p <= _activePaddleCount; p++)
        _playerPaddle[p].Draw();

    //Draw the balls
    for (int b = 0; b <= _activeBallCount; b++)
        _gameBall[b].Draw();

    if (_spawnPowerUps)
        if (_setPower->_active)
            _setPower->DrawObject();

    EndDrawing();
}

//END GAME
void Game::EndGameUpdate()
{
    //Check to see if player wants to continue
    if (IsKeyReleased(NEXTKEY) || IsMouseButtonPressed(0))
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
    std::string s = std::to_string(_score);
    if (_score < 10)
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
            DrawText(pchar, (SCREENSIZE / 2 - GOTEXTSIZE / 2) + (GOTEXTSIZE + GOSCORESPACING) * x + cos(_angle) * x, GOTEXTOFFSETY + (GOTEXTSIZE - GOSCORESPACING) * y + sin(_angle) * y, GOTEXTSIZE, DEEPERRED);
            DrawText(pchar, (SCREENSIZE / 2 - GOTEXTSIZE / 2) + (GOTEXTSIZE + GOSCORESPACING) * x + cos(_angle) * x * GOSCOREMOVEMENTMULTIPLIER, GOTEXTOFFSETY + (GOTEXTSIZE - GOSCORESPACING)* y + sin(_angle) * y * GOSCOREMOVEMENTMULTIPLIER, GOTEXTSIZE, DEEPRED);
        }
    }
    //Display losing text over this grid
    DrawText("YOU LOSE", GOTEXTOFFSETX, GOTEXTOFFSETY, GOTEXTSIZE, RAYWHITE);
    DrawText("Press 'ENTER' or click to continue", SCREENSIZE / 2 - GOTEXTSIZE / 10 * 35 / 2, GOTEXTOFFSETY + GOTEXTSIZE, GOTEXTSIZE / 5, RAYWHITE);

    EndDrawing();
}