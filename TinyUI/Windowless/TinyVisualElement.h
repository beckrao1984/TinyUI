#pragma once
#include "TinyVisual.h"

namespace TinyUI
{
	namespace Windowless
	{
		/// <summary>
		/// ���ӻ�Ԫ�ض����һЩ���Ժͷ���
		/// </summary>
		class TinyVisualElement : public TinyVisual
		{
		public:
			 BOOL ParseVisual(LPCSTR pzText) OVERRIDE;
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



