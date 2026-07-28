#include "Graphics.h"

#include "Clipper.h"
#include "Viewport.h"

void Graphics::NewFrame()
{
	Viewport::Get()->OnNewFrame();
	Clipper::Get()->OnNewFrame();

	Matrix4 matTrans = Matrix4::Translation(4.0f, 10.0f, 5.0f);
	Matrix4 matRotX = Matrix4::RotationX(45.0f * MathHelper::DegToRad);
	Matrix4 matRotY = Matrix4::RotationY(15.0f * MathHelper::DegToRad);
	Matrix4 matFinal = matRotX * matRotY * matTrans;
	Matrix4 matInv = MathHelper::Inverse(matFinal);
	Matrix4 matIdentity = matFinal * matInv;
}