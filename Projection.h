#pragma once

#include "Vec3.h"

void PerspectiveView(float zvp, Vec3f prp, Vec3f& point)
{
	const float u = (zvp - point.z) / (prp.z - point.z);
	point.x = point.x - u * (point.x - prp.x);
	point.y = point.y - u * (point.y - prp.y);
	point.z = zvp;
}