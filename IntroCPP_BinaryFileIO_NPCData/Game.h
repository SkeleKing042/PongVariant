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
	void GameInitalisation();
	void Update();
private:
	void MenuStateUpdate();
	void GameUpdate();
	void EndGameUpdate();

	void MenuDraw();
	void GameDraw();
	void EndGameDraw();

private:
	ClickableObject startButton;
	ClickableObject quitButton;

	int deltaFrames = 0;
	double angle = 0;
	double scalesSaved[5] = { TIER1, TIER2, TIER3, TIER4, TIER5 };
	double* scalePointer = 0;
	
	Paddle playerPaddle;
	Ball gameBall;

	int score = 0;
	//bool gameOver = false;

	enum GameState
	{
		startMenu,
		playing,
		gameOver
	};
	GameState state;

};