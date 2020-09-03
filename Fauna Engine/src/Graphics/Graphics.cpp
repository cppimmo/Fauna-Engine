#include "Graphics/Graphics.h"
#include "Utility/Error.h"
#include "Utility/Util.h"

using namespace DirectX;
namespace wrl = Microsoft::WRL;

Graphics::~Graphics()
{
	ImGui_ImplDX11_Shutdown();
	ImGui_ImplWin32_Shutdown();
	ImGui::DestroyContext();
}

bool Graphics::Init(bool isFullscreen, bool isVsync, unsigned int width, 
	unsigned int height, HWND hWnd) try //function try catch
{
	this->isFullscreen = isFullscreen;
	this->isVsync = isVsync;
	this->samplingLevel = SAMPLE_LEVEL_4;
	HRESULT hr = S_OK;

	UINT creationFlags = D3D11_CREATE_DEVICE_BGRA_SUPPORT;
#if defined(_DEBUG)
	creationFlags |= D3D11_CREATE_DEVICE_DEBUG;
#endif
	D3D_FEATURE_LEVEL featureLevels[] = {
		D3D_FEATURE_LEVEL_11_1,
		D3D_FEATURE_LEVEL_11_0,
		D3D_FEATURE_LEVEL_10_1,
		D3D_FEATURE_LEVEL_10_0,
		D3D_FEATURE_LEVEL_9_3,
		D3D_FEATURE_LEVEL_9_2,
		D3D_FEATURE_LEVEL_9_1,
	};
	D3D_FEATURE_LEVEL feature_level;
	hr = D3D11CreateDevice(
		nullptr,
		D3D_DRIVER_TYPE_HARDWARE,
		nullptr,
		creationFlags,
		featureLevels,
		std::size(featureLevels),
		D3D11_SDK_VERSION,
		pDevice.GetAddressOf(),
		&feature_level,
		pContext.GetAddressOf()
	);
	THROW_IF_FAILED(hr, "Create device and swapchain failed");
	if ((feature_level != D3D_FEATURE_LEVEL_11_0) && (feature_level != D3D_FEATURE_LEVEL_11_1)) {
		THROW_NORMAL("You must have DirectX 11 Compatible graphics card!");
	}
	hr = pDevice->CheckMultisampleQualityLevels(DXGI_FORMAT_R8G8B8A8_UNORM, samplingLevel, &sampleQuality);
	if (!(sampleQuality > 0)) {
		THROW_NORMAL("Sampling level not supported");
	}

	//Create SwapChain after device to allow for multisampling
	DXGI_SWAP_CHAIN_DESC sd = {};
	sd.BufferDesc.Width = width;
	sd.BufferDesc.Height = height;
	sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	sd.BufferDesc.RefreshRate.Numerator = 60;
	sd.BufferDesc.RefreshRate.Denominator = 1;
	sd.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
	sd.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
	sd.SampleDesc.Count = samplingLevel;
	sd.SampleDesc.Quality = sampleQuality - 1;
	sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	sd.BufferCount = 1;
	sd.OutputWindow = hWnd;
	sd.Windowed = TRUE;
	sd.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
	sd.Flags = 0;

	wrl::ComPtr<IDXGIDevice> dxgiDevice = nullptr;
	hr = pDevice->QueryInterface(__uuidof(IDXGIDevice), reinterpret_cast<void**>(dxgiDevice.GetAddressOf()));
	THROW_IF_FAILED(hr, "BRO");
	wrl::ComPtr<IDXGIAdapter> dxgiAdapter = nullptr;
	dxgiDevice->GetParent(__uuidof(IDXGIAdapter), reinterpret_cast<void**>(dxgiAdapter.GetAddressOf()));

	wrl::ComPtr<IDXGIFactory> dxgiFactory = nullptr;
	dxgiAdapter->GetParent(__uuidof(IDXGIFactory), reinterpret_cast<void**>(dxgiFactory.GetAddressOf()));
	THROW_IF_FAILED(hr, "Facotry");
	dxgiFactory->CreateSwapChain(pDevice.Get(), &sd, pSwapChain.GetAddressOf());
	dxgiDevice.Reset();
	dxgiAdapter.Reset();
	dxgiFactory.Reset();

	this->onSize(width, height);

	D3D11_RASTERIZER_DESC rsd = {};
	rsd.FillMode = D3D11_FILL_WIREFRAME;
	rsd.CullMode = D3D11_CULL_NONE;
	
	hr = pDevice->CreateRasterizerState(&rsd, pWireframeState.GetAddressOf());
	THROW_IF_FAILED(hr, "Create rasterizer state failed");

	D3D11_RASTERIZER_DESC skyRSD = {};
	skyRSD.FillMode = D3D11_FILL_SOLID;
	skyRSD.CullMode = D3D11_CULL_NONE;

	hr = pDevice->CreateRasterizerState(&skyRSD, pSkyboxState.GetAddressOf());
	THROW_IF_FAILED(hr, "Skybox creation failed.");

	D3D11_DEPTH_STENCIL_DESC dsd = {};
	dsd.DepthEnable = true;
	dsd.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
	dsd.DepthFunc = D3D11_COMPARISON_LESS_EQUAL;

	hr = pDevice->CreateDepthStencilState(&dsd, pDSLessEqualState.GetAddressOf());
	THROW_IF_FAILED(hr, "Depth Stencil State creation failed.");

	D3D11_BLEND_DESC blend_desc = {};
	blend_desc.AlphaToCoverageEnable = false;
	blend_desc.IndependentBlendEnable = false;

	blend_desc.RenderTarget[0].BlendEnable = true;
	blend_desc.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA;
	blend_desc.RenderTarget[0].DestBlend = D3D11_BLEND_INV_SRC_ALPHA;
	blend_desc.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;
	blend_desc.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ONE;
	blend_desc.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ZERO;
	blend_desc.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;
	blend_desc.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;

	hr = pDevice->CreateBlendState(&blend_desc, pTransBlendState.GetAddressOf());

	D3D11_RASTERIZER_DESC cull_desc = {};
	cull_desc.FillMode = D3D11_FILL_SOLID;
	cull_desc.CullMode = D3D11_CULL_BACK;

	cull_desc.FrontCounterClockwise = true;
	hr = pDevice->CreateRasterizerState(&cull_desc, pCCWCullState.GetAddressOf());
	THROW_IF_FAILED(hr, "Failed to create rasterizer state.");

	cull_desc.FrontCounterClockwise = false;
	hr = pDevice->CreateRasterizerState(&cull_desc, pCWCullState.GetAddressOf());
	THROW_IF_FAILED(hr, "Failed to create rasterizer state.");

	D3D11_INPUT_ELEMENT_DESC layout[] =
	{
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	};
	if (!vertexShader.Init(*this, L"VertexShader.cso", layout, std::size(layout)))
		THROW_NORMAL("Vertex Shader failed to create");
	if (!pixelShader.Init(*this, L"PixelShader.cso"))
		THROW_NORMAL("Pixel Shader failed to create");

	if (!skySphere_VS.Init(*this, L"SkySphere_VS.cso", layout, std::size(layout)))
		THROW_NORMAL("Vertex Shader failed to create");
	if (!skySphere_PS.Init(*this, L"SkySphere_PS.cso"))
		THROW_NORMAL("Pixel Shader failed to create");

	/*D3D11_INPUT_ELEMENT_DESC layout2[2] = 
	{
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	};
	if (!vertexShaderColor.init(pDevice, L"VertexShaderColor.cso", layout2, std::size(layout2)))
		THROW_NORMAL("Vertex Shader failed to create");
	if (!pixelShaderColor.init(pDevice, L"PixelShaderColor.cso"))
		THROW_NORMAL("Pixel Shader failed to create");*/

	//create texture sampler state
	D3D11_SAMPLER_DESC tsd = {};
	tsd.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
	tsd.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
	tsd.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
	tsd.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
	tsd.ComparisonFunc = D3D11_COMPARISON_NEVER;
	tsd.MinLOD = 0;
	tsd.MaxLOD = D3D11_FLOAT32_MAX;
	hr = pDevice->CreateSamplerState(&tsd, pTexSamplerState.GetAddressOf());
	THROW_IF_FAILED(hr, "Create sampler state failed");
	//setup imgui
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	//ImGuiContext* context = ImGui::CreateContext();
	//ImGui::SetCurrentContext(context);
	//ImGuiIO& io = ImGui::GetIO();
	ImGui_ImplWin32_Init(hWnd);
	ImGui_ImplDX11_Init(this->pDevice.Get(), this->pContext.Get());
	ImGui::StyleColorsDark();
	return true;
} catch (HrException& e) {
	ErrorLogger::Log(e);
	return false;
}

