#include "PowerUp.h"

TimeSlow::TimeSlow(double* s)
{ 
	_timeScale = s;
	_powerTimeLimit = 8.0;
}

void TimeSlow::DoEffect()
{
	_counting = true;
	*_timeScale *= 0.5;
}

void TimeSlow::UndoEffect()
{
	_counting = false;
	*_timeScale = 1;
}

void TimeSlow::DrawObject()
{
	DrawCircleV(_position, 50, SKYBLUE);
}

void TimeSlow::DrawVisuals()
{

}