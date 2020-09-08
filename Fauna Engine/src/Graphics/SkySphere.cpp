#include "SkySphere.h"
#include <DDSTextureLoader.h>
#include "Utility/Util.h"
#include "Utility/Error.h"
#include "Graphics/VertexTypes.h"
#include <vector>

using namespace DirectX;

bool SkySphere::Init(Graphics& gfx, std::wstring& filePath) try 
{
	HRESULT hr = S_OK;
	this->pContext = gfx.getContext();
	/*std::vector<VertexSkybox> vertices = {
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

	//hr = vertexBuffer.init(pDevice, vertices.data(), vertices.size());
	//THROW_IF_FAILED(hr, "Vertex buffer creation failed.");
	//hr = indexBuffer.init(pDevice, indices.data(), indices.size());
	//THROW_IF_FAILED(hr, "Index buffer creation failed.");
	//hr = constantBuffer.init(pDevice, pContext);
	//THROW_IF_FAILED(hr, "Constant buffer creation failed.");
	//if (!cubeMap.load(pDevice, filePath))
	//	THROW_NORMAL("Failed to load cubemap texture");*/
	int LatLines = 10;
	int LongLines = 10;

	int NumSphereVertices = ((LatLines - 2) * LongLines) + 2;
	int NumSphereFaces = ((LatLines - 3) * (LongLines) * 2) + (LongLines * 2);

	float sphereYaw = 0.0f;
	float spherePitch = 0.0f;

	std::vector<Vertex> vertices(NumSphereVertices);

	XMVECTOR currVertPos = XMVectorSet(0.0f, 0.0f, 1.0f, 0.0f);

	vertices[0].pos.x = 0.0f;
	vertices[0].pos.y = 0.0f;
	vertices[0].pos.z = 1.0f;

	for (std::size_t i = 0; i < LatLines - 2; ++i)
	{
		spherePitch = (i + 1) * (3.14 / (LatLines - 1));
		XMMATRIX Rotationx = XMMatrixRotationX(spherePitch);
		for (std::size_t j = 0; j < LongLines; ++j)
		{
			sphereYaw = j * (6.28 / (LongLines));
			XMMATRIX Rotationy = XMMatrixRotationZ(sphereYaw);
			currVertPos = XMVector3TransformNormal(XMVectorSet(0.0f, 0.0f, 1.0f, 0.0f), (Rotationx * Rotationy));
			currVertPos = XMVector3Normalize(currVertPos);
			vertices[i * LongLines + j + 1].pos.x = XMVectorGetX(currVertPos);
			vertices[i * LongLines + j + 1].pos.y = XMVectorGetY(currVertPos);
			vertices[i * LongLines + j + 1].pos.z = XMVectorGetZ(currVertPos);
		}
	}

	vertices[NumSphereVertices - 1].pos.x = 0.0f;
	vertices[NumSphereVertices - 1].pos.y = 0.0f;
	vertices[NumSphereVertices - 1].pos.z = -1.0f;

	hr = vertexBuffer.Init(gfx, vertices.data(), vertices.size());
	THROW_IF_FAILED(hr, "Vertex buffer creation failed.");

	std::vector<DWORD> indices(NumSphereFaces * 3);

	int k = 0;
	for (std::size_t l = 0; l < LongLines - 1; ++l)
	{
		indices[k] = 0;
		indices[k + 1] = l + 1;
		indices[k + 2] = l + 2;
		k += 3;
	}

	indices[k] = 0;
	indices[k + 1] = LongLines;
	indices[k + 2] = 1;
	k += 3;

	for (std::size_t i = 0; i < LatLines - 3; ++i)
	{
		for (std::size_t j = 0; j < LongLines - 1; ++j)
		{
			indices[k] = i * LongLines + j + 1;
			indices[k + 1] = i * LongLines + j + 2;
			indices[k + 2] = (i + 1) * LongLines + j + 1;

			indices[k + 3] = (i + 1) * LongLines + j + 1;
			indices[k + 4] = i * LongLines + j + 2;
			indices[k + 5] = (i + 1) * LongLines + j + 2;

			k += 6; // next quad
		}

		indices[k] = (i * LongLines) + LongLines;
		indices[k + 1] = (i * LongLines) + 1;
		indices[k + 2] = ((i + 1) * LongLines) + LongLines;

		indices[k + 3] = ((i + 1) * LongLines) + LongLines;
		indices[k + 4] = (i * LongLines) + 1;
		indices[k + 5] = ((i + 1) * LongLines) + 1;

		k += 6;
	}

	for (std::size_t l = 0; l < LongLines - 1; ++l)
	{
		indices[k] = NumSphereVertices - 1;
		indices[k + 1] = (NumSphereVertices - 1) - (l + 1);
		indices[k + 2] = (NumSphereVertices - 1) - (l + 2);
		k += 3;
	}

	indices[k] = NumSphereVertices - 1;
	indices[k + 1] = (NumSphereVertices - 1) - LongLines;
	indices[k + 2] = NumSphereVertices - 2;

	hr = indexBuffer.Init(gfx, indices.data(), indices.size());
	THROW_IF_FAILED(hr, "Index buffer creation failed.");

	hr = vsCBuffer.Init(gfx);
	THROW_IF_FAILED(hr, "Constant buffer creation failed.");
	if (!cubeMap.Load(gfx, filePath))
		THROW_NORMAL("Failed to load cubemap texture");
	return true;
} catch (HrException& e) {
	ErrorLogger::Log(e);
	return false;
}

void SkySphere::Bind(Graphics& gfx, VertexShader& vs, PixelShader& ps)
{
	vs.Bind(gfx);
	ps.Bind(gfx);
	ps.SetShaderResources(gfx, 0, 1, cubeMap.getTexture());
	pContext->IASetVertexBuffers(0u, 1u, vertexBuffer.getBuffer(), vertexBuffer.getStridePtr(), vertexBuffer.getOffset());
	pContext->IASetIndexBuffer(indexBuffer.getBuffer(), DXGI_FORMAT_R32_UINT, 0u);
	gfx.setDrawMode(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
}

void SkySphere::Draw(Graphics& gfx, Camera& camera)
{
	world = XMMatrixIdentity();
	scale = XMMatrixScaling(5.0f, 5.0f, 5.0f);
	translation = XMMatrixTranslation(
		XMVectorGetX(camera.getPosition()),
		XMVectorGetY(camera.getPosition()),
		XMVectorGetZ(camera.getPosition())
	);
	world = scale * translation;
	
	vsCBuffer.data.WVP = XMMatrixTranspose(world * camera.getView() * camera.getProjection());
	vsCBuffer.Bind(gfx);
	vsCBuffer.Update(gfx);
	vsCBuffer.Unbind(gfx);

	gfx.getContext()->DrawIndexed(indexBuffer.getIndexCount(), 0u, 0u);
}

void SkySphere::Unbind(Graphics& gfx)
{
	pContext->VSSetShader(nullptr, nullptr, 0u);
	pContext->PSSetShader(nullptr, nullptr, 0u);
	pContext->IASetVertexBuffers(0u, 0u, nullptr, nullptr, nullptr);
	pContext->IASetIndexBuffer(nullptr, DXGI_FORMAT_R32_UINT, 0u);
}
