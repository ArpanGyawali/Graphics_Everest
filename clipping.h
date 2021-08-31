//#pragma once
//#include "Vec3.h"
//#include "Vec2.h"
//#include "Light.h"
//#include "triangles.h"
//
//Vec3f Vector_IntersectPlane(Vec3f& plane_p, Vec3f& plane_n, Vec3f& lineStart, Vec3f& lineEnd, float& t)
//{
//	plane_n = plane_n.Normalize(plane_n);
//	float plane_d = -plane_n.dot(plane_p);
//	float ad = lineStart.dot(plane_n);
//	float bd = lineEnd.dot(plane_n);
//	t = (-plane_d - ad) / (bd - ad);
//	Vec3f lineStartToEnd = lineEnd - lineStart;
//	Vec3f lineToIntersect = lineStartToEnd * t;
//	return lineStart + lineToIntersect;
//}
//
//int Triangle_ClipAgainstPlane(Vec3f plane_p, Vec3f plane_n, triangle& in_tri, triangle& out_tri1, triangle& out_tri2)
//{
//	// Make sure plane normal is indeed normal
//	plane_n = plane_n.Normalize(plane_n);
//
//	// Return signed shortest distance from point to plane, plane normal must be normalised
//	auto dist = [&](Vec3f& p)
//	{
//		Vec3f n = p.Normalize(p);
//		return (plane_n.x * p.x + plane_n.y * p.y + plane_n.z * p.z - plane_n.dot(plane_p));
//	};
//
//	// Create two temporary storage arrays to classify points either side of plane
//	// If distance sign is positive, point lies on "inside" of plane
//	Vec3f* inside_points[3];  int nInsidePointCount = 0;
//	Vec3f* outside_points[3]; int nOutsidePointCount = 0;
//	/*Vec2f* inside_tex[3]; int nInsideTexCount = 0;
//	Vec2f* outside_tex[3]; int nOutsideTexCount = 0;*/
//
//	// Ge t signed distance of each point in triangle to plane
//	float d0 = dist(in_tri.p[0]);
//	float d1 = dist(in_tri.p[1]);
//	float d2 = dist(in_tri.p[2]);
//
//	if (d0 >= 0) { inside_points[nInsidePointCount++] = &in_tri.p[0]; /*inside_tex[nInsideTexCount++] = &in_tri.t[0];*/ }
//	else { outside_points[nOutsidePointCount++] = &in_tri.p[0]; /*outside_tex[nOutsideTexCount++] = &in_tri.t[0];*/ }
//	if (d1 >= 0) { inside_points[nInsidePointCount++] = &in_tri.p[1]; /*inside_tex[nInsideTexCount++] = &in_tri.t[1];*/	}
//	else { outside_points[nOutsidePointCount++] = &in_tri.p[1]; /*outside_tex[nOutsideTexCount++] = &in_tri.t[1];*/	}
//	if (d2 >= 0) { inside_points[nInsidePointCount++] = &in_tri.p[2]; /*inside_tex[nInsideTexCount++] = &in_tri.t[2];*/	}
//	else { outside_points[nOutsidePointCount++] = &in_tri.p[2]; /*outside_tex[nOutsideTexCount++] = &in_tri.t[2];*/	}
//
//	// Now classify triangle points, and break the input triangle into 
//	// smaller output triangles if required. There are four possible
//	// outcomes...
//
//	if (nInsidePointCount == 0)
//	{
//		// All points lie on the outside of plane, so clip whole triangle
//		// It ceases to exist
//
//		return 0; // No returned triangles are valid
//	}
//
//	if (nInsidePointCount == 3)
//	{
//		// All points lie on the inside of plane, so do nothing
//		// and allow the triangle to simply pass through
//		out_tri1 = in_tri;
//
//		return 1; // Just the one returned original triangle is valid
//	}
//
//	if (nInsidePointCount == 1 && nOutsidePointCount == 2)
//	{
//		// Triangle should be clipped. As two points lie outside
//		// the plane, the triangle simply becomes a smaller triangle
//
//		// Copy appearance info to new triangle
//		out_tri1.c[0] = in_tri.c[0];
//		out_tri1.c[1] = in_tri.c[1];
//		out_tri1.c[2] = in_tri.c[2];
//
//
//		// The inside point is valid, so keep that...
//		out_tri1.p[0] = *inside_points[0];
//		//out_tri1.t[0] = *inside_tex[0];
//
//		// but the two new points are at the locations where the 
//		// original sides of the triangle (lines) intersect with the plane
//		float t;
//		out_tri1.p[1] = Vector_IntersectPlane(plane_p, plane_n, *inside_points[0], *outside_points[0], t);
//		/*out_tri1.t[1].x = t * (outside_tex[0]->x - inside_tex[0]->x) + inside_tex[0]->x;
//		out_tri1.t[1].y = t * (outside_tex[0]->y - inside_tex[0]->y) + inside_tex[0]->y;
//		out_tri1.t[1].w = t * (outside_tex[0]->w - inside_tex[0]->w) + inside_tex[0]->w;*/
//
//		out_tri1.p[2] = Vector_IntersectPlane(plane_p, plane_n, *inside_points[0], *outside_points[1], t);
//		/*out_tri1.t[2].x = t * (outside_tex[1]->x - inside_tex[0]->x) + inside_tex[0]->x;
//		out_tri1.t[2].y = t * (outside_tex[1]->y - inside_tex[0]->y) + inside_tex[0]->y;
//		out_tri1.t[2].w = t * (outside_tex[1]->w - inside_tex[0]->w) + inside_tex[0]->w;*/
//
//		return 1; // Return the newly formed single triangle
//	}
//
//	if (nInsidePointCount == 2 && nOutsidePointCount == 1)
//	{
//		// Triangle should be clipped. As two points lie inside the plane,
//		// the clipped triangle becomes a "quad". Fortunately, we can
//		// represent a quad with two new triangles
//
//		// Copy appearance info to new triangles
//		out_tri1.c[0] = in_tri.c[0];
//		out_tri1.c[1] = in_tri.c[1];
//		out_tri1.c[2] = in_tri.c[2];
//
//		out_tri2.c[0] = in_tri.c[0];
//		out_tri2.c[1] = in_tri.c[1];
//		out_tri2.c[2] = in_tri.c[2];
//
//		// The first triangle consists of the two inside points and a new
//		// point determined by the location where one side of the triangle
//		// intersects with the plane
//		out_tri1.p[0] = *inside_points[0];
//		out_tri1.p[1] = *inside_points[1];
//		/*out_tri1.t[0] = *inside_tex[0];
//		out_tri1.t[1] = *inside_tex[1];*/
//
//		float t;
//		out_tri1.p[2] = Vector_IntersectPlane(plane_p, plane_n, *inside_points[0], *outside_points[0], t);
//		/*out_tri1.t[2].x = t * (outside_tex[0]->x - inside_tex[0]->x) + inside_tex[0]->x;
//		out_tri1.t[2].y = t * (outside_tex[0]->y - inside_tex[0]->y) + inside_tex[0]->y;
//		out_tri1.t[2].w = t * (outside_tex[0]->w - inside_tex[0]->w) + inside_tex[0]->w;*/
//
//		// The second triangle is composed of one of he inside points, a
//		// new point determined by the intersection of the other side of the 
//		// triangle and the plane, and the newly created point above
//		out_tri2.p[0] = *inside_points[1];
//		//out_tri2.t[0] = *inside_tex[1];
//		out_tri2.p[1] = out_tri1.p[2];
//		//out_tri2.t[1] = out_tri1.t[2];
//		out_tri2.p[2] = Vector_IntersectPlane(plane_p, plane_n, *inside_points[1], *outside_points[0], t);
//		//out_tri2.t[2].x = t * (outside_tex[0]->x - inside_tex[1]->x) + inside_tex[1]->x;
//		//out_tri2.t[2].y = t * (outside_tex[0]->y - inside_tex[1]->y) + inside_tex[1]->y;
//		//out_tri2.t[2].w = t * (outside_tex[0]->w - inside_tex[1]->w) + inside_tex[1]->w;
//
//		return 2; // Return two newly formed triangles which form a quad
//	}
//}
#pragma once
#include "Vec3.h"
#include "Vec2.h"
#include "Light.h"
#include "triangles.h"

