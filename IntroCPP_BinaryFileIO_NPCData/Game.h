#pragma once

#include "GameDefines.h"
#include "Paddle.h"
#include "Ball.h"

using namespace std;

class Game
{
public:
	void Initalisation();
	void Update();
	void Draw();

private:
	int deltaFrames;
	double PaddleRadius;
	
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