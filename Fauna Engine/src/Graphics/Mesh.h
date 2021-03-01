#pragma once

#include "Graphics/Graphics.h"
#include "Graphics/Buffer/VertexBuffer.h"
#include "Graphics/Buffer/IndexBuffer.h"
#include "Graphics/Buffer/ConstantBuffer.h"
#include "Graphics/Texture.h"
#include "Graphics/Camera.h"
#include "Component/Transform.h"

#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>
#include <assimp/scene.h>

#include <vector>

class Mesh;

class Model3D
{
public:
	Model3D() = default;
	Model3D(const Model3D&) = delete;
	Model3D& operator=(const Model3D&) = delete;
	~Model3D() = default;

	bool Init(Graphics& gfx, const std::string& filePath);
	void Bind(Graphics& gfx, VertexShader& vs, PixelShader& ps, Texture& tex);
	void Draw(Graphics& gfx, Camera& camera);
	void Unbind(Graphics& gfx);
private:
	Transform transform;
	VSConstantBuffer<CB_WVP> vsCBuffer;
	PSConstantBuffer<CB_CamPos> psCBuffer;
private:	
	bool Load(Graphics& gfx, const std::string& filePath);	
	void processNode(Graphics& gfx, aiNode* pNode, const aiScene* pScene);
	Mesh processMesh(Graphics& gfx, aiMesh* pMesh, const aiScene* pScene);
	std::vector<Mesh> meshes;
};

class Mesh
{
public:
	Mesh(Graphics& gfx, std::vector<Vertex>& vertices, std::vector<DWORD>& indices);
	Mesh(const Mesh& mesh);
	void Bind() noexcept;
	void Draw() noexcept;
	void Unbind() noexcept;
private:
	VertexBuffer<Vertex> vertexBuffer;
	IndexBuffer indexBuffer;
	ID3D11DeviceContext* pContext;
};