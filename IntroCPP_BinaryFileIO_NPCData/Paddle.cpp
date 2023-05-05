#include "Paddle.h"
#include "raylib.h"
#include <iostream>

using namespace std;

Paddle::Paddle(double givenSpeed, double givenWidth, double givenHeight)
{
	speed = givenSpeed;
	angle = 0;
	size.first = givenWidth;
	size.second = givenHeight;
}

Paddle::~Paddle()
{

}

void Paddle::MovePaddle(int inputDir)
{
	switch (inputDir)
	{
	case 0:
		angle -= speed;
		break;
	case 1:
		angle += speed;
		break;
	}

	// Resets player angle if angle is too high or low
	if (angle > PI * 2)
		angle -= PI * 2;
	if (angle < 0)
		angle += PI * 2;
}