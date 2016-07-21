#pragma once
#include "TinyD3D.h"

namespace TinyUI
{
	namespace D3D
	{
		inline FARPROC GetVTable(LPVOID ptr, UINT funcOffset)
		{
			ULONG *vtable = *(ULONG**)ptr;
			return (FARPROC)(*(vtable + funcOffset));
		}

		inline void SetVTable(LPVOID ptr, UINT funcOffset, FARPROC funcAddress)
		{
			ULONG *vtable = *(ULONG**)ptr;
			DWORD oldProtect;
			if (!VirtualProtect((LPVOID)(vtable + funcOffset), sizeof(ULONG), PAGE_EXECUTE_READWRITE, &oldProtect))
				return;
			*(vtable + funcOffset) = (ULONG)funcAddress;
		}
		/// <summary>
		/// D3D APIע�� Ŀǰ��ʵ��x86
		/// </summary>
		class D3DAPIHook
		{
		public:
			D3DAPIHook();
			~D3DAPIHook();
			BOOL	Initialize(FARPROC pfnOrig, FARPROC pfnHook);
			BOOL	BeginHook();
			BOOL	EndHook();
		protected:
			FARPROC	m_pfnOrig;
			FARPROC	m_pfnHook;
			DWORD	m_dwOrigProtect;
			BYTE	m_data[5];//ԭʼ�������ڻ�ԭ�ֳ�(x64��Ҫ14���ֽ�)
			BOOL	m_bHook;
		};
		/// <summary>
		/// ע�붯̬��
		/// </summary>
		BOOL WINAPI InjectLibrary(HANDLE hProcess, const WCHAR *pszDLL, DWORD dwSize);
	}
}



