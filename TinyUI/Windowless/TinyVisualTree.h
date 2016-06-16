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
			DISALLOW_COPY_AND_ASSIGN(TinyVisualTree);
		public:
			TinyVisualTree(TinyVisualHWND* pv);
			~TinyVisualTree();
		public:
			BOOL			Initialize();
			void			Uninitialize();
			TinyVisualHWND*	GetVisualHWND();
			TinyVisual*		GetVisual(TinyVisual* spvis, UINT cmd) const;
			TinyVisual*		SetParent(TinyVisual* spvis, TinyVisual* spvisNewParent);
			TinyVisual*		GetParent(TinyVisual* spvis) const;
			BOOL			IsChild(TinyVisual* spvisParent, TinyVisual* spvis) const;
			BOOL			IsVisible(TinyVisual* spvis) const;
			BOOL			MoveVisual(TinyVisual* spvis, INT x, INT y);
			TinyVisual*		GetVisualByPos(TinyVisual* spvis, INT x, INT y);
			TinyVisual*		GetVisualByPos(INT x, INT y);
			TinyVisual*		GetCapture() const;
			TinyVisual*		SetCapture(TinyVisual* pNew);
			TinyVisual*		GetFocus() const;
			TinyVisual*		SetFocus(TinyVisual* pNew);
			TinyRectangle	ConvertToClient(TinyVisual* spvis);
			void			Resize();//���¼����С
#ifdef _DEBUG
			void			Dump();
			void			Dump(TinyVisual* spvis, INT& deep);
#endif
		public:
			HRESULT			OnMouseMove(POINT pos);
			HRESULT			OnLButtonDown(POINT pos);
			HRESULT			OnLButtonUp(POINT pos);
			HRESULT			OnRButtonDown(POINT pos);
			HRESULT			OnRButtonUp(POINT pos);
		private:
			TinyVisual*		GetVisualByPos2(TinyVisual* spvis, INT x, INT y);
			void			LinkVisual(TinyVisual* spvis, TinyVisual* spvisInsert, TinyVisual**pspvisFirst);
			void			UnlinkVisual(TinyVisual* spvisUnlink, TinyVisual** pspvisFirst);
			TinyVisual*		GetPrevVisual(TinyVisual* spvisList, TinyVisual* spvisFind) const;
		protected:
			TinyVisualHWND*						m_pWindow;
			TinyVisual*							m_spvisWindow;//���ڵ�
			TinyVisual*							m_spvisCapture;
			TinyVisual*							m_spvisFocus;
			TinyScopedPtr<TinyVisualParse>		m_parse;
			TinyScopedPtr<TinyVisualFactory>	m_fs;
		};
	};
}



