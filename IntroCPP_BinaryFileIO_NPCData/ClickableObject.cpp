#include "ClickableObject.h"
#include <sstream>

ClickableObject::ClickableObject()
{
	_rec.width = _rec.height = _rec.x = _rec.y = 0;
}
ClickableObject::~ClickableObject() { }

void ClickableObject::Init(double width, double height, double x, double y, const char* name)
{
	_rec.width = width;
	_rec.height = height;
	_rec.x = x;
	_rec.y = y;
	this->_name = name;
	_nameLength = strlen(name);
}

bool ClickableObject::Clicked(Vector2 pos)
{
	//Check to see if a given position is within the button's rectangle
	if (_rec.x < pos.x && pos.x < _rec.width + _rec.x && _rec.y < pos.y && pos.y < _rec.height + _rec.y)
		return true;
	else
		return false;
}

void ClickableObject::Draw()
{
	DrawRectangleRec(_rec, RAYWHITE);
	DrawRectangleLinesEx(_rec, 2, GRAY);
	DrawText(_name, _rec.x + _rec.width / 2 - (_nameLength + 1.0) / 2.0 * (MENUTEXTSIZE / 2), _rec.y + _rec.height / 2.0 - MENUTEXTSIZE / 2.0, MENUTEXTSIZE, BLACK);
}