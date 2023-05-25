#include "PowerUp.h"
#include "Paddle.h"

DoubleUp::DoubleUp(int* c, Paddle* pad, Color cl) : PowerUp(cl)
{
	_paddleCount = c;
	_paddlePoint = pad;
	_powerTimeLimit = 10.0;
}

void DoubleUp::DoEffect()
{
	_counting = true;
	_doDrawVisuals = true;
	(_paddlePoint + 1)->Init((_paddlePoint + 0)->_speed, (_paddlePoint + 0)->_rec.width, (_paddlePoint + 0)->_rec.height, (_paddlePoint + 0)->_distanceFromCenter, (_paddlePoint + 0)->_angle[0] * RAD2DEG, (_paddlePoint + 0)->_firstColor, (_paddlePoint + 0)->_secondColor);
	(_paddlePoint + 1)->_angle[1] = 180 * DEG2RAD;
	(_paddlePoint + 1)->SetCorners();
	*_paddleCount += 1;
}

void DoubleUp::UndoEffect()
{
	_counting = false;
	_doDrawVisuals = false;
	*_paddleCount -= 1;
}

void DoubleUp::DrawObject()
{
	DrawCircleV(_position, 50, _color);
}

void DoubleUp::DrawVisuals()
{
	//Draws a line between the two paddles then a circle around the dupe
	DrawLineEx((_paddlePoint + 0)->_position, (_paddlePoint + 1)->_position, (_paddlePoint + 0)->_rec.height * (1 - (_powerTimer / _powerTimeLimit)), _color);
	DrawCircleLines((_paddlePoint + 1)->_position.x, (_paddlePoint + 1)->_position.y, (_paddlePoint + 1)->_rec.height * 0.75, _color);

}