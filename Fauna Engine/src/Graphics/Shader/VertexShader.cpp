#include "Graphics/Shader/VertexShader.h"

#include "Utility/Log.h"
#include "Utility/Util.h"
#include "Graphics/Graphics.h"
#include <Utility\Error.h>

bool VertexShader::Init(Graphics& gfx, std::wstring filePath, D3D11_INPUT_ELEMENT_DESC* pDesc, UINT numElements)
{
	try
	{
		HRESULT hr = S_OK;
		hr = D3DReadFileToBlob(filePath.c_str(), &pBlob);
		std::wstring errMsg = L"Vertex shader could not be loaded at: ";
		errMsg += filePath;
		THROW_IF_FAILED(hr, wstring_to_string(errMsg));

		hr = gfx.getDevice()->CreateVertexShader(pBlob->GetBufferPointer(),
			pBlob->GetBufferSize(), nullptr, &pVertexShader);
		THROW_IF_FAILED(hr, "Could not create Vertex shader");

		hr = gfx.getDevice()->CreateInputLayout(pDesc, numElements, pBlob->GetBufferPointer(),
			pBlob->GetBufferSize(), &pInputLayout);
		THROW_IF_FAILED(hr, "Could not create input layout");
	}
	catch (const HrException& e)
	{
		Log::Message_Box(e);
		return false;
	}
	return true;
}

void VertexShader::Bind(Graphics& gfx)
{
	gfx.getContext()->IASetInputLayout(pInputLayout.Get());
	gfx.getContext()->VSSetShader(pVertexShader.Get(), nullptr, NULL);
}

void VertexShader::SetShaderResources(Graphics& gfx, UINT startSlot, UINT numViews, ID3D11ShaderResourceView* const* pViews)
{
	gfx.getContext()->VSSetShaderResources(startSlot, numViews, pViews);
}

void VertexShader::SetSamplers(Graphics& gfx, UINT startSlot, UINT numSamplers, ID3D11SamplerState* const* pSamplers)
{
	gfx.getContext()->VSSetSamplers(startSlot, numSamplers, pSamplers);
}

void VertexShader::SetInputLayout(Graphics& gfx, const D3D11_INPUT_ELEMENT_DESC* pDesc, UINT numElements)
{
	if (pInputLayout)
		pInputLayout.Reset();
	gfx.getDevice()->CreateInputLayout(pDesc, numElements,
		Shader::pBlob->GetBufferPointer(), Shader::pBlob->GetBufferSize(), pInputLayout.GetAddressOf());
}