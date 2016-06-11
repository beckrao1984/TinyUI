#pragma once
#include "TinyVisualCommon.h"

namespace TinyUI
{
	namespace Windowless
	{
		class TinyVisual;
		/// <summary>
		/// ������ 
		/// </summary>
		class TinyVisualLayout
		{
		public:
			TinyVisualLayout(TinyVisual* spvis);
		public:
			virtual BOOL Add(TinyVisual* spvis);
			virtual BOOL Remove(TinyVisual* spvis);
			virtual void RemoveAll();
			virtual void Layout() = 0;
		private:
			TinyVisual* m_spvis;
			TinyArray<TinyVisual*> m_items;
		};
		/// <summary>
		/// ˮƽ����
		/// </summary>
		class TinyHBoxLayout : public TinyVisualLayout
		{
		public:
			TinyHBoxLayout(TinyVisual* spvis);
		public:
			void Layout() OVERRIDE;
		};
		/// <summary>
		/// ��ֱ����
		/// </summary>
		class TinyVBoxLayout : public TinyVisualLayout
		{
		public:
			TinyVBoxLayout(TinyVisual* spvis);
		public:
			void Layout() OVERRIDE;
		};
	}
}



