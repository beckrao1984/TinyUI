pragma once
#include "../Common/TinyHook.h"

namespace TinyUI
{
	/// <summary>
	/// Ƥ��API Hook
	/// </summary>
	class TinySkinHook
	{
	public:
		TinySkinHook();
		virtual ~TinySkinHook();
		static TinySkinHook* GetInstance();
	public:
		TinyScopedReferencePtr<TinyIATHook> m_hook;
		TinyCriticalSection m_cs;
	};
}