void Graphics::onSize(unsigned int newWidth, unsigned int newHeight) try
{
	pRenderTarget.Reset();
	pDepthStencilView.Reset();
	pDepthStencilBuffer.Reset();

	HRESULT hr = S_OK;

	hr = pSwapChain->ResizeBuffers(1, newWidth, newHeight, DXGI_FORMAT_B8G8R8A8_UNORM, 0);
	ID3D11Texture2D* BackBuffer; //Create our BackBuffer
	hr = pSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), reinterpret_cast<void**>(&BackBuffer));
	THROW_IF_FAILED(hr, "GetBuffer failed");
	//Create our Render Target
	hr = pDevice->CreateRenderTargetView(BackBuffer, nullptr, pRenderTarget.GetAddressOf());
	ReleaseCOM(BackBuffer);//release backbuffer incase of exception
	THROW_IF_FAILED(hr, "Create render target view failed");

	D3D11_TEXTURE2D_DESC ds = {};
	ds.Width = newWidth;
	ds.Height = newHeight;
	ds.MipLevels = 1;
	ds.ArraySize = 1;
	ds.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
	ds.SampleDesc.Count = samplingLevel;
	ds.SampleDesc.Quality = sampleQuality - 1;
	ds.Usage = D3D11_USAGE_DEFAULT;
	ds.BindFlags = D3D11_BIND_DEPTH_STENCIL;
	ds.CPUAccessFlags = 0;
	ds.MiscFlags = 0;

	hr = pDevice->CreateTexture2D(&ds, nullptr, pDepthStencilBuffer.GetAddressOf());
	THROW_IF_FAILED(hr, "DepthStencilBuffer could not be created");
	hr = pDevice->CreateDepthStencilView(pDepthStencilBuffer.Get(), nullptr, pDepthStencilView.GetAddressOf());
	THROW_IF_FAILED(hr, "DepthStencilView could not be created");
	//Set our Render Target
	pContext->OMSetRenderTargets(1, pRenderTarget.GetAddressOf(), pDepthStencilView.Get());

	CD3D11_VIEWPORT viewport(0.0f, 0.0f, static_cast<float>(newWidth), static_cast<float>(newHeight), 0.0f, 1.0f);
	pContext->RSSetViewports(1, &viewport);
} catch (HrException& e) {
	ErrorLogger::Log(e);
}

