#pragma once

#include <d3d11.h>
#include "Graphics/Shader/Shader.h"
#include "Graphics/Bindable.h"

class Graphics;

class HullShader : public Shader, public Bindable
{
public:
	bool Init(Graphics& gfx, std::wstring& filePath);
	HullShader() = default;
	~HullShader() = default;

	void Bind(Graphics& gfx) override;
	void SetShaderResources(Graphics& gfx, UINT startSlot, UINT numViews, ID3D11ShaderResourceView* const* pViews) override;
	void SetSamplers(Graphics& gfx, UINT startSlot, UINT numSamplers, ID3D11SamplerState* const* pSamplers) override;

	ID3D11HullShader* getHullShader() const { return pHullShader.Get(); }
private:
	Microsoft::WRL::ComPtr<ID3D11HullShader> pHullShader = nullptr;
};

