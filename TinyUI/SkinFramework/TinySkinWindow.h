#pragma once
#include "../Control/TinyControl.h"
#include "../Render/TinyImage.h"
#include "../Control/TinyLabel.h"
#include "../Control/TinyButton.h"
#include "../Control/TinyRichTextBox.h"

namespace TinyUI
{
	/// <summary>
	/// Ƥ������
	/// </summary>
	class TinySkinWindow : public TinyControl
	{
		DECLARE_DYNAMIC(TinySkinWindow)
	public:
		TinySkinWindow();
		virtual ~TinySkinWindow();
		//5����������
		DWORD RetrieveStyle() OVERRIDE;
		DWORD RetrieveExStyle() OVERRIDE;
		LPCSTR RetrieveClassName() OVERRIDE;
		LPCSTR RetrieveTitle() OVERRIDE;
		HICON RetrieveIcon() OVERRIDE;
		//�¼�
		LRESULT OnCreate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled) OVERRIDE;
		LRESULT OnDestory(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled) OVERRIDE;
		LRESULT OnClose(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled) OVERRIDE;
		LRESULT OnPaint(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled) OVERRIDE;
		LRESULT OnErasebkgnd(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled) OVERRIDE;
		LRESULT OnSize(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled) OVERRIDE;
		//����
		BOOL Create(HWND hParent, INT x, INT y, INT cx, INT cy);
	private:
		void OnInjectLibrary(void*, INT);
		DWORD FindProcess(const TinyString& name);
		void AppendLog(TinyString& str);
	protected:
		//�������ʽ
		TinySize	m_size;
		TinyButton	m_inject;
		TinyLabel	m_lblState;
		TinyRichTextBox	m_txtLog;
		CHARFORMAT2	m_cf;
		TinyScopedPtr<Delegate<void(void*, INT)>> m_onInjectClick;
	};
}
