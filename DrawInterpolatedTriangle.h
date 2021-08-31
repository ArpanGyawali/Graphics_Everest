//#pragma once
//
//#include <cmath>
//#include <GL/glut.h>
//#include <vector>
//#include "Vec3.h"
//#include "Vec2.h"
//#include "Color.h"
//#include "Line.h"
//#include "Vertex.h"
//#include "Triangle.h"
//#include "TextureLoad.h"
//#include "texture.h"
//
//Image* image;
//
//void setImageTex(Image* img) {
//	image = img;
//}
//
//template<typename T>
//constexpr T interpolate(const T& src, const T& dst, float alpha)
//{
//	return src + (dst - src) * alpha;
//}
//
//void DrawTriangle(const Triangle<Vertex>& triangle, std::vector<unsigned char>& image);
//void DrawFlatTopTriangle(const Vertex& it0,
//	const Vertex& it1,
//	const Vertex& it2, std::vector<unsigned char>& image);
//void DrawFlatBottomTriangle(const Vertex& it0,
//	const Vertex& it1,
//	const Vertex& it2, std::vector<unsigned char>& image);
//void DrawFlatTriangle(const Vertex& it0,
//	const Vertex& it1,
//	const Vertex& it2,
//	const Vertex& dv0,
//	const Vertex& dv1,
//	Vertex itEdge1, std::vector<unsigned char>& image);
//
//
//void ProcessTriangle(const Vertex& v0, const Vertex& v1, const Vertex& v2, std::vector<unsigned char>& image)
//{
//	// generate triangle from 3 vertices using gs
//	// and send to post-processing
//	Triangle<Vertex> triangle = { v0, v1, v2 };
//	DrawTriangle(triangle, image);
//}
//// vertex post-processing function
//// perform perspective and viewport transformations
//// 
////void PostProcessTriangleVertices(Triangle<Vertex>& triangle)
////{
////	// perspective divide and screen transform for all 3 vertices
////	pst.Transform(triangle.v0.pos);
////	pst.Transform(triangle.v1.pos);
////	pst.Transform(triangle.v2.pos);
////	// draw the triangle
////	DrawTriangle(triangle);
////}
//// 
//// === triangle rasterization functions ===
////   it0, it1, etc. stand for interpolants
////   (values which are interpolated across a triangle in screen space)
////
//// entry point for tri rasterization
//// sorts vertices, determines case, splits to flat tris, dispatches to flat tri funcs
//void DrawTriangle(const Triangle<Vertex>& triangle, std::vector<unsigned char>& image)
//{
//	// using pointers so we can swap (for sorting purposes)
//	const Vertex* pv0 = &triangle.v0;
//	const Vertex* pv1 = &triangle.v1;
//	const Vertex* pv2 = &triangle.v2;
//	// sorting vertices by y
//	if (pv1->pos.y < pv0->pos.y) std::swap(pv0, pv1);
//	if (pv2->pos.y < pv1->pos.y) std::swap(pv1, pv2);
//	if (pv1->pos.y < pv0->pos.y) std::swap(pv0, pv1);
//	if (pv0->pos.y == pv1->pos.y) // natural flat top
//	{
//		// sorting top vertices by x
//		if (pv1->pos.x < pv0->pos.x) std::swap(pv0, pv1);
//		DrawFlatTopTriangle(*pv0, *pv1, *pv2, image);
//	}
//	else if (pv1->pos.y == pv2->pos.y) // natural flat bottom
//	{
//		// sorting bottom vertices by x
//		if (pv2->pos.x < pv1->pos.x) std::swap(pv1, pv2);
//		DrawFlatBottomTriangle(*pv0, *pv1, *pv2, image);
//	}
//	else // general triangle
//	{
//		// find splitting vertex interpolant
//		const float alphaSplit =
//			(pv1->pos.y - pv0->pos.y) /
//			(pv2->pos.y - pv0->pos.y);
//		const auto vi = interpolate(*pv0, *pv2, alphaSplit);
//		if (pv1->pos.x < vi.pos.x) // major right
//		{
//			DrawFlatBottomTriangle(*pv0, *pv1, vi, image);
//			DrawFlatTopTriangle(*pv1, vi, *pv2, image);
//		}
//		else // major left
//		{
//			DrawFlatBottomTriangle(*pv0, vi, *pv1, image);
//			DrawFlatTopTriangle(vi, *pv1, *pv2, image);
//		}
//	}
//}
//// does flat *TOP* tri-specific calculations and calls DrawFlatTriangle
//void DrawFlatTopTriangle(const Vertex& it0,
//	const Vertex& it1,
//	const Vertex& it2, std::vector<unsigned char>& image)
//{
//	// calulcate dVertex / dy
//	// change in interpolant for every 1 change in y
//	const float delta_y = it2.pos.y - it0.pos.y;
//	const auto dit0 = (it2 - it0) / delta_y;
//	const auto dit1 = (it2 - it1) / delta_y;
//	// create right edge interpolant
//	auto itEdge1 = it1;
//	// call the flat triangle render routine
//	DrawFlatTriangle(it0, it1, it2, dit0, dit1, itEdge1, image);
//}
//// does flat *BOTTOM* tri-specific calculations and calls DrawFlatTriangle
//void DrawFlatBottomTriangle(const Vertex& it0,
//	const Vertex& it1,
//	const Vertex& it2, std::vector<unsigned char>& image)
//{
//	// calulcate dVertex / dy
//	// change in interpolant for every 1 change in y
//	const float delta_y = it2.pos.y - it0.pos.y;
//	const auto dit0 = (it1 - it0) / delta_y;
//	const auto dit1 = (it2 - it0) / delta_y;
//	// create right edge interpolant
//	auto itEdge1 = it0;
//	// call the flat triangle render routine
//	DrawFlatTriangle(it0, it1, it2, dit0, dit1, itEdge1, image);
//}
//// does processing common to both flat top and flat bottom tris
//// scan over triangle in screen space, interpolate attributes,
//// invoke ps and write pixel to screen
//void DrawFlatTriangle(const Vertex& it0,
//	const Vertex& it1,
//	const Vertex& it2,
//	const Vertex& dv0,
//	const Vertex& dv1,
//	Vertex itEdge1, std::vector<unsigned char>& image)
//{
//	// create edge interpolant for left edge (always v0)
//	auto itEdge0 = it0;
//	// calculate start and end scanlines
//	const int yStart = (int)ceil(it0.pos.y - 0.5f);
//	const int yEnd = (int)ceil(it2.pos.y - 0.5f); // the scanline AFTER the last line drawn
//	// do interpolant prestep
//	itEdge0 += dv0 * (float(yStart) + 0.5f - it0.pos.y);
//	itEdge1 += dv1 * (float(yStart) + 0.5f - it0.pos.y);
//
//	float tex_width = getWidth();
//	float tex_height = getHeight();
//	float tex_xclamp = tex_width - 1.0;
//	float tex_yclamp = tex_height - 1.0;
//	for (int y = yStart; y < yEnd; y++, itEdge0 += dv0, itEdge1 += dv1)
//	{
//		// calculate start and end pixels
//		const int xStart = (int)ceil(itEdge0.pos.x - 0.5f);
//		const int xEnd = (int)ceil(itEdge1.pos.x - 0.5f); // the pixel AFTER the last pixel drawn
//		// create scanline interpolant startpoint
//		// (some waste for interpolating x,y,z, but makes life easier not having
//		//  to split them off, and z will be needed in the future anyways...)
//		auto iLine = itEdge0;
//		// calculate delta scanline interpolant / dx
//		const float dx = itEdge1.pos.x - itEdge0.pos.x;
//		const auto diLine = (itEdge1 - iLine) / dx;
//		// prestep scanline interpolant
//		iLine += diLine * (float(xStart) + 0.5f - itEdge0.pos.x);
//		for (int x = xStart; x < xEnd; x++, iLine += diLine)
//		{
//			/*if (1.0 / iLine.pos.w > depthBuf[x * WIDTH + y])
//			{*/
//            Vec3f intensity = { iLine.color.x, iLine.color.y, iLine.color.z };
//				//depthBuf[x * WIDTH + y] = 1.0 / iLine.pos.w;
//			//}
//			// invoke pixel shader and write resulting color value
//			Vec3f texCol = image->getpixel(iLine.tex.x, iLine.tex.y);
//			Vec3f colorVec = intensity * texCol;
//			Color color = { colorVec.x, colorVec.y, colorVec.z };
//			putPixel(x, y, color); 
//
//		}
//	}
//}
//
//void wireFrame(const Vertex& v0, const Vertex& v1, const Vertex& v2)
//{
//	Bressenham(v0.pos.x, v0.pos.y, v1.pos.x, v1.pos.y, RED);
//	Bressenham(v1.pos.x, v1.pos.y, v2.pos.x, v2.pos.y, RED);
//	Bressenham(v2.pos.x, v2.pos.y, v0.pos.x, v0.pos.y, RED);
//}


