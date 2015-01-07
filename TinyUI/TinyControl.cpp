#include "stdafx.h"
#include "TinyControl.h"

namespace TinyUI
{
	TinyControl::TinyControl()
	{
	}
	TinyControl::~TinyControl()
	{
	}
	LRESULT CALLBACK TinyControl::CbtFilterHook(INT code, WPARAM wParam, LPARAM lParam)
	{
		if (code != HCBT_CREATEWND)
			return CallNextHookEx(m_pHook, code, wParam, lParam);
		ASSERT(lParam != NULL);
		LPCREATESTRUCT lpcs = ((LPCBT_CREATEWND)lParam)->lpcs;
		ASSERT(lpcs != NULL);
		TinyControl *_this = NULL;
		_this = (TinyControl*)(lpcs->lpCreateParams);
		if (_this != NULL)
		{
			_this->SubclassWindow((HWND)wParam);
		}
		return CallNextHookEx(m_pHook, code, wParam, lParam);
	};
	BOOL TinyControl::Create(HWND hParent, int x, int y, int cx, int cy, BOOL bHook)
	{
		BOOL bRes = FALSE;
		if (bHook)
		{
			m_pHook = SetWindowsHookEx(WH_CBT, CbtFilterHook, TinyApplication::Instance()->Handle(), GetCurrentThreadId());
			ASSERT(m_pHook != NULL);
			bRes = TinyWindow::Create(hParent, x, y, cx, cy);
			::SendMessage(m_hWND, WM_SETFONT, (WPARAM)(HFONT)GetStockObject(DEFAULT_GUI_FONT), MAKELPARAM(TRUE, 0));
			UnhookWindowsHookEx(m_pHook);
			m_pHook = NULL;
			return FALSE;
		}
		bRes = TinyWindow::Create(hParent, x, y, cx, cy);
		return FALSE;
	};
	LPCSTR TinyControl::RetrieveClassName()
	{
		return TEXT("TinyControl");
	}
	HICON TinyControl::RetrieveIcon()
	{
		return NULL;
	}
	LPCTSTR TinyControl::RetrieveTitle()
	{
		return TEXT("TinyControl");
	}
	DWORD TinyControl::RetrieveStyle()
	{
		return (WS_VISIBLE | WS_CHILD);
	}
	DWORD TinyControl::RetrieveExStyle()
	{
		return (WS_EX_LEFT | WS_EX_LTRREADING | WS_EX_RIGHTSCROLLBAR);
	}
	LRESULT TinyControl::OnCreate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		bHandled = FALSE;
		return FALSE;
	}
	LRESULT TinyControl::OnClose(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		bHandled = FALSE;
		return FALSE;
	}
	LRESULT TinyControl::OnDestory(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		bHandled = FALSE;
		return FALSE;
	}
	LRESULT TinyControl::OnSetCursor(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		bHandled = FALSE;
		return FALSE;
	}
	LRESULT TinyControl::OnCommand(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		bHandled = FALSE;
		if (lParam != NULL)
		{
			return ::SendMessage((HWND)lParam, (WM_COMMAND + WM_REFLECT), wParam, lParam);
		}
		else
		{
			bHandled = TRUE;
			//�˵�Click�¼�
			/*INT wID = LOWORD(wParam);
			SysMenu* menuPtr = (SysMenu*)__Module.GetMapMENUID().FromKey(wID);
			if (menuPtr != NULL)
			{
			menuPtr->OnClick(menuPtr, wID);
			}*/
			return TRUE;
		}
		return FALSE;
	}
	LRESULT TinyControl::OnCommandReflect(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		bHandled = FALSE;
		return FALSE;
	}
	LRESULT TinyControl::OnNotify(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		bHandled = FALSE;
		LPNMHDR p = (LPNMHDR)lParam;
		return ::SendMessage(p->hwndFrom, (uMsg + WM_REFLECT), wParam, lParam);
	}
	LRESULT TinyControl::OnNotifyReflect(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		bHandled = FALSE;
		return FALSE;
	}
	LRESULT TinyControl::OnDeleteItemReflect(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		bHandled = FALSE;
		return FALSE;
	}
	LRESULT TinyControl::OnDrawItemReflect(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		bHandled = FALSE;
		return FALSE;
	}
	LRESULT TinyControl::OnMeasureItem(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		bHandled = FALSE;
		return FALSE;
	}
	LRESULT TinyControl::OnMeasureItemReflect(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		bHandled = FALSE;
		return FALSE;
	}
}
