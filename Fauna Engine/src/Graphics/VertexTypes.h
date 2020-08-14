#pragma once

#include <DirectXMath.h>

struct Vertex2D
{
	Vertex2D(float x, float y, float u,
		float v) : pos(x, y, 0.0f), uv(u, v)
	{ }
	DirectX::XMFLOAT3 pos;
	DirectX::XMFLOAT2 uv;
};

struct VertexColor2D
{
	VertexColor2D(float x, float y, float r, float g, float b, float a = 1.0f)
		: pos(x, y, 0.0f), color{ r, g, b, a }
	{ }
	VertexColor2D(float x, float y, float r, DirectX::XMVECTORF32 col)
		: pos(x, y, 0.0f), color{ col }
	{ }
	DirectX::XMFLOAT3 pos;
	DirectX::XMVECTORF32 color;
};

struct Vertex
{
	Vertex() {}
	Vertex(float x, float y, float z,
		float u, float v)
		: pos(x, y, z), uv(u, v)
	{ }
	DirectX::XMFLOAT3 pos;
	DirectX::XMFLOAT2 uv;
};

struct VertexMD5
{
	VertexMD5() {}
	VertexMD5(float x, float y, float z, 
		float u, float v,
		float nx, float ny, float nz, 
		float tx, float ty, float tz)
		: pos(x, y, z), texCoord(u, v), normal(nx, ny, nz),
		tangent(tx, ty, tz)
	{}
	DirectX::XMFLOAT3 pos;
	DirectX::XMFLOAT2 texCoord;
	DirectX::XMFLOAT3 normal;
	DirectX::XMFLOAT3 tangent;
	DirectX::XMFLOAT3 biTangent;

	int StartWeight;
	int WeightCount;
};

struct VertexSkybox
{
	VertexSkybox(float x, float y, float z)
		: pos(x, y, z)
	{ }
	DirectX::XMFLOAT3 pos;
};

struct VertexColor
{
private:
	typedef unsigned char uchar;
public:
	VertexColor(float x, float y, float z,
		uchar r, uchar g, uchar b, uchar a = 1.0f)
		: pos(x, y, z), r(r), g(g), b(b), a(a)
	{ }
	DirectX::XMFLOAT3 pos;
	uchar r, g, b, a;
};
