#pragma once
#include "Common/TinyCommon.h"
#include "Common/TinyCore.h"
#include "IO/TinySharedMemory.h"
#include "D3DUtility.h"
#include "D3D10Texture.h"
#include "D3D10VertexShader.h"
#include "D3D10PixelShader.h"
#include "D3D10VertexBuffer.h"

using namespace TinyUI;

enum GSBlendType { GS_BLEND_ZERO, GS_BLEND_ONE, GS_BLEND_SRCCOLOR, GS_BLEND_INVSRCCOLOR, GS_BLEND_SRCALPHA, GS_BLEND_INVSRCALPHA, GS_BLEND_DSTCOLOR, GS_BLEND_INVDSTCOLOR, GS_BLEND_DSTALPHA, GS_BLEND_INVDSTALPHA, GS_BLEND_FACTOR, GS_BLEND_INVFACTOR };

namespace D3D
{
	class CD3D10Texture;
	class CD3D10VertexShader;
	class CD3D10PixelShader;
	class CD3D10VertexBuffer;

	class CD3D10Device
	{
	public:
		CD3D10Device();
		~CD3D10Device();
		BOOL Initialize(HWND hWND, INT cx, INT cy);//D3D标准化的初始化过程
		void SetViewport(FLOAT x, FLOAT y, FLOAT cx, FLOAT cy);
		void SetScissorRect(const D3D10_RECT *pRects);
		BOOL ResizeView();
		ID3D10Device1*	GetD3D() const;
		void CopyTexture(CD3D10Texture *texDest, CD3D10Texture *texSrc);
		void LoadVertexBuffer(CD3D10VertexBuffer* vb);
		void LoadVertexShader(CD3D10VertexShader* pVertexShader);
		void LoadPixelShader(CD3D10PixelShader* pPixelShader);
		void LoadTexture(CD3D10Texture *texture, UINT idTexture = 0);
		CD3D10PixelShader* GetCurrentPixelShader() const;
		CD3D10VertexShader* GetCurrentVertexShader() const;
		void SetRenderTarget(CD3D10Texture *texture);
		BOOL DrawSprite(CD3D10Texture *texture, DWORD color, float x, float y, float x2, float y2, float u, float v, float u2, float v2);
		BOOL DrawSpriteRotate(CD3D10Texture *texture, DWORD color, float x, float y, float x2, float y2, float degrees, float u, float v, float u2, float v2, float texDegrees);
	private:
		IO::TinySharedMemory						m_sharedCapture;
		DXGI_SWAP_CHAIN_DESC						m_dscd;
		TinyUI::TinyComPtr<IDXGISwapChain>			m_swap;
		TinyUI::TinyComPtr<ID3D10Device1>			m_d3d;
		TinyUI::TinyComPtr<ID3D10DepthStencilState> m_depthState;
		TinyUI::TinyComPtr<ID3D10RasterizerState>	m_rasterizerState;
		TinyUI::TinyComPtr<ID3D10RasterizerState>   m_scissorState;
		TinyUI::TinyComPtr<ID3D10RenderTargetView>  m_renderView;
		TinyUI::TinyComPtr<ID3D10BlendState>        m_blendState;
		CD3D10VertexBuffer							m_spriteVertexBuffer;
		CD3D10Texture*								m_pCurrentTexture;
		CD3D10VertexShader*							m_pCurrentVertexShader;
		CD3D10PixelShader*							m_pCurrentPixelShader;
		CD3D10VertexBuffer*							m_pCurrentVertexBuffer;
		CD3D10VertexShader							m_mainVertexShader;
		CD3D10PixelShader							m_mainPixelShader;
		CD3D10Texture*								m_currentTextures[8];
		FLOAT										m_currentCroppings[4];
	};
}

