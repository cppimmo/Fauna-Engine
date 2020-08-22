#include "Terrain.h"
#include <vector>
#include <DirectXMath.h>

using namespace DirectX;

bool Terrain::Init(Graphics& gfx, float width, float depth, UINT m, UINT n)
{
	UINT vertexCount = m * n;
	UINT faceCount = (m - 1) * (n - 1) * 2;

	std::vector<VertexColor> vertices;
	std::vector<DWORD> indices;
	vertices.resize(vertexCount);
	indices.resize(faceCount);

	//Create vertices.
	float halfWidth = 0.5f * width;
	float halfDepth = 0.5f * depth;

	float dx = width / (n - 1);
	float dz = depth / (m - 1);

	for (std::size_t i = 0; i < m; ++i)
	{
		float z = halfDepth - i * dz;
		for (std::size_t j = 0; j < n; ++j)
		{
			float x = -halfWidth + j * dx;

			vertices[i * n + j].pos = XMFLOAT3(x, 0.0f, z);
		}
	}

	UINT k = 0;
	for (std::size_t i = 0; i < m - 1; ++i)
	{
		for (std::size_t j = 0; j < n - 1; ++j)
		{
			indices[k] = i * n + j;
			indices[k + 1] = i * n + j + 1;
			indices[k + 2] = (i + 1) * n + j;
			indices[k + 3] = (i + 1) * n + j;
			indices[k + 4] = i * n + j + 1;
			indices[k + 5] = (i + 1) * n + j + 1;

			k += 6; // next quad
		}
	}

	for (std::size_t i = 0; i < vertexCount; ++i)
	{
		XMFLOAT3 p = vertices[i].pos;
		p.y = GetHeight(p.x, p.z);

		vertices[i].pos = p;

		if (p.y < -10.0f)
		{
			vertices[i].color = XMFLOAT4(1.0f, 0.96f, 0.62f, 1.0f);
		}
		else if (p.y < -5.0f)
		{
			vertices[i].color = XMFLOAT4(0.48f, 0.77f, 0.46f, 1.0f);
		}
		else if (p.y < 12.0f)
		{
			vertices[i].color = XMFLOAT4(0.1f, 0.48f, 0.19f, 1.0f);
		}
		else if (p.y < 20.0f)
		{
			vertices[i].color = XMFLOAT4(0.45f, 0.39f, 0.34f, 1.0f);
		}
		else
		{
			vertices[i].color = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
		}
	}

	if (!vBuffer.Init(gfx, vertices.data(), vertices.size()))
		return false;
	if (!iBuffer.Init(gfx, indices.data(), indices.size()))
		return false;
	if (!vsCBuffer.Init(gfx))
		return false;
}

void Terrain::Bind(Graphics& gfx, VertexShader& vs, PixelShader& ps)
{
	
}

void Terrain::Draw(Graphics& gfx)
{
}

void Terrain::Unbind(Graphics& gfx)
{
}
