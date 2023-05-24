#include "PowerUp.h"

ExtraPoint::ExtraPoint(int* s, Vector2 p) : PowerUp(p)
{
	_gameScore = s;
	_powerTimeLimit = 0;
}

void ExtraPoint::DoEffect()
{
	DrawVisuals();
	*_gameScore += 1;
}

void ExtraPoint::DrawObject()
{
	DrawCircleV(_position, 50, ORANGE);
}

void ExtraPoint::DrawVisuals()
{

}