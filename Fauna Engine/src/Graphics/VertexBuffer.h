#pragma once

#include <d3d11.h>
#include "Graphics/Graphics.h"
#include "Graphics/Bindable.h"
#include "Utility/Util.h"
#include <wrl.h>

template<class T>
class VertexBuffer : public Bindable
{
public:
	VertexBuffer() : vertexCount(0), stride(sizeof(T)) {}
	~VertexBuffer() = default;
	VertexBuffer(const VertexBuffer<T>& rhs)
	{
		this->pBuffer = rhs.pBuffer;
		this->stride = rhs.stride;
		this->vertexCount = rhs.vertexCount;
	}
	VertexBuffer& operator=(const VertexBuffer<T>& rhs)
	{
		this->pBuffer = rhs.pBuffer;
		this->stride = rhs.stride;
		this->vertexCount = rhs.vertexCount;
		return *this;
	}

	HRESULT Init(Graphics& gfx, T* data, UINT numVertices)
	{
		if (pBuffer.Get() != nullptr)
			pBuffer.Reset();
		this->vertexCount = numVertices;

		D3D11_BUFFER_DESC vbd = {};//fill out buffer desc of type vertex
		vbd.ByteWidth = stride * numVertices;
		vbd.Usage = D3D11_USAGE_DEFAULT;
		vbd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
		vbd.CPUAccessFlags = 0;
		vbd.MiscFlags = 0;

		D3D11_SUBRESOURCE_DATA sd = {};//give sub data to buffer upon creation
		sd.pSysMem = data;

		HRESULT hr = gfx.getDevice()->CreateBuffer(&vbd, &sd, pBuffer.GetAddressOf());
		return hr;//handle exceptions later
	}
	void Bind(Graphics& gfx) override
	{
		gfx.getContext()->IASetVertexBuffers(0u, 1u, pBuffer.GetAddressOf(), &stride, &offset);
	}
	void Draw(Graphics& gfx, UINT startLocation)
	{
		gfx.getContext()->Draw(vertexCount, startLocation);
	}
	void Unbind(Graphics& gfx) override
	{
		gfx.getContext()->IASetVertexBuffers(NULL, NULL, nullptr, nullptr, nullptr);
	}
public://getters
	ID3D11Buffer* const* getBuffer() { return pBuffer.GetAddressOf(); }
	const UINT getStride() const { return stride; }
	const UINT* getStridePtr() const { return &stride; }
	const UINT getVertexCount() const { return vertexCount; }
	const UINT* getOffset() const { return &offset; }
	void setOffset(UINT offset) { this->offset = offset; }
private:
	Microsoft::WRL::ComPtr<ID3D11Buffer> pBuffer = nullptr;
	UINT vertexCount;	
	UINT stride;
	UINT offset = 0;
};
