#pragma once

#include <d3d11.h>
#include "Graphics/Graphics.h"
#include "Graphics/Shader/Shader.h"
#include "Graphics/Bindable.h"

class DomainShader : public Shader, public Bindable
{
public:
	bool Init(ID3D11Device* pDevice, std::wstring& filePath);
	DomainShader() = default;
	~DomainShader();

	void Bind(Graphics& gfx) override;
	void Unbind(Graphics& gfx) override;

	ID3D11DomainShader* getHullShader() const { return pDomainShader; }
private:
	ID3D11DomainShader* pDomainShader = nullptr;
};

