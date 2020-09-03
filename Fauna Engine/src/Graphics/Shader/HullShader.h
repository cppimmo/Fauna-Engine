#pragma once

#include <d3d11.h>
#include "Graphics/Shader/Shader.h"
#include "Graphics/Bindable.h"

class Graphics;

class HullShader : public Shader, public Bindable
{
public:
	bool Init(ID3D11Device* pDevice, std::wstring& filePath);
	HullShader() = default;
	~HullShader() = default;

	void Bind(Graphics& gfx) override;
	void Unbind(Graphics& gfx) override;

	ID3D11HullShader* getHullShader() const { return pHullShader.Get(); }
private:
	Microsoft::WRL::ComPtr<ID3D11HullShader> pHullShader = nullptr;
};

