#pragma once

#include <d3d11.h>
#include "Graphics/Graphics.h"
#include "Graphics/Bindable.h"
#include "Utility/Util.h"
#include <wrl.h>

class IndexBuffer : public Bindable
{
public:
	IndexBuffer() = default;
	IndexBuffer(const IndexBuffer& rhs)
	{
		this->indexCount = rhs.indexCount;
		this->pBuffer = rhs.pBuffer;
	}
	IndexBuffer& operator=(const IndexBuffer& rhs)
	{
		this->indexCount = rhs.indexCount;
		this->pBuffer = rhs.pBuffer;
		return *this;
	}
	~IndexBuffer() = default;

	HRESULT Init(Graphics& gfx, DWORD* data, UINT numIndices)
	{
		if (pBuffer.Get() != nullptr)
			pBuffer.Reset();
		this->indexCount = numIndices;

		D3D11_BUFFER_DESC ibd = {};
		ibd.ByteWidth = sizeof(DWORD) * numIndices;
		ibd.Usage = D3D11_USAGE_DEFAULT;
		ibd.BindFlags = D3D11_BIND_INDEX_BUFFER;
		ibd.CPUAccessFlags = 0u;
		ibd.MiscFlags = 0u;

		D3D11_SUBRESOURCE_DATA sd = {};
		sd.pSysMem = data;

		HRESULT hr = gfx.getDevice()->CreateBuffer(&ibd, &sd, pBuffer.GetAddressOf());
		return hr;
	}
	void Bind(Graphics& gfx) override
	{
		gfx.getContext()->IASetIndexBuffer(this->pBuffer.Get(), DXGI_FORMAT_R32_UINT, 0u);
	}
	void Draw(Graphics& gfx, UINT startIndexLocation, INT baseIndexLocation)
	{
		gfx.getContext()->DrawIndexed(indexCount, startIndexLocation, baseIndexLocation);
	}
	void Unbind(Graphics& gfx) override
	{
		gfx.getContext()->IASetIndexBuffer(nullptr, DXGI_FORMAT_R32_UINT, 0u);
	}
public://getters
	ID3D11Buffer* getBuffer() const { return pBuffer.Get(); }
	const UINT getIndexCount() const { return indexCount; }
	const UINT* getIndexCountPtr() const { return &indexCount; }
private:
	Microsoft::WRL::ComPtr<ID3D11Buffer> pBuffer = nullptr;
	UINT indexCount = 0;
};