#pragma once

#include <cmath>
#include <GL/glut.h>
#include <vector>
#include "Vec3.h"
#include "Vec2.h"
#include "Color.h"
#include "Line.h"
#include "Vertex.h"
#include "Triangle.h"
#include "texLoad.h"


class Drawtriangle {
public:
	Image image;
	Vec3f intensity;
	Vec3f texcol;
	Vec3f colorVec;
	Color color;

	Drawtriangle(Image img)
		:
		image(img), intensity(Vec3f(0.0, 0.0, 0.0)), texcol(Vec3f(0.0, 0.0, 0.0)),
		colorVec(Vec3f(0.0, 0.0, 0.0)), color(Color{ 0.0, 0.0, 0.0 })
	{}

	void ProcessTriangle(const Vertex& v0, const Vertex& v1, const Vertex& v2)
	{
		// generate triangle from 3 vertices using gs
		// and send to post-processing
		Triangle<Vertex> triangle = { v0, v1, v2 };
		DrawTriangle(triangle);
	}

	void wireFrame(const Vertex& v0, const Vertex& v1, const Vertex& v2)
	{
		Bressenham(v0.pos.x, v0.pos.y, v1.pos.x, v1.pos.y, WHITE);
		Bressenham(v1.pos.x, v1.pos.y, v2.pos.x, v2.pos.y, WHITE);
		Bressenham(v2.pos.x, v2.pos.y, v0.pos.x, v0.pos.y, WHITE);
	}

private:
	template<typename T>
	constexpr T interpolate(const T& src, const T& dst, float alpha)
	{
		return src + (dst - src) * alpha;
	}

