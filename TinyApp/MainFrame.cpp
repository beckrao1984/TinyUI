#include "stdafx.h"
#include "MainFrame.h"
#include "VideoCapture.h"
using namespace Media;

CMainFrame::CMainFrame()
{

}

CMainFrame::~CMainFrame()
{
}

LRESULT CMainFrame::OnClose(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	bHandled = FALSE;
	PostQuitMessage(0);
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
	return TEXT("IQiyiWindowClass");
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

	/*vector<VideoCapture::Name> names;
	VideoCapture::GetDevices(names);
	vector<VideoCaptureParam> params;
	VideoCapture::GetDeviceParams(names[0], params);
	*/

	m_inject.Create(m_hWND, 10, 10, 100, 25);
	m_inject.SetText("ע�뵽War3");
	m_onInjectClick.Reset(new Delegate<void(void*, INT)>(this, &CMainFrame::OnInjectLibrary));
	m_inject.EVENT_Click += m_onInjectClick;
	m_lblState.Create(m_hWND, 130, 16, 100, 25);
	m_lblState.SetText("״̬");
	return FALSE;
}

LRESULT CMainFrame::OnDestory(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	bHandled = FALSE;
	m_inject.EVENT_Click -= m_onInjectClick;
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

void CMainFrame::OnInjectLibrary(void*, INT)
{

}

