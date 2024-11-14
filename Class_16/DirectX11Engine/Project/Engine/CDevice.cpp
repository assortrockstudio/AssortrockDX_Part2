#include "pch.h"
#include "CDevice.h"

#include "CConstBuffer.h"

CDevice::CDevice()
	: m_hMainWnd(nullptr)
	, m_Sampler{}
{
}

CDevice::~CDevice()
{	
	Safe_Del_Array(m_CB);
}

int CDevice::init(HWND _hWnd, Vec2 _Resolution)
{
	m_hMainWnd = _hWnd;
	m_RenderResolution = _Resolution;

	UINT iFlag = 0;
#ifdef _DEBUG
	iFlag = D3D11_CREATE_DEVICE_DEBUG;
#endif

	D3D_FEATURE_LEVEL level = D3D_FEATURE_LEVEL_11_0;

	if (FAILED(D3D11CreateDevice(nullptr, D3D_DRIVER_TYPE_HARDWARE
		, nullptr, iFlag, nullptr, 0, D3D11_SDK_VERSION
		, m_Device.GetAddressOf(), &level, m_Context.GetAddressOf())))
	{
		return E_FAIL;
	}

	// SwapChain
	if (FAILED(CreateSwapChain()))
	{
		return E_FAIL;
	}

	// View
	if (FAILED(CreateView()))
	{
		return E_FAIL;
	}
	
	// ViewPort ����
	// ������ ȭ�鿡 ������ ������ ����
	D3D11_VIEWPORT viewport = {};
	viewport.TopLeftX = 0;
	viewport.TopLeftY = 0;
	viewport.Width = (float)m_RenderResolution.x;
	viewport.Height = (float)m_RenderResolution.y;

	// ���� �ؽ��Ŀ� ����Ǵ� ���� Min, Max ����
	viewport.MinDepth = 0;
	viewport.MaxDepth = 1;

	// ViewPort ���� ����
	m_Context->RSSetViewports(1, &viewport);

	// �ʿ��� ������� ����
	if (FAILED(CreateConstBuffer()))
	{
		return E_FAIL;
	}

	// �ʿ��� ���÷� ����
	if (FAILED(CreateSamplerState()))
	{
		return E_FAIL;
	}	

	// Rasterizer State ����
	if (FAILED(CreateRasterizerState()))
	{
		return E_FAIL;
	}

	// DepthStencilState ����
	if (FAILED(CreateDepthStencilState()))
	{
		return E_FAIL;
	}

	// BlendState ����
	if (FAILED(CreateBlendState()))
	{
		return E_FAIL;
	}


	return S_OK;
}

void CDevice::ClearTarget(float(&_ArrColor)[4])
{
	m_Context->ClearRenderTargetView(m_RTV.Get(), _ArrColor);	
	m_Context->ClearDepthStencilView(m_DSV.Get(), D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.f, 0);
}


int CDevice::CreateSwapChain()
{
	DXGI_SWAP_CHAIN_DESC Desc = {};

	// SwapChain ��� ������
	Desc.OutputWindow = m_hMainWnd;
	Desc.Windowed = true;
	
	// RenderTarget �ؽ����� �ػ� ����
	Desc.BufferCount = 1;
	Desc.BufferDesc.Width = m_RenderResolution.x;
	Desc.BufferDesc.Height = m_RenderResolution.y;
	Desc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	Desc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;

	Desc.BufferDesc.RefreshRate.Denominator = 1;
	Desc.BufferDesc.RefreshRate.Numerator = 60;
	Desc.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
	Desc.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
	
	Desc.SampleDesc.Count = 1;
	Desc.SampleDesc.Quality = 0;
	Desc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
	Desc.Flags = 0;
	
	ComPtr<IDXGIDevice>		pDXGIDevice = nullptr;
	ComPtr<IDXGIAdapter>	pAdapter = nullptr;
	ComPtr<IDXGIFactory>	pFactory = nullptr;

	m_Device->QueryInterface(__uuidof(IDXGIDevice), (void**)pDXGIDevice.GetAddressOf());
	pDXGIDevice->GetParent(__uuidof(IDXGIAdapter), (void**)pAdapter.GetAddressOf());
	pAdapter->GetParent(__uuidof(IDXGIFactory), (void**)pFactory.GetAddressOf());
			
	// SwapChain ����
	if (FAILED(pFactory->CreateSwapChain(m_Device.Get(), &Desc, m_SwapChain.GetAddressOf())))
		return E_FAIL;

	return S_OK;
}

