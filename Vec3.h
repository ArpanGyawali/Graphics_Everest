#pragma once
#include <vector>
#include <GL/glut.h>

class Vec3f
{
public:
	float x = 0.0,y = 0.0,z = 0.0;
	float w = 1.0;
	Vec3f() = default;
	Vec3f( float x,float y, float z )
		:
		x( x ),
		y( y ),
		z( z )
	{}
	Vec3f(float x, float y, float z, float w)
		:
		x(x),
		y(y),
		z(z),
		w(w)
	{}
	explicit operator Vec3f() const
	{
		return{ x,y,z };
	}
	float dot(const Vec3f& rhs) const
	{
		return x * rhs.x + y * rhs.y + z * rhs.z;
	}
	float length(Vec3f& v)
	{
		return sqrtf(dot(v));
	}
	Vec3f Normalize(Vec3f& v)
	{
		float l = length(v);
		return { v.x / l, v.y / l, v.z / l };
	}
	/*Vec4	operator-() const
	{
		return Vec4( -x,-y );
	}*/
	Vec3f cross(const Vec3f& rhs) const
	{
		return Vec3f(
			y * rhs.z - z * rhs.y,
			z * rhs.x - x * rhs.z,
			x * rhs.y - y * rhs.x
		);
	}
	
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
	Vec3f& operator=( const Vec3f &rhs )
	{
		x = rhs.x;
		y = rhs.y;
		z = rhs.z;
		w = rhs.w;
		return *this;
	}
	
	Vec3f& operator+=( const Vec3f &rhs )
	{
		x += rhs.x;
		y += rhs.y;
		z += rhs.z;
		return *this;
	}
	Vec3f& operator-=( const Vec3f &rhs )
	{
		x -= rhs.x;
		y -= rhs.y;
		z -= rhs.z;
		return *this;
	}
	Vec3f operator+( const Vec3f &rhs ) const
	{
		return Vec3f( *this ) += rhs;
	}
	Vec3f operator-( const Vec3f &rhs ) const
	{
		return Vec3f( *this ) -= rhs;
	}
	Vec3f& operator*=( const float &rhs )
	{
		x *= rhs;
		y *= rhs;
		z *= rhs;
		return *this;
	}
	Vec3f operator*( const float &rhs ) const			//multiply const with vector
	{
		return Vec3f( *this ) *= rhs;
	}
	Vec3f& operator*=(const Vec3f& rhs)		//for light color
	{
		{
			x *= rhs.x;
			y *= rhs.y;
			z *= rhs.z;
			return *this;
		}
	}
	Vec3f operator*(const Vec3f& rhs) const
	{
		return Vec3f(*this) *= rhs;
	}
	Vec3f& operator/=( const float &rhs )
	{
		x /= rhs;
		y /= rhs;
		z /= rhs;
		w /= rhs;
		return *this;
	}
	Vec3f operator/( const float &rhs ) const
	{
		return Vec3f( *this ) /= rhs;
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