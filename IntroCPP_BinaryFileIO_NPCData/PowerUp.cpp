#include "PowerUp.h"
#include <iostream>
PowerUp::PowerUp(Color cl, double si)
{
	//Generates a random int based off the screen size and use it to give the power up a random spawn
	//point each time
	int offset = rand() % (int)round(SCREENSIZE * STARTINGOFFSETSCALAR);
	if (offset % 2 == 0)
		offset *= -1;
	_position.x = (float)SCREENSIZE / 2 + (float)offset;
	offset = rand() % (int)round(SCREENSIZE * STARTINGOFFSETSCALAR);
	if (offset % 2 == 0)
		offset *= -1;
	_position.y = (float)SCREENSIZE / 2 + (float)offset;

	_color = cl;
	_size = si;
}
PowerUp::PowerUp(Color cl, double si, Vector2 ps)
{
	_color = cl;
	_size = si;
	_position = ps;
}
PowerUp::~PowerUp()
{ }
void PowerUp::DoEffect()
{
	std::cout << "Child class missed when calling \'DoEffect\'" << std::endl;
}
void PowerUp::DoCountDown()
{
	//Undo the effect when the time limit is reached
	if (_powerTimer >= _powerTimeLimit)
	{
		_powerTimer = 0;
		UndoEffect();
		_counting = false;
	}
	else if (_counting)
		_powerTimer += 1.0 / FPS;
}
void PowerUp::UndoEffect()
{
	std::cout << "Child class missed when calling \'UndoEffect\'" << std::endl;
}
void PowerUp::DrawObject()
{
	std::cout << "Child class missed when calling \'DrawObject\'" << std::endl;
	DrawCircle(_position.x, _position.y, _size, WHITE);
}
void PowerUp::DrawVisuals()
{
	std::cout << "Child class missed when calling \'DrawVisuals\'" << std::endl;
}