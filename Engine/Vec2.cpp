#include "Vec2.h"

Vec2::Vec2(float xIn, float yIn)
	:
	x(xIn),
	y(yIn)
{
}

Vec2 Vec2::operator+(const Vec2& rhs) const
{
	return Vec2(x + rhs.x, y + rhs.y);
}

Vec2& Vec2::operator+=(const Vec2& rhs)
{
	return *this = *this + rhs;
}

Vec2 Vec2::operator-(const Vec2& rhs) const
{
	return Vec2(x - rhs.x, y - rhs.y);
}

Vec2& Vec2::operator-=(const Vec2& rhs)
{
	return *this = *this - rhs;
}

Vec2 Vec2::operator*(float rhs) const
{
	return Vec2(x * rhs, y * rhs);
}

Vec2& Vec2::operator*=(float rhs)
{
	return *this = *this * rhs;
}

Vec2 Vec2::operator/(float rhs) const
{
	return Vec2(x / rhs, y / rhs);
}

Vec2& Vec2::operator/=(float rhs)
{
	return *this = *this / rhs;
}
