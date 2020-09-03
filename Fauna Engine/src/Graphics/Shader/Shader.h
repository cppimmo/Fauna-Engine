#pragma once

#include <d3d11.h>
#include <d3dcompiler.h>
#include <wrl.h>
#include <string>
#include "Utility/Util.h"

class Shader //virutal class
{
public:
	virtual ~Shader() = default;
	ID3DBlob* getBlob() const { return pBlob.Get(); }
protected:
	Microsoft::WRL::ComPtr<ID3DBlob> pBlob = nullptr;
};
