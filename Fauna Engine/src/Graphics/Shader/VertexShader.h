#pragma once

#include <d3d11.h>
#include "Graphics/Shader/Shader.h"
#include "Graphics/Bindable.h"

class Graphics;

class VertexShader : public Shader, public Bindable
{
public:
	bool Init(Graphics& gfx, std::wstring filePath, 
		D3D11_INPUT_ELEMENT_DESC* pDesc, UINT numElements);
	VertexShader() = default;
	~VertexShader() = default;

	void Bind(Graphics& gfx) override; //bind sets inputlayout as well
	void SetShaderResources(Graphics& gfx, UINT startSlot, UINT numViews, ID3D11ShaderResourceView* const* pViews) override;
	void SetSamplers(Graphics& gfx, UINT startSlot, UINT numSamplers, ID3D11SamplerState* const* pSamplers) override;
	void SetInputLayout(Graphics& gfx, const D3D11_INPUT_ELEMENT_DESC* pDesc, UINT numElements);

	ID3D11VertexShader* getVertexShader() const { return pVertexShader.Get(); }
	ID3D11InputLayout* getInputLayout() const { return pInputLayout.Get(); }
private:
	Microsoft::WRL::ComPtr<ID3D11VertexShader> pVertexShader = nullptr;
	Microsoft::WRL::ComPtr<ID3D11InputLayout> pInputLayout = nullptr;
};

