#include "Platform.h"
#include <random>
#include <assert.h>

void Platform::Spawn()
{
	std::random_device rd;
	std::mt19937 rng(rd());
	std::uniform_real_distribution<float> setHalfWidth(30.0f, 80.0f);
	std::uniform_real_distribution<float> setHalfHeight(7.0f, 14.0f);
	std::uniform_real_distribution<float> yPos(160.0f, float(Graphics::ScreenHeight) - 60.0f);
	std::uniform_real_distribution<float> xVel(-100.0f, -50.0f);
	std::uniform_real_distribution<float> yVel(-20.0f, 20.0f);
	std::uniform_int_distribution<int> setState(1, 1000);

	halfWidth = setHalfWidth(rng);
	halfHeight = setHalfHeight(rng);
	posCenter = Vec2(Graphics::ScreenWidth - halfWidth, yPos(rng));
	vel = Vec2(xVel(rng), yVel(rng));
	const int stateSet = setState(rng);
	if (stateSet < 100)
	{
		state = State::Live;
	}
	else if (stateSet < 400)
	{
		state = State::Free;
	}
	else
	{
		state = State::Deadly;
	}
}

void Platform::Activate()
{
	assert(state != State::Uninitialized);
	assert(!isActive);
	assert(posCenter.x > Graphics::ScreenWidth / 2);
	isActive = true;
}

void Platform::Update(float ft)
{
	if (isActive)
	{
		posCenter += vel * ft;
	}
}

void Platform::ClampScreen()
{
	if (isActive)
	{
		const RectF rect = GetRect();
		if (rect.left < 0.0f)
		{
			isActive = false;
		}
		else if (rect.right > Graphics::ScreenWidth)
		{
			isActive = false;
		}
		if (rect.top < 100.0f)
		{
			isActive = false;
		}
		else if (rect.bottom > Graphics::ScreenHeight)
		{
			isActive = false;
		}
	}
}

RectF Platform::GetRect() const
{
	return RectF(halfWidth, halfHeight, posCenter);
}

Vec2 Platform::GetVel() const
{
	return vel;
}

Platform::State Platform::GetState() const
{
	return state;
}

void Platform::SetState(State stateSet)
{
	state = stateSet;
}

void Platform::Draw(Graphics& gfx) const
{
	if (isActive)
	{
		switch (state)
		{
		case Platform::State::Free:
			gfx.DrawRect(GetRect(), colFree);
			break;
		case Platform::State::Live:
			gfx.DrawRect(GetRect(), colLive);
			break;
		case Platform::State::Touched:
			gfx.DrawRect(GetRect(), colTouched);
			break;
		case Platform::State::Deadly:
			gfx.DrawRect(GetRect(), colDeadly);
			break;
		}
	}
}