int CDevice::CreateView()
{
	// RenderTarget View �����
	// 1. RenderTarget �� �ؽ��ĸ� SwapChain ���κ��� �����´�.
	m_SwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)m_RenderTargetTex.GetAddressOf());	

	// 2. ����Ÿ�� �ؽ��ĸ� �̿��ؼ� ����Ÿ�ٺ並 �����.
	m_Device->CreateRenderTargetView(m_RenderTargetTex.Get(), nullptr, m_RTV.GetAddressOf());
	
	
	// DepthStencil View �����
	// 1. DepthStencil Texture �� �����Ѵ�.
	D3D11_TEXTURE2D_DESC Desc = {};

	Desc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
	Desc.Width = m_RenderResolution.x;
	Desc.Height = m_RenderResolution.y;
	Desc.ArraySize = 1;
	
	Desc.CPUAccessFlags = 0;
	Desc.Usage = D3D11_USAGE_DEFAULT;
	Desc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
	Desc.MipLevels = 1;
	Desc.SampleDesc.Count = 1;
	Desc.SampleDesc.Quality = 0;

	m_Device->CreateTexture2D(&Desc, nullptr, &m_DepthStencilTex);

	// 2. DepthStencilView�� �����Ѵ�.
	m_Device->CreateDepthStencilView(m_DepthStencilTex.Get(), nullptr, m_DSV.GetAddressOf());

	// SwapChain �� �ؽ��ĸ� ����Ÿ������ �����ϰ�, 
	// ���� ���� DepthStencil �� �ؽ��ĸ� ���� ����� �ؽ��ķ� ������
	m_Context->OMSetRenderTargets(1, m_RTV.GetAddressOf(), m_DSV.Get());

	return S_OK;
}

int CDevice::CreateConstBuffer()
{
	m_CB[(UINT)CB_TYPE::TRANSFORM] = new CConstBuffer;
	m_CB[(UINT)CB_TYPE::TRANSFORM]->Create(sizeof(tTransform), CB_TYPE::TRANSFORM);

	m_CB[(UINT)CB_TYPE::MATERIAL] = new CConstBuffer;
	m_CB[(UINT)CB_TYPE::MATERIAL]->Create(sizeof(tMtrlConst), CB_TYPE::MATERIAL);




	return S_OK;
}

int CDevice::CreateSamplerState()
{
	D3D11_SAMPLER_DESC Desc[2] = { };

	Desc[0].AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
	Desc[0].AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
	Desc[0].AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
	Desc[0].Filter = D3D11_FILTER_ANISOTROPIC;	
	DEVICE->CreateSamplerState(Desc, m_Sampler[0].GetAddressOf());
	CONTEXT->PSSetSamplers(0, 1, m_Sampler[0].GetAddressOf());


	Desc[1].AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
	Desc[1].AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
	Desc[1].AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
	Desc[1].Filter = D3D11_FILTER_MIN_MAG_MIP_POINT;
	DEVICE->CreateSamplerState(Desc + 1, m_Sampler[1].GetAddressOf());
	CONTEXT->PSSetSamplers(1, 1, m_Sampler[1].GetAddressOf());


	return 0;
}

int CDevice::CreateRasterizerState()
{
	// CULL_BACK ����� Default �ɼ��̱� ������, nullptr �� �д�.
	m_RS[(UINT)RS_TYPE::CULL_BACK] = nullptr;

	// CULL_FRONT
	D3D11_RASTERIZER_DESC Desc = {};
	Desc.CullMode = D3D11_CULL_FRONT;
	Desc.FillMode = D3D11_FILL_SOLID;
	DEVICE->CreateRasterizerState(&Desc, m_RS[(UINT)RS_TYPE::CULL_FRONT].GetAddressOf());

	// CULL_NONE
	Desc.CullMode = D3D11_CULL_NONE;
	Desc.FillMode = D3D11_FILL_SOLID;
	DEVICE->CreateRasterizerState(&Desc, m_RS[(UINT)RS_TYPE::CULL_NONE].GetAddressOf());

	// WIRE_FRAME
	Desc.CullMode = D3D11_CULL_NONE;
	Desc.FillMode = D3D11_FILL_WIREFRAME;
	DEVICE->CreateRasterizerState(&Desc, m_RS[(UINT)RS_TYPE::WIRE_FRAME].GetAddressOf());

	return S_OK;
}

