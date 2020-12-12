#include "Graphics/Shader/HullShader.h"

#include "Utility/Log.h"
#include "Utility/Util.h"
#include "Graphics/Graphics.h"
#include <Utility\Error.h>

bool HullShader::Init(Graphics& gfx, std::wstring& filePath)
{
	try
	{
		HRESULT hr = S_OK;

		hr = D3DReadFileToBlob(filePath.c_str(), &pBlob);
		std::wstring errMsg = L"Pixel shader could not be loaded at: ";
		errMsg += filePath;
		THROW_IF_FAILED(hr, wstring_to_string(errMsg));

		hr = gfx.getDevice()->CreateHullShader(pBlob->GetBufferPointer(),
			pBlob->GetBufferSize(), nullptr, &pHullShader);
		THROW_IF_FAILED(hr, "Pixel shader failed to create");
	}
	catch (const HrException& e)
	{
		Log::Message_Box(e);
		return false;
	}
	return true;
}

void HullShader::Bind(Graphics& gfx)
{
	gfx.getContext()->HSSetShader(pHullShader.Get(), nullptr, NULL);
}

void HullShader::SetShaderResources(Graphics& gfx, UINT startSlot, UINT numViews, ID3D11ShaderResourceView* const* pViews)
{
	gfx.getContext()->HSSetShaderResources(startSlot, numViews, pViews);
}

void HullShader::SetSamplers(Graphics& gfx, UINT startSlot, UINT numSamplers, ID3D11SamplerState* const* pSamplers)
{
	gfx.getContext()->HSSetSamplers(startSlot, numSamplers, pSamplers);
}
