#include "Graphics/Shader/PixelShader.h"
#include "Utility/Error.h"
#include "Utility/Util.h"
#include "Graphics/Graphics.h"

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
	catch (HrException& e)
	{
		ErrorLogger::Log(e);
		return false;
	}
	return true;
}

PixelShader::~PixelShader()
{
	ReleaseCOM(pPixelShader);
}

void PixelShader::Bind(Graphics& gfx)
{
	gfx.getContext()->PSSetShader(pPixelShader, nullptr, NULL);
}

void PixelShader::Unbind(Graphics& gfx)
{
	gfx.getContext()->PSSetShader(nullptr, nullptr, NULL);
}
