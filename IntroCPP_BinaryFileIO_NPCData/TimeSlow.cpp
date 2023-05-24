#include "PowerUp.h"

TimeSlow::TimeSlow(double* s, Vector2 p) : PowerUp(p)
{ 
	_timeScale = s;
	_powerTimeLimit = 5;
}

void TimeSlow::DoEffect()
{
	*_timeScale *= 0.5;
}

void TimeSlow::UndoEffect()
{
	*_timeScale = 1;
}

void TimeSlow::DrawObject()
{
	DrawCircleV(_position, 50, SKYBLUE);
}

void TimeSlow::DrawVisuals()
{

}