#include "PowerUp.h"
#include <iostream>

PowerUp::PowerUp()
{
	_position.x = _position.y = SCREENSIZE / 2;
}

PowerUp::PowerUp(Vector2 p)
{
	_position = p;
}

PowerUp::~PowerUp()
{ }

void PowerUp::DoEffect()
{
	std::cout << "Child class missed when calling \'DoEffect\'" << std::endl;
}
void PowerUp::DoCountDown()
{
	if (_powerTimer >= _powerTimeLimit)
	{
		_powerTimer = 0;
		UndoEffect();
		_counting = false;
	}
	else if (_counting)
		_powerTimer += 0.0167;
}
void PowerUp::UndoEffect()
{
	std::cout << "Child class missed when calling \'UndoEffect\'" << std::endl;
}

void PowerUp::DrawObject()
{
	std::cout << "Child class missed when calling \'DrawObject\'" << std::endl;
	DrawCircle(_position.x, _position.y, 10, WHITE);
}

void PowerUp::DrawVisuals()
{
	std::cout << "Child class missed when calling \'DrawVisuals\'" << std::endl;
}