	// === triangle rasterization functions ===
//   it0, it1, etc. stand for interpolants
//   (values which are interpolated across a triangle in screen space)
//
// entry point for tri rasterization
// sorts vertices, determines case, splits to flat tris, dispatches to flat tri funcs
	void DrawTriangle(const Triangle<Vertex>& triangle)
	{
		// using pointers so we can swap (for sorting purposes)
		const Vertex* pv0 = &triangle.v0;
		const Vertex* pv1 = &triangle.v1;
		const Vertex* pv2 = &triangle.v2;
		// sorting vertices by y
		if (pv1->pos.y < pv0->pos.y) std::swap(pv0, pv1);
		if (pv2->pos.y < pv1->pos.y) std::swap(pv1, pv2);
		if (pv1->pos.y < pv0->pos.y) std::swap(pv0, pv1);
		if (pv0->pos.y == pv1->pos.y) // natural flat top
		{
			// sorting top vertices by x
			if (pv1->pos.x < pv0->pos.x) std::swap(pv0, pv1);
			DrawFlatTopTriangle(*pv0, *pv1, *pv2);
		}
		else if (pv1->pos.y == pv2->pos.y) // natural flat bottom
		{
			// sorting bottom vertices by x
			if (pv2->pos.x < pv1->pos.x) std::swap(pv1, pv2);
			DrawFlatBottomTriangle(*pv0, *pv1, *pv2);
		}
		else // general triangle
		{
			// find splitting vertex interpolant
			const float alphaSplit =
				(pv1->pos.y - pv0->pos.y) /
				(pv2->pos.y - pv0->pos.y);
			const auto vi = interpolate(*pv0, *pv2, alphaSplit);
			if (pv1->pos.x < vi.pos.x) // major right
			{
				DrawFlatBottomTriangle(*pv0, *pv1, vi);
				DrawFlatTopTriangle(*pv1, vi, *pv2);
			}
			else // major left
			{
				DrawFlatBottomTriangle(*pv0, vi, *pv1);
				DrawFlatTopTriangle(vi, *pv1, *pv2);
			}
		}
	}

