#include "PowerUp.h"
#include "Paddle.h"

DoubleUp::DoubleUp(int* c, Paddle* pad)
{
	_paddleCount = c;
	_paddlePoint = pad;
	_powerTimeLimit = 10.0;
}

void DoubleUp::DoEffect()
{
	_counting = true;
	(_paddlePoint + 1)->Init((_paddlePoint + 0)->_speed, (_paddlePoint + 0)->_rec.width, (_paddlePoint + 0)->_rec.height, (_paddlePoint + 0)->_distanceFromCenter, (_paddlePoint + 0)->_angle[0] * RAD2DEG);
	(_paddlePoint + 1)->_angle[1] = 180 * DEG2RAD;
	(_paddlePoint + 1)->SetCorners();
	*_paddleCount += 1;
}

void DoubleUp::UndoEffect()
{
	_counting = false;
	*_paddleCount -= 1;
}

void DoubleUp::DrawObject()
{
	DrawCircleV(_position, 50, RED);
}

void DoubleUp::DrawVisuals()
{

}