#include "Graphics/CubeTexture.h"
#include <DDSTextureLoader.h>

#include "Utility/Log.h"
#include "Utility/Util.h"
#include <Utility\Error.h>

using namespace DirectX;

bool CubeTexture::Load(Graphics& gfx, std::wstring& filePath) try 
{
	HRESULT hr = S_OK;

	hr = CreateDDSTextureFromFileEx(
		gfx.getDevice(),
		filePath.c_str(),
		0,
		D3D11_USAGE_DEFAULT,
		D3D11_BIND_SHADER_RESOURCE,
		0,
		D3D11_RESOURCE_MISC_TEXTURECUBE,
		false,
		reinterpret_cast<ID3D11Resource**>(pTexture.GetAddressOf()),
		&pSRV,
		nullptr
	);
	THROW_IF_FAILED(hr, "Failed to load cubemap texture.");

	return true;
} catch (const HrException& e) {
	Log::Message_Box(e);
	return false;
}
