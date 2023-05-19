#include "ClickableObject.h"
#include <sstream>

using namespace std;

ClickableObject::ClickableObject()
{
	rec.width = rec.height = rec.x = rec.y = 0;
}
ClickableObject::~ClickableObject() { }

void ClickableObject::Init(double width, double height, double x, double y, const char* name)
{
	rec.width = width;
	rec.height = height;
	rec.x = x;
	rec.y = y;
	this->name = name;
	nameLength = strlen(name);
}

bool ClickableObject::Clicked(Vector2 pos)
{
	//Check to see if a given position is within the button's rectangle
	if (rec.x < pos.x && pos.x < rec.width + rec.x && rec.y < pos.y && pos.y < rec.height + rec.y)
		return true;
	else
		return false;
}

void ClickableObject::Draw()
{
	DrawRectangleRec(rec, RAYWHITE);
	DrawRectangleLinesEx(rec, 2, GRAY);
	DrawText(name, rec.x + rec.width / 2 - MENUTEXTSIZE / 2.0 * nameLength / 2.0, rec.y + rec.height / 2.0 - MENUTEXTSIZE / 2.0, MENUTEXTSIZE, BLACK);
}