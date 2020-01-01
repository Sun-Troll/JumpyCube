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
		posCenter += vel * ft;
	}
	else if (state == State::Sticking)
	{
		if (stickingToPlat)
		{
			posCenter += vel * ft;
		}
		else
		{
			vel = Vec2(0.0f, 0.0f);
		}
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

void JumpyCube::Jump(PlayerPlatform& playform, bool charging, const Vec2& mouseVec, float ft)
{
	if (state == State::Sticking || state == State::Respawning)
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
				mustJumpRespawnCounter = 0.0f;
			}
			jumpCharging = false;
			vel += Vec2(mouseVec - posCenter).Normalize() * jumpVel;
			state = State::Jumping;
			if (stickingToPlat)
			{
				stickingToPlat = false;
			}
			else
			{
				playform.SetState(PlayerPlatform::State::Touched);
			}
			jumpVel = jumpVelMin;
		}
	}
}

void JumpyCube::StickPlayform(PlayerPlatform& playform)
{
	if (GetRect().IsOverlaping(playform.GetRect()) && state == State::Jumping
		&& playform.GetState() == PlayerPlatform::State::Free)
	{
		state = State::Sticking;
		playform.SetState(PlayerPlatform::State::JumpyOn);
	}
}

bool JumpyCube::StickPlats(Platform& plat)
{
	if (GetRect().IsOverlaping(plat.GetRect()) && state == State::Jumping
		&& plat.GetState() == Platform::State::Free)
	{
		state = State::Sticking;
		plat.SetState(Platform::State::Touched);
		stickingToPlat = true;
		vel = plat.GetVel();
		return true;
	}
	return false;
}

bool JumpyCube::OutsideBorders(PlayerPlatform& playform)
{
	const RectF rect = GetRect();
	if (state != State::Dead && state != State::Respawning
		&& (rect.left < borders.left || rect.right > borders.right || rect.top < borders.top || rect.bottom > borders.bottom))
	{
		nLives--;
		state = State::Dead;
		playform.SetState(PlayerPlatform::State::JumpyDead);
		respawnCounter = 0.0f;
		return true;
	}
	return false;
}

bool JumpyCube::Respawn(PlayerPlatform& playform, float ft)
{
	if (state == State::Dead)
	{
		respawnCounter += ft;
		if (respawnCounter >= respawnTime)
		{
			state = State::Respawning;
			playform.SetState(PlayerPlatform::State::jumpyResp);
			respawnCounter = 0.0f;
			posCenter = Vec2(playform.GetPos());
			vel = Vec2(0.0f, 0.0f);
			jumpCharging = false;
			jumpVel = jumpVelMin;
			return true;
		}
	}
	else if (state == State::Respawning)
	{
		posCenter = Vec2(playform.GetPos());
		mustJumpRespawnCounter += ft;
		if (mustJumpRespawnCounter >= mustJumpRespawnTime)
		{
			state = State::Jumping;
			playform.SetState(PlayerPlatform::State::Touched);
			mustJumpRespawnCounter = 0.0f;
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

void JumpyCube::DrawBorders(Graphics& gfx) const
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
