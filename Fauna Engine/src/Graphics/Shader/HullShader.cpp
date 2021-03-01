#include "Graphics/Shader/HullShader.h"

#include "Utility/Log.h"
#include "Utility/Util.h"
#include "Graphics/Graphics.h"
#include <Utility\Error.h>

bool HullShader::Init(Graphics& gfx, std::wstring& filePath)
{
	HRESULT hr = S_OK;

	hr = D3DReadFileToBlob(filePath.c_str(), &pBlob);
	std::wstring errMsg = L"Pixel shader could not be loaded at: ";
	errMsg += filePath;
	THROW_IF_FAILED(hr, wstring_to_string(errMsg));

	hr = gfx.GetDevice()->CreateHullShader(pBlob->GetBufferPointer(),
		pBlob->GetBufferSize(), nullptr, &pHullShader);
	THROW_IF_FAILED(hr, "Pixel shader failed to create");
	return true;
}

void HullShader::Bind(Graphics& gfx)
{
	gfx.GetContext()->HSSetShader(pHullShader.Get(), nullptr, NULL);
}

void HullShader::SetShaderResources(Graphics& gfx, UINT startSlot, UINT numViews, ID3D11ShaderResourceView* const* pViews)
{
	gfx.GetContext()->HSSetShaderResources(startSlot, numViews, pViews);
}

void HullShader::SetSamplers(Graphics& gfx, UINT startSlot, UINT numSamplers, ID3D11SamplerState* const* pSamplers)
{
	gfx.GetContext()->HSSetSamplers(startSlot, numSamplers, pSamplers);
}
