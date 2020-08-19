#pragma once

#include <d3d11.h>
#include "Graphics/Graphics.h"
#include <string>

class Texture
{
public:
	Texture() = default;
	~Texture();

	bool Load(Graphics& gfx, std::wstring filePath);
	//return double ptr to objs for pssetblahblah functions
	ID3D11ShaderResourceView* const* getTexture() const { return &pTexture; }
private:
	ID3D11ShaderResourceView* pTexture = nullptr;
};

