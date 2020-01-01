#pragma once
#include "Graphics.h"

class Platform
{
public:
	enum class State
	{
		Uninitialized,
		Free,
		Live,
		Touched,
		Deadly
	};
public:
	void Spawn();
	void Activate();
	void Update(float speedUp, float ft);
	void ClampScreen();
	RectF GetRect() const;
	Vec2 GetVel() const;
	State GetState() const;
	void SetState(State stateSet);
	void Draw(Graphics& gfx) const;
private:
	Vec2 posCenter{ 0.0f, 0.0f };
	Vec2 vel{ 0.0f, 0.0f };
	float halfWidth;
	float halfHeight;
	State state = State::Uninitialized;
	static constexpr Color colFree = Colors::Green;
	static constexpr Color colLive = Colors::Magenta;
	static constexpr Color colTouched = Colors::Blue;
	static constexpr Color colDeadly = Colors::Red;
	bool isActive = false;
};