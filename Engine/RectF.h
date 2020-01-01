#pragma once
#include "Vec2.h"

class RectF
{
public:
	RectF(float left_in, float right_in, float top_in, float bottom_in);
	RectF(const Vec2& leftTop, const Vec2& rightBottom);
	RectF(float halfWidth, float halfHeight, const Vec2& center);
	RectF(const Vec2& leftTop, float width, float height);
	bool IsOverlaping(const RectF rect) const;
public:
	float left;
	float right;
	float top;
	float bottom;
};