int CDevice::CreateDepthStencilState()
{
	m_DS[(UINT)DS_TYPE::LESS] = nullptr;

	D3D11_DEPTH_STENCIL_DESC Desc = {};


	// LESS_EQUAL
	Desc.DepthEnable = true;	// ���� �� ��� ���
	Desc.StencilEnable = false;	// ���ٽ� ��� ��Ȱ��ȭ
	Desc.DepthFunc = D3D11_COMPARISON_LESS_EQUAL;	// �۰ų� ������� ���
	Desc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL; // ���� �׽�Ʈ ���� ��, ���� ���

	DEVICE->CreateDepthStencilState(&Desc, m_DS[(UINT)DS_TYPE::LESS_EQUAL].GetAddressOf());

	// GREATER
	Desc.DepthEnable = true;	// ���� �� ��� ���
	Desc.StencilEnable = false;	// ���ٽ� ��� ��Ȱ��ȭ
	Desc.DepthFunc = D3D11_COMPARISON_GREATER;	// �۰ų� ������� ���
	Desc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL; // ���� �׽�Ʈ ���� ��, ���� ���

	DEVICE->CreateDepthStencilState(&Desc, m_DS[(UINT)DS_TYPE::GREATER].GetAddressOf());


	// NO_TEST
	Desc.DepthEnable = true;	// ���� �� ��� ���
	Desc.StencilEnable = false;	// ���ٽ� ��� ��Ȱ��ȭ
	Desc.DepthFunc = D3D11_COMPARISON_ALWAYS;	// �۰ų� ������� ���
	Desc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL; // ���� �׽�Ʈ ���� ��, ���� ���

	DEVICE->CreateDepthStencilState(&Desc, m_DS[(UINT)DS_TYPE::NO_TEST].GetAddressOf());

	// NO_TEST_NO_WRITE
	Desc.DepthEnable = false;	// ���� �� ��� ���
	Desc.StencilEnable = false;	// ���ٽ� ��� ��Ȱ��ȭ
	Desc.DepthFunc = D3D11_COMPARISON_ALWAYS;	// �۰ų� ������� ���
	Desc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ZERO; // ���� �׽�Ʈ ���� ��, ���� ���

	DEVICE->CreateDepthStencilState(&Desc, m_DS[(UINT)DS_TYPE::NO_TEST_NO_WRITE].GetAddressOf());

	return S_OK;
}

int CDevice::CreateBlendState()
{
	m_BS[(UINT)BS_TYPE::DEFAULT] = nullptr;

	D3D11_BLEND_DESC Desc = {};


	// ALPHA_BLEND	
	Desc.AlphaToCoverageEnable = false;
	Desc.IndependentBlendEnable = false;

	Desc.RenderTarget[0].BlendEnable = true;

	// ������ ���
	Desc.RenderTarget[0].BlendOp = D3D11_BLEND_OP::D3D11_BLEND_OP_ADD;
	Desc.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP::D3D11_BLEND_OP_ADD;

	// ������ ���
	Desc.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA;
	Desc.RenderTarget[0].DestBlend = D3D11_BLEND_INV_SRC_ALPHA;
	Desc.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;

	// ���ĳ����� ȥ�ս�
	Desc.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ONE;
	Desc.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ONE;

	HRESULT hr = DEVICE->CreateBlendState(&Desc, m_BS[(UINT)BS_TYPE::ALPHA_BLEND].GetAddressOf());




	// ONE_ONE
	Desc.AlphaToCoverageEnable = false;
	Desc.IndependentBlendEnable = false;

	Desc.RenderTarget[0].BlendEnable = true;

	// ������ ���
	Desc.RenderTarget[0].BlendOp = D3D11_BLEND_OP::D3D11_BLEND_OP_ADD;
	Desc.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP::D3D11_BLEND_OP_ADD;

	// ������ ���
	Desc.RenderTarget[0].SrcBlend = D3D11_BLEND_ONE;
	Desc.RenderTarget[0].DestBlend = D3D11_BLEND_ONE;
	Desc.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;

	// ���ĳ����� ȥ�ս�
	Desc.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ONE;
	Desc.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ONE;
	DEVICE->CreateBlendState(&Desc, m_BS[(UINT)BS_TYPE::ONE_ONE].GetAddressOf());


	return S_OK;
}