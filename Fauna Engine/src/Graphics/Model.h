#pragma once

#include "Win.h"
#include "Window/Window.h"
#include "Graphics/Graphics.h"
#include "Graphics/Buffer/VertexBuffer.h"
#include "Graphics/Buffer/IndexBuffer.h"
#include "Graphics/Buffer/ConstantBuffer.h"
#include "Graphics/Camera.h"
#include "Graphics/Texture/Texture.h"
#include "Camera.h"
#include "Component/Transform.h"

#include <vector>
#include <DirectXCollision.h>

#define RAW_MDL

#ifdef RAW_MDL
class Model
{
public:
	Model() = default;
	Model(const Model&) = delete;
	Model& operator=(const Model&) = delete;

	void Create(Graphics& gfx, std::vector<Vertex>& vertices);
	void Create(Graphics& gfx, std::vector<Vertex>& vertices, 
		std::vector<DWORD>& indices);

	bool isColliding(Model& model);

	void Bind(Graphics& gfx, VertexShader& vs, PixelShader& ps, Texture& tex);
	void Draw(Graphics& gfx, Camera& camera);
	void DrawImGUI() {}
	void Unbind(Graphics& gfx);
public:
	void updateMatrix(Camera& camera);
	void resetMatrix();
	void adjustPos(float x, float y, float z);
	void setPos(float x, float y, float z);
	void adjustRot(float x, float y, float z);
	void setRot(float x, float y, float z);
	void scale(float x, float y, float z);
	void setScale(float x, float y, float z);
	Transform transform;
private:
	VertexBuffer<Vertex> vertexBuffer;
	IndexBuffer indexBuffer;
	VSConstantBuffer<CB_WVP> vsCBuffer;
	PSConstantBuffer<CB_CamPos> psCBuffer;
	std::vector<Vertex> vertices;
private:
	DirectX::BoundingOrientedBox box;
	DirectX::XMMATRIX translation;
public:
	DirectX::XMMATRIX rotation;
private:
	DirectX::XMMATRIX sca;
	DirectX::XMMATRIX world;
	DirectX::XMMATRIX WVP;
	bool isIndexed = false;
	static constexpr UINT offset = 0;
};
#else
class Model
{
public:
	Model();

private:

};
#endif