	// does flat *TOP* tri-specific calculations and calls DrawFlatTriangle
	void DrawFlatTopTriangle(const Vertex& it0,
		const Vertex& it1,
		const Vertex& it2)
	{
		// calulcate dVertex / dy
		// change in interpolant for every 1 change in y
		const float delta_y = it2.pos.y - it0.pos.y;
		const auto dit0 = (it2 - it0) / delta_y;
		const auto dit1 = (it2 - it1) / delta_y;
		// create right edge interpolant
		auto itEdge1 = it1;
		// call the flat triangle render routine
		DrawFlatTriangle(it0, it1, it2, dit0, dit1, itEdge1);
	}

	// does flat *BOTTOM* tri-specific calculations and calls DrawFlatTriangle
	void DrawFlatBottomTriangle(const Vertex& it0,
		const Vertex& it1,
		const Vertex& it2)
	{
		// calulcate dVertex / dy
		// change in interpolant for every 1 change in y
		const float delta_y = it2.pos.y - it0.pos.y;
		const auto dit0 = (it1 - it0) / delta_y;
		const auto dit1 = (it2 - it0) / delta_y;
		// create right edge interpolant
		auto itEdge1 = it0;
		// call the flat triangle render routine
		DrawFlatTriangle(it0, it1, it2, dit0, dit1, itEdge1);
	}

	// does processing common to both flat top and flat bottom tris
// scan over triangle in screen space, interpolate attributes,
// invoke ps and write pixel to screen
	void DrawFlatTriangle(const Vertex& it0,
		const Vertex& it1,
		const Vertex& it2,
		const Vertex& dv0,
		const Vertex& dv1,
		Vertex itEdge1)
	{
		// create edge interpolant for left edge (always v0)
		auto itEdge0 = it0;
		// calculate start and end scanlines
		const int yStart = (int)ceil(it0.pos.y - 0.5f);
		const int yEnd = (int)ceil(it2.pos.y - 0.5f); // the scanline AFTER the last line drawn
		// do interpolant prestep
		itEdge0 += dv0 * (float(yStart) + 0.5f - it0.pos.y);
		itEdge1 += dv1 * (float(yStart) + 0.5f - it0.pos.y);

		for (int y = yStart; y < yEnd; y++, itEdge0 += dv0, itEdge1 += dv1)
		{
			// calculate start and end pixels
			const int xStart = (int)ceil(itEdge0.pos.x - 0.5f);
			const int xEnd = (int)ceil(itEdge1.pos.x - 0.5f); // the pixel AFTER the last pixel drawn
			// create scanline interpolant startpoint
			// (some waste for interpolating x,y,z, but makes life easier not having
			//  to split them off, and z will be needed in the future anyways...)
			auto iLine = itEdge0;
			// calculate delta scanline interpolant / dx
			const float dx = itEdge1.pos.x - itEdge0.pos.x;
			const auto diLine = (itEdge1 - iLine) / dx;
			// prestep scanline interpolant
			iLine += diLine * (float(xStart) + 0.5f - itEdge0.pos.x);
			for (int x = xStart; x < xEnd; x++, iLine += diLine)
			{
				/*if (1.0 / iLine.pos.w > depthBuf[x * WIDTH + y])
				{*/
				intensity = { iLine.color.x, iLine.color.y, iLine.color.z };
				//depthBuf[x * WIDTH + y] = 1.0 / iLine.pos.w;
			//}
			// invoke pixel shader and write resulting color value
				texcol = image.getpixel(iLine.tex.x, iLine.tex.y);
				colorVec = intensity * (texcol/255.0);
				color = { colorVec.x, colorVec.y, colorVec.z };
				putPixel(x, y, color);

			}
		}
	}

};












