#pragma once
#include "GameDefines.h"
#include "raylib.h"
/// <summary>
/// Buttons, essentally
/// </summary>
class ClickableObject
{
public:
	Rectangle _rec;
	Color _baseColor;
	Color _outLineColor;
	Color _textColor;
	const char* _name = "";
	int _nameLength = 0;
public:
	/// <summary>
/// Clickable Object contructor
/// </summary>
	ClickableObject();
	/// <summary>
/// Clickable Object destructor
/// </summary>
	~ClickableObject();
	/// <summary>
/// Clickable object initialisation
/// </summary>
/// <param name="Width"></param>
/// <param name="Height"></param>
/// <param name="X Position"></param>
/// <param name="Y Position"></param>
/// <param name="Name"></param>
/// 	<param name="Base Color"></param>
/// 	<param name="Outline Color"></param>
/// 	<param name="Text Color"></param>
	void Init(double Width, double Height, double xPostion, double yPosition, const char* Name, Color BaseColor, Color OutlineColor, Color TextColor);
	/// <summary>
/// Checks if it has been clicked
/// <para/>"pos" is the mouse position
/// </summary>
/// <param name="Mouse Poition"></param>
/// <returns></returns>
	bool Clicked(Vector2 MousePosition);
	/// <summary>
/// Draws this Clickable Object
/// </summary>
	void Draw();
};