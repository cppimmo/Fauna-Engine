#pragma once

/*#include "Graphics/Graphics.h"
#include "Graphics/VertexBuffer.h"
#include <Graphics/IndexBuffer.h>
#include "Graphics/ConstantBuffer.h"
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

	bool init(Graphics& gfx, const std::string& filePath);
	bool load(Graphics& gfx, const std::string& filePath);
	void processNode(Graphics& gfx, aiNode* pNode, const aiScene* pScene);
	Mesh processMesh(Graphics& gfx, aiMesh* pMesh, const aiScene* pScene);
	void bind(Graphics& gfx, VertexShader& vs, PixelShader& ps, Texture& tex);
	void draw(Graphics& gfx);
	void unbind(Graphics& gfx);
public:
	Transform transform;
	VSConstantBuffer<CB_WVP> vsCBuffer;
private:
	std::vector<Mesh> meshes;
};

class Mesh
{
public:
	Mesh(Graphics& gfx, std::vector<Vertex>& vertices, std::vector<DWORD>& indices);
	Mesh(const Mesh& mesh);
	void bind() noexcept;
	void draw() noexcept;
	void unbind() noexcept;
private:
	VertexBuffer<Vertex> vertexBuffer;
	IndexBuffer indexBuffer;
	ID3D11DeviceContext* pContext;
};*/