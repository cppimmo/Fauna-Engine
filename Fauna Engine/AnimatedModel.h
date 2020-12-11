#pragma once

#include "Graphics/Graphics.h"
#include "Graphics/VertexBuffer.h"
#include "Graphics/IndexBuffer.h"
#include "Graphics/ConstantBuffer.h"
#include "Graphics/VertexTypes.h"
#include "Graphics/Texture.h"

#include <DirectXMath.h>
#include <string>
#include <vector>

struct Joint {
	std::wstring name;
	int parentID;

	DirectX::XMFLOAT3 pos;
	DirectX::XMFLOAT4 orientation;
};

struct Weight {
	int jointID;
	float bias;
	DirectX::XMFLOAT3 pos;
};

struct Mesh {
	int texArrayIndex;
	int numTriangles;  

	std::vector<VertexMD5> vertices;
	std::vector<DWORD> indices;
	std::vector<Weight> weights;

	std::vector<DirectX::XMFLOAT3> positions;

	VertexBuffer<VertexMD5> vertexBuffer;
	IndexBuffer indexBuffer;
};

class AnimatedModel
{
public:
	AnimatedModel() = default;
	//AnimatedModel(const AnimatedModel&) = delete;
	//AnimatedModel& operator=(const AnimatedModel&) = delete;
	~AnimatedModel() = default;

	bool Load(Graphics& gfx, std::wstring& filePath, 
		std::vector<std::wstring>& texFilePaths);

	void Bind();
	void Draw();
	void Unbind();

private:
	int numMeshes;
	int numJoints;
	
	std::vector<Joint> joints;
	std::vector<Mesh> meshes;
	std::vector<Texture> textures;
	ID3D11DeviceContext* pContext = nullptr;
};

