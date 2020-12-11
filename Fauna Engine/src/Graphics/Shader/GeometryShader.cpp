#include "Graphics/Shader/GeometryShader.h"

#include "Utility/Log.h"
#include "Utility/Util.h"
#include "Graphics/Graphics.h"

bool GeometryShader::Init(ID3D11Device* pDevice, std::wstring& filePath)
{
	try
	{
		HRESULT hr = S_OK;

		hr = D3DReadFileToBlob(filePath.c_str(), &pBlob);
		std::wstring errMsg = L"Pixel shader could not be loaded at: ";
		errMsg += filePath;
		THROW_IF_FAILED(hr, wstring_to_string(errMsg));

		hr = pDevice->CreateGeometryShader(pBlob->GetBufferPointer(),
			pBlob->GetBufferSize(), nullptr, &pGeometryShader);
		THROW_IF_FAILED(hr, "Pixel shader failed to create");
	}
	catch (HrException& e)
	{
		Log::Message_Box(e);
		return false;
	}
	return true;
}

void GeometryShader::Bind(Graphics& gfx)
{
	gfx.getContext()->GSSetShader(pGeometryShader.Get(), nullptr, NULL);
}

void GeometryShader::SetShaderResources(Graphics& gfx, UINT startSlot, UINT numViews, ID3D11ShaderResourceView* const* pViews)
{
	gfx.getContext()->GSSetShaderResources(startSlot, numViews, pViews);
}

void GeometryShader::SetSamplers(Graphics& gfx, UINT startSlot, UINT numSamplers, ID3D11SamplerState* const* pSamplers)
{
	gfx.getContext()->GSSetSamplers(startSlot, numSamplers, pSamplers);
}
