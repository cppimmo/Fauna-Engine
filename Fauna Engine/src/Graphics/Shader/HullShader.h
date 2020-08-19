#pragma once

#include <d3d11.h>
#include "Graphics/Graphics.h"
#include "Graphics/Shader/Shader.h"
#include "Graphics/Bindable.h"

class HullShader : public Shader, public Bindable
{
public:
	bool Init(ID3D11Device* pDevice, std::wstring& filePath);
	HullShader() = default;
	~HullShader();

	void Bind(Graphics& gfx) override;
	void Unbind(Graphics& gfx) override;

	ID3D11HullShader* getHullShader() const { return pHullShader; }
private:
	ID3D11HullShader* pHullShader = nullptr;
};

