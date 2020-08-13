#pragma once

#include <d3d11.h>
#include <string>
#include "Graphics/Graphics.h"
#include "Graphics/Texture.h"

class CubeTexture
{
public:
	CubeTexture() = default;
	~CubeTexture();

	bool load(ID3D11Device* pDevice, std::wstring& filePath);

	ID3D11ShaderResourceView** getTexture() { return &pSRV; }
private:
	ID3D11ShaderResourceView* pSRV = nullptr;
	ID3D11Texture2D* pTexture = nullptr;
};
