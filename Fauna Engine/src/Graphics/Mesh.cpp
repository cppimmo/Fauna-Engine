#include "Graphics/Mesh.h"
#include "Utility/Error.h"
#include "Utility/Util.h"
/*
using namespace DirectX;

/*Model::Model(Graphics& gfx)
	: pGfx(&gfx)
{
}

Model::~Model()
{
}

void Model::create(std::vector<Vertex>& vertices)
{
	HRESULT hr = S_OK;

	hr = vertexBuffer.init(pGfx->getDevice(), vertices.data(), vertices.size());
	ErrorLogger::Log(hr, L"Vertex buffer initialization failed");

	hr = constantBuffer.init(pGfx->getDevice(), pGfx->getContext());
	ErrorLogger::Log(hr, L"const buffer init failed");
	/*vertexCount = vertices.size();
	D3D11_BUFFER_DESC bd = {};
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = sizeof(Vertex) * vertexCount;
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bd.CPUAccessFlags = 0;
	bd.MiscFlags = 0;

	D3D11_SUBRESOURCE_DATA sd = {};
	sd.pSysMem = vertices.data();

	hr = pGfx->getDevice()->CreateBuffer(&bd, &sd, &pVertexBuffer);
	ErrorLogger::Log(hr, L"Create Buffer failed");

	D3D11_BUFFER_DESC cbd = {};
	cbd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	cbd.Usage = D3D11_USAGE_DYNAMIC;
	cbd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	//cbd.Usage = D3D11_USAGE_DEFAULT;//D3D11_USAGE_DYNAMIC
	//cbd.CPUAccessFlags = 0u;//D3D11_CPU_ACCESS_WRITE
	cbd.MiscFlags = 0u;
	cbd.ByteWidth = sizeof(CB_WVP);
	cbd.StructureByteStride = 0u;

	D3D11_SUBRESOURCE_DATA csd = {};
	csd.pSysMem = &cb;
	pGfx->getDevice()->CreateBuffer(&cbd, &csd, &pConstantBuffer);
	ErrorLogger::Log(hr, L"Create Buffer failed");
}

void Model::create(std::vector<Vertex>& vertices, std::vector<DWORD>& indices)
{
	//////////////////////////////////////////////////
	this->isIndexed = true;
	//////////////////////////////////////////////////

	HRESULT hr = S_OK;

	hr = vertexBuffer.init(pGfx->getDevice(), vertices.data(), vertices.size());
	ErrorLogger::Log(hr, L"Vertex buffer init failed");

	hr = indexBuffer.init(pGfx->getDevice(), indices.data(), indices.size());
	ErrorLogger::Log(hr, L"Index buffer init failed");

	hr = constantBuffer.init(pGfx->getDevice(), pGfx->getContext());
	ErrorLogger::Log(hr, L"const buffer init failed");
	//VERTEX BUFFER STUFF
	vertexCount = vertices.size();
	D3D11_BUFFER_DESC bd = {};
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = sizeof(Vertex) * vertexCount;
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bd.CPUAccessFlags = 0;
	bd.MiscFlags = 0;

	D3D11_SUBRESOURCE_DATA sd = {};
	sd.pSysMem = vertices.data();

	hr = pGfx->getDevice()->CreateBuffer(&bd, &sd, &pVertexBuffer);
	ErrorLogger::Log(hr, L"Create Buffer failed");

	//INDEX BUFFER STUFF
	indexCount = indices.size();
	D3D11_BUFFER_DESC ibd = {};
	ibd.Usage = D3D11_USAGE_DEFAULT;
	ibd.ByteWidth = sizeof(UINT) * indexCount;
	ibd.BindFlags = D3D11_BIND_INDEX_BUFFER;
	ibd.CPUAccessFlags = 0;
	ibd.MiscFlags = 0;

	D3D11_SUBRESOURCE_DATA isd = {};
	isd.pSysMem = indices.data();
	hr = pGfx->getDevice()->CreateBuffer(&ibd, &isd, &pIndexBuffer);
	ErrorLogger::Log(hr, L"Creation of Index Buffer Failed");

	D3D11_BUFFER_DESC cbd = {};
	cbd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	cbd.Usage = D3D11_USAGE_DYNAMIC;
	cbd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	cbd.MiscFlags = 0u;
	cbd.ByteWidth = sizeof(CB_WVP);
	cbd.StructureByteStride = 0u;

	//D3D11_SUBRESOURCE_DATA csd = {};
	//csd.pSysMem = &cb;
	hr = pGfx->getDevice()->CreateBuffer(&cbd, nullptr, &pConstantBuffer);
	ErrorLogger::Log(hr, L"Create Buffer failed");
}*/

