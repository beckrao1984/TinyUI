#pragma once
#include "../Common/TinyString.h"
#include "../Common/TinyEvent.h"
#include "../Render/TinyCanvas.h"
#include "../XML//tinyxml.h"
#include "TinyVisualLayout.h"
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
			void				SetText(LPCSTR pzText);
			TinyString			GetText() const;
			void				SetName(LPCSTR pzName);
			TinyString			GetName() const;
			void				SetToolTip(LPCSTR pzTitle);
			TinyString			GetToolTip() const;
			TinyPoint			GetPosition() const;
			void				SetPosition(const TinyPoint& pos);
			TinySize			GetSize() const;
			void				SetSize(const TinySize& size);
			void				SetMaximumSize(const TinySize& size);
			void				SetMinimumSize(const TinySize& size);
			TinySize			GetMaximumSize() const;
			TinySize			GetMinimumSize() const;
			BOOL				IsVisible() const;
			BOOL				IsEnable() const;
			void				SetVisible(BOOL visible);
			void				SetEnable(BOOL enable);
			void				SetClip(HRGN hrgnClip);
			BOOL				SetStyleImage(StyleImage type, LPCSTR pzFile);
			BOOL				SetStyleImage(StyleImage type, BYTE*	ps, DWORD dwSize);
		public:
			virtual void		Resize();
			virtual void		OnSizeChange(const TinySize&, const TinySize&);
			virtual void		OnPosChange(const TinyPoint&, const TinyPoint&);
		public:
			virtual ~TinyVisual();
			virtual TinyString	RetrieveTag() const = 0;
			virtual HRESULT		OnDraw(TinyCanvas& canvas) = 0;
			virtual HRESULT		OnMouseMove(const TinyPoint& pos, DWORD dwKey);
			virtual HRESULT		OnLButtonDown(const TinyPoint& pos, DWORD dwKey);
			virtual HRESULT		OnLButtonUp(const TinyPoint& pos, DWORD dwKey);
			virtual HRESULT		OnRButtonDown(const TinyPoint& pos, DWORD dwKey);
			virtual HRESULT		OnRButtonUp(const TinyPoint& pos, DWORD dwKey);
			virtual HRESULT		OnMButtonDown(const TinyPoint& pos, DWORD dwKey);
			virtual HRESULT		OnMButtonUp(const TinyPoint& pos, DWORD dwKey);
		protected:

			TinyImage			m_images[3];
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



