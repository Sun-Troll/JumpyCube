#include "PlayerPlatform.h"

PlayerPlatform::PlayerPlatform(const Vec2& startPos)
	:
	posCenter(startPos)
{
}

RectF PlayerPlatform::GetRect() const
{
	return RectF(halfWidth, halfHeight, posCenter);
}

void PlayerPlatform::Update(bool left, bool right, bool top, bool bottom, float ft)
{
	Vec2 moveDirection{ 0.0f, 0.0f };
	if (left)
	{
		moveDirection.x = -1.0f;
	}
	else if (right)
	{
		moveDirection.x = 1.0f;
	}
	if (top)
	{
		moveDirection.y = -1.0f;
	}
	else if (bottom)
	{
		moveDirection.y = 1.0f;
	}
	moveDirection.Normalize();
	posCenter += moveDirection * movementSpeed * ft;
}

void PlayerPlatform::ClampScreen()
{
	const RectF rect = GetRect();
	if (rect.left < 0.0f)
	{
		posCenter.x = halfWidth;
	}
	else if (rect.right > Graphics::ScreenWidth)
	{
		posCenter.x = Graphics::ScreenWidth - halfWidth;
	}
	if (rect.top < 100.0f)
	{
		posCenter.y = halfHeight + 100.0f;
	}
	else if (rect.bottom > Graphics::ScreenHeight)
	{
		posCenter.y = Graphics::ScreenHeight - halfHeight;
	}
}

void PlayerPlatform::Draw(Graphics& gfx) const
{
	switch (state)
	{
	case PlayerPlatform::State::Free:
		gfx.DrawRect(GetRect(), colFree);
		break;
	case PlayerPlatform::State::JumpyOn:
		gfx.DrawRect(GetRect(), colJumpyOn);
		break;
	case PlayerPlatform::State::Touched:
		gfx.DrawRect(GetRect(), colTouched);
		break;
	case PlayerPlatform::State::JumpyDead:
		gfx.DrawRect(GetRect(), colDead);
		break;
	case PlayerPlatform::State::jumpyResp:
		gfx.DrawRect(GetRect(), colRespawning);
		break;
	}
}

PlayerPlatform::State PlayerPlatform::GetState() const
{
	return state;
}

void PlayerPlatform::SetState(State stateSet)
{
	state = stateSet;
}

Vec2 PlayerPlatform::GetPos() const
{
	return posCenter;
}
