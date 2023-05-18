#pragma once

#include "GameDefines.h"
#include "raylib.h"

using namespace std;

class ClickableObject
{
public:
	Rectangle rec;

public:
	ClickableObject();
	~ClickableObject();

	void Init(double width, double height, double x, double y);
	bool Clicked(Vector2 mosPos);
};