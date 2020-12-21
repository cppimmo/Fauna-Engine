#include "ComputeShader.h"
#include <Utility\Log.h>
#include <Utility\Error.h>

bool ComputeShader::Init(ID3D11Device* pDevice, std::wstring& filePath)
{
	HRESULT hr = S_OK;

	hr = D3DReadFileToBlob(filePath.c_str(), &pBlob);
	std::wstring errMsg = L"Pixel shader could not be loaded at: ";
	errMsg += filePath;
	THROW_IF_FAILED(hr, wstring_to_string(errMsg));

	hr = pDevice->CreateComputeShader(pBlob->GetBufferPointer(),
		pBlob->GetBufferSize(), nullptr, pComputeShader.GetAddressOf());
	THROW_IF_FAILED(hr, "Pixel shader failed to create");
	return true;
}

void ComputeShader::Bind(Graphics& gfx)
{
}

void ComputeShader::SetShaderResources(Graphics& gfx, UINT startSlot, UINT numViews, ID3D11ShaderResourceView* const* pViews)
{
}

void ComputeShader::SetSamplers(Graphics& gfx, UINT startSlot, UINT numSamplers, ID3D11SamplerState* const* pSamplers)
{
}
