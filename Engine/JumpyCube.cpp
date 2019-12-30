#include "JumpyCube.h"

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

void JumpyCube::Draw(Graphics & gfx) const
{
	gfx.DrawRect(GetRect(), c);
}