/*void Model::resetMatrix()
{
	world = XMMatrixIdentity();
}

void Model::updateMatrix(Camera& camera)
{
	//scale
	XMMATRIX sca = XMMatrixScaling(transform.scale.x, transform.scale.y,
		transform.scale.z);
	//rotate
	XMMATRIX rotation = XMMatrixRotationRollPitchYaw(transform.rotation.x,
		transform.rotation.y, transform.rotation.z);
	//translate
	XMMATRIX translation = XMMatrixTranslation(transform.position.x,
		transform.position.y, transform.position.z);

	world = sca * rotation * translation;

	WVP = world * camera.getView() * camera.getProjection();
	constantBuffer.data.WVP = XMMatrixTranspose(WVP);
}

void Model::move(float x, float y, float z)
{
	transform.position.x += x;
	transform.position.y += y;
	transform.position.z += z;
	transform.position.w = 1.0f;
}

void Model::setPos(float x, float y, float z)
{
	transform.position.x = x;
	transform.position.y = y;
	transform.position.z = z;
	transform.position.w = 1.0f;
}

void Model::rotate(float x, float y, float z)
{
	transform.rotation.x += x;
	transform.rotation.y += y;
	transform.rotation.z += z;
}

void Model::setRotation(float x, float y, float z)
{
	transform.rotation.x = x;
	transform.rotation.y = y;
	transform.rotation.z = z;
}

void Model::scale(float x, float y, float z)
{
	transform.scale.x += x;
	transform.scale.y += y;
	transform.scale.z += z;
	transform.scale.w = 1.0f;
}

void Model::setScale(float x, float y, float z)
{
	transform.scale.x = x;
	transform.scale.y = y;
	transform.scale.z = z;
	transform.scale.w = 1.0f;
}

/*void RawModel::draw()
{
	//pGfx->getContext()->UpdateSubresource(pConstantBuffer, 0, NULL, &cb, 0, 0);

	pGfx->getContext()->VSSetConstantBuffers(0, 1, constantBuffer.getBuffer());
	constantBuffer.update();

	if (isIndexed)
		pGfx->getContext()->DrawIndexed(indexBuffer.getIndexCount(), 0u, 0u);
	else
		pGfx->getContext()->Draw(vertexBuffer.getVertexCount(), 0u);
}

void RawModel::bind(VertexShader& vs, PixelShader& ps, Texture& tex)
{
	const UINT offset = 0;
	pGfx->getContext()->VSSetShader(vs.getVertexShader(), nullptr, 0u);
	pGfx->getContext()->PSSetShader(ps.getPixelShader(), nullptr, 0u);
	pGfx->getContext()->PSSetShaderResources(0, 1, tex.getTexture());
	pGfx->getContext()->PSSetSamplers(0, 1, pGfx->getSamplerState());
	pGfx->getContext()->IASetVertexBuffers(0u, 1u, vertexBuffer.getBuffer(), vertexBuffer.getStridePtr(), &offset);
	if (isIndexed) pGfx->getContext()->IASetIndexBuffer(indexBuffer.getBuffer(), DXGI_FORMAT_R32_UINT, 0u);
	pGfx->getContext()->IASetInputLayout(vs.getInputLayout());
	pGfx->getContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
}

void Model::unbind()
{
	pGfx->getContext()->VSSetShader(nullptr, nullptr, 0u);
	pGfx->getContext()->PSSetShader(nullptr, nullptr, 0u);
	pGfx->getContext()->IASetVertexBuffers(0u, 0u, nullptr, nullptr, nullptr);
	if (isIndexed) pGfx->getContext()->IASetIndexBuffer(nullptr, DXGI_FORMAT_R32_UINT, 0u);
}
bool Model3D::init(Graphics& gfx, const std::string& filePath)
{
	try
	{
		if (!this->load(gfx, filePath))
			THROW_NORMAL("Could not load 3d model: " + filePath);
	}
	catch (HrException& e)
	{
		ErrorLogger::Log(e);
		return false;
	}
	return true;
}

bool Model3D::load(Graphics& gfx, const std::string& filePath)
{
	Assimp::Importer importer;

	const aiScene* pScene = importer.ReadFile(filePath,
		aiProcess_Triangulate | aiProcess_ConvertToLeftHanded);

	if (pScene == nullptr)
		return false;

	processNode(gfx, pScene->mRootNode, pScene);
	return true;
}

void Model3D::processNode(Graphics& gfx, aiNode* pNode, const aiScene* pScene)
{
	for (std::size_t i = 0; i < pNode->mNumMeshes; i++)
	{
		aiMesh* pMesh = pScene->mMeshes[pNode->mMeshes[i]];
		meshes.push_back(processMesh(gfx, pMesh, pScene));
	}

	for (std::size_t i = 0; i < pNode->mNumChildren; i++)
	{
		processNode(gfx, pNode->mChildren[i], pScene);
	}
}

Mesh Model3D::processMesh(Graphics& gfx, aiMesh* pMesh, const aiScene* pScene)
{
	std::vector<Vertex> vertices;
	std::vector<DWORD> indices;

	for (std::size_t i = 0; i < pMesh->mNumVertices; i++)
	{
		Vertex vertex;
		vertex.pos.x = pMesh->mVertices[i].x;
		vertex.pos.y = pMesh->mVertices[i].y;
		vertex.pos.z = pMesh->mVertices[i].z;

		if (pMesh->mTextureCoords[0])
		{
			vertex.uv.x = static_cast<float>(pMesh->mTextureCoords[0][i].x);
			vertex.uv.y = static_cast<float>(pMesh->mTextureCoords[0][i].y);
		}

		vertices.push_back(vertex);
	}

	//for (std::size_t i = 0; i < pMesh->mFaces->mNumIndices; i++)
	//{
	//	indices[i] = pMesh->mFaces->mIndices[i];
	//}
	for (UINT i = 0; i < pMesh->mNumFaces; i++)
	{
		aiFace face = pMesh->mFaces[i];

		for (UINT j = 0; j < face.mNumIndices; j++)
			indices.push_back(face.mIndices[j]);
	}

	return Mesh(gfx, vertices, indices);
}

void Model3D::bind(Graphics& gfx, VertexShader& vs, PixelShader& ps, Texture& tex)
{
	gfx.getContext()->VSSetShader(vs.getVertexShader(), nullptr, 0u);
	gfx.getContext()->PSSetShader(ps.getPixelShader(), nullptr, 0u);
	gfx.getContext()->PSSetShaderResources(0, 1, tex.getTexture());
	gfx.getContext()->IASetInputLayout(vs.getInputLayout());
	gfx.getContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
}

void Model3D::draw(Graphics& gfx)
{
	vsCBuffer.Bind(gfx);
	vsCBuffer.Update();
	vsCBuffer.Unbind(gfx);

	for (std::size_t i = 0; i < meshes.size(); i++)
	{
		meshes[i].bind();
		meshes[i].draw();
		meshes[i].unbind();
	}
}

void Model3D::unbind(Graphics& gfx)
{
	gfx.getContext()->VSSetShader(nullptr, nullptr, 0u);
	gfx.getContext()->PSSetShader(nullptr, nullptr, 0u);
	gfx.getContext()->IASetVertexBuffers(0u, 0u, nullptr, nullptr, nullptr);
	gfx.getContext()->IASetIndexBuffer(nullptr, DXGI_FORMAT_R32_UINT, 0u);
}

Mesh::Mesh(Graphics& gfx, std::vector<Vertex>& vertices, std::vector<DWORD>& indices)
{
	this->pContext = gfx.getContext();

	HRESULT hr = vertexBuffer.Init(gfx, vertices.data(), vertices.size());
	THROW_IF_FAILED(hr, "Failed to init vertex buffer");

	hr = indexBuffer.Init(gfx, indices.data(), indices.size());
	THROW_IF_FAILED(hr, "Failed to init index buffer");
}

Mesh::Mesh(const Mesh& mesh)
{
	this->pContext = mesh.pContext;
	this->indexBuffer = mesh.indexBuffer;
	this->vertexBuffer = mesh.vertexBuffer;
}

void Mesh::bind() noexcept
{
	const UINT offset = 0;
	pContext->IASetVertexBuffers(0u, 1u, vertexBuffer.getBuffer(), vertexBuffer.getStridePtr(), &offset);
	pContext->IASetIndexBuffer(indexBuffer.getBuffer(), DXGI_FORMAT_R32_UINT, 0u);
}

void Mesh::draw() noexcept
{
	pContext->DrawIndexed(indexBuffer.getIndexCount(), 0u, 0u);
}

void Mesh::unbind() noexcept
{
	pContext->IASetVertexBuffers(0u, 0u, nullptr, nullptr, nullptr);
	pContext->IASetIndexBuffer(nullptr, DXGI_FORMAT_R32_UINT, 0u);
}*/