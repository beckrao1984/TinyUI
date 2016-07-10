#pragma once
#include "TinyVisualManage.h"

namespace TinyUI
{
	namespace Windowless
	{
#define PVISUAL_TOP        (TinyVisual*)0
#define PVISUAL_BOTTOM     (TinyVisual*)1	
#define CMD_FIRST        0  //��һ���ֵܽڵ�
#define CMD_LAST         1  //���һ���ֵܽڵ�
#define CMD_NEXT         2  //��һ���ֵܽڵ�
#define CMD_PREV         3  //��һ���ֵܽڵ�
#define CMD_OWNER        4  //ӵ���߽ڵ�
#define CMD_CHILD        5  //��һ�����ӽڵ�
#define NOSIZE          0x0001
#define NOMOVE          0x0002
#define NOZORDER        0x0004
#define NOREDRAW        
		class TinyVisual;
		class TinyVisualHWND;
		/// <summary>
		/// ���ӻ���
		/// </summary>
		class TinyVisualTree
		{
			friend class TinyVisualParse;
			friend class TinyVisualFactory;
			friend class TinyVisualHWND;
			DISALLOW_COPY_AND_ASSIGN(TinyVisualTree);
		public:
			TinyVisualTree(TinyVisualHWND* pv);
			~TinyVisualTree();
		public:
			BOOL			Initialize();
			void			Uninitialize();
			BOOL			RedrawVisual(const TinyVisual* spvis);
		public:
			TinyVisualHWND*	GetVisualHWND();
			TinyVisual*		GetVisual(TinyVisual* spvis, UINT cmd) const;
			TinyVisual*		SetParent(TinyVisual* spvis, TinyVisual* spvisNewParent);
			TinyVisual*		GetParent(TinyVisual* spvis) const;
			BOOL			IsChild(TinyVisual* spvisParent, TinyVisual* spvis) const;
			BOOL			IsVisible(TinyVisual* spvis) const;
			BOOL			IsEnable(TinyVisual* spvis) const;
			TinyVisual*		GetVisualByName(const TinyString& name);
			TinyVisual*		GetVisualByPos(INT x, INT y);
			TinyVisual*		GetCapture() const;
			TinyVisual*		SetCapture(TinyVisual* spvis);
			BOOL			ReleaseCapture();
			TinyVisual*		GetFocus() const;
			TinyVisual*		SetFocus(TinyVisual* spvis);
			TinyPoint		GetWindowPos(const TinyVisual* spvis);
			TinyRectangle	GetWindowRect(const TinyVisual* spvis);
			TinyPoint		GetScreenPos(const TinyVisual* spvis);
			BOOL			Invalidate(RECT* lpRect = NULL);
			BOOL			Redraw(RECT *lprcUpdate = NULL, HRGN hrgnUpdate = NULL);
		public:
			HRESULT			OnMouseLeave();
			HRESULT			OnMouseEnter();
			HRESULT			OnMouseMove(const TinyPoint& pos, DWORD dwFlags);
			HRESULT			OnLButtonDown(const TinyPoint& pos, DWORD dwFlags);
			HRESULT			OnLButtonUp(const TinyPoint& pos, DWORD dwFlags);
			HRESULT			OnRButtonDown(const TinyPoint& pos, DWORD dwFlags);
			HRESULT			OnRButtonUp(const TinyPoint& pos, DWORD dwFlags);
			HRESULT			OnMButtonDown(const TinyPoint& pos, DWORD dwFlags);
			HRESULT			OnMButtonUp(const TinyPoint& pos, DWORD dwFlags);
		private:
			void			ConvertToVisualPos(TinyVisual* spvis, TinyPoint& pos);//�����ԭ�����ڵ�����ת����Ԫ������
			TinyVisual*		GetVisualByName1(TinyVisual* spvis, const TinyString& name);
			TinyVisual*		GetVisualByName2(TinyVisual* spvis, const TinyString& name);
			TinyVisual*		GetVisualByPos1(TinyVisual* spvis, INT x, INT y);
			TinyVisual*		GetVisualByPos2(TinyVisual* spvis, INT x, INT y);
			void			LinkVisual(TinyVisual* spvis, TinyVisual* spvisInsert, TinyVisual**pspvisFirst);
			void			UnlinkVisual(TinyVisual* spvisUnlink, TinyVisual** pspvisFirst);
			TinyVisual*		GetPrevVisual(TinyVisual* spvisList, TinyVisual* spvisFind) const;
			void			Draw(TinyVisualCacheDC* ps, const RECT& rcPaint);
			void			Draw(TinyVisual* spvis, HDC hDC, const RECT& rcPaint);
		protected:
			TinyVisual*							m_spvisWindow;//���ڵ�
			TinyVisual*							m_spvisCapture;
			TinyVisual*							m_spvisFocus;
			TinyVisual*							m_spvisLastMouse;//��ǰ������ڵ�Ԫ��
			TinyVisualHWND*						m_pWindow;
			TinyScopedPtr<TinyVisualParse>		m_parse;
			TinyScopedPtr<TinyVisualFactory>	m_fs;
		public:
#ifdef _DEBUG
			void			Dump();
			void			Dump(TinyVisual* spvis, INT& deep);
#endif
		};
	};
}



