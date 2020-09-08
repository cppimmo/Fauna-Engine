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

	void Bind(Graphics& gfx) override;
	void SetShaderResources(Graphics& gfx, UINT startSlot, UINT numViews, ID3D11ShaderResourceView* const* pViews) override;
	void SetSamplers(Graphics& gfx, UINT startSlot, UINT numSamplers, ID3D11SamplerState* const* pSamplers) override;

	ID3D11PixelShader* getPixelShader() const { return pPixelShader.Get(); }
private:
	Microsoft::WRL::ComPtr<ID3D11PixelShader> pPixelShader = nullptr;
};