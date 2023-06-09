#pragma once
#include "raylib.h"
#include "GameDefines.h"
#include "Paddle.h"
/// <summary>
/// Basic power up with no effects
/// </summary>
class PowerUp
{
public:
	Vector2 _position;
	double _size;
	bool _active = false;
	double _powerTimeLimit = 0;
	double _powerTimer = 0;
	bool _counting = false;
	bool _doDrawVisuals = false;
	Color _color;

public:
	/// <summary>
/// Power up contructor with a random position
/// <param name="Color"></param>
/// 	<param name="Size"></param>
/// </summary>
	PowerUp(Color Color, double Size);
	/// <summary>
/// Power up contructor with a given position
/// </summary>
/// <param name="Color"></param>
///	<param name="Size"></param>
/// <param name="Position"></param>
	PowerUp(Color Color, double Size, Vector2 Position);
	/// <summary>
/// Power up destructor
/// </summary>
	~PowerUp();

	/// <summary>
/// Does the effect of the power up
/// </summary>
	virtual void DoEffect();
	/// <summary>
/// If the power up stays for some time, this counts down till the power up ends
/// </summary>
	void DoCountDown();
	/// <summary>
/// Undoes the effects of the power up
/// </summary>
	virtual void UndoEffect();
	/// <summary>
/// Draws the power up
/// </summary>
	virtual void DrawObject();
	/// <summary>
/// Draw the visuals for the power up if there are any
/// </summary>
	virtual void DrawVisuals();
};
/// <summary>
/// Power up that grants a bonus point on collection
/// </summary>
class ExtraPoint : public PowerUp
{
public:
	int _value;
public:
	/// <summary>
	/// Extra point constructor
	/// <param name="Value"></param>
	/// <param name="Score"></param>
	///	<param name="Color"></param>
	/// <param name="Size"></param>
	/// </summary>
	ExtraPoint(int GivenValue, int* Score, Color Color, double Size);
	/// <summary>
/// Grants an extra point
/// </summary>
	void DoEffect() override;
	/// <summary>
	/// Draw the power up
	/// </summary>
	void DrawObject() override;
	/// <summary>
/// Draw the visuals for the power up if there are any
/// </summary>
	void DrawVisuals() override;

private:
	int* _gameScore;
};
/// <summary>
/// A power up that slow time on collection
/// </summary>
class TimeSlow : public PowerUp
{
private:
	double _slownessStrength = 1;
public:
	/// <summary>
	/// Time slow power up contructor
	/// <param name="Time Scale"></param>
	///	<param name="Color"></param>
	/// <param name="Size"></param>
	/// <param name="Effect Time"></param>
	/// <param name="Effect Strength"></param>
	/// </summary>
	TimeSlow(double* TimeScale, Color Color, double Size, double EffectTime, double EffectStrength);
	/// <summary>
	/// Slows time down
	/// </summary>
	void DoEffect() override;
	/// <summary>
	/// Reverts time back to normal
	/// </summary>
	void UndoEffect() override;
	/// <summary>
	/// Draws the power up
	/// </summary>
	void DrawObject() override;
	/// <summary>
	/// Draws the visual effects for the power up
	/// </summary>
	void DrawVisuals() override;
private:
	double* _timeScale;
};
/// <summary>
/// A power up that adds a second paddle opposite the player
/// </summary>
class DoubleUp : public PowerUp
{
public:
	/// <summary>
	/// Double up contructor
	/// <param name="Counter"></param>
	/// <param name="List"></param>
	/// <param name="Color"></param>
	/// <param name="Size"></param>
	/// <param name="Effect Time"></param>
	/// </summary>
	DoubleUp(int* Counter, Paddle* List, Color Color, double Size, double EffectTime);
	/// <summary>
	/// Adds the second paddle
	/// </summary>
	void DoEffect() override;
	/// <summary>
	/// Removes the second paddle
	/// </summary>
	void UndoEffect() override;
	/// <summary>
	/// Draws the power up object
	/// </summary>
	void DrawObject() override;
	/// <summary>
	/// Draws the power up visuals
	/// </summary>
	void DrawVisuals() override;
private:
	int* _paddleCount;
	Paddle* _paddlePoint;
};