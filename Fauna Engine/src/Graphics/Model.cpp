#include "Model.h"

#include "Utility/Util.h"

using namespace DirectX;

#ifdef RAW_MDL

void Model::Create(Graphics& gfx, std::vector<Vertex>& vertices)
{
	HRESULT hr = S_OK;
	this->vertices = vertices;

	XMVECTOR vMin = XMVectorZero(), vMax = XMVectorZero();
	for (std::size_t i = 0; i < vertices.size(); i++)
	{
		XMVECTOR point = XMLoadFloat3(&vertices[i].pos);

		vMin = XMVectorMin(vMin, point);
		vMax = XMVectorMax(vMax, point);
	}
	XMStoreFloat3(&box.Center, 0.5f * (vMin + vMax));
	XMStoreFloat3(&box.Extents, 0.5f * (vMax - vMin));
	box.CreateFromPoints(box, vertices.size(), &vertices[0].pos, sizeof(Vertex));

	hr = vertexBuffer.Init(gfx, vertices.data(), vertices.size());
	Fuana::Log::Message_Box(hr, "Vertex buffer initialization failed");

	hr = vsCBuffer.Init(gfx);
	Fuana::Log::Message_Box(hr, "const buffer init failed");

	hr = psCBuffer.Init(gfx);
	Fuana::Log::Message_Box(hr, "const buffer init failed");
}

void Model::Create(Graphics& gfx, std::vector<Vertex>& vertices, std::vector<DWORD>& indices)
{
	this->isIndexed = true;
	this->vertices = vertices;
	//////////////////////////////////////////////////

	HRESULT hr = S_OK;

	XMVECTOR vMin = XMVectorZero(), vMax = XMVectorZero();
	for (std::size_t i = 0; i < vertices.size(); i++)
	{
		XMVECTOR point = XMLoadFloat3(&vertices[i].pos);

		vMin = XMVectorMin(vMin, point);
		vMax = XMVectorMax(vMax, point);
	}
	XMStoreFloat3(&box.Center, 0.5f * (vMin + vMax));
	XMStoreFloat3(&box.Extents, 0.5f * (vMax - vMin));
	box.CreateFromPoints(box, vertices.size(), &vertices[0].pos, sizeof(Vertex));

	hr = vertexBuffer.Init(gfx, vertices.data(), vertices.size());
	Fuana::Log::Message_Box(hr, "Vertex buffer init failed");

	hr = indexBuffer.Init(gfx, indices.data(), indices.size());
	Fuana::Log::Message_Box(hr, "Index buffer init failed");

	hr = vsCBuffer.Init(gfx);
	Fuana::Log::Message_Box(hr, "const buffer init failed");

	hr = psCBuffer.Init(gfx);
	Fuana::Log::Message_Box(hr, "const buffer init faield");
}

bool Model::isColliding(Model& model)
{
	const float boxSize = 0.5f;
	XMFLOAT4 min = { model.transform.position.x - boxSize, model.transform.position.y - boxSize, model.transform.position.z - boxSize, 0.0f };
	XMFLOAT4 max = { model.transform.position.x + boxSize, model.transform.position.y + boxSize, model.transform.position.z + boxSize, 0.0f };

	if ((transform.position.x >= min.x && transform.position.x <= max.x) &&
		(transform.position.y >= min.y && transform.position.y <= max.y) &&
		(transform.position.y >= min.y && transform.position.z <= max.z))
	{
		return true;
	}
	else
	{
		return false;
	}
}

void Model::resetMatrix()
{
	translation = XMMatrixIdentity();
	rotation = XMMatrixIdentity();
	sca = XMMatrixIdentity();
}

