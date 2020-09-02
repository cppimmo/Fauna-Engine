#pragma once

#include "Win.h"
#include <d3d11.h>
#include <DirectXMath.h>
#include <wrl.h>

#include "Graphics/VertexTypes.h"
#include "Graphics/Shader/VertexShader.h"
#include "Graphics/Shader/PixelShader.h"
#include "Utility/Util.h"

#include <imgui.h>
#include <imgui_impl_dx11.h>
#include <imgui_impl_win32.h>

namespace wrl = Microsoft::WRL;

class Graphics
{
private:
	enum SAMPLE_LEVEL
	{
		SAMPLE_LEVEL_NONE = 1,
		SAMPLE_LEVEL_4 = 4,
		SAMPLE_LEVEL_8 = 8,
		SAMPLE_LEVEL_16 = 16,
	} samplingLevel;
public:
	Graphics() = default;
	Graphics(const Graphics&) = delete;
	Graphics& operator=(const Graphics&) = delete;
	~Graphics();

	bool Init(bool isFullscreen, bool isVsync, unsigned int width, unsigned int height, HWND hWnd);

	void onSize(unsigned int newWidth, unsigned int newHeight);
	void setFullscreen(bool fullscreen, unsigned int widhth, unsigned int height);
	bool getFullscreen() const { return isFullscreen; }
	void setWireframe(bool value);
	void setBlendState(bool value);
	void setSkyboxState(bool value);
	bool isWireframe() const { return isWireframeEnabled; }
	void Begin(float r, float g, float b);
	void End();

	ID3D11Device* getDevice() { return pDevice.Get(); }
	ID3D11DeviceContext* getContext() { return pContext.Get(); }
	ID3D11SamplerState* const* getSamplerState() { return &pTexSamplerState; }
public:
	VertexShader vertexShader;
	PixelShader pixelShader;
	VertexShader skySphere_VS;
	PixelShader skySphere_PS;
	//VertexShader vertexShaderColor;
	//PixelShader pixelShaderColor;
private:
	bool isVsync = false;
	bool isFullscreen = false;
	bool isWireframeEnabled = false;
	UINT sampleQuality = 0;
private: //com MAKE THESE COMPTRS DING DONGa
	wrl::ComPtr<ID3D11Device> pDevice = nullptr;
	wrl::ComPtr<ID3D11DeviceContext> pContext = nullptr;
	wrl::ComPtr<IDXGISwapChain> pSwapChain = nullptr;
	wrl::ComPtr<ID3D11RenderTargetView> pRenderTarget = nullptr;
	wrl::ComPtr<ID3D11DepthStencilView> pDepthStencilView = nullptr;
	wrl::ComPtr<ID3D11Texture2D> pDepthStencilBuffer = nullptr;
	//pipline states
	wrl::ComPtr<ID3D11RasterizerState> pWireframeState = nullptr;
	wrl::ComPtr<ID3D11RasterizerState> pSkyboxState = nullptr;
	wrl::ComPtr<ID3D11RasterizerState> pCWCullState = nullptr;
	wrl::ComPtr<ID3D11RasterizerState> pCCWCullState = nullptr;
	wrl::ComPtr<ID3D11BlendState> pTransBlendState = nullptr;
	wrl::ComPtr<ID3D11DepthStencilState> pDSLessEqualState = nullptr;
	wrl::ComPtr<ID3D11SamplerState> pTexSamplerState = nullptr;
};

