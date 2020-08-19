#pragma once

#include <d3d11.h>
#include <DirectXMath.h>
#include "Graphics/Graphics.h"
#include "Graphics/VertexBuffer.h"
#include "Graphics/IndexBuffer.h"
#include "Graphics/ConstantBuffer.h"
#include "Graphics/Shader/VertexShader.h"
#include "Graphics/Shader/PixelShader.h"
#include "Graphics/VertexTypes.h"
#include "Graphics/CubeTexture.h"
#include "Camera.h"
#include "Utility/Util.h"
#include <array>

class SkySphere
{
public:
	SkySphere() = default;
	~SkySphere() = default;

	bool Init(Graphics& gfx, std::wstring& filePath);
	void Bind(Graphics& gfx, VertexShader& vs, PixelShader& ps);
	void Draw(Graphics& gfx, Camera& camera);
	void Unbind(Graphics& gfx);
private:
	DirectX::XMMATRIX world;
	DirectX::XMMATRIX scale;
	DirectX::XMMATRIX translation;
	VertexBuffer<Vertex> vertexBuffer;
	IndexBuffer indexBuffer;
	VSConstantBuffer<CB_WVP> vsCBuffer;
	CubeTexture cubeMap;

	ID3D11DeviceContext* pContext = nullptr;
};

