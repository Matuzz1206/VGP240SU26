#include "PrimitivesManager.h"
#include "Rasterizer.h"
#include "Clipper.h"
#include "MatrixStack.h"
#include "Camera.h"

extern float gResolutionX;
extern float gResolutionY;

namespace 
{
    Matrix4 GetScreenTransform() 
    {
		const float hw = gResolutionX * 0.5f;
		const float hh = gResolutionY * 0.5f;
        return{
            hw, 0.0f, 0.0f, 0.0f,
            0.0f, -hh, 0.0f, 0.0f,
            0.0f, 0.0f, 1.0f, 0.0f,
            hw, hh, 0.0f, 1.0f
        };
    }
}

PrimitivesManager::PrimitivesManager()
{
}
PrimitivesManager* PrimitivesManager::Get()
{
    static PrimitivesManager sInstance;
    return &sInstance;
}
bool PrimitivesManager::BeginDraw(Topology topology, bool applyTransform)
{
    mVertexBuffer.clear();
    mTopology = topology;
    mApplyTransform = applyTransform;
    mDrawBegin = true;
    return true;
}

void PrimitivesManager::AddVertex(const Vertex& v)
{
    if (mDrawBegin)
    {

        mVertexBuffer.push_back(v);
    }
}

void PrimitivesManager::EndDraw()
{

    if (!mDrawBegin)
    {
        return;

    }

    // apply transformation pipeline
	//matLocal -> matWorld - > matView -> matProj -> matScreen
	Matrix4 matWorld = MatrixStack::Get()->GetTransform();  
    //view matrix from camera
	Matrix4 matView = Camera::Get()->GetViewMatrix();
	//projection matrix from camera
	Matrix4 matProj = Camera::Get()->GetProjectionMatrix();
    // screen space matrix from the screen
	Matrix4 matScreen = GetScreenTransform();
	//full transformation pipeline
	Matrix4 matFinal = matWorld * matView * matProj * matScreen;

    switch (mTopology)
    {
    case Topology::Point:
    {
        for (uint32_t i = 0; i < mVertexBuffer.size(); ++i)
        {
            if (!Clipper::Get()->ClipPoint(mVertexBuffer[i]))
            {
                Rasterizer::Get()->Drawpoint(mVertexBuffer[i]);

            }
        }
        break;
    }
    case Topology::Line:
    {
        for (uint16_t i = 1; i < mVertexBuffer.size(); i += 2) {
            if (!Clipper::Get()->ClipLine(mVertexBuffer[i - 1], mVertexBuffer[i]))
            {

                Rasterizer::Get()->DrawLine(mVertexBuffer[i - 1], mVertexBuffer[i]);
            }
        }
        break;
    }
    case Topology::Triangle:
    {
        for (uint16_t i = 2; i < mVertexBuffer.size(); i += 3)
        {
            std::vector<Vertex> triangle = {
                mVertexBuffer[i - 2],
                 mVertexBuffer[i - 1],
                 mVertexBuffer[i]
            };
            // from local to screen space via transformation pipeline
            if (mApplyTransform)
            {
                for (size_t t = 0; t < triangle.size(); ++t)
                {
                    triangle[t].pos = MathHelper::TransformCoord(triangle[t].pos, matFinal);
                    //after convertin to screen space make sure x and y are whole numbers
                    MathHelper::FlattenVectorScreenCoord(triangle[t].pos);

                }
            }
            // all done in screen space
            if (!Clipper::Get()->ClipTriangle(triangle))
            {
                for (size_t t = 2; t < triangle.size(); ++t)
                {
                    Rasterizer::Get()->DrawTriangle(triangle[0], triangle[t - 1], triangle[t]);
                }
            }
        }

    }
    break;
    default:
        break;

    }
}