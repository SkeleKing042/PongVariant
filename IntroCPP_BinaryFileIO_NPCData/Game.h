#pragma once
#include "GameDefines.h"
#include "Paddle.h"
#include "Ball.h"
#include "ClickableObject.h"
#include "PowerUp.h"
#include <iostream>
/// <summary>
/// The game and its functions
/// </summary>
class Game
{
public:
	/// <summary>
/// Game contructor
/// </summary>
	Game();
	/// <summary>
/// Initalises the Main menu
/// <para/>Has start and quit buttons along with speed changing options
/// </summary>
	void MenuInitalisation();
	/// <summary> 
/// Initalises the mode selection menu
/// <para/>Displays several modes that the player can choose from.
/// <para/>These modes alter gameplay
/// </summary>
	void ModeMenuInitalisation();
	/// <summary>
/// Initalises the game
/// <para/>Loaded the player paddle and ball
/// <para/>Also check if any gamemode have been chosen
/// </summary>
/// <param name="Mode"></param>
	void GameInitalisation(int Mode);
	/// <summary>
/// Initialses the game over state
/// <para/>Disables any gamemode alterations
/// </summary>
	void LossInitalisation();
	/// <summary>
/// Checks what state the game is currently in
/// <para/>Is called every frame
/// </summary>
	void Update();
private:
	/// <summary>
/// Checks the current menu state and loads the approprate menu
/// </summary>
	void MenuStateUpdate();
	/// <summary>
/// Update function called while in the main menu
/// </summary>
	void MainMenuUpdate();
	/// <summary>
/// Update function called while in the mode selection menu
/// </summary>
	void ModeSelectMenuUpdate();
	/// <summary>
/// Update function called while the game is being played
/// </summary>
	void GameUpdate();
	/// <summary>
/// Update function called while in the game over state
/// </summary>
	void EndGameUpdate();
	/// <summary>
/// Draws the main menu
/// </summary>
	void MainMenuDraw();
	/// <summary>
/// Draws the mode selection menu
/// </summary>
	void ModeSelectMenuDraw();
	/// <summary>
/// Draws the game
/// </summary>
	void GameDraw();
	/// <summary>
/// Draws the game over state
/// </summary>
	void EndGameDraw();
private:
	//Buttons
	ClickableObject _startButton;
	ClickableObject _quitButton;
	ClickableObject _modeButtons[MODEMENUEXTRAMODES];
	const char* _modeNames[MODEMENUNAMES] = { "STANDARD", "SMALL", "RING", "CHAOS", "MIRROR", "POWER"};
	int _modeNameCount = MODEMENUNAMES;
	ClickableObject _returnButton;

	//Numbers for maths or timing
	int _deltaFrames = 0;
	double _angle = 0;
	double _scalesSaved[5] = { TIER1, TIER2, TIER3, TIER4, TIER5 };
	double* _scalePointer = 0;
	
	//Paddles
	Paddle _playerPaddle[MAXIMUMPADDLECOUNT];
	Paddle* _paddlePtr;
	int _activePaddleCount = 0;
	//Balls
	Ball _gameBall[MAXIMUMBALLCOUNT];
	int _activeBallCount = 0;
	bool _randomBallSpeed = false;

	//Power Ups
	PowerUp* _setPower;
	PowerUp* _boosterPoint;
	bool _spawnPowerUps = false;
	double _powerUpSpawnTime = POWERUPSPAWNTIME;
	double _powerUpSpawnCountdown = _powerUpSpawnTime;

	//Game Logic
	int _score = 0;
	double _timeScale = 1;
	enum GameState
	{
		startMenu,
		playing,
		gameOver
	};
	GameState _state;
	int _menuState = 0;

};