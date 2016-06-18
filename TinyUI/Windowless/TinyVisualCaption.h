#pragma once
#include "TinyVisual.h"

namespace TinyUI
{
	namespace Windowless
	{
		/// <summary>
		/// ϵͳ��ť
		/// </summary>
		class TinyVisualSysButton : public TinyVisual
		{
			friend class TinyVisualFactory;
			DECLARE_DYNAMIC(TinyVisualSysButton);
			DISALLOW_COPY_AND_ASSIGN(TinyVisualSysButton);
		protected:
			TinyVisualSysButton(TinyVisual* spvisParent, TinyVisualTree* vtree);
		public:
			virtual ~TinyVisualSysButton();
			TinyString RetrieveTag() const OVERRIDE;
			HRESULT OnDraw(TinyCanvas& canvas) OVERRIDE;
			HRESULT OnMouseMove(const TinyPoint& pos, DWORD dwKey) OVERRIDE;
			HRESULT OnLButtonDown(const TinyPoint& pos, DWORD dwKey) OVERRIDE;
			HRESULT OnLButtonUp(const TinyPoint& pos, DWORD dwKey) OVERRIDE;
		};
		/// <summary>
		/// �����������ؼ�HorizontalLayout
		/// </summary>
		class TinyVisualCaption : public TinyVisual
		{
			friend class TinyVisualFactory;
			DECLARE_DYNAMIC(TinyVisualCaption);
			DISALLOW_COPY_AND_ASSIGN(TinyVisualCaption);
		protected:
			TinyVisualCaption(TinyVisual* spvisParent, TinyVisualTree* vtree);
		public:
			virtual ~TinyVisualCaption();
			TinyString RetrieveTag() const OVERRIDE;
			void Resize() OVERRIDE;
			HRESULT OnDraw(TinyCanvas& canvas) OVERRIDE;
			HRESULT OnMouseMove(const TinyPoint& pos, DWORD dwKey) OVERRIDE;
			HRESULT OnLButtonDown(const TinyPoint& pos, DWORD dwKey) OVERRIDE;
			HRESULT OnLButtonUp(const TinyPoint& pos, DWORD dwKey) OVERRIDE;
		};
	}
}



