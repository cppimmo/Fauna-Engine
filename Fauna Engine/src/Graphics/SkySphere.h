#pragma once

#include <d3d11.h>
#include <DirectXMath.h>
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

	bool init(ID3D11Device* pDevice, ID3D11DeviceContext* pContext,
		std::wstring& filePath);
	void bind(VertexShader& vs, PixelShader& ps);
	void draw(/*ID3D11DeviceContext* pContext,*/ Camera& camera);
	void unbind();
private:
	DirectX::XMMATRIX world;
	DirectX::XMMATRIX scale;
	DirectX::XMMATRIX translation;
	VertexBuffer<VertexSkybox> vertexBuffer;
	IndexBuffer indexBuffer;
	ConstantBuffer<CB_WVP> constantBuffer;
	CubeTexture cubeMap;
	ID3D11DeviceContext* pContext;
};

