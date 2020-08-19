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

DomainShader::~DomainShader()
{
	ReleaseCOM(pDomainShader);
}

void DomainShader::Bind(Graphics& gfx)
{
	gfx.getContext()->DSSetShader(pDomainShader, nullptr, NULL);
}

void DomainShader::Unbind(Graphics& gfx)
{
	gfx.getContext()->DSSetShader(nullptr, nullptr, NULL);
}
