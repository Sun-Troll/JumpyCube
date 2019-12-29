#pragma once

class Vec2
{
public:
	Vec2(float xIn, float yIn);
	Vec2 operator+ (const Vec2& rhs) const;
	Vec2& operator+= (const Vec2& rhs);
	Vec2 operator- (const Vec2& rhs) const;
	Vec2& operator-= (const Vec2& rhs);
	Vec2 operator* (float rhs) const;
	Vec2& operator*= (float rhs);
	Vec2 operator/ (float rhs) const;
	Vec2& operator/= (float rhs);
private:
	float x;
	float y;
};