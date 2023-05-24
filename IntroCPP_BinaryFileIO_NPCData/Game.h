#pragma once

#include "GameDefines.h"
#include "Paddle.h"
#include "Ball.h"
#include "ClickableObject.h"
#include "PowerUp.h"
#include <iostream>

class Game
{
public:
	Game();
	void MenuInitalisation();
	void ModeMenuInitalisation();
	void GameInitalisation(int mode);
	void Update();
private:
	void MenuStateUpdate();
	void MainMenuUpdate();
	void ModeSelectMenuUpdate();
	void GameUpdate();
	void EndGameUpdate();

	void MainMenuDraw();
	void ModeSelectMenuDraw();
	void GameDraw();
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
	Paddle _playerPaddle[255];
	int _activePaddleCount = 0;
	//Balls
	Ball _gameBall[255];
	int _activeBallCount = 0;
	bool _randomBallSpeed = false;

	//Power Ups
	PowerUp* _setPower;
	bool _spawnPowerUps = false;
	double _powerUpSpawnTime = 5;
	double _powerUpSpawnCountdown = _powerUpSpawnTime;


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