#pragma once
#include "../Common/TinyString.h"
#include "../Common/TinyEvent.h"
#include "../Render/TinyGDI.h"
#include "TinyUtility.h"

namespace TinyUI
{
	namespace Windowless
	{
		/// <summary>
		/// ���ӻ�Ԫ�ػ���
		/// </summary>
		class TinyVisual : public TinyObject
		{
			DECLARE_DYNAMIC(TinyVisual)
		public:
			TinyVisual();
			virtual ~TinyVisual();
			void			SetMaximumSize(const TinySize& size);
			void			SetMinimumSize(const TinySize& size);
			TinySize		GetMaximumSize() const;
			TinySize		GetMinimumSize() const;
			virtual HRESULT	OnDraw(TinyDC& dc, TinyRectangle& drawRect);
		private:
			TinyVisual*		m_spvisPrev;//ͬ����һ���ֵܽڵ�
			TinyVisual*		m_spvisNext;//ͬ����һ���ֵܽڵ�
			TinyVisual*		m_spvisParent;//���ڵ�
			TinyVisual*		m_spvisChild;//���ӽڵ�
			TinyVisual*		m_spvisOwner;//����Popup����ʹ��
			TinyPoint		m_pos;//Ԫ����Դ��ڵ�����
			TinySize		m_size;//Ԫ�����ش�С
			TinySize		m_maximumSize;//Ԫ�ص�������ش�С
			TinySize		m_minimumSize;//Ԫ�ص���С���ش�С
		};
	}
}



