#include "RectF.h"
#include <assert.h>

RectF::RectF(float left_in, float right_in, float top_in, float bottom_in)
	:
	left(left_in),
	right(right_in),
	top(top_in),
	bottom(bottom_in)
{
	assert(left <= right);
	assert(top <= bottom);
}

RectF::RectF(const Vec2& leftTop, const Vec2& rightBottom)
	:
	left(leftTop.x),
	right(rightBottom.x),
	top(leftTop.y),
	bottom(rightBottom.y)
{
	assert(left <= right);
	assert(top <= bottom);
}

RectF::RectF(float halfWidth, float halfHeight, const Vec2& center)
	:
	left(center.x - halfWidth),
	right(center.x + halfWidth),
	top(center.y - halfHeight),
	bottom(center.y + halfHeight)
{
	assert(left <= right);
	assert(top <= bottom);
}

RectF::RectF(const Vec2 & leftTop, float width, float height)
	:
	left(leftTop.x),
	right(leftTop.x + width),
	top(leftTop.y),
	bottom(leftTop.y + height)
{
	assert(left <= right);
	assert(top <= bottom);
}
