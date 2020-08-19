#include "Graphics/Shader/HullShader.h"
#include "Utility/Error.h"
#include "Utility/Util.h"
#include "Graphics/Graphics.h"

bool HullShader::Init(ID3D11Device* pDevice, std::wstring& filePath)
{
	try
	{
		HRESULT hr = S_OK;

		hr = D3DReadFileToBlob(filePath.c_str(), &pBlob);
		std::wstring errMsg = L"Pixel shader could not be loaded at: ";
		errMsg += filePath;
		THROW_IF_FAILED(hr, wstring_to_string(errMsg));

		hr = pDevice->CreateHullShader(pBlob->GetBufferPointer(),
			pBlob->GetBufferSize(), nullptr, &pHullShader);
		THROW_IF_FAILED(hr, "Pixel shader failed to create");
	}
	catch (HrException& e)
	{
		ErrorLogger::Log(e);
		return false;
	}
	return true;
}

HullShader::~HullShader()
{
	ReleaseCOM(pHullShader);
}

void HullShader::Bind(Graphics& gfx)
{
	gfx.getContext()->HSSetShader(pHullShader, nullptr, NULL);
}

void HullShader::Unbind(Graphics& gfx)
{
	gfx.getContext()->HSSetShader(nullptr, nullptr, NULL);
}
