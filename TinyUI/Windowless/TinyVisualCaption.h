#pragma once
#include "TinyVisual.h"

namespace TinyUI
{
	namespace Windowless
	{
		/// <summary>
		/// ϵͳ��ť
		/// </summary>
		class TinySysButton : public TinyVisual
		{
		public:
			TinySysButton(TinyVisual* spvisParent);
			virtual ~TinySysButton();
			LPCSTR RetrieveTag() OVERRIDE;
			HRESULT OnDraw(TinyDC& dc, TinyRectangle& drawRect) OVERRIDE;
			HRESULT OnMouseMove(POINT pos) OVERRIDE;
			HRESULT OnLButtonDown(POINT pos) OVERRIDE;
			HRESULT OnLButtonUp(POINT pos) OVERRIDE;
			HRESULT OnRButtonDown(POINT pos) OVERRIDE;
			HRESULT OnRButtonUp(POINT pos) OVERRIDE;
		private:
			TinyImage	m_images[3];
		};
		/// <summary>
		/// ������
		/// </summary>
		class TinyVisualCaption : public TinyVisual
		{
		public:
			TinyVisualCaption(TinyVisual* spvisParent);
			virtual ~TinyVisualCaption();
			LPCSTR RetrieveTag() OVERRIDE;
			HRESULT OnDraw(TinyDC& dc, TinyRectangle& drawRect) OVERRIDE;
			HRESULT OnMouseMove(POINT pos) OVERRIDE;
			HRESULT OnLButtonDown(POINT pos) OVERRIDE;
			HRESULT OnLButtonUp(POINT pos) OVERRIDE;
			HRESULT OnRButtonDown(POINT pos) OVERRIDE;
			HRESULT OnRButtonUp(POINT pos) OVERRIDE;
		};
	}
}



