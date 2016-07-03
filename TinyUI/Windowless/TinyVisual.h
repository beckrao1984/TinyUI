#pragma once
#include "../Common/TinyString.h"
#include "../Common/TinyEvent.h"
#include "../Render/TinyCanvas.h"
#include "../XML//tinyxml.h"
#include "TinyVisualLayout.h"
#include "TinyVisualEvent.h"
#include "TinyUtility.h"

namespace TinyUI
{
	namespace Windowless
	{
		enum StyleImage
		{
			NORMAL = 0,
			HIGHLIGHT = 1,
			DOWN = 2
		};
		/// <summary>
		/// ���ӻ�Ԫ�ػ���
		/// </summary>
		class TinyVisual : public TinyObject
		{
			friend class TinyVisualTree;
			friend class TinyVisualParse;
			friend class TinyVisualFactory;
			DECLARE_DYNAMIC(TinyVisual);
			DISALLOW_COPY_AND_ASSIGN(TinyVisual);
		protected:
			TinyVisual(TinyVisual* spvisParent, TinyVisualTree* vtree);
		public:
			TinyString			GetText() const;
			TinyString			GetName() const;
			TinyString			GetToolTip() const;
			TinyPoint			GetPosition() const;
			TinySize			GetSize() const;
			TinySize			GetMaximumSize() const;
			TinySize			GetMinimumSize() const;
			TinyRectangle		GetRectangle() const;
			HRGN				GetClip() const;
			BOOL				IsVisible() const;
			BOOL				IsEnable() const;
			void				SetName(LPCSTR pzName);
			void				SetToolTip(LPCSTR pzTitle);
			void				SetText(LPCSTR pzText);
			void				SetPosition(const TinyPoint& pos);
			void				SetSize(const TinySize& size);
			void				SetMaximumSize(const TinySize& size);
			void				SetMinimumSize(const TinySize& size);
			void				SetClip(HRGN hrgnClip);
			void				SetVisible(BOOL visible);
			void				SetEnable(BOOL enable);
			BOOL				SetStyleImage(StyleImage type, LPCSTR pzFile);
			BOOL				SetStyleImage(StyleImage type, BYTE*	ps, DWORD dwSize);
		public:
			TinyVisualTree*		GetVisualTree();
			virtual void		Resize();
			virtual void		OnSizeChange(const TinySize&, const TinySize&);
			virtual void		OnPosChange(const TinyPoint&, const TinyPoint&);
		public:
			virtual ~TinyVisual();
			virtual TinyString	RetrieveTag() const = 0;
		protected:
			virtual BOOL		OnDraw(HDC hDC);
			virtual HRESULT		OnMouseMove(TinyPoint pos, DWORD dwFlags);
			virtual HRESULT		OnMouseEnter();
			virtual HRESULT		OnMouseLeave();
			virtual HRESULT		OnLButtonDown(TinyPoint pos, DWORD dwFlags);
			virtual HRESULT		OnLButtonUp(TinyPoint pos, DWORD dwFlags);
			virtual HRESULT		OnLButtonDBClick(TinyPoint pos, DWORD dwFlags);
			virtual HRESULT		OnRButtonDown(TinyPoint pos, DWORD dwFlags);
			virtual HRESULT		OnRButtonUp(TinyPoint pos, DWORD dwFlags);
			virtual HRESULT		OnRButtonDBClick(TinyPoint pos, DWORD dwFlags);
			virtual HRESULT		OnMButtonDown(TinyPoint pos, DWORD dwFlags);
			virtual HRESULT		OnMButtonUp(TinyPoint pos, DWORD dwFlags);
			virtual HRESULT		OnMButtonDBClick(TinyPoint pos, DWORD dwFlags);
			virtual HRESULT		OnKeyDown(DWORD dwChar, DWORD dwRepCnt, DWORD dwFlags);
			virtual HRESULT		OnKeyUp(DWORD dwChar, DWORD dwRepCnt, DWORD dwFlags);
		public:
			Event<void(EventArgs&)>			EVENT_Click;
			Event<void(MouseEventArgs&)>	EVENT_MouseMove;
			Event<void(MouseEventArgs&)>	EVENT_MouseDown;
			Event<void(MouseEventArgs&)>	EVENT_MouseUp;
			Event<void(MouseEventArgs&)>	EVENT_MouseClick;
			Event<void(MouseEventArgs&)>	EVENT_MouseDoubleClick;
			Event<void(KeyEventArgs&)>		EVENT_KeyDown;
			Event<void(KeyEventArgs&)>		EVENT_KeyUp;
		protected:
			TinyImage			m_images[3];//��̬ͼƬ
			TinyVisual*			m_spvisNext;//ͬ����һ���ֵܽڵ�
			TinyVisual*			m_spvisParent;//���ڵ�
			TinyVisual*			m_spvisChild;//��һ�����ӽڵ�
			TinyVisual*			m_spvisOwner;//����Popup����ʹ��
			TinyVisualTree*		m_vtree;
			TinyString			m_strName;
			TinyString			m_strText;
			TinyString			m_strToolTip;
			TinyRectangle		m_windowRect;//����ڸ�Ԫ������
			TinySize			m_maximumSize;//Ԫ�ص�������ش�С
			TinySize			m_minimumSize;//Ԫ�ص���С���ش�С
			HRGN				m_hrgnClip;
			BOOL				m_visible;
			BOOL				m_enable;
		};
	}
}



