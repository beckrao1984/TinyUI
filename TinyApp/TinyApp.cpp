// TinyApp.cpp : ����Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include "TinyApp.h"
#include "Common/TinyModule.h"
#include "Control/TinyFrameUI.h"
#include "Windowless/TinyVisualHWND.h"
#include "Database/TinyAdo.h"
#include "Network/TinyConnector.h"
#include "Common/TinyLogging.h"
#include "Common/TinyAPIHook.h"
#include <algorithm>
#include <map>
#include "MyDemo.h"
#include "Media/TinyVideoCapture.h"

#pragma comment(lib,"TinyUI.lib")
using namespace TinyUI;

INT APIENTRY _tWinMain(HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	LPTSTR    lpCmdLine,
	INT       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

	//CMapWordToPtr

	/*for (USHORT i = 0; i < 30; i++)
	{
	ULONG s = TinyHashKey<USHORT>(i) % 17;
	TRACE("s:%d\n", s);
	}*/

	WSADATA   wsd;
	WSAStartup(MAKEWORD(2, 2), &wsd);
	HRESULT hRes = OleInitialize(NULL);

	::DefWindowProc(NULL, 0, 0, 0L);
	TinyApplication::GetInstance()->Initialize(hInstance, lpCmdLine, nCmdShow, MAKEINTRESOURCE(IDC_TINYAPP));
	TinyMessageLoop theLoop;
	TinyApplication::GetInstance()->AddMessageLoop(&theLoop);
	TinyUI::TinyFrameUI uiImpl;
	uiImpl.Create(NULL, 50, 50, 400, 500);
	uiImpl.ShowWindow(nCmdShow);
	uiImpl.UpdateWindow();
	INT loopRes = theLoop.MessageLoop();
	TinyApplication::GetInstance()->RemoveMessageLoop();
	TinyApplication::GetInstance()->Uninitialize();
	OleUninitialize();
	WSACleanup();
	return loopRes;
};