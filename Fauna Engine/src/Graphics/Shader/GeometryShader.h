#pragma once

#include <d3d11.h>
#include "Graphics/Graphics.h"
#include "Graphics/Shader/Shader.h"
#include "Graphics/Bindable.h"

class GeometryShader : public Shader, public Bindable
{
public:
	bool Init(ID3D11Device* pDevice, std::wstring& filePath);
	GeometryShader() = default;
	~GeometryShader();

	void Bind(Graphics& gfx) override;
	void Unbind(Graphics& gfx) override;

	ID3D11GeometryShader* getGeometryShader() const { return pGeometryShader; }
private:
	ID3D11GeometryShader* pGeometryShader = nullptr;
};

