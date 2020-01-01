#pragma once
#include "Graphics.h"

class PlayerPlatform
{
public:
	enum class State
	{
		Free,
		JumpyOn,
		Touched,
		JumpyDead,
		jumpyResp
	};
public:
	PlayerPlatform(const Vec2& startPos);
	RectF GetRect() const;
	void Update(bool left, bool right, bool top, bool bottom, float ft);
	void ClampScreen();
	void Draw(Graphics& gfx) const;
	State GetState() const;
	void SetState(State stateSet);
	Vec2 GetPos() const;
	/*void Cheat()
	{
		state = State::Free;
	}*/
private:
	Vec2 posCenter;
	static constexpr float movementSpeed = 300.0f;
	static constexpr float halfWidth = 50.0f;
	static constexpr float halfHeight = 10.0f;
	State state = State::jumpyResp;
	static constexpr Color colFree{ 200, 200, 200 };
	static constexpr Color colJumpyOn{ 50, 50, 50 };
	static constexpr Color colTouched{ 50, 50, 200 };
	static constexpr Color colDead{ 250, 250, 10 };
	static constexpr Color colRespawning = { 250, 10, 10 };
};