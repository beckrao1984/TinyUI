#include "stdafx.h"
#include "DX11.h"

namespace DXFramework
{
	DX11::DX11()
		:m_hWND(NULL)
	{

	}
	DX11::~DX11()
	{

	}
	BOOL DX11::Initialize(HWND hWND, INT x, INT y, INT cx, INT cy)
	{
		m_hWND = hWND;
		m_pos.x = x;
		m_pos.y = y;
		m_size.cx = cx;
		m_size.cy = cy;
		DXGI_SWAP_CHAIN_DESC swapDesc;
		ZeroMemory(&swapDesc, sizeof(swapDesc));
		swapDesc.BufferCount = 2;
		swapDesc.BufferDesc.Width = cx;
		swapDesc.BufferDesc.Height = cy;
		swapDesc.BufferDesc.Format = DXGI_FORMAT_B8G8R8A8_UNORM;
		swapDesc.BufferDesc.RefreshRate.Numerator = 0;
		swapDesc.BufferDesc.RefreshRate.Denominator = 1;
		swapDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
		swapDesc.OutputWindow = hWND;
		swapDesc.SampleDesc.Count = 1;
		swapDesc.SampleDesc.Quality = 0;
		swapDesc.Windowed = TRUE;
		swapDesc.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
		swapDesc.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
		swapDesc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
		swapDesc.Flags = 0;
		HRESULT hRes = S_OK;
		D3D_FEATURE_LEVEL level = D3D_FEATURE_LEVEL_11_0;
		hRes = D3D11CreateDeviceAndSwapChain(NULL, D3D_DRIVER_TYPE_HARDWARE, NULL, 0, &level, 1, D3D11_SDK_VERSION, &swapDesc, &m_swap, &m_d3d, NULL, &m_context);
		if (FAILED(hRes))
			return FALSE;
		TinyComPtr<ID3D11Texture2D> backBuffer;
		hRes = m_swap->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&backBuffer);
		if (FAILED(hRes))
			return FALSE;
		hRes = m_d3d->CreateRenderTargetView(backBuffer, NULL, &m_renderView);
		if (FAILED(hRes))
			return FALSE;
		D3D11_TEXTURE2D_DESC depthBufferDesc;
		ZeroMemory(&depthBufferDesc, sizeof(depthBufferDesc));
		depthBufferDesc.Width = cx;
		depthBufferDesc.Height = cy;
		depthBufferDesc.MipLevels = 1;
		depthBufferDesc.ArraySize = 1;
		depthBufferDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
		depthBufferDesc.SampleDesc.Count = 1;
		depthBufferDesc.SampleDesc.Quality = 0;
		depthBufferDesc.Usage = D3D11_USAGE_DEFAULT;
		depthBufferDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
		depthBufferDesc.CPUAccessFlags = 0;
		depthBufferDesc.MiscFlags = 0;
		hRes = m_d3d->CreateTexture2D(&depthBufferDesc, NULL, &m_depthStencilBuffer);
		if (FAILED(hRes))
			return FALSE;
		D3D11_DEPTH_STENCIL_DESC depthStencilDesc;
		ZeroMemory(&depthStencilDesc, sizeof(depthStencilDesc));
		depthStencilDesc.DepthEnable = TRUE;
		depthStencilDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
		depthStencilDesc.DepthFunc = D3D11_COMPARISON_LESS;
		depthStencilDesc.StencilEnable = TRUE;
		depthStencilDesc.StencilReadMask = 0xFF;
		depthStencilDesc.StencilWriteMask = 0xFF;
		depthStencilDesc.FrontFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
		depthStencilDesc.FrontFace.StencilDepthFailOp = D3D11_STENCIL_OP_INCR;
		depthStencilDesc.FrontFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
		depthStencilDesc.FrontFace.StencilFunc = D3D11_COMPARISON_ALWAYS;
		depthStencilDesc.BackFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
		depthStencilDesc.BackFace.StencilDepthFailOp = D3D11_STENCIL_OP_DECR;
		depthStencilDesc.BackFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
		depthStencilDesc.BackFace.StencilFunc = D3D11_COMPARISON_ALWAYS;
		hRes = m_d3d->CreateDepthStencilState(&depthStencilDesc, &m_depthStencilState);
		if (FAILED(hRes))
			return FALSE;
		m_context->OMSetDepthStencilState(m_depthStencilState, 1);
		D3D11_DEPTH_STENCIL_VIEW_DESC depthStencilViewDesc;
		ZeroMemory(&depthStencilViewDesc, sizeof(depthStencilViewDesc));
		depthStencilViewDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
		depthStencilViewDesc.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
		depthStencilViewDesc.Texture2D.MipSlice = 0;
		hRes = m_d3d->CreateDepthStencilView(m_depthStencilBuffer, &depthStencilViewDesc, &m_depthStencilView);
		if (FAILED(hRes))
			return FALSE;
		m_context->OMSetRenderTargets(1, &m_renderView, m_depthStencilView);
		D3D11_RASTERIZER_DESC rasterDesc;
		rasterDesc.AntialiasedLineEnable = FALSE;
		rasterDesc.CullMode = D3D11_CULL_BACK;
		rasterDesc.DepthBias = 0;
		rasterDesc.DepthBiasClamp = 0.0F;
		rasterDesc.DepthClipEnable = TRUE;
		rasterDesc.FillMode = D3D11_FILL_SOLID;
		rasterDesc.FrontCounterClockwise = FALSE;
		rasterDesc.MultisampleEnable = FALSE;
		rasterDesc.ScissorEnable = FALSE;
		rasterDesc.SlopeScaledDepthBias = 0.0F;
		hRes = m_d3d->CreateRasterizerState(&rasterDesc, &m_rasterizerState);
		if (FAILED(hRes))
			return FALSE;
		m_context->RSSetState(m_rasterizerState);
		D3D11_VIEWPORT viewport;
		viewport.Width = static_cast<FLOAT>(cx);
		viewport.Height = static_cast<FLOAT>(cy);
		viewport.MinDepth = 0.0F;
		viewport.MaxDepth = 1.0F;
		viewport.TopLeftX = 0.0F;
		viewport.TopLeftY = 0.0F;
		m_context->RSSetViewports(1, &viewport);
		FLOAT fov = (FLOAT)D3DX_PI / 4.0F;
		FLOAT aspect = (FLOAT)cx / (FLOAT)cy;
		D3DXMatrixPerspectiveFovLH(&m_projectionMatrix, fov, aspect, 1000.0F, 0.1F);
		D3DXMatrixIdentity(&m_worldMatrix);
		D3DXMatrixOrthoLH(&m_orthoMatrix, (FLOAT)cx, (FLOAT)cy, 1000.0F, 0.1F);
		D3D11_DEPTH_STENCIL_DESC disableDepthStencilDesc;
		ZeroMemory(&disableDepthStencilDesc, sizeof(disableDepthStencilDesc));
		disableDepthStencilDesc.DepthEnable = FALSE;
		disableDepthStencilDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
		disableDepthStencilDesc.DepthFunc = D3D11_COMPARISON_LESS;
		disableDepthStencilDesc.StencilEnable = TRUE;
		disableDepthStencilDesc.StencilReadMask = 0xFF;
		disableDepthStencilDesc.StencilWriteMask = 0xFF;
		disableDepthStencilDesc.FrontFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
		disableDepthStencilDesc.FrontFace.StencilDepthFailOp = D3D11_STENCIL_OP_INCR;
		disableDepthStencilDesc.FrontFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
		disableDepthStencilDesc.FrontFace.StencilFunc = D3D11_COMPARISON_ALWAYS;
		disableDepthStencilDesc.BackFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
		disableDepthStencilDesc.BackFace.StencilDepthFailOp = D3D11_STENCIL_OP_DECR;
		disableDepthStencilDesc.BackFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
		disableDepthStencilDesc.BackFace.StencilFunc = D3D11_COMPARISON_ALWAYS;
		hRes = m_d3d->CreateDepthStencilState(&disableDepthStencilDesc, &m_disableDepthState);
		if (FAILED(hRes))
			return FALSE;
		return TRUE;
	}
	BOOL DX11::ResizeView(INT cx, INT cy)
	{
		if (!m_context)
			return FALSE;
		m_size.cx = cx;
		m_size.cy = cy;
		LPVOID val = NULL;
		m_context->OMSetRenderTargets(0, 0, 0);
		m_renderView.Release();
		HRESULT hRes = m_swap->ResizeBuffers(0, 0, 0, DXGI_FORMAT_UNKNOWN, 0);
		if (FAILED(hRes))
			return FALSE;
		TinyComPtr<ID3D11Texture2D> backBuffer;
		hRes = m_swap->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)&backBuffer);
		if (FAILED(hRes))
			return FALSE;
		hRes = m_d3d->CreateRenderTargetView(backBuffer, NULL, &m_renderView);
		if (FAILED(hRes))
			return FALSE;
		m_depthStencilBuffer.Release();
		D3D11_TEXTURE2D_DESC depthBufferDesc;
		ZeroMemory(&depthBufferDesc, sizeof(depthBufferDesc));
		depthBufferDesc.Width = m_size.cx;
		depthBufferDesc.Height = m_size.cy;
		depthBufferDesc.MipLevels = 1;
		depthBufferDesc.ArraySize = 1;
		depthBufferDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
		depthBufferDesc.SampleDesc.Count = 1;
		depthBufferDesc.SampleDesc.Quality = 0;
		depthBufferDesc.Usage = D3D11_USAGE_DEFAULT;
		depthBufferDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
		depthBufferDesc.CPUAccessFlags = 0;
		depthBufferDesc.MiscFlags = 0;
		hRes = m_d3d->CreateTexture2D(&depthBufferDesc, NULL, &m_depthStencilBuffer);
		if (FAILED(hRes))
			return FALSE;
		m_depthStencilView.Release();
		D3D11_DEPTH_STENCIL_VIEW_DESC depthStencilViewDesc;
		ZeroMemory(&depthStencilViewDesc, sizeof(depthStencilViewDesc));
		depthStencilViewDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
		depthStencilViewDesc.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
		depthStencilViewDesc.Texture2D.MipSlice = 0;
		hRes = m_d3d->CreateDepthStencilView(m_depthStencilBuffer, &depthStencilViewDesc, &m_depthStencilView);
		if (FAILED(hRes))
			return FALSE;
		m_context->OMSetRenderTargets(1, &m_renderView, m_depthStencilView);
		//�����ӿ�
		D3D11_VIEWPORT viewport;
		viewport.Width = static_cast<FLOAT>(m_size.cx);
		viewport.Height = static_cast<FLOAT>(m_size.cy);
		viewport.MinDepth = 0.0F;
		viewport.MaxDepth = 1.0F;
		viewport.TopLeftX = 0.0F;
		viewport.TopLeftY = 0.0F;
		m_context->RSSetViewports(1, &viewport);
		FLOAT fov = (FLOAT)D3DX_PI / 4.0F;
		FLOAT aspect = (FLOAT)m_size.cx / (FLOAT)m_size.cy;
		D3DXMatrixPerspectiveFovLH(&m_projectionMatrix, fov, aspect, 1000.0F, 0.1F);
		D3DXMatrixIdentity(&m_worldMatrix);
		D3DXMatrixOrthoLH(&m_orthoMatrix, (FLOAT)m_size.cx, (FLOAT)m_size.cy, 1000.0F, 0.1F);
		return TRUE;
	}
	void DX11::BeginScene()
	{
		ASSERT(m_context);
		FLOAT color[4] = { 0.0F, 0.0F, 0.0F, 1.0F };
		m_context->ClearRenderTargetView(m_renderView, color);
		m_context->ClearDepthStencilView(m_depthStencilView, D3D10_CLEAR_DEPTH, 1.0F, 0);
	}
	void DX11::EndScene()
	{
		ASSERT(m_swap && m_context);
		m_swap->Present(0, 0);
		m_context->Flush();
	}
	void DX11::AllowDepth(BOOL allow)
	{
		if (m_context)
		{
			m_context->OMSetDepthStencilState(allow ? m_depthStencilState : m_disableDepthState, 1);
		}
	}
	ID3D11Device* DX11::GetD3D() const
	{
		return m_d3d;
	}
	ID3D11DeviceContext* DX11::GetContext() const
	{
		return m_context;
	}
	IDXGISwapChain*	DX11::GetSwap() const
	{
		return m_swap;
	}
	HWND DX11::GetHWND() const
	{
		return m_hWND;
	}
	TinySize DX11::GetSize() const
	{
		return m_size;
	}
	D3DXMATRIX DX11::GetProjectionMatrix()
	{
		return m_projectionMatrix;
	}
	D3DXMATRIX DX11::GetWorldMatrix()
	{
		return m_worldMatrix;
	}
	D3DXMATRIX DX11::GetOrthoMatrix()
	{
		return m_orthoMatrix;
	}
}
