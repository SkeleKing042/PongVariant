#pragma once

#include "raylib.h"
#include <vector>

using namespace std;

class Paddle
{
	//Every var can have a second var used for modifiers to the first
public:
	//[0] = angle value
	//[1] = offset
	double angle[2] = {0, 0};
	double speed = 1.0;
	Rectangle rec;
	Vector2 recCenter;
	Vector2 position;
	double distanceFromCenter;
	pair<pair<Vector2, Vector2>, pair<Vector2, Vector2>> corners;

public:
	Paddle();
	~Paddle();

	void Init(double speed, double width, double height, double radius, double angle);
	void MovePaddle(int inputDir, double scale);
	void SetCorners();
	void Draw();
};