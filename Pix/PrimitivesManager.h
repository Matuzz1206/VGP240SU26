#pragma once

#include "Vertex.h"

//purpose of the Primitives manager is to store all of the verticies
//render all of the shapes base on Topology
//clip/cull all of the non visible faces

enum class Topology
{
	Point,
	Line,
	Triangle
};

class PrimitivesManager
{
public:
	static PrimitivesManager* Get();

	//start accepting Vertices
	bool BeginDraw(Topology topology, bool applyTransform);
    // add vertices to the manager
	void AddVertex(const Vertex& v);
	//send all the stored vertices to render as specifies
	//by topology, to the rasterizer
	void EndDraw();
private:
	PrimitivesManager();

	std::vector<Vertex> mVertexBuffer;
	Topology mTopology = Topology::Point;
	bool mDrawBegin = false;
	bool mApplyTransform = false;
};