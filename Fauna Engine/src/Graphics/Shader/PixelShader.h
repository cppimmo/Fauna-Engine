#pragma once

#include <d3d11.h>
//#include "Graphics/Graphics.h"
#include "Graphics/Shader/Shader.h"
#include "Graphics/Bindable.h"

class Graphics;

class PixelShader :  public Shader, public Bindable
{
public:
	bool Init(Graphics& gfx, std::wstring filePath);
	PixelShader() = default;
	~PixelShader();

	void Bind(Graphics& gfx);
	void Unbind(Graphics& gfx);

	ID3D11PixelShader* getPixelShader() const { return pPixelShader; }
private:
	ID3D11PixelShader* pPixelShader = nullptr;
};
