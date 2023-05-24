#pragma once

#include "GameDefines.h"
#include "raylib.h"


class ClickableObject
{
public:
	Rectangle _rec;
	const char* _name = "";
	int _nameLength = 0;

public:
	ClickableObject();
	~ClickableObject();

	void Init(double width, double height, double x, double y, const char* name);
	bool Clicked(Vector2 mosPos);
	void Draw();
};