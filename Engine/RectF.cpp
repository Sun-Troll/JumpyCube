#include "RectF.h"

RectF::RectF(float left_in, float right_in, float top_in, float bottom_in)
	:
	left(left_in),
	right(right_in),
	top(top_in),
	bottom(bottom_in)
{
}

RectF::RectF(const Vec2 & leftTop, const Vec2 & rightBottom)
	:
	left(leftTop.x),
	right(rightBottom.x),
	top(leftTop.y),
	bottom(rightBottom.y)
{
}
