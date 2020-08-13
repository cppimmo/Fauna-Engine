#include "SkySphere.h"
#include <DDSTextureLoader.h>
#include "Utility/Util.h"
#include "Utility/Error.h"
#include "Graphics/VertexTypes.h"
#include <vector>

using namespace DirectX;

bool SkySphere::init(ID3D11Device* pDevice, ID3D11DeviceContext* pContext, std::wstring& filePath) try 
{
	HRESULT hr = S_OK;
	this->pContext = pContext;

	std::vector<VertexSkybox> vertices = {
		{ -1.0f, -1.0f, -1.0f },
		{ -1.0f,  1.0f, -1.0f },
		{  1.0f,  1.0f, -1.0f },
		{  1.0f, -1.0f, -1.0f },
		//back face          
		{ -1.0f, -1.0f, 1.0f },
		{  1.0f, -1.0f, 1.0f },
		{  1.0f, 1.0f,  1.0f },
		{ -1.0f, 1.0f,  1.0f },
		//top face            
		{ -1.0f, 1.0f, -1.0f },
		{ -1.0f, 1.0f,  1.0f },
		{  1.0f, 1.0f,  1.0f },
		{  1.0f, 1.0f, -1.0f },
		//bottom face        
		{ -1.0f, -1.0f, -1.0f },
		{  1.0f, -1.0f, -1.0f },
		{  1.0f, -1.0f,  1.0f },
		{ -1.0f, -1.0f,  1.0f },
		//left face          
		{ -1.0f, -1.0f,  1.0f },
		{ -1.0f,  1.0f,  1.0f },
		{ -1.0f,  1.0f, -1.0f },
		{ -1.0f, -1.0f, -1.0f },
		//right face         
		{  1.0f, -1.0f, -1.0f },
		{  1.0f,  1.0f, -1.0f },
		{  1.0f,  1.0f,  1.0f },
		{  1.0f, -1.0f,  1.0f },
	};
	
	std::vector<DWORD> indices = {
		// Front Face
		2,  1,  0,
		3,  2,  0,
		// Back Face
		6,  5,  4,
		7,  6,  4,
		// Top Face
		10,  9, 8,
		11, 10, 8,
		// Bottom Face
		14, 13, 12,
		15, 14, 12,
		// Left Face
		18, 17, 16,
		19, 18, 16,
		// Right Face
		22, 21, 20,
		23, 22, 20 
	};

	hr = vertexBuffer.init(pDevice, vertices.data(), vertices.size());
	THROW_IF_FAILED(hr, "Vertex buffer creation failed.");
	hr = indexBuffer.init(pDevice, indices.data(), indices.size());
	THROW_IF_FAILED(hr, "Index buffer creation failed.");
	hr = constantBuffer.init(pDevice, pContext);
	THROW_IF_FAILED(hr, "Constant buffer creation failed.");
	return true;
} catch (HrException& e) {
	ErrorLogger::Log(e);
	return false;
}

void SkySphere::bind(VertexShader& vs, PixelShader& ps)
{
	pContext->VSSetShader(vs.getVertexShader(), nullptr, 0u);
	pContext->PSSetShader(ps.getPixelShader(), nullptr, 0u);
	pContext->PSSetShaderResources(0, 1, cubeMap.getTexture());
	const UINT offset = 0u;
	pContext->IASetVertexBuffers(0u, 1u, vertexBuffer.getBuffer(), vertexBuffer.getStridePtr(), &offset);
	pContext->IASetIndexBuffer(indexBuffer.getBuffer(), DXGI_FORMAT_R32_UINT, 0u);
	pContext->IASetInputLayout(vs.getInputLayout());
	pContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
}

void SkySphere::draw(/*ID3D11DeviceContext* pContext,*/ Camera& camera)
{
	world = XMMatrixIdentity();
	scale = XMMatrixScaling(5.0f, 5.0f, 5.0f);
	translation = XMMatrixTranslation(
		XMVectorGetX(camera.getPosition()),
		XMVectorGetY(camera.getPosition()),
		XMVectorGetZ(camera.getPosition())
	);
	world = scale * translation;
	
	constantBuffer.data.WVP = XMMatrixTranspose(world * camera.getView() * camera.getProjection());
	pContext->VSSetConstantBuffers(0, 1, constantBuffer.getBuffer());
	constantBuffer.update();

	pContext->DrawIndexed(indexBuffer.getIndexCount(), 0u, 0u);
}

void SkySphere::unbind()
{
	pContext->VSSetShader(nullptr, nullptr, 0u);
	pContext->PSSetShader(nullptr, nullptr, 0u);
	pContext->IASetVertexBuffers(0u, 0u, nullptr, nullptr, nullptr);
	pContext->IASetIndexBuffer(nullptr, DXGI_FORMAT_R32_UINT, 0u);
}
