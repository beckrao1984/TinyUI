#pragma once
#include "D3DCommon.h"
#include "D3DSemaphore.h"

class D3DAPIHook
{
public:
	D3DAPIHook();
	~D3DAPIHook();
	BOOL	Initialize(FARPROC pfnOrig, FARPROC pfnHook);
	BOOL	BeginHook();
	BOOL	EndHook();
	BOOL	IsValid() const;
protected:
	FARPROC	m_pfnOrig;
	FARPROC	m_pfnHook;
	DWORD	m_dwOrigProtect;
	BYTE	m_data[5];//ԭʼ�������ڻ�ԭ�ֳ�(x64��Ҫ14���ֽ�)
	BOOL	m_bHook;
};

typedef struct tagCaptureEntry
{
	UINT    captureType;
	DWORD   format;
	UINT    cx;
	UINT	cy;
	BOOL    bFlip;
	UINT    pitch;
	UINT    mapID;
	DWORD   mapSize;
	DWORD   hwndCapture;
}CaptureEntry;
/// <summary>
/// ��������
/// </summary>
typedef struct tagSharedTextureData
{
	LONGLONG    frameTime;
	DWORD       textureHandle;
}SharedTextureData;
