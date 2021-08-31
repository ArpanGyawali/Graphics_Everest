//#pragma once
//
//#include "Vec3.h"
//#include "Vec2.h"
//#include "Color.h"
//
//class Vertex
//{
//public:
//	Vec3f pos;
//	//Vec2f tex;
//	Vec3f normal;
//	Vec3f color;
//public:
//	Vertex() = default;
//	/*Vertex(const Vec3f& pos)
//		:
//		pos(pos)
//	{}
//	Vertex(const Vec3f& pos, const Vertex& src)
//		:
//		color(src.color),
//		pos(pos)
//	{}*/
//	Vertex(const Vec3f& pos/*, const Vec2f& tex*/, const Vec3f& normal, const Vec3f& color)
//		:
//		color(color),
//		normal(normal),
//		pos(pos)
//		//tex(tex)
//	{}
//	Vertex& operator+=(const Vertex& rhs)
//	{
//		pos += rhs.pos;
//		//tex += rhs.tex;
//		color += rhs.color;
//		return *this;
//	}
//	Vertex operator+(const Vertex& rhs) const
//	{
//		return Vertex(*this) += rhs;
//	}
//	Vertex& operator-=(const Vertex& rhs)
//	{
//		pos -= rhs.pos;
//		//tex -= rhs.tex;
//		color -= rhs.color;
//		return *this;
//	}
//	Vertex operator-(const Vertex& rhs) const
//	{
//		return Vertex(*this) -= rhs;
//	}
//	Vertex& operator*=(float rhs)
//	{
//		pos *= rhs;
//		//tex *= rhs;
//		color *= rhs;
//		return *this;
//	}
//	Vertex operator*(float rhs) const
//	{
//		return Vertex(*this) *= rhs;
//	}
//	Vertex& operator/=(float rhs)
//	{
//		pos /= rhs;
//		//tex /= rhs;
//		color /= rhs;
//		return *this;
//	}
//	Vertex operator/(float rhs) const
//	{
//		return Vertex(*this) /= rhs;
//	}
//};

#pragma once

#include "Vec3.h"
#include "Vec2.h"
#include "Color.h"

class Vertex
{
public:
	Vec3f pos;
	Vec2f tex;
	Vec3f normal;
	Vec3f color;
public:
	Vertex() = default;
	/*Vertex(const Vec3f& pos)
		:
		pos(pos)
	{}
	Vertex(const Vec3f& pos, const Vertex& src)
		:
		color(src.color),
		pos(pos)
	{}*/
	Vertex(const Vec3f& pos, const Vec2f& tex, const Vec3f& normal, const Vec3f& color)
		:
		color(color),
		normal(normal),
		pos(pos),
		tex(tex)
	{}
	Vertex& operator+=(const Vertex& rhs)
	{
		pos += rhs.pos;
		tex += rhs.tex;
		color += rhs.color;
		return *this;
	}
	Vertex operator+(const Vertex& rhs) const
	{
		return Vertex(*this) += rhs;
	}
	Vertex& operator-=(const Vertex& rhs)
	{
		pos -= rhs.pos;
		tex -= rhs.tex;
		color -= rhs.color;
		return *this;
	}
	Vertex operator-(const Vertex& rhs) const
	{
		return Vertex(*this) -= rhs;
	}
	Vertex& operator*=(float rhs)
	{
		pos *= rhs;
		tex *= rhs;
		color *= rhs;
		return *this;
	}
	Vertex operator*(float rhs) const
	{
		return Vertex(*this) *= rhs;
	}
	Vertex& operator/=(float rhs)
	{
		pos /= rhs;
		tex /= rhs;
		color /= rhs;
		return *this;
	}
	Vertex operator/(float rhs) const
	{
		return Vertex(*this) /= rhs;
	}
};