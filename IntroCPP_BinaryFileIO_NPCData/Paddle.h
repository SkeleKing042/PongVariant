#pragma once

#include "raylib.h"
#include <vector>

class Paddle
{
	//Every var can have a second var used for modifiers to the first
public:
	//[0] = angle value
	//[1] = offset
	double _angle[2] = {0, 0};
	double _speed = 1.0;
	Rectangle _rec;
	Vector2 _recCenter;
	Vector2 _position;
	double _distanceFromCenter;
	std::pair<std::pair<Vector2, Vector2>, std::pair<Vector2, Vector2>> _corners;

public:
	Paddle();
	~Paddle();

	void Init(double speed, double width, double height, double radius, double angle);
	void MovePaddle(int inputDir, double scale);
	void SetCorners();
	void Draw();
};