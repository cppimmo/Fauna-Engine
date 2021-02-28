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

	void OnSize(unsigned int newWidth, unsigned int newHeight);
	void SetFullscreen(bool fullscreen, unsigned int widhth, unsigned int height);
	bool GetFullscreen() const { return isFullscreen; }
	void SetWireframe(bool value);
	void SetBlendState(bool value);
	void SetSkyboxState(bool value);
	void SetDrawMode(D3D11_PRIMITIVE_TOPOLOGY mode);
	bool IsWireframe() const { return isWireframeEnabled; }
	void Begin(float r, float g, float b);
	void End();

	auto GetDevice() const -> ID3D11Device*;
	auto GetContext() const -> ID3D11DeviceContext*;
	auto GetSamplerState() const -> ID3D11SamplerState* const*;
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
	UINT bufferCount = 1;
	UINT sampleQuality = 0;
private:
	Microsoft::WRL::ComPtr<ID3D11Device> pDevice = nullptr;
	Microsoft::WRL::ComPtr<ID3D11DeviceContext> pContext = nullptr;
	Microsoft::WRL::ComPtr<IDXGISwapChain> pSwapChain = nullptr;
	Microsoft::WRL::ComPtr<ID3D11RenderTargetView> pRenderTarget = nullptr;
	Microsoft::WRL::ComPtr<ID3D11DepthStencilView> pDepthStencilView = nullptr;
	Microsoft::WRL::ComPtr<ID3D11Texture2D> pDepthStencilBuffer = nullptr;
	//pipline states
	Microsoft::WRL::ComPtr<ID3D11RasterizerState> pWireframeState = nullptr;
	Microsoft::WRL::ComPtr<ID3D11RasterizerState> pSkyboxState = nullptr;
	Microsoft::WRL::ComPtr<ID3D11RasterizerState> pCWCullState = nullptr;
	Microsoft::WRL::ComPtr<ID3D11RasterizerState> pCCWCullState = nullptr;
	Microsoft::WRL::ComPtr<ID3D11BlendState> pTransBlendState = nullptr;
	Microsoft::WRL::ComPtr<ID3D11DepthStencilState> pDSLessEqualState = nullptr;
	Microsoft::WRL::ComPtr<ID3D11SamplerState> pSamplerState = nullptr;
};

