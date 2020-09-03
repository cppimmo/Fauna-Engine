#pragma once


#include <d3d11.h>
#include "Graphics/Shader/Shader.h"
#include "Graphics/Bindable.h"

class Graphics;
class Texture;
class CubeTexture;

class PixelShader :  public Shader, public Bindable
{
public:
	bool Init(Graphics& gfx, std::wstring filePath);
	PixelShader() = default;
	~PixelShader() = default;

	void setShaderResource(Graphics& gfx, Texture& tex);
	void setShaderResource(Graphics& gfx, CubeTexture& cubeTex);
	void Bind(Graphics& gfx) override;
	void Unbind(Graphics& gfx) override;

	ID3D11PixelShader* getPixelShader() const { return pPixelShader.Get(); }
private:
	Microsoft::WRL::ComPtr<ID3D11PixelShader> pPixelShader = nullptr;
};