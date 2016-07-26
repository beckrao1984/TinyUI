#include "stdafx.h"
#include "MainFrame.h"


CMainFrame::CMainFrame()
{

}

CMainFrame::~CMainFrame()
{
}

LRESULT CMainFrame::OnClose(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	bHandled = FALSE;
	PostQuitMessage(0);//�˳�Ӧ�ó���
	return FALSE;
}

BOOL CMainFrame::Create(HWND hParent, INT x, INT y, INT cx, INT cy)
{
	return TinyControl::Create(hParent, x, y, cx, cy, FALSE);
}
DWORD CMainFrame::RetrieveStyle()
{
	return (WS_VISIBLE | WS_CLIPSIBLINGS | WS_CLIPCHILDREN | WS_OVERLAPPEDWINDOW | WS_CAPTION);
}

DWORD CMainFrame::RetrieveExStyle()
{
	return (WS_EX_LEFT | WS_EX_RIGHTSCROLLBAR);
}

LPCSTR CMainFrame::RetrieveClassName()
{
	return TEXT("FramwUI");
}

LPCSTR CMainFrame::RetrieveTitle()
{
	return TEXT("FramwUI");
}

HICON CMainFrame::RetrieveIcon()
{
	return NULL;
}

LRESULT CMainFrame::OnCreate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	bHandled = FALSE;
	m_inject.Create(m_hWND, 10, 10, 100, 25);
	m_inject.SetText("ע�뵽War3");
	m_onInjectClick.Reset(new Delegate<void(void*, INT)>(this, &CMainFrame::OnInjectLibrary));
	m_inject.Click += m_onInjectClick;
	m_lblState.Create(m_hWND, 130, 16, 100, 25);
	m_lblState.SetText("״̬");
	m_txtLog.Create(m_hWND, 10, 40, 300, 300);
	m_txtLog.SetReadOnly(TRUE);
	memset(&m_cf, 0, sizeof(m_cf));
	m_cf.dwMask = CFM_COLOR | CFM_FACE | CFM_SIZE | CFM_EFFECTS;
	m_cf.dwEffects |= CFE_BOLD;
	m_cf.sSpacing = 5;
	m_cf.cbSize = sizeof(CHARFORMAT2);
	m_cf.crTextColor = RGB(0, 114, 193);
	m_cf.yHeight = 180;
	strcpy(m_cf.szFaceName, _T("΢���ź�"));
	return TRUE;
}

LRESULT CMainFrame::OnDestory(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	bHandled = FALSE;
	m_inject.Click -= m_onInjectClick;
	return FALSE;
}

LRESULT CMainFrame::OnPaint(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	bHandled = FALSE;
	return FALSE;
}

LRESULT CMainFrame::OnErasebkgnd(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	bHandled = FALSE;
	return FALSE;
}

LRESULT CMainFrame::OnSize(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	bHandled = FALSE;
	m_size.cx = LOWORD(lParam);
	m_size.cy = HIWORD(lParam);
	return FALSE;
}

void CMainFrame::OnInjectLibrary(void*, INT)
{
	SetWindowText(m_txtLog.Handle(), "");
	DWORD dwProcess = FindProcess("War3.exe");

	m_lblState.SetText("War3�����ҵ�");
	HANDLE hProcess = ::OpenProcess(PROCESS_ALL_ACCESS, FALSE, dwProcess);
	if (hProcess)
	{

		if (D3D::InjectLibrary(hProcess, TEXT("D:\\Develop\\GitHub\\TinyUI\\Debug\\D3DCaptureHook.dll")))
		{
			m_lblState.SetText("ע��ɹ�");
		}
		else
		{
			m_lblState.SetText("ע��ʧ��");
		}
		CloseHandle(hProcess);
	}
	else
	{
		m_lblState.SetText("War3����û�ҵ�");
	}
}

DWORD CMainFrame::FindProcess(const TinyString& name)
{
	TinyString str1 = "Ҫ���ҽ���";
	str1.Append(name);
	AppendLog(str1);
	DWORD dwProcessID = 0;
	HANDLE hProcessSnap = NULL;
	PROCESSENTRY32 pe32 = { 0 };
	hProcessSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	if (hProcessSnap == (HANDLE)-1)
		return FALSE;
	pe32.dwSize = sizeof(PROCESSENTRY32);
	if (Process32First(hProcessSnap, &pe32))
	{
		do
		{
			TinyString str(pe32.szExeFile);
			if (str == name)
			{
				dwProcessID = pe32.th32ProcessID;
				break;
			}
			AppendLog(str);
		} while (Process32Next(hProcessSnap, &pe32));
	}
	CloseHandle(hProcessSnap);
	return dwProcessID;
}
void CMainFrame::AppendLog(TinyString& str)
{
	str += "\n";
	INT pos = GetWindowTextLength(m_txtLog.Handle());
	m_txtLog.SetSel(pos, -1);
	m_txtLog.SetSelectionCharFormat(m_cf);
	m_txtLog.ReplaceSel(str.STR());
	::SendMessage(m_txtLog.Handle(), WM_VSCROLL, SB_BOTTOM, 0);
}
