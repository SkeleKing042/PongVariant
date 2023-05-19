#pragma once

#include "GameDefines.h"
#include "raylib.h"

using namespace std;

class ClickableObject
{
public:
	Rectangle rec;
	const char* name = "";
	int nameLength = 0;

public:
	ClickableObject();
	~ClickableObject();

	void Init(double width, double height, double x, double y, const char* name);
	bool Clicked(Vector2 mosPos);
	void Draw();
};