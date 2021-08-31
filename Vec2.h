#pragma once
#include <vector>
#include <GL/glut.h>

class Vec2f
{
public:
	float x = 0.0, y = 0.0;
	float w = 1.0;
	Vec2f() = default;
	Vec2f(float x, float y)
		:
		x(x),
		y(y)
	{}
	Vec2f(float x, float y, float w)
		:
		x(x),
		y(y),
		w(w)
	{}
	explicit operator Vec2f() const
	{
		return{ x,y };
	}
	float dot(const Vec2f& rhs) const
	{
		return x * rhs.x + y * rhs.y;
	}
	float length(Vec2f& v)
	{
		return sqrtf(dot(v));
	}
	Vec2f Normalize(Vec2f& v)
	{
		float l = length(v);
		return { v.x / l, v.y / l };
	}
	/*Vec4	operator-() const
	{
		return Vec4( -x,-y );
	}*/

	/*Vec3& max()
	{
		if (x < 0)
			x = 0;
		if (y < 0)
			y = 0;
		if (z < 0)
			z = 0;
		return *this;
	}*/
	Vec2f& operator=(const Vec2f& rhs)
	{
		x = rhs.x;
		y = rhs.y;
		w = rhs.w;
		return *this;
	}

	Vec2f& operator+=(const Vec2f& rhs)
	{
		x += rhs.x;
		y += rhs.y;
		return *this;
	}
	Vec2f& operator-=(const Vec2f& rhs)
	{
		x -= rhs.x;
		y -= rhs.y;
		return *this;
	}
	Vec2f operator+(const Vec2f& rhs) const
	{
		return Vec2f(*this) += rhs;
	}
	Vec2f operator-(const Vec2f& rhs) const
	{
		return Vec2f(*this) -= rhs;
	}
	Vec2f& operator*=(const float& rhs)
	{
		x *= rhs;
		y *= rhs;
		return *this;
	}
	Vec2f operator*(const float& rhs) const			//multiply const with vector
	{
		return Vec2f(*this) *= rhs;
	}
	Vec2f& operator*=(const Vec2f& rhs)		//for light color
	{
		{
			x *= rhs.x;
			y *= rhs.y;
			return *this;
		}
	}
	Vec2f operator*(const Vec2f& rhs) const
	{
		return Vec2f(*this) *= rhs;
	}
	Vec2f& operator/=(const float& rhs)
	{
		x /= rhs;
		y /= rhs;
		w /= rhs;
		return *this;
	}
	Vec2f operator/(const float& rhs) const
	{
		return Vec2f(*this) /= rhs;
	}
	//bool	operator==( const Vec4 &rhs ) const
	//{
	//	return x == rhs.x && y == rhs.y;
	//}
	//bool	operator!=( const Vec4 &rhs ) const
	//{
	//	return !(*this == rhs);
	//}
};