Vec3f Vector_IntersectPlane(Vec3f& plane_p, Vec3f& plane_n, Vec3f& lineStart, Vec3f& lineEnd, float& t)
{
	plane_n = plane_n.Normalize(plane_n);
	float plane_d = -plane_n.dot(plane_p);
	float ad = lineStart.dot(plane_n);
	float bd = lineEnd.dot(plane_n);
	t = (-plane_d - ad) / (bd - ad);
	Vec3f lineStartToEnd = lineEnd - lineStart;
	Vec3f lineToIntersect = lineStartToEnd * t;
	return lineStart + lineToIntersect;
}

int Triangle_ClipAgainstPlane(Vec3f plane_p, Vec3f plane_n, triangle& in_tri, triangle& out_tri1, triangle& out_tri2)
{
	// Make sure plane normal is indeed normal
	plane_n = plane_n.Normalize(plane_n);

	// Return signed shortest distance from point to plane, plane normal must be normalised
	auto dist = [&](Vec3f& p)
	{
		Vec3f n = p.Normalize(p);
		return (plane_n.x * p.x + plane_n.y * p.y + plane_n.z * p.z - plane_n.dot(plane_p));
	};

	// Create two temporary storage arrays to classify points either side of plane
	// If distance sign is positive, point lies on "inside" of plane
	Vec3f* inside_points[3];  int nInsidePointCount = 0;
	Vec3f* outside_points[3]; int nOutsidePointCount = 0;
	Vec2f* inside_tex[3]; int nInsideTexCount = 0;
	Vec2f* outside_tex[3]; int nOutsideTexCount = 0;

	// Ge t signed distance of each point in triangle to plane
	float d0 = dist(in_tri.p[0]);
	float d1 = dist(in_tri.p[1]);
	float d2 = dist(in_tri.p[2]);

	if (d0 >= 0) { inside_points[nInsidePointCount++] = &in_tri.p[0]; inside_tex[nInsideTexCount++] = &in_tri.t[0]; }
	else { outside_points[nOutsidePointCount++] = &in_tri.p[0]; outside_tex[nOutsideTexCount++] = &in_tri.t[0]; }
	if (d1 >= 0) { inside_points[nInsidePointCount++] = &in_tri.p[1]; inside_tex[nInsideTexCount++] = &in_tri.t[1]; }
	else { outside_points[nOutsidePointCount++] = &in_tri.p[1]; outside_tex[nOutsideTexCount++] = &in_tri.t[1]; }
	if (d2 >= 0) { inside_points[nInsidePointCount++] = &in_tri.p[2]; inside_tex[nInsideTexCount++] = &in_tri.t[2]; }
	else { outside_points[nOutsidePointCount++] = &in_tri.p[2]; outside_tex[nOutsideTexCount++] = &in_tri.t[2]; }

	// Now classify triangle points, and break the input triangle into 
	// smaller output triangles if required. There are four possible
	// outcomes...

	if (nInsidePointCount == 0)
	{
		// All points lie on the outside of plane, so clip whole triangle
		// It ceases to exist

		return 0; // No returned triangles are valid
	}

	if (nInsidePointCount == 3)
	{
		// All points lie on the inside of plane, so do nothing
		// and allow the triangle to simply pass through
		out_tri1 = in_tri;

		return 1; // Just the one returned original triangle is valid
	}

	if (nInsidePointCount == 1 && nOutsidePointCount == 2)
	{
		// Triangle should be clipped. As two points lie outside
		// the plane, the triangle simply becomes a smaller triangle

		// Copy appearance info to new triangle
		out_tri1.c[0] = in_tri.c[0];
		out_tri1.c[1] = in_tri.c[1];
		out_tri1.c[2] = in_tri.c[2];


		// The inside point is valid, so keep that...
		out_tri1.p[0] = *inside_points[0];
		out_tri1.t[0] = *inside_tex[0];

		// but the two new points are at the locations where the 
		// original sides of the triangle (lines) intersect with the plane
		float t;
		out_tri1.p[1] = Vector_IntersectPlane(plane_p, plane_n, *inside_points[0], *outside_points[0], t);
		out_tri1.t[1].x = t * (outside_tex[0]->x - inside_tex[0]->x) + inside_tex[0]->x;
		out_tri1.t[1].y = t * (outside_tex[0]->y - inside_tex[0]->y) + inside_tex[0]->y;
		out_tri1.t[1].w = t * (outside_tex[0]->w - inside_tex[0]->w) + inside_tex[0]->w;

		out_tri1.p[2] = Vector_IntersectPlane(plane_p, plane_n, *inside_points[0], *outside_points[1], t);
		out_tri1.t[2].x = t * (outside_tex[1]->x - inside_tex[0]->x) + inside_tex[0]->x;
		out_tri1.t[2].y = t * (outside_tex[1]->y - inside_tex[0]->y) + inside_tex[0]->y;
		out_tri1.t[2].w = t * (outside_tex[1]->w - inside_tex[0]->w) + inside_tex[0]->w;

		return 1; // Return the newly formed single triangle
	}

	if (nInsidePointCount == 2 && nOutsidePointCount == 1)
	{
		// Triangle should be clipped. As two points lie inside the plane,
		// the clipped triangle becomes a "quad". Fortunately, we can
		// represent a quad with two new triangles

		// Copy appearance info to new triangles
		out_tri1.c[0] = in_tri.c[0];
		out_tri1.c[1] = in_tri.c[1];
		out_tri1.c[2] = in_tri.c[2];

		out_tri2.c[0] = in_tri.c[0];
		out_tri2.c[1] = in_tri.c[1];
		out_tri2.c[2] = in_tri.c[2];

		// The first triangle consists of the two inside points and a new
		// point determined by the location where one side of the triangle
		// intersects with the plane
		out_tri1.p[0] = *inside_points[0];
		out_tri1.p[1] = *inside_points[1];
		out_tri1.t[0] = *inside_tex[0];
		out_tri1.t[1] = *inside_tex[1];

		float t;
		out_tri1.p[2] = Vector_IntersectPlane(plane_p, plane_n, *inside_points[0], *outside_points[0], t);
		out_tri1.t[2].x = t * (outside_tex[0]->x - inside_tex[0]->x) + inside_tex[0]->x;
		out_tri1.t[2].y = t * (outside_tex[0]->y - inside_tex[0]->y) + inside_tex[0]->y;
		out_tri1.t[2].w = t * (outside_tex[0]->w - inside_tex[0]->w) + inside_tex[0]->w;

		// The second triangle is composed of one of he inside points, a
		// new point determined by the intersection of the other side of the 
		// triangle and the plane, and the newly created point above
		out_tri2.p[0] = *inside_points[1];
		out_tri2.t[0] = *inside_tex[1];
		out_tri2.p[1] = out_tri1.p[2];
		out_tri2.t[1] = out_tri1.t[2];
		out_tri2.p[2] = Vector_IntersectPlane(plane_p, plane_n, *inside_points[1], *outside_points[0], t);
		out_tri2.t[2].x = t * (outside_tex[0]->x - inside_tex[1]->x) + inside_tex[1]->x;
		out_tri2.t[2].y = t * (outside_tex[0]->y - inside_tex[1]->y) + inside_tex[1]->y;
		out_tri2.t[2].w = t * (outside_tex[0]->w - inside_tex[1]->w) + inside_tex[1]->w;

		return 2; // Return two newly formed triangles which form a quad
	}
}