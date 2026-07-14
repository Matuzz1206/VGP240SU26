#pragma once

#include "mathHelper.h"
#include "XColors.h"

struct Vertex
{
	Vector3 pos; // position of the vertex
	X::Color color; // color of the vertex

};

inline Vector3 LerpPosition(const Vector3& a, const Vector3& b, float t)
{
	return
	{
		a.x + (b.x - a.x) * t,
		a.y + (b.y - a.y) * t,
		a.z + (b.z - a.z) * t
	};
}

inline X::Color LerpColor(const X::Color& a, const X::Color& b, float t)
{
	return
	{
		a.x + (b.x - a.x) * t,
		a.y + (b.y - a.y) * t,
		a.z + (b.z - a.z) * t,
		a.a + (b.a - a.a) * t
	};
}

inline Vertex LerpVertex(const Vertex& a, const Vertex& b, float t)
{
	{
		Vertex v;
		v.pos = LerpPosition(a.pos, b.pos, t);
		v.color = LerpColor(a.color, b.color, t);

		//Because this is typically done in screen space, x and y shold be "pixel positions"
		//To convert float to int/index it std::floor(pos.y + 0.5f)
		//This is to get Pixel position when all is calculated
		//Otherwise in some functions, the floats miss checks and program infinite loops
		v.pos.x = floorf(v.pos.x + 0.5f);
		v.pos.y = floorf(v.pos.y + 0.5f);

		return v;
	};
}