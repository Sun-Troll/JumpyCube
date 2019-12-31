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
	if (state == State::Jumping)
	{
		vel.y += gravity * ft;
		vel /= pow(friction, ft);
		posCenter += vel;
	}
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
	if (rect.top < 100.0f)
	{
		posCenter.y = halfDim + 100.0f;
	}
	else if (rect.bottom > Graphics::ScreenHeight)
	{
		posCenter.y = Graphics::ScreenHeight - halfDim;
	}
}

void JumpyCube::Jump(bool charging, const Vec2& mouseVec, float ft)
{
	if (state == State::Jumping || state == State::Respawning) //change jumping to sticking
	{
		if (charging)
		{
			jumpCharging = true;
			jumpVel = std::min(jumpVel + jumpChargeSpeed * ft, jumpVelMax);
		}
		else if (!charging && jumpCharging)
		{
			if (state == State::Respawning)
			{
				state = State::Jumping;
				mustJumpRespawnCounter = 0.0f;
				posCenter = Vec2(Graphics::ScreenWidth / 2.0f, Graphics::ScreenHeight / 2.0f);
				vel = Vec2(0.0f, 0.0f);
			}
			jumpCharging = false;
			vel += Vec2(mouseVec - posCenter).Normalize() * jumpVel;
			jumpVel = jumpVelMin;
		}
	}
}

bool JumpyCube::OutsideBorders()
{
	const RectF rect = GetRect();
	if (state != State::Dead && state != State::Respawning
		&& (rect.left < borders.left || rect.right > borders.right || rect.top < borders.top || rect.bottom > borders.bottom))
	{
		nLives--;
		state = State::Dead;
		respawnCounter = 0.0f;
		return true;
	}
	return false;
}

bool JumpyCube::Respawn(float ft)
{
	if (state == State::Dead)
	{
		respawnCounter += ft;
		if (respawnCounter >= respawnTime)
		{
			state = State::Respawning;
			respawnCounter = 0.0f;
			return true;
		}
	}
	else if (state == State::Respawning)
	{
		posCenter = Vec2(Graphics::ScreenWidth / 2.0f, Graphics::ScreenHeight / 2.0f);
		mustJumpRespawnCounter += ft;
		if (mustJumpRespawnCounter >= mustJumpRespawnTime)
		{
			state = State::Jumping;
			mustJumpRespawnCounter = 0.0f;
			vel = Vec2(0.0f, 0.0f);
		}
	}
	return false;
}

void JumpyCube::Draw(Graphics& gfx) const
{
	switch (state)
	{
	case JumpyCube::State::Jumping:
		gfx.DrawRect(GetRect(), colJumping);
		break;
	case JumpyCube::State::Sticking:
		gfx.DrawRect(GetRect(), colSticking);
		break;
	case JumpyCube::State::Dead:
		gfx.DrawRect(GetRect(), colDead);
		break;
	case JumpyCube::State::Respawning:
		gfx.DrawRect(GetRect(), colRespawning);
		break;
	default:
		break;
	}
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

void JumpyCube::DrawLives(Graphics& gfx) const
{
	for (int life = 0; life < nLivesMax; life++)
	{
		const RectF rect{ Vec2(livesDrawTopLeft + Vec2((LivesDrawDim + LivesDrawPadding) * float(life), 0.0f)),
			LivesDrawDim, LivesDrawDim };
		gfx.DrawRect(rect, LivesBaseC);
	}
	for (int life = 0; life < nLives; life++)
	{
		const RectF rect{ Vec2(livesDrawTopLeft + Vec2((LivesDrawDim + LivesDrawPadding) * float(life), 0.0f)),
			LivesDrawDim, LivesDrawDim };
		gfx.DrawRect(rect, LiveCurC);
	}
}
