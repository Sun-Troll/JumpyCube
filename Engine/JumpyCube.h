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
	static constexpr float jumpInHeight = 5.0f;
	static constexpr float jumpInDrawChargeRatio = jumpInWidth / (jumpVelMax - jumpVelMin);
	static constexpr Color jInColBase{ 125, 75, 25 };
	static constexpr Color jInColCharge{ 250, 150, 50 };
};