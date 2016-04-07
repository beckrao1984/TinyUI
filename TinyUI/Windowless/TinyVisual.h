#pragma once
#include "../Common/TinyString.h"
#include "../Common/TinyEvent.h"
#include "../Render/TinyGDI.h"
#include "TinyUtility.h"
#include "TinyVisualTree.h"
#include "../XML//tinyxml.h"

namespace TinyUI
{
	namespace Windowless
	{
		/// <summary>
		/// ���ӻ�Ԫ�ػ���
		/// </summary>
		class TinyVisual : public TinyObject
		{
			friend class TinyVisualTree;
			friend class TinyVisualParse;
			DECLARE_DYNAMIC(TinyVisual)
		public:
			TinyVisual();
			virtual ~TinyVisual();
			void			SetText(LPCSTR pzText);
			TinyString		GetText() const;
			void			SetName(LPCSTR pzName);
			TinyString		GetName() const;
			void			SetToolTip(LPCSTR pzTitle);
			TinyString		GetToolTip() const;
			void			SetMaximumSize(const TinySize& size);
			void			SetMinimumSize(const TinySize& size);
			TinySize		GetMaximumSize() const;
			TinySize		GetMinimumSize() const;
			BOOL			IsVisible() const;
			BOOL			IsEnable() const;
			void			SetVisible(BOOL visible);
			void			SetEnable(BOOL enable);
			BOOL			GetClientRect(LPRECT ps);
			BOOL			GetWindowRect(LPRECT ps);
		public:
			virtual BOOL	ParseVisual(TiXmlElement* ps) = 0;
			virtual LPCSTR	RetrieveTag() = 0;
			virtual HRESULT	OnDraw(TinyDC& dc, TinyRectangle& drawRect) = 0;
			virtual HRESULT OnMouseMove(POINT pos) = 0;
			virtual HRESULT OnLButtonDown(POINT pos) = 0;
			virtual HRESULT OnLButtonUp(POINT pos) = 0;
			virtual HRESULT OnRButtonDown(POINT pos) = 0;
			virtual HRESULT OnRButtonUp(POINT pos) = 0;
			//Ԫ������
			static const CHAR* NAME;
			static const CHAR* TEXT;
			static const CHAR* TOOLTIP;
			static const CHAR* MAXSIZE;
			static const CHAR* MINSIZE;
			static const CHAR* VISIBLE;
			static const CHAR* ENABLE;
		protected:
			TinyVisual*		m_spvisNext;//ͬ����һ���ֵܽڵ�
			TinyVisual*		m_spvisParent;//���ڵ�
			TinyVisual*		m_spvisChild;//��һ�����ӽڵ�
			TinyVisual*		m_spvisOwner;//����Popup����ʹ��
			TinyRectangle   m_windowRect;//��Ļ����(��Ļ����)
			TinyRectangle	m_clientRect;//�ͻ�����(��Ļ����)
			TinySize		m_maximumSize;//Ԫ�ص�������ش�С
			TinySize		m_minimumSize;//Ԫ�ص���С���ش�С
			TinyString		m_strName;
			TinyString		m_strText;
			TinyString		m_strToolTip;
			HRGN			m_hrgnClip;
			BOOL			m_visible;
			BOOL			m_enable;
		};
	}
}



