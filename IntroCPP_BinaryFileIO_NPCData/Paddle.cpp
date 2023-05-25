#include "Paddle.h"
#include "GameDefines.h"
Paddle::Paddle()
{
	_angle[0] = _distanceFromCenter = _rec.x = _rec.y = _rec.width = _rec.height = _recCenter.x = _recCenter.y = _position.x = _position.y = 0;
}
Paddle::~Paddle()
{ }
void Paddle::Init(double givenSpeed, double givenWidth, double givenHeight, double givenRadius, double givenAngle)
{
	_speed = givenSpeed;
	_angle[0] = givenAngle * DEG2RAD;
	_rec.width = givenWidth;
	_rec.height = givenHeight;
	_distanceFromCenter = givenRadius;
	_rec.x = GetScreenWidth() / 2.0 + cos(_angle[0]) * _distanceFromCenter;
	_rec.y = GetScreenHeight() / 2.0 + sin(_angle[0]) * _distanceFromCenter;
	_recCenter.x = _rec.width / 2;
	_recCenter.y = _rec.height / 2;

	SetCorners();
}
void Paddle::MovePaddle(int inputDir, double s)
{
	//Used to slow down the paddle at fast speeds when needed
	double speedModifier = 1;
	if (IsKeyDown(KEY_SPACE))
		speedModifier = 1 / s;

	//Change the paddle angle depending on the player input
	switch (inputDir)
	{
	case 0:
		_angle[0] -= _speed * s * speedModifier;
		break;
	case 1:
		_angle[0] += _speed * s * speedModifier;
		break;
	}

	//Update positions
	_rec.x = GetScreenWidth() / 2.0 + cos(_angle[0] + _angle[1]) * _distanceFromCenter;
	_rec.y = GetScreenHeight() / 2.0 + sin(_angle[0] + _angle[1]) * _distanceFromCenter;

	SetCorners();

	//Resets player angle if angle is too high or low
	if (_angle[0] > PI * 2)
		_angle[0] -= PI * 2;
	if (_angle[0] < 0)
		_angle[0] += PI * 2;
}
void Paddle::SetCorners()
{
	//Gets the center of the paddle
	_position.x = SCREENSIZE / 2 + cos(_angle[0] + _angle[1]) * _distanceFromCenter;
	_position.y = SCREENSIZE / 2 + sin(_angle[0] + _angle[1]) * _distanceFromCenter;

	//The format for the corners is as follows:
	//- corners.first == front
	//- corners.second == back
	//- corners."  ".first == left
	//- corners."  ".second = right

	//The position of each corner takes the center of the paddle, then finds the position offset by
	//size and current angle of the player paddle.
	_corners.first.first.x = _position.x - _rec.height / 2 * sin(_angle[0] + _angle[1]) - _rec.width / 2 * cos(_angle[0] + _angle[1]);
	_corners.first.first.y = _position.y + _rec.height / 2 * cos(_angle[0] + _angle[1]) - _rec.width / 2 * sin(_angle[0] + _angle[1]);

	_corners.first.second.x = _position.x + _rec.height / 2 * sin(_angle[0] + _angle[1]) - _rec.width / 2 * cos(_angle[0] + _angle[1]);
	_corners.first.second.y = _position.y - _rec.height / 2 * cos(_angle[0] + _angle[1]) - _rec.width / 2 * sin(_angle[0] + _angle[1]);

	_corners.second.first.x = _position.x - _rec.height / 2 * sin(_angle[0] + _angle[1]) + _rec.width / 2 * cos(_angle[0] + _angle[1]);
	_corners.second.first.y = _position.y + _rec.height / 2 * cos(_angle[0] + _angle[1]) + _rec.width / 2 * sin(_angle[0] + _angle[1]);

	_corners.second.second.x = _position.x + _rec.height / 2 * sin(_angle[0] + _angle[1]) + _rec.width / 2 * cos(_angle[0] + _angle[1]);
	_corners.second.second.y = _position.y - _rec.height / 2 * cos(_angle[0] + _angle[1]) + _rec.width / 2 * sin(_angle[0] + _angle[1]);
}
void Paddle::Draw()
{
	DrawTriangle(_corners.second.second, _corners.first.second, _corners.first.first, PLAYERCOLOURA);
	DrawTriangle(_corners.first.first, _corners.second.first, _corners.second.second, PLAYERCOLOURB);
}