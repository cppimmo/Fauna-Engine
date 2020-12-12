#include "Graphics/Shader/PixelShader.h"

#include "Utility/Log.h"
#include "Utility/Util.h"
#include "Graphics/Graphics.h"
#include "Graphics/Texture.h"
#include "Graphics/CubeTexture.h"
#include <Utility\Error.h>

bool PixelShader::Init(Graphics& gfx, std::wstring filePath)
{
	try
	{
		HRESULT hr = S_OK;

		hr = D3DReadFileToBlob(filePath.c_str(), &pBlob);
		std::wstring errMsg = L"Pixel shader could not be loaded at: ";
		errMsg += filePath;
		THROW_IF_FAILED(hr, wstring_to_string(errMsg));

		hr = gfx.getDevice()->CreatePixelShader(pBlob->GetBufferPointer(),
			pBlob->GetBufferSize(), nullptr, &pPixelShader);
		THROW_IF_FAILED(hr, "Pixel shader failed to create");
	}
	catch (const HrException& e)
	{
		Log::Message_Box(e);
		return false;
	}
	return true;
}

void PixelShader::Bind(Graphics& gfx)
{
	gfx.getContext()->PSSetShader(pPixelShader.Get(), nullptr, NULL);
}

void PixelShader::SetShaderResources(Graphics& gfx, UINT startSlot, UINT numViews, ID3D11ShaderResourceView* const* pViews)
{
	gfx.getContext()->PSSetShaderResources(startSlot, numViews, pViews);
}

void PixelShader::SetSamplers(Graphics& gfx, UINT startSlot, UINT numSamplers, ID3D11SamplerState* const* pSamplers)
{
	gfx.getContext()->PSSetSamplers(startSlot, numSamplers, pSamplers);
}
