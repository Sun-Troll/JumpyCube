#pragma once
#include "Graphics.h"

class JumpyCube
{
public:
	JumpyCube(const Vec2& startPos, int startLives);
	RectF GetRect() const;
	void Update(float gravity, float friction, float ft);
	void ClampScreen();
	void Draw(Graphics& gfx) const;
private:
	Vec2 posCenter;
	Vec2 vel{ 0.0f, 0.0f };
	static constexpr float jumpVelMin = 10.0f;
	static constexpr float jumpVelMax = 100.0f;
	float jumpVel;
	int nLives;
	static constexpr float halfDim = 10.0f;
	static constexpr Color c = Colors::White;
};