#pragma once

#include <GL/glut.h>
#include "Vec3.h"

#define WIDTH 1000
#define HEIGHT 1000

//Vec3f& Transform(Vec3f& normalized)
//{
//	//const float zInv = 1.0f / normalized.z;
//	normalized.x = (normalized.x+1.0f)  * (float(WIDTH) / 2.0f);
//	normalized.y = (normalized.y+1.0f)  * (float(HEIGHT) / 2.0f);
//	return normalized;
//}

Vec3f& Transform(Vec3f& normalized)
{
	//const float zInv = 1.0f / normalized.z;
	normalized.x = (normalized.x + 1) * (float(WIDTH) / 2.0f);
	normalized.y = (normalized.y + 1) * (float(HEIGHT) / 2.0f);
	return normalized;
}
