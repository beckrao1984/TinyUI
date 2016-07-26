#pragma once
#include <DXGI.h>
#include <d3d.h>
#include <d3d10_1.h>
#include "Common/TinyCommon.h"
#include "Common/TinyCore.h"
using namespace TinyUI;

#define TEXTUREMEMORY			TEXT("Local\\TextureMemory")
#define BEGIN_CAPTURE_EVENT		TEXT("D3DBeginCapture")
#define END_CAPTURE_EVENT		TEXT("D3DEndCapture")

namespace D3D
{
	class D3DSystem
	{
	public:
		D3DSystem();
		~D3DSystem();
		BOOL Initialize(HWND hWND, INT cx, INT cy);//D3D��׼���ĳ�ʼ������
		void SetViewport(FLOAT x, FLOAT y, FLOAT cx, FLOAT cy);
		void SetScissorRect(const D3D10_RECT *pRects);
	private:
		DXGI_SWAP_CHAIN_DESC				m_dsc;
		TinyComPtr<IDXGISwapChain>			m_swap;
		TinyComPtr<ID3D10Device1>			m_d3d;
		TinyComPtr<ID3D10DepthStencilState> m_depthState;
		TinyComPtr<ID3D10RasterizerState>	m_rasterizerState;
		TinyComPtr<ID3D10RasterizerState>   m_scissorState;
		TinyComPtr<ID3D10RenderTargetView>  m_renderView;
		TinyComPtr<ID3D10BlendState>        m_blendState;
	};
}

