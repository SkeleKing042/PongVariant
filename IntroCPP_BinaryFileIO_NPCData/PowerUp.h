#pragma once

#include "raylib.h"
#include "GameDefines.h"

class PowerUp
{
public:
	Vector2 _position;
	bool _active = false;
	double _powerTimeLimit = 0;
	double _powerTimer = 0;
	bool _counting = false;

public:
	PowerUp();
	PowerUp(Vector2 Position);
	~PowerUp();

	virtual void DoEffect();
	void DoCountDown();
	virtual void UndoEffect();
	virtual void DrawObject();
	virtual void DrawVisuals();
};

class ExtraPoint : public PowerUp
{
public:
	ExtraPoint(int* Score, Vector2 Position);

	void DoEffect() override;
	void DrawObject() override;
	void DrawVisuals() override;

private:
	int* _gameScore;
};

class TimeSlow : public PowerUp
{
public:
	TimeSlow(double* TimeScale, Vector2 Position);

	void DoEffect() override;
	void UndoEffect() override;
	void DrawObject() override;
	void DrawVisuals() override;
private:
	double* _timeScale;
};