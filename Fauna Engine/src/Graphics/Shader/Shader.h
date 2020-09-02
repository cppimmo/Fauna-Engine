#pragma once

#include <d3d11.h>
#include <d3dcompiler.h>
#include <string>
#include "Utility/Util.h"
#include <wrl.h>

namespace wrl = Microsoft::WRL;

class Shader//virutal class
{
public:
	virtual ~Shader() = default;
	ID3DBlob* getBlob() const { return pBlob.Get(); }
protected:
	wrl::ComPtr<ID3DBlob> pBlob = nullptr;
};

