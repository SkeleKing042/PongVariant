#include "PowerUp.h"

TimeSlow::TimeSlow(double* s, Color cl, double si, double et, double es) : PowerUp(cl, si)
{ 
	_timeScale = s;
	_powerTimeLimit = et;
	_slownessStrength = es;
}

void TimeSlow::DoEffect()
{
	_counting = true;
	_doDrawVisuals = true;
	*_timeScale *= _slownessStrength;
}

void TimeSlow::UndoEffect()
{
	_counting = false;
	_doDrawVisuals = false;
	*_timeScale = 1;
}

void TimeSlow::DrawObject()
{
	DrawCircleV(_position, _size, _color);
}

void TimeSlow::DrawVisuals()
{
	//Draws a clock in the background
	DrawCircleLines(SCREENSIZE / 2, SCREENSIZE / 2, SCREENSIZE / 2, _color);
	//DrawCircle(SCREENSIZE / 2, SCREENSIZE / 2, SCREENSIZE / 2 * (_powerTimer / _powerTimeLimit), _color);
	DrawLine(SCREENSIZE / 2, SCREENSIZE / 2, SCREENSIZE / 2 + cos((_powerTimer / _powerTimeLimit * 360 - 90) * DEG2RAD)* SCREENSIZE / 2, SCREENSIZE / 2 + sin((_powerTimer / _powerTimeLimit * 360 - 90) * DEG2RAD) * SCREENSIZE / 2, _color);
	DrawLine(SCREENSIZE / 2, SCREENSIZE / 2, SCREENSIZE / 2 + cos((_powerTimer * 360 - 90) * DEG2RAD) * SCREENSIZE / 4, SCREENSIZE / 2 + sin((_powerTimer * 360 - 90) * DEG2RAD) * SCREENSIZE / 4, _color);
}