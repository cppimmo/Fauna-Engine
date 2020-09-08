#include "Graphics/Shader/DomainShader.h"
#include "Utility/Error.h"
#include "Utility/Util.h"
#include "Graphics/Graphics.h"

bool DomainShader::Init(ID3D11Device* pDevice, std::wstring& filePath)
{
	try
	{
		HRESULT hr = S_OK;

		hr = D3DReadFileToBlob(filePath.c_str(), &pBlob);
		std::wstring errMsg = L"Pixel shader could not be loaded at: ";
		errMsg += filePath;
		THROW_IF_FAILED(hr, wstring_to_string(errMsg));

		hr = pDevice->CreateDomainShader(pBlob->GetBufferPointer(),
			pBlob->GetBufferSize(), nullptr, &pDomainShader);
		THROW_IF_FAILED(hr, "Pixel shader failed to create");
	}
	catch (HrException& e)
	{
		ErrorLogger::Log(e);
		return false;
	}
	return true;
}

void DomainShader::Bind(Graphics& gfx)
{
	gfx.getContext()->DSSetShader(pDomainShader.Get(), nullptr, NULL);
}

void DomainShader::SetShaderResources(Graphics& gfx, UINT startSlot, UINT numViews, ID3D11ShaderResourceView* const* pViews)
{
	gfx.getContext()->DSSetShaderResources(startSlot, numViews, pViews);
}

void DomainShader::SetSamplers(Graphics& gfx, UINT startSlot, UINT numSamplers, ID3D11SamplerState* const* pSamplers)
{
	gfx.getContext()->DSSetSamplers(startSlot, numSamplers, pSamplers);
}
