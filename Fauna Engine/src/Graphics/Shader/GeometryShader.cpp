#include "Graphics/Shader/GeometryShader.h"
#include "Utility/Error.h"
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
		ErrorLogger::Log(e);
		return false;
	}
	return true;
}

GeometryShader::~GeometryShader()
{
	ReleaseCOM(pGeometryShader);
}

void GeometryShader::Bind(Graphics& gfx)
{
	gfx.getContext()->GSSetShader(pGeometryShader, nullptr, NULL);
}

void GeometryShader::Unbind(Graphics& gfx)
{
	gfx.getContext()->GSSetShader(nullptr, nullptr, NULL);
}
