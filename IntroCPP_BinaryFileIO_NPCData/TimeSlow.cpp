#include "PowerUp.h"

TimeSlow::TimeSlow(double* s, Color cl) : PowerUp(cl)
{ 
	_timeScale = s;
	_powerTimeLimit = 8.0;
}

void TimeSlow::DoEffect()
{
	_counting = true;
	_doDrawVisuals = true;
	*_timeScale *= 0.5;
}

void TimeSlow::UndoEffect()
{
	_counting = false;
	_doDrawVisuals = false;
	*_timeScale = 1;
}

void TimeSlow::DrawObject()
{
	DrawCircleV(_position, 50, _color);
}

void TimeSlow::DrawVisuals()
{
	//Draws a clock in the background
	DrawCircleLines(SCREENSIZE / 2, SCREENSIZE / 2, SCREENSIZE / 2, _color);
	DrawLine(SCREENSIZE / 2, SCREENSIZE / 2, SCREENSIZE / 2 + cos((_powerTimer / _powerTimeLimit * 360 - 90) * DEG2RAD)* SCREENSIZE / 2, SCREENSIZE / 2 + sin((_powerTimer / _powerTimeLimit * 360 - 90) * DEG2RAD) * SCREENSIZE / 2, _color);
}