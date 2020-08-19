#pragma once

#include <d3d11.h>
//#include "Graphics/Graphics.h"
#include "Graphics/Shader/Shader.h"
#include "Graphics/Bindable.h"

class Graphics;

class VertexShader : public Shader, public Bindable
{
public:
	bool Init(Graphics& gfx, std::wstring filePath, 
		D3D11_INPUT_ELEMENT_DESC* pLayoutDesc, UINT numElements);
	VertexShader() = default;
	~VertexShader();

	void Bind(Graphics& gfx) override;
	void Unbind(Graphics& gfx) override;

	ID3D11VertexShader* getVertexShader() const { return pVertexShader; }
	ID3D11InputLayout* getInputLayout() const{ return pInputLayout; }
private:
	ID3D11VertexShader* pVertexShader = nullptr;
	ID3D11InputLayout* pInputLayout = nullptr;
};

