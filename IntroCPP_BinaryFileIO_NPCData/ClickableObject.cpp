#include "ClickableObject.h"
#include <sstream>
ClickableObject::ClickableObject()
{
	//Creates a default rec to avoid errors for undifined rec values
	_rec.width = _rec.height = _rec.x = _rec.y = 0;
	_baseColor = RAYWHITE;
	_outLineColor = GRAY;
	_textColor = BLACK;
}
ClickableObject::~ClickableObject() { }
void ClickableObject::Init(double width, double height, double x, double y, const char* name, Color bc, Color oc, Color tc)
{
	_rec.width = width;
	_rec.height = height;
	_rec.x = x;
	_rec.y = y;
	this->_name = name;
	//Name length is needed for text positioning
	_nameLength = strlen(name);
	_baseColor = bc;
	_outLineColor = oc;
	_textColor = tc;
}
bool ClickableObject::Clicked(Vector2 pos)
{
	//Check to see if the given position is within the button's rectangle
	if (_rec.x < pos.x && pos.x < _rec.width + _rec.x && _rec.y < pos.y && pos.y < _rec.height + _rec.y)
		return true;
	else
		return false;
}
void ClickableObject::Draw()
{
	DrawRectangleRec(_rec, _baseColor);
	DrawRectangleLinesEx(_rec, BUTTONOUTLINESIZE, _outLineColor);
	DrawText(_name, _rec.x + _rec.width / 2 - (_nameLength + 1.0) / 2.0 * (MENUTEXTSIZE / 2.0), _rec.y + _rec.height / 2.0 - MENUTEXTSIZE / 2.0, MENUTEXTSIZE, _textColor);
}