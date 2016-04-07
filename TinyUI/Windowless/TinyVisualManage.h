#pragma once
#include "TinyVisual.h"
#include "../IO/TinyIO.h"
#include "../XML/TinyXMLParse.h"

namespace TinyUI
{
	namespace Windowless
	{
		class TinyVisualTag
		{
		public:
			const static CHAR* WINDOW;
			const static CHAR* CAPTION;
			const static CHAR* SYSBUTTON;
			const static CHAR* BUTTON;
			const static CHAR* COMBOBOX;
			const static CHAR* TAB;
			const static CHAR* LIST;
			const static CHAR* TREEVIEW;
			const static CHAR* TOOLBAR;
		};
		/// <summary>
		/// ���ӻ�Ԫ�ع���
		/// </summary>
		class TinyVisualParse : public TinyObject
		{
			DECLARE_DYNAMIC(TinyVisualParse)
		public:
			TinyVisualParse();
			~TinyVisualParse();
			BOOL LoadFile(LPCSTR pzFile);
			BOOL BuildVisualTree(TinyVisualTree* ps);
		private:
			TiXmlDocument	m_doc;
		};
	};
}



