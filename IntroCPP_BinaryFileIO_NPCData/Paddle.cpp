#include "Paddle.h"
#include "raylib.h"
#include <iostream>

using namespace std;

Paddle::Paddle(double givenSpeed, double givenWidth, double givenHeight, double givenRadius, double givenAngle)
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
	rec.x = GetScreenWidth() / 2 + cos(angle) * distanceFromCenter;
	rec.y = GetScreenHeight() / 2 + sin(angle) * distanceFromCenter;

	// Resets player angle if angle is too high or low
	if (angle > PI * 2)
		angle -= PI * 2;
	if (angle < 0)
		angle += PI * 2;
}
double Paddle::GetPaddleNormal()
{
	double normalAngle = 0;
	normalAngle = 180 + (angle * RAD2DEG);
	if (normalAngle < 0) normalAngle += 360;
	return normalAngle * DEG2RAD;
}