void Graphics::setFullscreen(bool fullscreen, unsigned int width, unsigned int height)
{
	//onSize(width, height);
	this->isFullscreen = fullscreen;
	pSwapChain->SetFullscreenState(fullscreen, nullptr);
}

void Graphics::setWireframe(bool value)
{
	isWireframeEnabled = value;
	if (value)
		pContext->RSSetState(pWireframeState.Get());
	else
		pContext->RSSetState(nullptr);
}

void Graphics::setBlendState(bool value)
{
	if (value)
	{
		::XMFLOAT4 blendFactor = { 0.75f, 0.75f, 0.75f, 1.0f };
		pContext->OMSetBlendState(pTransBlendState.Get(), reinterpret_cast<float*>(&blendFactor), 0xffffffff);
	}
	else
	{
		pContext->OMSetBlendState(0, 0, 0xffffffff);
	}
}

void Graphics::setSkyboxState(bool value)
{
	if (value)
	{
		pContext->RSSetState(pSkyboxState.Get());
		pContext->OMSetDepthStencilState(pDSLessEqualState.Get(), 0);
	}
	else
	{
		pContext->RSSetState(nullptr);
		pContext->OMSetDepthStencilState(nullptr, 0);
	}	
}

void Graphics::setDrawMode(D3D11_PRIMITIVE_TOPOLOGY mode)
{
	pContext->IASetPrimitiveTopology(mode);
}

void Graphics::Begin(float r, float g, float b)
{
	const float color[4] = { r, g, b, 1.0f };
	pContext->ClearRenderTargetView(pRenderTarget.Get(), color);
	pContext->ClearDepthStencilView(pDepthStencilView.Get(), D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);
	pContext->PSSetSamplers(0u, 1u, &pTexSamplerState);
}

void Graphics::End()
{
	pSwapChain->Present(isVsync, 0u);
}
