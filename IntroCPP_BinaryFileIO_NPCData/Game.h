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

	int deltaFrames;
	double paddleRadius;
	
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

	double angle;
};