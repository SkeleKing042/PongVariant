#include "ClickableObject.h"
#include <sstream>
/// <summary>
/// Clickable Object contructor
/// </summary>
ClickableObject::ClickableObject()
{
	//Creates a default rec to avoid errors for undifined rec values
	_rec.width = _rec.height = _rec.x = _rec.y = 0;
}
/// <summary>
/// Clickable Object destructor
/// </summary>
ClickableObject::~ClickableObject() { }
/// <summary>
/// Clickable object initialisation
/// </summary>
/// <param name="Width"></param>
/// <param name="Height"></param>
/// <param name="X Position"></param>
/// <param name="Y Position"></param>
/// <param name="Name"></param>
void ClickableObject::Init(double width, double height, double x, double y, const char* name)
{
	_rec.width = width;
	_rec.height = height;
	_rec.x = x;
	_rec.y = y;
	this->_name = name;
	//Name length is needed for text positioning
	_nameLength = strlen(name);
}
/// <summary>
/// Checks if it has been clicked
/// <para/>"pos" is the mouse position
/// </summary>
/// <param name="Mouse Poition"></param>
/// <returns></returns>
bool ClickableObject::Clicked(Vector2 pos)
{
	//Check to see if the given position is within the button's rectangle
	if (_rec.x < pos.x && pos.x < _rec.width + _rec.x && _rec.y < pos.y && pos.y < _rec.height + _rec.y)
		return true;
	else
		return false;
}
/// <summary>
/// Draws this Clickable Object
/// </summary>
void ClickableObject::Draw()
{
	DrawRectangleRec(_rec, RAYWHITE);
	DrawRectangleLinesEx(_rec, 2, GRAY);
	DrawText(_name, _rec.x + _rec.width / 2 - (_nameLength + 1.0) / 2.0 * (MENUTEXTSIZE / 2), _rec.y + _rec.height / 2.0 - MENUTEXTSIZE / 2.0, MENUTEXTSIZE, BLACK);
}