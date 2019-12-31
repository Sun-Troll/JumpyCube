#pragma once
#include "Graphics.h"

class JumpyCube
{
public:
	JumpyCube(const Vec2& startPos, int startLives);
	RectF GetRect() const;
	void Update(float gravity, float friction, float ft);
	void ClampScreen();
	void Jump(bool charging, const Vec2& mouseVec, float ft);
	void Draw(Graphics& gfx) const;
	void DrawBorders(Graphics& gfx) const;
	void DrawJumpIn(Graphics& gfx) const;
private:
	Vec2 posCenter;
	Vec2 vel{ 0.0f, 0.0f };
	int nLives;
	static constexpr float halfDim = 10.0f;
	static constexpr Color c = Colors::White;
	//jump
	static constexpr float jumpVelMin = 3.0f;
	static constexpr float jumpVelMax = 15.0f;
	float jumpVel = jumpVelMin;
	bool jumpCharging = false;
	static constexpr float jumpChargeSpeed = 6.0f;
	const Vec2 jumpInTopLeft{ 20.0f, 50.0f }; //Why can't do static constexpr?
	static constexpr float jumpInWidth = 100.0f;
	static constexpr float jumpInHeight = 10.0f;
	static constexpr float jumpInDrawChargeRatio = jumpInWidth / (jumpVelMax - jumpVelMin);
	static constexpr Color jInColBase{ 125, 75, 25 };
	static constexpr Color jInColCharge{ 250, 150, 50 };
	//borders
	const RectF borders{ 200.0f, float(Graphics::ScreenWidth) - 200.0f, 150.0f, float(Graphics::ScreenHeight) - 50.0f };
	static constexpr float borderDrawThick = 5.0f;
	static constexpr Color borderC{ 250, 10, 10 };
	const RectF borderRectLeft{ borders.left - borderDrawThick, borders.left,
		borders.top - borderDrawThick, borders.bottom + borderDrawThick };
	const RectF borderRectRight{ borders.right, borders.right + borderDrawThick,
		borders.top - borderDrawThick, borders.bottom + borderDrawThick };
	const RectF borderRectTop{ borders.left, borders.right,
		borders.top - borderDrawThick, borders.top };
	const RectF borderRectBottom{ borders.left, borders.right,
		borders.bottom, borders.bottom + borderDrawThick };
};