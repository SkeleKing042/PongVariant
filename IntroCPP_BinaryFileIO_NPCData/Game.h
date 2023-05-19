#pragma once

#include "GameDefines.h"
#include "Paddle.h"
#include "Ball.h"
#include "ClickableObject.h"


using namespace std;

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
	ClickableObject startButton;
	ClickableObject quitButton;

	ClickableObject modeButtons[MODEMENUEXTRAMODES];
	const char* modeNames[MODEMENUNAMES] = { "STANDARD", "SMALL", "RING", "CHAOS", "MIRROR"};
	int modeNameCount = MODEMENUNAMES;

	int deltaFrames = 0;
	double angle = 0;
	double scalesSaved[5] = { TIER1, TIER2, TIER3, TIER4, TIER5 };
	double* scalePointer = 0;
	
	Paddle playerPaddle[255];
	int activePaddleCount = 0;
	Ball gameBall[255];
	int activeBallCount = 0;
	bool randomBallSpeed = false;


	int score = 0;
	//bool gameOver = false;

	enum GameState
	{
		startMenu,
		playing,
		gameOver
	};
	GameState state;
	int menuState = 0;

};