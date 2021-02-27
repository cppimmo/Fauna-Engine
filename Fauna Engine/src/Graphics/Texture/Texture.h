#pragma once

#include <d3d11.h>
#include "Graphics/Graphics.h"
#include <string>

class Texture
{
public:
	Texture() = default;
	~Texture() = default;

	bool Load(Graphics& gfx, std::wstring filePath);
	ID3D11ShaderResourceView* const* getTexture() const { return pTexture.GetAddressOf(); }
private:
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> pTexture = nullptr;
};

