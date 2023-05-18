#include "Paddle.h"
#include "raylib.h"
#include "GameDefines.h"
#include <iostream>

using namespace std;

Paddle::Paddle()
{
	angle = distanceFromCenter = rec.x = rec.y = rec.width = rec.height = recCenter.x = recCenter.y = 0;
}

Paddle::~Paddle() { }

void Paddle::Init(double givenSpeed, double givenWidth, double givenHeight, double givenRadius, double givenAngle)
{
	speed = givenSpeed;
	angle = givenAngle * DEG2RAD;
	size.first = givenWidth;
	size.second = givenHeight;
	distanceFromCenter = givenRadius;
	rec.x = GetScreenWidth() / 2 + cos(angle) * distanceFromCenter;
	rec.y = GetScreenHeight() / 2 + sin(angle) * distanceFromCenter;
	rec.width = size.first;
	rec.height = size.second;
	recCenter.x = size.first / 2;
	recCenter.y = size.second / 2;

	SetCorners();
}

void Paddle::MovePaddle(int inputDir)
{
	//Change the paddle angle depending on the player input
	switch (inputDir)
	{
	case 0:
		angle -= speed;
		break;
	case 1:
		angle += speed;
		break;
	}

	//Update positions
	rec.x = GetScreenWidth() / 2 + cos(angle) * distanceFromCenter;
	rec.y = GetScreenHeight() / 2 + sin(angle) * distanceFromCenter;

	SetCorners();

	//Resets player angle if angle is too high or low
	if (angle > PI * 2)
		angle -= PI * 2;
	if (angle < 0)
		angle += PI * 2;
}

/// <summary>
/// Finds the corners of the player paddle and saves them to a
/// pair<pair<Vector2, Vector2>, pair<Vector2, Vector2>> variable
/// </summary>
void Paddle::SetCorners()
{
	Vector2 playerCenter;
	playerCenter.x = SCREENSIZE / 2 + cos(angle) * distanceFromCenter;
	playerCenter.y = SCREENSIZE / 2 + sin(angle) * distanceFromCenter;

	//The format for the corners is as follows:
	//- corners.first == front
	//- corners.second == back
	//- corners."  ".first == left
	//- corners."  ".second = right

	//The position of each corner takes the center of the paddle, then finds the position offset by
	//size and current angle of the player paddle.
	corners.first.first.x = playerCenter.x - size.second / 2 * sin(angle) - PADDLEWIDTH / 2 * cos(angle);
	corners.first.first.y = playerCenter.y + size.second / 2 * cos(angle) - PADDLEWIDTH / 2 * sin(angle);

	corners.first.second.x = playerCenter.x + size.second / 2 * sin(angle) - PADDLEWIDTH / 2 * cos(angle);
	corners.first.second.y = playerCenter.y - size.second / 2 * cos(angle) - PADDLEWIDTH / 2 * sin(angle);

	corners.second.first.x = playerCenter.x - size.second / 2 * sin(angle) + PADDLEWIDTH / 2 * cos(angle);
	corners.second.first.y = playerCenter.y + size.second / 2 * cos(angle) + PADDLEWIDTH / 2 * sin(angle);

	corners.second.second.x = playerCenter.x + size.second / 2 * sin(angle) + PADDLEWIDTH / 2 * cos(angle);
	corners.second.second.y = playerCenter.y - size.second / 2 * cos(angle) + PADDLEWIDTH / 2 * sin(angle);
}