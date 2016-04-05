#pragma once
#include "TinyVisualElement.h"

namespace TinyUI
{
	namespace Windowless
	{
		/// <summary>
		/// ϵͳ��ť-���,��С,��ԭ,�ر�
		/// </summary>
		class TinySysButton : public TinyVisualElement
		{
		public:
			LPCSTR RetrieveTag() OVERRIDE;
			HRESULT OnDraw(TinyDC& dc, TinyRectangle& drawRect) OVERRIDE;
			HRESULT OnMouseMove(POINT pos) OVERRIDE;
			HRESULT OnLButtonDown(POINT pos) OVERRIDE;
			HRESULT OnLButtonUp(POINT pos) OVERRIDE;
			HRESULT OnRButtonDown(POINT pos) OVERRIDE;
			HRESULT OnRButtonUp(POINT pos) OVERRIDE;
		};
		/// <summary>
		/// ������
		/// </summary>
		class TinyVisualCaption : public TinyVisualElement
		{
		public:
			LPCSTR RetrieveTag() OVERRIDE;
		};
	}
}



