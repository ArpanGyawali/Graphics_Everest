#pragma once

#define PI 3.1428
#include "Vec3.h"

class Mat4f
{
public:
	float elements[4][4];
	Mat4f& operator=(const Mat4f& rhs)
	{
		memcpy(elements, rhs.elements, sizeof(elements));
		return *this;
	}
	/*Mat4& operator*=(T rhs)
	{
		for (auto& row : elements)
		{
			for (T& e : row)
			{
				e *= rhs;
			}
		}
		return *this;
	}*/

	Mat4f operator*(float rhs) const
	{
		Mat4f result = *this;
		return result = result * rhs;
	}

	Mat4f operator*(const Mat4f& rhs) const
	{
		Mat4f result;
		for (size_t i = 0; i < 4; i++)
		{
			for (size_t j = 0; j < 4; j++)
			{
				float sum = 0.0;
				for (size_t k = 0; k < 4; k++)
				{
					sum += elements[i][k] * rhs.elements[k][j];
				}
				result.elements[i][j] = sum;
			}
		}
		return result;
	}

	constexpr static Mat4f Identity()
	{
		return {
			1.0,0.0,0.0,0.0,
			0.0,1.0,0.0,0.0,
			0.0,0.0,1.0,0.0,
			0.0,0.0,0.0,1.0,
		};
	}

	constexpr static Mat4f Scaling(float factor)
	{
		return {
			factor,0.0,0.0,0.0,
			0.0,factor,0.0,0.0,
			0.0,0.0,factor,0.0,
			0.0,0.0,0.0,1.0,
		};
	}

	static Mat4f RotationZ(float theta)
	{
		const float sinTheta = sin(theta);
		const float cosTheta = cos(theta);	
		return {
			cosTheta, -sinTheta,0.0,0.0,
			sinTheta, cosTheta,0.0,0.0,
			0.0,      0.0,     1.0,0.0,
			0.0,	  0.0,    0.0,1.0,
		};
	}

	static Mat4f RotationY(float theta)
	{
		const float sinTheta = sin(theta);
		const float cosTheta = cos(theta);
		return {
			cosTheta, 0.0,sinTheta,0.0,
			0.0, 1.0,0.0,0.0,
			-sinTheta,      0.0,     cosTheta,0.0,
			0.0,	  0.0,    0.0,1.0,
		};
	}

	static Mat4f RotationX(float theta)
	{
		const float sinTheta = sin(theta);
		const float cosTheta = cos(theta);
		return {
			1.0, 0.0,   0.0,  0.0,
			0.0, cosTheta, -sinTheta,0.0,
			0.0, sinTheta, cosTheta,0.0,
			0.0, 0.0,   0.0,  1.0,
		};
	}

	/*template<class V>
	constexpr static Mat4 Translation(const V& tl)
	{
		return Translation(tl.x, tl.y, tl.z);
	}*/

	constexpr static Mat4f Translation(float tx, float ty, float tz)
	{
		return {
			1.0,0.0,0.0,tx,
			0.0,1.0,0.0,ty,
			0.0,0.0,1.0,tz,
			0.0,0.0,0.0,1.0,
		};
	}

	static Mat4f RotView(Vec3f right, Vec3f up, Vec3f dir)
	{
		return {
			right.x,right.y,right.z,0.0f,
			up.x,up.y,up.z,0.0f,
			dir.x,dir.y,dir.z,0.0f,
			0.0f,0.0f,0.0f,1.0f,
		};
	}

	static Mat4f TranslateView(Vec3f pos)
	{
		return {
			1.0f,0.0f,0.0f,-pos.x,
			0.0f,1.0f,0.0f,-pos.y,
			0.0f,0.0f,1.0f,-pos.z,
			0.0f,0.0f,0.0f,1.0f,
		};
	}

	static Mat4f PerspectiveFOV(float fov, float ar, float fNear, float fFar)
	{
		float fovRad = 1.0f / tanf(fov * 0.5f / 180.0f * 3.14159f);
		return {
			ar * fovRad, 0.0, 0.0, 0.0,
			0.0, fovRad, 0.0, 0.0,
			0.0, 0.0, fFar / (fFar - fNear), (-fFar * fNear) / (fFar - fNear),
			0.0, 0.0, -1.0, 0.0,
		};
	}

	Vec3f operator*(const Vec3f& lhs)
	{
		return{
			lhs.x * elements[0][0] + lhs.y * elements[0][1] + lhs.z * elements[0][2] + lhs.w * elements[0][3],
			lhs.x * elements[1][0] + lhs.y * elements[1][1] + lhs.z * elements[1][2] + lhs.w * elements[1][3],
			lhs.x * elements[2][0] + lhs.y * elements[2][1] + lhs.z * elements[2][2] + lhs.w * elements[2][3],
			lhs.x * elements[3][0] + lhs.y * elements[3][1] + lhs.z * elements[3][2] + lhs.w * elements[3][3],
		};
	}
};

//template<typename T>
//_Vec3<T>& operator*=(_Vec3<T>& lhs, const Mat4<T, 3>& rhs)
//{
//	return lhs = lhs * rhs;
//}

//template<typename T>
//Vec3<T> operator*(const _Vec3<T>& lhs, const Mat4<T, 3>& rhs)
//{
//	return{
//		lhs.x * rhs.elements[0][0] + lhs.y * rhs.elements[1][0] + lhs.z * rhs.elements[2][0],
//		lhs.x * rhs.elements[0][1] + lhs.y * rhs.elements[1][1] + lhs.z * rhs.elements[2][1],
//		lhs.x * rhs.elements[0][2] + lhs.y * rhs.elements[1][2] + lhs.z * rhs.elements[2][2]
//	};
//}

//template<typename T>
//_Vec4<T>& operator*=(_Vec4<T>& lhs, const Mat4<T, 4>& rhs)
//{
//	return lhs = lhs * rhs;
//}
