#include "PowerUp.h"

ExtraPoint::ExtraPoint(int* s)
{
	_gameScore = s;
	_powerTimeLimit = 0;
}

void ExtraPoint::DoEffect()
{
	DrawVisuals();
	*_gameScore += 1;
	_active = false;
	_doDrawVisuals = true;
	_counting = false;
	_powerTimeLimit = 0.5;
	_powerTimer = _powerTimeLimit;
}

void ExtraPoint::DrawObject()
{
	DrawCircleV(_position, 50, ORANGE);
}

void ExtraPoint::DrawVisuals()
{
	//Draws a subtle "pop" effect
	_powerTimer += 0.0167;
	DrawCircleLines(_position.x, _position.y, 50 + 10 * _powerTimer, ORANGE);
	if (_powerTimer > _powerTimeLimit)
		_doDrawVisuals = false;
}