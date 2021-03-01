#pragma once

#include <d3d11.h>
#include <wrl.h>
#include "Graphics/Buffer/ConstantBufferTypes.h"

#include "Utility/Log.h"
#include "Graphics/Bindable.h"

template<typename BufferType>
class Fauna::ConstantBuffer;
template<typename BufferType>//vertex shader
class Fauna::VSConstantBuffer;
template<typename BufferType>
class Fauna::PSConstantBuffer;
template<typename BufferType>
class Fauna::HSConstantBuffer;
template<typename BufferType>
class Fauna::DSConstantBuffer;
template<typename BufferType>
class Fauna::GSConstantBuffer;

namespace Fauna
{
	template<typename BufferType>
	class ConstantBuffer : public Bindable
	{
	public:
		ConstantBuffer() = default;
		ConstantBuffer(const ConstantBuffer<BufferType>&) = delete;
		ConstantBuffer& operator=(const ConstantBuffer<BufferType>&) = delete;
		~ConstantBuffer() = default;
		BufferType data;

		HRESULT Init(Graphics& gfx)
		{
			if (pBuffer != nullptr)
				pBuffer.Reset();

			D3D11_BUFFER_DESC cbd = {};
			cbd.Usage = D3D11_USAGE_DYNAMIC;
			cbd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
			cbd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
			cbd.MiscFlags = 0;
			cbd.ByteWidth = static_cast<UINT>(sizeof(BufferType) + (16 - (sizeof(C) % 16)));
			cbd.StructureByteStride = 0;

			HRESULT hr = gfx.GetDevice()->CreateBuffer(&cbd, nullptr, pBuffer.GetAddressOf());
			return hr;
		}
		HRESULT Init(Graphics& gfx, BufferType* initialData)
		{
			if (pBuffer != nullptr)
				pBuffer.Reset();

			D3D11_BUFFER_DESC cbd = {};
			cbd.Usage = D3D11_USAGE_DYNAMIC;
			cbd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
			cbd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
			cbd.MiscFlags = 0;
			cbd.ByteWidth = static_cast<UINT>(sizeof(BufferType) + (16 - (sizeof(BufferType) % 16)));
			cbd.StructureByteStride = 0;

			D3D11_SUBRESOURCE_DATA sd = {};
			sd.pSysMem = data;

			HRESULT hr = gfx.GetDevice()->CreateBuffer(&cbd, data, pBuffer.GetAddressOf());
			return hr;
		}
		bool Update(Graphics& gfx)
		{
			D3D11_MAPPED_SUBRESOURCE msr = {};
			HRESULT hr = gfx.getContext()->Map(pBuffer.Get(), 0, D3D11_MAP_WRITE_DISCARD, 0, &msr);
			if (FAILED(hr)) {
				Fuana::Log::Message_Box(hr, "Failed to map constant buffer.");
				return false;
			}
			memcpy(msr.pData, &data, sizeof(BufferType));
			gfx.getContext()->Unmap(pBuffer.Get(), 0);
			return true;
		}
		ID3D11Buffer* getBuffer() const { return pBuffer.Get(); }
	protected:
		Microsoft::WRL::ComPtr<ID3D11Buffer> pBuffer = nullptr;
	};

	//Constantbuffer types listed in order of occurence in graphics pipeline
	template<typename BufferType>//vertex shader
	class VSConstantBuffer : public ConstantBuffer<BufferType>
	{
	public:
		void Bind(Graphics& gfx) override
		{
			gfx.GetContext()->VSSetConstantBuffers(0, 1, this->pBuffer.GetAddressOf());
		}
	};

	template<typename BufferType>//hull shader 
	class HSConstantBuffer : public ConstantBuffer<BufferType>
	{
	public:
		void Bind(Graphics& gfx) override
		{
			gfx.GetContext()->HSSetConstantBuffers(0, 1, this->pBuffer.GetAddressOf());
		}
	};

	template<typename BufferType>//domain shader
	class DSConstantBuffer : public ConstantBuffer<BufferType>
	{
	public:
		void Bind(Graphics& gfx) override
		{
			gfx.GetContext()->DSSetConstantBuffers(0, 1, this->pBuffer.GetAddressOf());
		}
	};

	template<typename BufferType>//geometry shader
	class GSConstantBuffer : public ConstantBuffer<BufferType>
	{
	public:
		void Bind(Graphics& gfx) override
		{
			gfx.GetContext()->GSSetConstantBuffers(0, 1, this->pBuffer.GetAddressOf());
		}
	};

	template<typename BufferType>//pixel shader
	class PSConstantBuffer : public ConstantBuffer<BufferType>
	{
	public:
		void Bind(Graphics& gfx) override
		{
			gfx.GetContext()->PSSetConstantBuffers(0, 1, this->pBuffer.GetAddressOf());
		}
	};

}
