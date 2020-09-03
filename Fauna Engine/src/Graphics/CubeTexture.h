#pragma once

#include <d3d11.h>
#include <string>
#include "Graphics/Graphics.h"
#include "Graphics/Texture.h"

class CubeTexture
{
public:
	CubeTexture() = default;
	~CubeTexture() = default;

	bool Load(Graphics& gfx, std::wstring& filePath);

	ID3D11ShaderResourceView* const* getTexture() const { return pSRV.GetAddressOf(); }
private:
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> pSRV = nullptr;
	Microsoft::WRL::ComPtr<ID3D11Texture2D> pTexture = nullptr;
};
