#include "Paddle.h"
#include "raylib.h"
#include "GameDefines.h"
#include <iostream>

using namespace std;

Paddle::Paddle()
{
	angle[0] = distanceFromCenter = rec.x = rec.y = rec.width = rec.height = recCenter.x = recCenter.y = 0;
}

Paddle::~Paddle() { }

void Paddle::Init(double givenSpeed, double givenWidth, double givenHeight, double givenRadius, double givenAngle)
{
	speed = givenSpeed;
	angle[0] = givenAngle * DEG2RAD;
	rec.width = givenWidth;
	rec.height = givenHeight;
	distanceFromCenter = givenRadius;
	rec.x = GetScreenWidth() / 2.0 + cos(angle[0]) * distanceFromCenter;
	rec.y = GetScreenHeight() / 2.0 + sin(angle[0]) * distanceFromCenter;
	recCenter.x = rec.width / 2;
	recCenter.y = rec.height / 2;

	SetCorners();
}

void Paddle::MovePaddle(int inputDir, double s)
{
	double speedModifier = 1;

	if (IsKeyDown(KEY_SPACE))
		speedModifier = 1 / s;
	//Change the paddle angle depending on the player input
	switch (inputDir)
	{
	case 0:
		angle[0] -= speed * s * speedModifier;
		break;
	case 1:
		angle[0] += speed * s * speedModifier;
		break;
	}

	//Update positions
	rec.x = GetScreenWidth() / 2.0 + cos(angle[0] + angle[1]) * distanceFromCenter;
	rec.y = GetScreenHeight() / 2.0 + sin(angle[0] + angle[1]) * distanceFromCenter;

	SetCorners();

	//Resets player angle if angle is too high or low
	if (angle[0] > PI * 2)
		angle[0] -= PI * 2;
	if (angle[0] < 0)
		angle[0] += PI * 2;
}

/// <summary>
/// Finds the corners of the player paddle and saves them to a
/// pair<pair<Vector2, Vector2>, pair<Vector2, Vector2>> variable
/// </summary>
void Paddle::SetCorners()
{
	position.x = SCREENSIZE / 2 + cos(angle[0] + angle[1]) * distanceFromCenter;
	position.y = SCREENSIZE / 2 + sin(angle[0] + angle[1]) * distanceFromCenter;

	//The format for the corners is as follows:
	//- corners.first == front
	//- corners.second == back
	//- corners."  ".first == left
	//- corners."  ".second = right

	//The position of each corner takes the center of the paddle, then finds the position offset by
	//size and current angle of the player paddle.
	corners.first.first.x = position.x - rec.height / 2 * sin(angle[0] + angle[1]) - rec.width / 2 * cos(angle[0] + angle[1]);
	corners.first.first.y = position.y + rec.height / 2 * cos(angle[0] + angle[1]) - rec.width / 2 * sin(angle[0] + angle[1]);

	corners.first.second.x = position.x + rec.height / 2 * sin(angle[0] + angle[1]) - rec.width / 2 * cos(angle[0] + angle[1]);
	corners.first.second.y = position.y - rec.height / 2 * cos(angle[0] + angle[1]) - rec.width / 2 * sin(angle[0] + angle[1]);

	corners.second.first.x = position.x - rec.height / 2 * sin(angle[0] + angle[1]) + rec.width / 2 * cos(angle[0] + angle[1]);
	corners.second.first.y = position.y + rec.height / 2 * cos(angle[0] + angle[1]) + rec.width / 2 * sin(angle[0] + angle[1]);

	corners.second.second.x = position.x + rec.height / 2 * sin(angle[0] + angle[1]) + rec.width / 2 * cos(angle[0] + angle[1]);
	corners.second.second.y = position.y - rec.height / 2 * cos(angle[0] + angle[1]) + rec.width / 2 * sin(angle[0] + angle[1]);
}

void Paddle::Draw()
{
	DrawTriangle(corners.second.second, corners.first.second, corners.first.first, PLAYERCOLOURA);
	DrawTriangle(corners.first.first, corners.second.first, corners.second.second, PLAYERCOLOURB);

}