#pragma once

#include <d3d11.h>
#include <d3dcompiler.h>
#include <wrl.h>
#include <string>
#include "Utility/Util.h"

class Graphics;

class Shader //virutal class
{
public:
	virtual ~Shader() = default;
	virtual void SetShaderResources(Graphics& gfx, UINT startSlot, UINT numViews, ID3D11ShaderResourceView* const* pViews) = 0;
	virtual void SetSamplers(Graphics& gfx, UINT startSlot, UINT numSamplers, ID3D11SamplerState* const* pSamplers) = 0;
	ID3DBlob* getBlob() const { return pBlob.Get(); }
protected:
	Microsoft::WRL::ComPtr<ID3DBlob> pBlob = nullptr;
};
