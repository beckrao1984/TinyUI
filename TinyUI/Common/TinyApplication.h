#pragma once
#include "TinyMsg.h"
#include "TinyCore.h"
#include "TinyHandleMap.h"
#include "TinyCollection.h"

namespace TinyUI
{
	class TinyHandleHWND;
	class TinyHandleHMENU;
	class TinyHandleHDC;
	class TinyHandleHBITMAP;
	class TinyHandleHFONT;
	class TinyHandleHPEN;
	class TinyHandleHBRUSH;
	class TinyHandleHPALETTE;
	class TinyHandleHRGN;
	/// <summary>
	/// TinyUI的应用实例
	/// </summary>
	class TinyApplication
	{
	private:
		INT					m_iCmdShow;
		HINSTANCE			m_hInstance;
		LPTSTR				m_hCmdLine;
		HACCEL				m_hAccTable;
		ULONG_PTR			m_token;
		WSADATA				m_wsd;
	private:
		TinyApplication();
	protected:
		~TinyApplication();
	public:
		//单例模式
		static TinyApplication* GetInstance() throw();
		//分静态成员
		HINSTANCE Handle() throw();
		BOOL AddMessageLoop(TinyMessageLoop* pMsgLoop);
		BOOL RemoveMessageLoop();
		TinyMessageLoop* GetMessageLoop(DWORD dwThreadID = ::GetCurrentThreadId());
		BOOL Initialize(HINSTANCE m_hInstance, LPTSTR m_lpCmdLine, INT m_nCmdShow, LPCTSTR lpTableName);
		BOOL Uninitialize();
	public:
		TinyHandleMap<HWND, TinyHandleHWND*>&				GetMapHWND();
		TinyHandleMap<HMENU, TinyHandleHMENU*>&				GetMapHMENU();
		TinyHandleMap<HDC, TinyHandleHDC*>&					GetMapHDC();
		TinyHandleMap<HBITMAP, TinyHandleHBITMAP*>&			GetMapHBITMAP();
		TinyHandleMap<HFONT, TinyHandleHFONT*>&				GetMapHFONT();
		TinyHandleMap<HPEN, TinyHandleHPEN*>&				GetMapHPEN();
		TinyHandleMap<HBRUSH, TinyHandleHBRUSH*>&			GetMapHBRUSH();
		TinyHandleMap<HPALETTE, TinyHandleHPALETTE*>&		GetMapHPALETTE();
		TinyHandleMap<HRGN, TinyHandleHRGN*>&				GetMapHRGN();
		TinyHandleMap<HIMAGELIST, TinyHandleHIMAGELIST*>&	GetMapHIMAGELIST();
	private:
		TinySimpleMap<DWORD, TinyMessageLoop*>			m_msgLoops;
	private:
		TinyHandleMap<HWND, TinyHandleHWND*>			m_MapHWND;
		TinyHandleMap<HMENU, TinyHandleHMENU*>			m_MapHMENU;
		TinyHandleMap<HDC, TinyHandleHDC*>				m_MapHDC;
		TinyHandleMap<HBITMAP, TinyHandleHBITMAP*>		m_MapHBITMAP;
		TinyHandleMap<HFONT, TinyHandleHFONT*>			m_MapHFONT;
		TinyHandleMap<HPEN, TinyHandleHPEN*>			m_MapHPEN;
		TinyHandleMap<HBRUSH, TinyHandleHBRUSH*>		m_MapHBRUSH;
		TinyHandleMap<HPALETTE, TinyHandleHPALETTE*>	m_MapHPALETTE;
		TinyHandleMap<HRGN, TinyHandleHRGN*>			m_MapHRGN;
		TinyHandleMap<HIMAGELIST, TinyHandleHIMAGELIST*>m_MapHIMAGELIST;
	};
	//////////////////////////////////////////////////////////////////////////
	LONG WINAPI TOP_LEVEL_EXCEPTION_FILTER(struct _EXCEPTION_POINTERS *pExp);
}