void Model::updateMatrix(Camera& camera)
{
	//scale
	/*XMMATRIX sca = XMMatrixScaling(transform.scale.x, transform.scale.y,
		transform.scale.z);
	//rotate
	//XMMATRIX rotation = XMMatrixRotationRollPitchYaw(transform.rotation.x,
		//transform.rotation.y, transform.rotation.z);
	//translate
	XMMATRIX translation = XMMatrixTranslation(transform.position.x,
		transform.position.y, transform.position.z);*/

	sca = XMMatrixScaling(transform.scale.x, transform.scale.y,
		transform.scale.z);
	translation = XMMatrixTranslation(transform.position.x,
		transform.position.y, transform.position.z);

	world = sca * rotation * translation;

	WVP = world * camera.getView() * camera.getProjection();
	vsCBuffer.data.WVP = XMMatrixTranspose(WVP);
}

void Model::adjustPos(float x, float y, float z)
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

void Model::adjustRot(float x, float y, float z)
{
	transform.rotation.x += x;
	transform.rotation.y += y;
	transform.rotation.z += z;
	transform.rotation.w += 1.0f;
	rotation = XMMatrixRotationAxis(XMVectorSet(1.0f, 0.0f, 0.0f, 1.0f), XMConvertToRadians(x));
	rotation = XMMatrixRotationAxis(XMVectorSet(0.0f, 1.0f, 0.0f, 1.0f), XMConvertToRadians(y));
	rotation = XMMatrixRotationAxis(XMVectorSet(0.0f, 0.0f, 1.0f, 1.0f), XMConvertToRadians(z));
	//XMVECTOR vect = XMVectorSet(x, y, z, 1.0f);
	//rotation = XMMatrixRotationAxis(vect, XMConvertToRadians(angle));
}

void Model::setRot(float x, float y, float z)
{
	transform.rotation.x = x;
	transform.rotation.y = y;
	transform.rotation.z = z;
	transform.rotation.w = 1.0f;
	rotation = XMMatrixRotationAxis(XMVectorSet(1.0f, 0.0f, 0.0f, 1.0f), XMConvertToRadians(x));
	rotation = XMMatrixRotationAxis(XMVectorSet(0.0f, 1.0f, 0.0f, 1.0f), XMConvertToRadians(y));
	rotation = XMMatrixRotationAxis(XMVectorSet(0.0f, 0.0f, 1.0f, 1.0f), XMConvertToRadians(z));
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

void Model::Draw(Graphics& gfx, Camera& camera)
{
	const float x = XMVectorGetX(camera.getPosition());
	const float y = XMVectorGetY(camera.getPosition());
	const float z = XMVectorGetZ(camera.getPosition());
	XMFLOAT3 tempVec = {x,y,z};
	psCBuffer.data.camPos = tempVec;


	DirectX::BoundingFrustum localFrustum;
	localFrustum.Transform(localFrustum, world);
	
	psCBuffer.Bind(gfx); 
	psCBuffer.Update(gfx);
	psCBuffer.Unbind(gfx);

	vsCBuffer.Bind(gfx);
	vsCBuffer.Update(gfx);
	vsCBuffer.Unbind(gfx);

//	if (camera.getFrustum().Intersects(box))
	//{
		OutputDebugStringA("Okay clown i can draw you");
		if (isIndexed) 
			indexBuffer.Draw(gfx, 0u, 0u);
		else
			vertexBuffer.Draw(gfx, 0u);
	//}
	//else
	////{
	//	OutputDebugStringA("Okay lol I like kinda can't draw you");
	//}
	
}

void Model::Bind(Graphics& gfx, VertexShader& vs, PixelShader& ps, Texture& tex)
{
	//const UINT offset = 0;

	vs.Bind(gfx); 
	ps.Bind(gfx);
	ps.SetShaderResources(gfx, 0, 1, tex.getTexture());
	vertexBuffer.Bind(gfx);
	if (isIndexed) indexBuffer.Bind(gfx);
	gfx.setDrawMode(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
}

void Model::Unbind(Graphics& gfx)
{
	gfx.getContext()->VSSetShader(nullptr, nullptr, 0u);
	gfx.getContext()->PSSetShader(nullptr, nullptr, 0u);
	vertexBuffer.Unbind(gfx);
	if (isIndexed) indexBuffer.Unbind(gfx);
}

#else

#endif