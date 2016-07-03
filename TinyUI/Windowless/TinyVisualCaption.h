#pragma once
#include "TinyVisualButton.h"

namespace TinyUI
{
	namespace Windowless
	{
		/// <summary>
		/// ϵͳ��ť
		/// </summary>
		class TinyVisualSysButton : public TinyVisualButton
		{
			friend class TinyVisualFactory;
			DECLARE_DYNAMIC(TinyVisualSysButton);
			DISALLOW_COPY_AND_ASSIGN(TinyVisualSysButton);
		protected:
			TinyVisualSysButton(TinyVisual* spvisParent, TinyVisualTree* vtree);
		public:
			virtual ~TinyVisualSysButton();
			TinyString RetrieveTag() const OVERRIDE;
		};
		/// <summary>
		/// �����������ؼ�
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
		};
	}
}



