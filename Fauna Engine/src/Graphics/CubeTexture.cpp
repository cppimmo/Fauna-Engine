#include "Graphics/CubeTexture.h"
#include <DDSTextureLoader.h>
#include "Utility/Error.h"
#include "Utility/Util.h"

using namespace DirectX;

CubeTexture::~CubeTexture()
{
	ReleaseCOM(pTexture);
	ReleaseCOM(pSRV);
}

bool CubeTexture::load(ID3D11Device* pDevice, std::wstring& filePath) try 
{
	HRESULT hr = S_OK;

	hr = CreateDDSTextureFromFileEx(
		pDevice,
		filePath.c_str(),
		0,
		D3D11_USAGE_DEFAULT,
		D3D11_BIND_SHADER_RESOURCE,
		0,
		D3D11_RESOURCE_MISC_TEXTURECUBE,
		false,
		reinterpret_cast<ID3D11Resource**>(&pTexture),
		&pSRV,
		nullptr
	);
	THROW_IF_FAILED(hr, "Failed to load cubemap texture.");

	return true;
} catch (HrException& e) {
	ErrorLogger::Log(e);
	return false;
}
