#pragma once

#include <d3d11.h>
#include "Utility/Error.h"
#include "Graphics/Bindable.h"

////////ConstantBuffer types
struct CB_WVP {
	DirectX::XMMATRIX WVP;
};

template<class C>//vertex shader
class VSConstantBuffer;

template<class C> 
class PSConstantBuffer;

template<class C>
class ConstantBuffer : public Bindable
{
public:
	ConstantBuffer() = default;
	ConstantBuffer(const ConstantBuffer<C>&) = delete;
	ConstantBuffer& operator=(const ConstantBuffer<C>&) = delete;
	~ConstantBuffer()
	{
		ReleaseCOM(pBuffer);
	}	
	C data;

	HRESULT Init(Graphics& gfx)
	{
		if (pBuffer != nullptr)
			ReleaseCOM(pBuffer);

		this->pContext = gfx.getContext();

		D3D11_BUFFER_DESC cbd = {};
		cbd.Usage = D3D11_USAGE_DYNAMIC;
		cbd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
		cbd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
		cbd.MiscFlags = 0;
		cbd.ByteWidth = static_cast<UINT>(sizeof(C) + (16 - (sizeof(C) % 16)));
		cbd.StructureByteStride = 0;

		HRESULT hr = gfx.getDevice()->CreateBuffer(&cbd, nullptr, &pBuffer);
		return hr;
	}
	HRESULT Init(Graphics& gfx, C* initialData)
	{
		if (pBuffer != nullptr)
			ReleaseCOM(pBuffer);

		this->pContext = gfx.getContext();

		D3D11_BUFFER_DESC cbd = {};
		cbd.Usage = D3D11_USAGE_DYNAMIC;
		cbd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
		cbd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
		cbd.MiscFlags = 0;
		cbd.ByteWidth = static_cast<UINT>(sizeof(C) + (16 - (sizeof(C) % 16)));
		cbd.StructureByteStride = 0;

		D3D11_SUBRESOURCE_DATA sd = {};
		sd.pSysMem = data;

		HRESULT hr = gfx.getDevice()->CreateBuffer(&cbd, data, &pBuffer);
		return hr;
	}
	bool Update()
	{
		D3D11_MAPPED_SUBRESOURCE msr = {};
		HRESULT hr = pContext->Map(pBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &msr);
		if (FAILED(hr)) {
			ErrorLogger::Log(hr, L"Failed to map constant buffer.");
			return false;
		}
		CopyMemory(msr.pData, &data, sizeof(C));
		pContext->Unmap(pBuffer, 0);
		return true;
	}
	ID3D11Buffer* getBuffer() const { return pBuffer; }
protected:
	ID3D11Buffer* pBuffer = nullptr;
	ID3D11DeviceContext* pContext = nullptr;
};

//Constantbuffer listed in order of graphics pipeline
template<class C>//vertex shader
class VSConstantBuffer : public ConstantBuffer<C>
{
public:
	void Bind(Graphics& gfx) override
	{
		gfx.getContext()->VSSetConstantBuffers(0, 1, &this->pBuffer);
	}
	void Unbind(Graphics& gfx) override
	{
		//do nothing or fatal error
		//gfx.getContext()->VSSetConstantBuffers(0, 1, nullptr);
	}
};

/*template<class C>//hull shader 
class HSConstantBuffer : public ConstantBuffer<C>
{
public:
	void bind(Graphics& gfx) override
	{
		pContext->HSSetConstantBuffers(0, 1, pBuffer);
	}
	void unbind(Graphics& gfx) override
	{
		pContext->HSSetConstantBuffers(0, 1, nullptr);
	}
};

template<class C>//domain shader
class DSConstantBuffer : public ConstantBuffer<C>
{
public:
	void bind(Graphics& gfx) override
	{
		pContext->DSSetConstantBuffers(0, 1, pBuffer);
	}
	void unbind(Graphics& gfx) override
	{
		pContext->DSSetConstantBuffers(0, 1, nullptr);
	}
};

template<class C>//geometry shader
class GSConstantBuffer : public ConstantBuffer<C>
{
public:
	void bind(Graphics& gfx) override
	{
		pContext->GSSetConstantBuffers(0, 1, pBuffer);
	}
	void unbind(Graphics& gfx) override
	{
		pContext->GSSetConstantBuffers(0, 1, nullptr);
	}
};*/

template<class C>//pixel shader
class PSConstantBuffer : public ConstantBuffer<C>
{
public:
	void Bind(Graphics& gfx) override
	{
		gfx.getContext()->PSSetConstantBuffers(0, 1, &this->pBuffer);
	}
	void Unbind(Graphics& gfx) override
	{
		//do nothing or fatal error
		//gfx.getContext()->PSSetConstantBuffers(0, 1, nullptr);
	}
};