#include "JumpyCube.h"
#include <assert.h>
#include <algorithm>

JumpyCube::JumpyCube(const Vec2& startPos, int startLives)
	:
	posCenter(startPos),
	nLives(startLives)
{
}

RectF JumpyCube::GetRect() const
{
	return RectF(halfDim, halfDim, posCenter);
}

void JumpyCube::Update(float gravity, float friction, float ft)
{
	vel.y += gravity * ft;
	vel /= pow(friction, ft);
	posCenter += vel;
}

void JumpyCube::ClampScreen()
{
	const RectF rect = GetRect();
	if (rect.left < 0.0f)
	{
		posCenter.x = halfDim;
	}
	else if (rect.right > Graphics::ScreenWidth)
	{
		posCenter.x = Graphics::ScreenWidth - halfDim;
	}
	if (rect.top < 0.0f)
	{
		posCenter.y = halfDim;
	}
	else if (rect.bottom > Graphics::ScreenHeight)
	{
		posCenter.y = Graphics::ScreenHeight - halfDim;
	}
}

void JumpyCube::Jump(bool charging, const Vec2& mouseVec, float ft)
{
	if (charging)
	{
		jumpCharging = true;
		jumpVel = std::min(jumpVel + jumpChargeSpeed * ft, jumpVelMax);
	}
	else if (!charging && jumpCharging)
	{
		jumpCharging = false;
		vel += Vec2(mouseVec - posCenter).Normalize() * jumpVel;
		jumpVel = jumpVelMin;
	}
}

void JumpyCube::Draw(Graphics& gfx) const
{
	gfx.DrawRect(GetRect(), c);
}

void JumpyCube::DrawBorders(Graphics & gfx) const
{
	gfx.DrawRect(borderRectLeft, borderC);
	gfx.DrawRect(borderRectRight, borderC);
	gfx.DrawRect(borderRectTop, borderC);
	gfx.DrawRect(borderRectBottom, borderC);
}

void JumpyCube::DrawJumpIn(Graphics& gfx) const
{
	gfx.DrawRect(RectF(jumpInTopLeft, jumpInWidth, jumpInHeight), jInColBase);
	gfx.DrawRect(RectF(jumpInTopLeft, jumpInDrawChargeRatio * (jumpVel - jumpVelMin), jumpInHeight), jInColCharge);
}
