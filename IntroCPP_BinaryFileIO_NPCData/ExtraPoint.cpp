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
}

void ExtraPoint::DrawObject()
{
	DrawCircleV(_position, 50, ORANGE);
}

void ExtraPoint::DrawVisuals()
{

}