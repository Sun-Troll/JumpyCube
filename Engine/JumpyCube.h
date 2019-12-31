#pragma once
#include "Graphics.h"

class JumpyCube
{
public:
	enum class State
	{
		Jumping,
		Sticking,
		Dead,
		Respawning
	};
public:
	JumpyCube(const Vec2& startPos, int startLives);
	RectF GetRect() const;
	void Update(float gravity, float friction, float ft);
	void ClampScreen();
	void Jump(bool charging, const Vec2& mouseVec, float ft);
	bool OutsideBorders();
	bool Respawn(float ft);
	//drawing
	void Draw(Graphics& gfx) const;
	void DrawBorders(Graphics& gfx) const;
	void DrawJumpIn(Graphics& gfx) const;
	void DrawLives(Graphics& gfx) const;
private:
	Vec2 posCenter;
	Vec2 vel{ 0.0f, 0.0f };
	static constexpr float halfDim = 10.0f;
	static constexpr Color colJumping = Colors::White;
	static constexpr Color colSticking = Colors::Gray;
	static constexpr Color colDead{ 250, 100, 100 };
	static constexpr Color colRespawning = { 250, 250, 100 };
	State state = State::Jumping;
	static constexpr float respawnTime = 3.0f;
	float respawnCounter = 0.0f;
	float mustJumpRespawnTime = 5.0f;
	float mustJumpRespawnCounter = 0.0f;
	//lives
	static constexpr int nLivesMax = 34;
	int nLives = 10;
	static constexpr float LivesDrawDim = 30.0f;
	static constexpr float LivesDrawPadding = 20.0f;
	const Vec2 livesDrawTopLeft{ 50.0f, 20.0f };
	static constexpr Color LivesBaseC{ 50, 125, 125 };
	static constexpr Color LiveCurC{ 100, 250, 250 };
	//jump
	static constexpr float jumpVelMin = 3.0f;
	static constexpr float jumpVelMax = 15.0f;
	float jumpVel = jumpVelMin;
	bool jumpCharging = false;
	static constexpr float jumpChargeSpeed = 6.0f;
	const Vec2 jumpInTopLeft{ 50.0f, 80.0f }; //Why can't do static constexpr?
	static constexpr float jumpInWidth = 200.0f;
	static constexpr float jumpInHeight = 20.0f;
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