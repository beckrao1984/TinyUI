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
		public:
			/// <summary>
			/// ԭ������
			/// </summary>
			TinyVisualHWND*	GetVisualHWND();
			/// <summary>
			/// ����ֵܺ���Ԫ��
			/// </summary>
			TinyVisual*		GetVisual(TinyVisual* spvis, UINT cmd) const;
			/// <summary>
			/// ���ø�Ԫ��
			/// </summary>
			TinyVisual*		SetParent(TinyVisual* spvis, TinyVisual* spvisNewParent);
			/// <summary>
			/// ��ø�Ԫ��
			/// </summary>
			TinyVisual*		GetParent(TinyVisual* spvis) const;
			/// <summary>
			/// �Ƿ���Ԫ��
			/// </summary>
			BOOL			IsChild(TinyVisual* spvisParent, TinyVisual* spvis) const;
			/// <summary>
			/// �Ƿ�Visible
			/// </summary>
			BOOL			IsVisible(TinyVisual* spvis) const;
			/// <summary>
			/// �Ƿ�Enable
			/// </summary>
			BOOL			IsEnable(TinyVisual* spvis) const;
			/// <summary>
			/// x,y�ֱ�����Ļ����
			/// </summary>
			TinyVisual*		GetVisualByPos(INT x, INT y);
			/// <summary>
			/// ��ò���Ԫ��
			/// </summary>
			TinyVisual*		GetCapture() const;
			/// <summary>
			/// ���ò���Ԫ��
			/// </summary>
			TinyVisual*		SetCapture(TinyVisual* spvis);
			/// <summary>
			/// ��ý���Ԫ��
			/// </summary>
			TinyVisual*		GetFocus() const;
			/// <summary>
			/// ���ý���Ԫ��
			/// </summary>
			TinyVisual*		SetFocus(TinyVisual* spvis);
			/// <summary>
			/// ���Ԫ������ڴ��ڵ�����
			/// </summary>
			TinyPoint		GetWindowPos(const TinyVisual* spvis);
			/// <summary>
			/// ���Ԫ���������Ļ������
			/// </summary>
			TinyPoint		GetScreenPos(const TinyVisual* spvis);
#ifdef _DEBUG
			void			Dump();
			void			Dump(TinyVisual* spvis, INT& deep);
#endif
		public:
			HRESULT			OnMouseMove(const TinyPoint& pos, DWORD dwKey);
			HRESULT			OnLButtonDown(const TinyPoint& pos, DWORD dwKey);
			HRESULT			OnLButtonUp(const TinyPoint& pos, DWORD dwKey);
			HRESULT			OnRButtonDown(const TinyPoint& pos, DWORD dwKey);
			HRESULT			OnRButtonUp(const TinyPoint& pos, DWORD dwKey);
		private:
			void			ConvertToVisualPos(TinyVisual* spvis, TinyPoint& pos);//�����ԭ�����ڵ�����ת����Ԫ������
			TinyVisual*		GetVisualByPos1(TinyVisual* spvis, INT x, INT y);
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



