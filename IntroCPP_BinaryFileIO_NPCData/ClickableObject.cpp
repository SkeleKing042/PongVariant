#include "ClickableObject.h"

using namespace std;

ClickableObject::ClickableObject()
{
}
ClickableObject::~ClickableObject(){}

void ClickableObject::Init(double width, double height, double x, double y)
{
	rec.width = width;
	rec.height = height;
	rec.x = x;
	rec.y = y;
}

bool ClickableObject::Clicked(Vector2 pos)
{
	if (rec.x < pos.x && pos.x < rec.width + rec.x && rec.y < pos.y && pos.y < rec.height + rec.y)
		return true;
	else
		return false;
}