#pragma once
#include "TinyVisualManage.h"

namespace TinyUI
{
	namespace Windowless
	{
#define PVISUAL_TOP        (TinyVisual*)0
#define PVISUAL_BOTTOM     (TinyVisual*)1	
#define CMD_FIRST        0  //第一个兄弟节点
#define CMD_LAST         1  //最后一个兄弟节点
#define CMD_NEXT         2  //下一个兄弟节点
#define CMD_PREV         3  //上一个兄弟节点
#define CMD_OWNER        4  //拥有者节点
#define CMD_CHILD        5  //第一个孩子节点
#define NOSIZE          0x0001
#define NOMOVE          0x0002
#define NOZORDER        0x0004
#define NOREDRAW        
		class TinyVisual;
		class TinyVisualHWND;
		/// <summary>
		/// 可视化树
		/// </summary>
		class TinyVisualDocument
		{
			friend class TinyVisualParse;
			friend class TinyVisualFactory;
			friend class TinyVisualHWND;
			DISALLOW_COPY_AND_ASSIGN(TinyVisualDocument);
		public:
			TinyVisualDocument(TinyVisualHWND* pv);
			~TinyVisualDocument();
			virtual BOOL	Initialize();
			virtual void	Uninitialize();
		public:
			template<typename T>
			T*		Create(INT x, INT y, INT cx, INT cy, TinyVisual* spvisParent);
			BOOL	Destory(TinyVisual* spvis);
		public:
			HWND				Handle() const;
			TinyVisualHWND*		GetVisualHWND() const;
			TinyVisualCacheDC*	GetCacheDC() const;
			TinyVisual*			GetVisual(TinyVisual* spvis, UINT cmd) const;
			TinyVisual*			SetParent(TinyVisual* spvis, TinyVisual* spvisNewParent);
			TinyVisual*			GetParent(TinyVisual* spvis) const;
			BOOL				IsChild(TinyVisual* spvisParent, TinyVisual* spvis) const;
			BOOL				IsVisible(TinyVisual* spvis) const;
			BOOL				IsEnable(TinyVisual* spvis) const;
			BOOL				IsActive(TinyVisual* spvis) const;
			TinyVisual*			GetVisualByName(const TinyString& name);
			TinyVisual*			GetVisualByPos(INT x, INT y);
			TinyVisual*			GetCapture() const;
			TinyVisual*			SetCapture(TinyVisual* spvis);
			BOOL				ReleaseCapture();
			TinyVisual*			GetFocus() const;
			TinyVisual*			SetFocus(TinyVisual* spvis);
			TinyVisual*			SetActive(TinyVisual* spvis);
			TinyVisual*			GetActive() const;
			TinyPoint			GetWindowPos(const TinyVisual* spvis);
			TinyRectangle		GetWindowRect(const TinyVisual* spvis);
			TinyPoint			GetScreenPos(const TinyVisual* spvis);
			BOOL				Invalidate(RECT* lpRect = NULL);
			BOOL				Redraw(RECT *lprcUpdate = NULL, HRGN hrgnUpdate = NULL);
		public:
			HRESULT				OnMouseLeave();
			HRESULT				OnMouseEnter();
			HRESULT				OnMouseMove(const TinyPoint& pos, DWORD dwFlags);
			HRESULT				OnMouseWheel(const TinyPoint& pos, SHORT zDelta, DWORD dwFlags);
			HRESULT				OnLButtonDown(const TinyPoint& pos, DWORD dwFlags);
			HRESULT				OnLButtonUp(const TinyPoint& pos, DWORD dwFlags);
			HRESULT				OnRButtonDown(const TinyPoint& pos, DWORD dwFlags);
			HRESULT				OnRButtonUp(const TinyPoint& pos, DWORD dwFlags);
			HRESULT				OnMButtonDown(const TinyPoint& pos, DWORD dwFlags);
			HRESULT				OnMButtonUp(const TinyPoint& pos, DWORD dwFlags);
			HRESULT				OnKeyDown(DWORD dwChar, DWORD dwRepCnt, DWORD dwFlags);
			HRESULT				OnKeyUp(DWORD dwChar, DWORD dwRepCnt, DWORD dwFlags);
			LRESULT				OnChar(DWORD dwChar, DWORD dwRepCnt, DWORD dwFlags);
			HRESULT				OnSetCursor(HWND hWND, DWORD dwHitTest, DWORD dwMessage);
			HRESULT				OnSetFocus(HWND hWND);
			HRESULT				OnKillFocus(HWND hWND);
		private:
			void				ConvertToVisualPos(TinyVisual* spvis, TinyPoint& pos);//相对于原生窗口的坐标转换到元素坐标
			TinyVisual*			GetVisualByName1(TinyVisual* spvis, const TinyString& name);
			TinyVisual*			GetVisualByName2(TinyVisual* spvis, const TinyString& name);
			TinyVisual*			GetVisualByPos1(TinyVisual* spvis, INT x, INT y);
			TinyVisual*			GetVisualByPos2(TinyVisual* spvis, INT x, INT y);
			void				LinkVisual(TinyVisual* spvis, TinyVisual* spvisInsert, TinyVisual**pspvisFirst);
			void				UnlinkVisual(TinyVisual* spvisUnlink, TinyVisual** pspvisFirst);
			TinyVisual*			GetPrevVisual(TinyVisual* spvisList, TinyVisual* spvisFind) const;
			void				Draw(TinyVisualCacheDC* ps, const RECT& rcPaint);
			void				Draw(TinyVisual* spvis, HDC hDC, const RECT& rcPaint);
		private:
			class TinyVisualFactory
			{
				friend class TinyVisual;
				friend class TinyVisualDocument;
				DISALLOW_COPY_AND_ASSIGN(TinyVisualFactory);
			private:
				TinyVisualFactory(TinyVisualDocument* vtree);
			public:
				template<typename T>
				T*		Create(INT x, INT y, INT cx, INT cy, TinyVisual* spvisParent);
				BOOL	Destory(TinyVisual* spvis);
			private:
				TinyVisualDocument* m_document;
			};
		protected:
			TinyVisual*							m_spvisWindow;//根节点
			TinyVisual*							m_spvisCapture;
			TinyVisual*							m_spvisFocus;
			TinyVisual*							m_spvisActive;
			TinyVisual*							m_spvisLastMouse;//当前鼠标所在的元素
			TinyVisualHWND*						m_pWindow;
			TinyScopedPtr<TinyVisualParse>		m_parse;
			TinyScopedPtr<TinyVisualFactory>	m_fs;
		public:
#ifdef _DEBUG
			void			Dump();
			void			Dump(TinyVisual* spvis, INT& deep);
#endif
		};
		template<typename T>
		T*	 TinyVisualDocument::Create(INT x, INT y, INT cx, INT cy, TinyVisual* spvisParent)
		{
			ASSERT(m_fs);
			//T必须要继承自TinyVisual
			COMPILE_ASSERT((std::is_convertible<T, TinyVisual>::value), T_must_convertible_to_TinyVisual);
			return m_fs->Create<T>(x, y, cx, cy, spvisParent);
		}
		template<typename T>
		T* TinyVisualDocument::TinyVisualFactory::Create(INT x, INT y, INT cx, INT cy, TinyVisual* spvisParent)
		{
			ASSERT(m_document);
			TinyVisual* spvis = new T(spvisParent, m_document);
			spvis->SetPosition(TinyPoint(x, y));
			spvis->SetSize(TinySize(cx, cy));
			m_document->SetParent(spvis, spvisParent);
			spvis->OnCreate();
			return static_cast<T*>(spvis);
		}
	};
}



