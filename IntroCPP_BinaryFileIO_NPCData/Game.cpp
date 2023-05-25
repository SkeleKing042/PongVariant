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
    //Set the menu state and reset all values
    _state = startMenu;
    _menuState = 0;
    _activePaddleCount = 0;
    _activeBallCount = 0;
    //Load menu buttons
    _startButton.Init(BUTTONWIDTH, BUTTONHEIGHT, STARTBUTTONX, STARTBUTTONY, STARTBUTTONTEXT);
    _quitButton.Init(BUTTONWIDTH, BUTTONHEIGHT, QUITBUTTONX, QUITBUTTONY, QUITBUTTONTEXT);
}
void Game::ModeMenuInitalisation()
{
    //Updates the menu state
    _menuState = 1;

    //Loading Buttons
    //Mode buttons are arranged in a grid
    //Y is each row and X is each column
    for(int y = 0; y < (double)MODEMENUEXTRAMODES / (double)MODEMENUBUTTONSPERROW; y++)
        for (int x = 0; x < MODEMENUBUTTONSPERROW; x++)
        {
            //If enough buttons have been put in this row, break
            if (y * MODEMENUBUTTONSPERROW + x >= MODEMENUEXTRAMODES)
                break;
            //Setup a button with the correct size and position to fit in the grid
            _modeButtons[y * MODEMENUBUTTONSPERROW + x]._rec.width = (MODEMENUSIDESPACING - ((MODEMENUBUTTONSPERROW - 1.0) * BUTTONSPACING)) / (double)MODEMENUBUTTONSPERROW;
            _modeButtons[y *MODEMENUBUTTONSPERROW + x]._rec.height = MODEMENUBUTTONHEIGHT;
            _modeButtons[y *MODEMENUBUTTONSPERROW + x]._rec.x = MODEMENUBUTTONXOFFSET + x * (_modeButtons[y * MODEMENUBUTTONSPERROW + x]._rec.width + MODEMENUBUTTONSPACING);
            _modeButtons[y *MODEMENUBUTTONSPERROW + x]._rec.y = MODEMENUBUTTONYOFFSET + y * (_modeButtons[y * MODEMENUBUTTONSPERROW + x]._rec.height + MODEMENUBUTTONSPACING);
            //If there is no avalible name for the button's mode, use "TBD
            if (y *MODEMENUBUTTONSPERROW + x >= _modeNameCount)
                _modeButtons[y *MODEMENUBUTTONSPERROW + x]._name = "TBD";
            else
                _modeButtons[y *MODEMENUBUTTONSPERROW + x]._name = _modeNames[y *MODEMENUBUTTONSPERROW + x];
            //Get the lenght of the mode name
            _modeButtons[y *MODEMENUBUTTONSPERROW + x]._nameLength = strlen(_modeButtons[y *MODEMENUBUTTONSPERROW + x]._name);
        }
    //Add a return button
    _returnButton.Init(BUTTONWIDTH, BUTTONHEIGHT, SCREENSIZE - BUTTONWIDTH - BUTTONSPACING, SCREENSIZE - BUTTONHEIGHT - BUTTONSPACING, "RETURN");
}
void Game::GameInitalisation(int mode)
{
    //Scoring and game logic 
    _state = playing;
    _score = 0;
    _timeScale = 1;

    //Ball and Paddle setup with a random angle
    double random = rand() % MAXRANDOMSTARTPOSTION;
    _playerPaddle[0].Init(PADDLESPEED, PADDLEWIDTH, PADDLEHEIGHT, SCREENSIZE / 2 - PADDLEPOSOFFSET, random);
    _paddlePtr = _playerPaddle;
    _gameBall[0].Init(INITIALBALLSPEED, BALLSIZE, random);

    //Checking the selected gamemode
    switch (mode)
    {
    case 1:
        //Resizes the paddle and ball to half size
        _playerPaddle[0]._rec.width /= 2;
        _playerPaddle[0]._rec.height /= 2;
        _gameBall[0]._size /= 2;
        _playerPaddle[0].SetCorners();
        break;
    case 2:
        //Creates a ring of paddles
        //Due to a collision bug, it is possible to lose this mode
        for (int i = 1; i < 20; i++)
        {
            _playerPaddle[i].Init(_playerPaddle[0]._speed, _playerPaddle[0]._rec.width, _playerPaddle[0]._rec.height, _playerPaddle[0]._distanceFromCenter, random);
            _playerPaddle[i]._angle[1] = (18 * i) * DEG2RAD;
            _playerPaddle[i].SetCorners();
            _activePaddleCount++;
        }
        break;
    case 3:
        //Enables random ball speeds
        _randomBallSpeed = true;
        break;
    case 4:
        //Creates another paddle opposite the player
        _playerPaddle[1].Init(_playerPaddle[0]._speed, _playerPaddle[0]._rec.width, _playerPaddle[0]._rec.height, _playerPaddle[0]._distanceFromCenter, random);
        //Offsets the paddle to be 180^ around the angle point and therefore, opposite the player
        _playerPaddle[1]._angle[1] = 180 * DEG2RAD;
        _playerPaddle[1].SetCorners();
        _activePaddleCount+=1;
        break;
    case 5:
        //Spawns power ups in game
        _spawnPowerUps = true;
        _setPower = new PowerUp{};
        _boosterPoint = new ExtraPoint{ &_score };
        break;
    }

    //Used for seeing the number of frames since a given action
    _deltaFrames = 0;
}
void Game::LossInitalisation()
{
    _state = gameOver;
    if (_randomBallSpeed) _randomBallSpeed = false;
    if (_spawnPowerUps) { _spawnPowerUps = false; _setPower = nullptr; _boosterPoint = nullptr; _powerUpSpawnCountdown = _powerUpSpawnTime; }
}
void Game::Update()
{
    //Checks the game's current state and calls the approprate update function
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

    //Angle is used for "animation"
    _angle += 0.04;
    //Resets angle when reaching 0 or 360 degrees 
    if (_angle > PI * 2)
        _angle -= PI * 2;
    if (_angle < 0)
        _angle += PI * 2;
}
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
    //Check to see if the player presses either button
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

    //Draws little tabs under the start button as additional speed level indicators
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
    //If the player clicks, check if they clicked on a button
    if (IsMouseButtonPressed(0))
    {
        for (int i = 0; i < MODEMENUEXTRAMODES; i++)
            if (_modeButtons[i].Clicked(GetMousePosition()))
            {
                //Start the game with a unique game mode enabled
                GameInitalisation(i);
            }
        //Go back to the main menu if the player clicked the return button
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

    //Draws all the mode buttons
    for (int i = 0; i < MODEMENUEXTRAMODES; i++)
    {
        _modeButtons[i].Draw();
    }

    //Draws the return button
    _returnButton.Draw();

    EndDrawing();
}
void Game::GameUpdate()
{
    //Move all active paddles if the player presses a movement input key
    for (int p = 0; p <= _activePaddleCount; p++)
    {
        if (IsKeyDown(MOVEPADDLERIGHT))
            _playerPaddle[p].MovePaddle(1, *_scalePointer);
        if (IsKeyDown(MOVEPADDLELEFT))
            _playerPaddle[p].MovePaddle(0, *_scalePointer);
    }

    //Update each active ball
    for (int b = 0; b <= _activeBallCount; b++)
    {
        //Moving the ball
        _gameBall[b].MoveBall(*_scalePointer * _timeScale);

        //Close game upon the ball hiting a wall
        //Scales with ball size
        if (_gameBall[b]._position.x <= 0 + _gameBall[b]._size || _gameBall[b]._position.x >= SCREENSIZE - _gameBall[b]._size || _gameBall[b]._position.y <= 0 + _gameBall[b]._size || _gameBall[b]._position.y >= SCREENSIZE - _gameBall[b]._size)
        {
            _angle = 0;
            LossInitalisation();
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

        //If power ups are enabled, check if they've been hit
        //Upon being hit, trigger the power up's effect(s), and disable them
        if (_spawnPowerUps)
        {
            if (_setPower->_active)
            {
                if (CheckCollisionCircles(_gameBall[b]._position, _gameBall[b]._size, _setPower->_position, 50))
                {
                    _setPower->DoEffect();
                    _setPower->_active = false;
                }
            }
            if (_boosterPoint->_active)
            {
                if (CheckCollisionCircles(_gameBall[b]._position, _gameBall[b]._size, _boosterPoint->_position, 50))
                {
                    _boosterPoint->DoEffect();
                    _boosterPoint->_active = false;
                }
            }

        }
    }

    //If power ups are enabled, try to spawn one
    if (_spawnPowerUps)
    {
        //After enough time has passed, try to spawn one
        if (_powerUpSpawnCountdown <= 0)
        {
            //If there is no power up active, spawn one
            if (!_setPower->_counting && !_setPower->_active)
            {
                //Choose a random power up to spawn
                int r = rand() % 3;
                switch (r)
                {
                case 0:
                    _setPower = new ExtraPoint{ &_score };
                    _setPower->_active = true;
                    break;
                case 1:
                    _setPower = new TimeSlow{ &_timeScale };
                    _setPower->_active = true;
                    break;
                case 2:
                    _setPower = new DoubleUp{ &_activePaddleCount, _paddlePtr };
                    _setPower->_active = true;
                default:
                    break;
                }
                //Start the countdown
                _powerUpSpawnCountdown = _powerUpSpawnTime;
            }
            //If there is an active power up, spawn an extra point power up
            else if (!_boosterPoint->_active && _setPower->_counting)
            {
                _boosterPoint = new ExtraPoint{ &_score };
                _boosterPoint->_active = true;
            }
        }
        //Continue the spawn countdown
        else if (!_setPower->_active && _powerUpSpawnCountdown > 0)
            _powerUpSpawnCountdown -= 0.0167;

        //Continue the effect countdown
        if (_setPower->_counting)
            _setPower->DoCountDown();
    }
    GameDraw();
}
void Game::GameDraw()
{
    BeginDrawing();

    ClearBackground(BLACK);

    //Draw the score
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

    //Draw any power ups if there're enabled
    if (_spawnPowerUps)
    {
        if (_setPower->_active)
            _setPower->DrawObject();
        if (_boosterPoint->_active)
            _boosterPoint->DrawObject();
    }

    EndDrawing();
}
void Game::EndGameUpdate()
{
    //Check to see if player wants to return to the main menu
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