#pragma once
#include "Mat4.h"
#include "Vec3.h"

Mat4f calculateLookAt(Vec3f& pos, Vec3f& target, Vec3f& up)
{
	// Calculate new forward direction
	Vec3f newForward = target - pos;
	newForward = newForward.Normalize(newForward);

	// Calculate new Up direction
	Vec3f a = newForward * up.dot(newForward);
	Vec3f newUp = up - a;
	newUp = newUp.Normalize(newUp);

	// New Right direction is easy, its just cross product
	Vec3f newRight = newUp.cross(newForward);
	Mat4f lookAt = Mat4f::RotView(newRight, newUp, newForward) * Mat4f::TranslateView(pos);
	return lookAt;
}
