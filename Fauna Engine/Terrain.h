#pragma once

#include "Graphics/Graphics.h"
#include "Graphics/Shader/VertexShader.h"
#include "Graphics/Shader/PixelShader.h"
#include "Graphics/Buffer/VertexBuffer.h"
#include "Graphics/Buffer/IndexBuffer.h"
#include "Graphics/VertexTypes.h"
#include "Graphics/Buffer/ConstantBuffer.h"

class Terrain
{
public:
	Terrain() = default;
	~Terrain() = default;

	bool Init(Graphics& gfx, float width, float depth, UINT m, UINT n);
	void Bind(Graphics& gfx, VertexShader& vs, PixelShader& ps);
	void Draw(Graphics& gfx);
	void Unbind(Graphics& gfx);
private:
	static float GetHeight(float x, float z)
	{
		return 0.3f * (z * sinf(0.1f * x) + x * cosf(0.1f * z));
	}
private:
	VertexBuffer<VertexColor> vBuffer;
	IndexBuffer iBuffer;
	VSConstantBuffer<CB_WVP> vsCBuffer;
	DirectX::XMMATRIX WVP;
};

