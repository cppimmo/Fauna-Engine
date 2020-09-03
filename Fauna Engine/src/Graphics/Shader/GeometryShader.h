#pragma once

#include <d3d11.h>
#include "Graphics/Shader/Shader.h"
#include "Graphics/Bindable.h"

class Graphics;

class GeometryShader : public Shader, public Bindable
{
public:
	bool Init(ID3D11Device* pDevice, std::wstring& filePath);
	GeometryShader() = default;
	~GeometryShader() = default;

	void Bind(Graphics& gfx) override;
	void Unbind(Graphics& gfx) override;

	ID3D11GeometryShader* getGeometryShader() const { return pGeometryShader.Get(); }
private:
	Microsoft::WRL::ComPtr<ID3D11GeometryShader> pGeometryShader = nullptr;
};

