#pragma once
#include "../Common/TinyString.h"
#include "../Common/TinyEvent.h"
#include "../Render/TinyGraphics.h"

namespace TinyUI
{
	/// <summary>
	/// 可视化元素
	/// </summary>
	class TinyVisual
	{
	private:
		TinyVisual*		m_pParent;
		TinyLinkList<TinyVisual*> m_visuals;//UI元素链表
	};
}



