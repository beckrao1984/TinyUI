#pragma once
#include "TinyScrollBox.h"
#include "TinyTextBox.h"
#include "TinyLabel.h"
#include "TinyButton.h"
#include "TinyContextMenu.h"
#include "../Render/TinyImage.h"

namespace TinyUI
{
	/// <summary>
	/// ���ڿ��,�ޱ߿�
	/// </summary>
	class TinyFrameUI : public TinyControl
	{
		DECLARE_DYNAMIC(TinyFrameUI)
	public:
		TinyFrameUI();
		virtual ~TinyFrameUI();
		//5����������
		virtual DWORD RetrieveStyle();
		virtual DWORD RetrieveExStyle();
		virtual LPCSTR RetrieveClassName();
		virtual LPCSTR RetrieveTitle();
		virtual HICON RetrieveIcon();
		//�¼�
		virtual LRESULT OnCreate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
		virtual LRESULT OnDestory(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
		virtual LRESULT OnClose(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
		virtual LRESULT OnPaint(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
		virtual LRESULT OnErasebkgnd(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
		virtual LRESULT OnSize(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
		virtual LRESULT OnNCCalcSize(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled) override;
		//����
		BOOL Create(HWND hParent, INT x, INT y, INT cx, INT cy);
	protected:
		//�������ʽ
		TinySize m_size;
	};
}
