#include "Graphics/Shader/VertexShader.h"
#include "Utility/Error.h"
#include "Utility/Util.h"
#include "Graphics/Graphics.h"

bool VertexShader::Init(Graphics& gfx, std::wstring filePath, D3D11_INPUT_ELEMENT_DESC* pLayoutDesc, UINT numElements)
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

		hr = gfx.getDevice()->CreateInputLayout(pLayoutDesc, numElements, pBlob->GetBufferPointer(),
			pBlob->GetBufferSize(), &pInputLayout);
		THROW_IF_FAILED(hr, "Could not create input layout");
	}
	catch (HrException& e)
	{
		ErrorLogger::Log(e);
		return false;
	}
	return true;
}

VertexShader::~VertexShader()
{
	ReleaseCOM(pVertexShader);
	ReleaseCOM(pInputLayout);
}

void VertexShader::Bind(Graphics& gfx)
{
	gfx.getContext()->VSSetShader(pVertexShader, nullptr, NULL);
}

void VertexShader::Unbind(Graphics& gfx)
{
	gfx.getContext()->VSSetShader(nullptr, nullptr, NULL);
}
