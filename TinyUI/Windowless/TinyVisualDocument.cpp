#include "../stdafx.h"
#include "TinyVisualHWND.h"
#include "TinyVisualWindow.h"
#include "TinyVisualDocument.h"

#include "TinyVisualComboBox.h"

namespace TinyUI
{
	namespace Windowless
	{
		TinyVisualDocument::TinyVisualDocument(TinyVisualHWND* pWindow)
			:m_spvisWindow(NULL),
			m_spvisCapture(NULL),
			m_spvisFocus(NULL),
			m_spvisLastMouse(NULL),
			m_pWindow(pWindow)
		{
			ASSERT(m_pWindow);
			m_fs.Reset(new TinyVisualFactory(this));
		}
		TinyVisualDocument::~TinyVisualDocument()
		{

		}
		BOOL TinyVisualDocument::Destory(TinyVisual* spvis)
		{
			ASSERT(m_fs);
			return m_fs->Destory(spvis);
		}
		BOOL TinyVisualDocument::Initialize()
		{
			m_spvisWindow = new TinyVisualWindow(NULL, this);
			m_spvisWindow->SetName("Window");
			m_spvisWindow->SetStyleImage(NORMAL, "D:\\image.png");
			TinyVisualComboBox* ps10 = Create<TinyVisualComboBox>(50, 320, 200, 50, m_spvisWindow);
			ps10->SetText("����");
			return TRUE;
		}
		void TinyVisualDocument::Uninitialize()
		{
			Destory(m_spvisWindow);
		}
		TinyVisualHWND*	TinyVisualDocument::GetVisualHWND() const
		{
			return m_pWindow;
		}
		TinyVisualCacheDC*	TinyVisualDocument::GetCacheDC() const
		{
			ASSERT(m_pWindow);
			return m_pWindow->m_cacheDC;
		}
		HWND TinyVisualDocument::Handle() const
		{
			return m_pWindow != NULL ? m_pWindow->Handle() : NULL;
		}
		void TinyVisualDocument::LinkVisual(TinyVisual* spvis, TinyVisual* spvisInsert, TinyVisual**pspvisFirst)
		{
			if (*pspvisFirst == spvis)
			{
				return;
			}
			if (spvisInsert == PVISUAL_TOP)
			{
			LINKTOP:
				spvis->m_spvisNext = *pspvisFirst;
				*pspvisFirst = spvis;
			}
			else
			{
				if (spvisInsert == PVISUAL_BOTTOM)
				{
					if ((spvisInsert = *pspvisFirst) == NULL)
					{
						goto LINKTOP;
					}
				}
				ASSERT(spvis != spvisInsert);
				ASSERT(spvis != spvisInsert->m_spvisNext);
				ASSERT(spvis->m_spvisParent == spvisInsert->m_spvisParent);
				spvis->m_spvisNext = spvisInsert->m_spvisNext;
				spvisInsert->m_spvisNext = spvis;
			}
		}
		void TinyVisualDocument::UnlinkVisual(TinyVisual* spvisUnlink, TinyVisual** pspvisFirst)
		{
			TinyVisual* pv = NULL;
			pv = *pspvisFirst;
			if (pv == spvisUnlink)
			{
				*pspvisFirst = spvisUnlink->m_spvisNext;
				spvisUnlink->m_spvisNext = NULL;
				return;
			}
			while (pv != NULL)
			{
				if (pv->m_spvisNext == spvisUnlink)
				{
					pspvisFirst = &pv->m_spvisNext;
					*pspvisFirst = spvisUnlink->m_spvisNext;
					spvisUnlink->m_spvisNext = NULL;
					return;
				}
				pv = pv->m_spvisNext;
			}
		}
		TinyVisual* TinyVisualDocument::GetVisual(TinyVisual* spvis, UINT cmd) const
		{
			if (spvis == m_spvisWindow)
			{
				switch (cmd)
				{
				case GW_CHILD:
					break;
				default:
					return NULL;
					break;
				}
			}
			TinyVisual* pv = NULL;
			BOOL fRebase = FALSE;
			switch (cmd)
			{
			case CMD_NEXT:
				pv = spvis->m_spvisNext;
				fRebase = TRUE;
				break;
			case CMD_FIRST:
				if (spvis->m_spvisParent)
				{
					pv = spvis->m_spvisParent;
					pv = pv->m_spvisChild;
				}
				break;
			case CMD_LAST:
				pv = GetPrevVisual(spvis, NULL);
				break;
			case CMD_PREV:
				pv = GetPrevVisual(spvis, spvis);
				break;
			case CMD_OWNER:
				pv = spvis->m_spvisOwner;
				fRebase = TRUE;
				break;
			case CMD_CHILD:
				pv = spvis->m_spvisChild;
				fRebase = TRUE;
				break;
			default:
				return NULL;
			}
			return pv;
		}
		TinyVisual* TinyVisualDocument::GetPrevVisual(TinyVisual* spvisList, TinyVisual* spvisFind) const
		{
			TinyVisual* spvisFound = NULL;
			TinyVisual* spvisNext = NULL;
			if (spvisList == NULL)
				return NULL;
			if (spvisList->m_spvisParent == NULL)
				return NULL;
			spvisNext = spvisList->m_spvisParent;
			spvisNext = spvisNext->m_spvisChild;
			while (spvisNext != NULL)
			{
				if (spvisNext == spvisFind)
					break;
				spvisFound = spvisNext;
				spvisNext = spvisNext->m_spvisNext;
			}
			return (spvisNext == spvisFind) ? spvisFound : NULL;
		}
		TinyVisual* TinyVisualDocument::GetParent(TinyVisual* spvis) const
		{
			if (!spvis) return m_spvisWindow;
			return spvis->m_spvisParent;
		}
		TinyVisual* TinyVisualDocument::SetParent(TinyVisual* spvis, TinyVisual* spvisNewParent)
		{
			ASSERT(spvis);
			if (spvisNewParent == NULL)
			{
				spvisNewParent = m_spvisWindow;
			}
			if (spvis == m_spvisWindow)
			{
				return NULL;
			}
			TinyVisual* pvT = NULL;
			for (pvT = spvisNewParent; pvT != NULL; pvT = pvT->m_spvisParent)
			{
				if (spvis == pvT)
				{
					return NULL;
				}
			}
			spvis->SetVisible(FALSE);
			TinyVisual* spvisOldParent = spvis->m_spvisParent;
			UnlinkVisual(spvis, &spvisOldParent->m_spvisChild);
			spvis->m_spvisParent = spvisNewParent;
			LinkVisual(spvis, NULL, &spvisNewParent->m_spvisChild);
			spvis->SetVisible(TRUE);
			return spvisOldParent;
		}
		BOOL TinyVisualDocument::IsChild(TinyVisual* spvisParent, TinyVisual* spvis) const
		{
			while (spvis != NULL)
			{
				spvis = spvis->m_spvisParent;
				if (spvisParent == spvis)
					return TRUE;
			}
			return FALSE;
		}
		BOOL TinyVisualDocument::IsVisible(TinyVisual* spvis) const
		{
			if (spvis == NULL)
				return TRUE;
			for (;;)
			{
				if (!spvis->IsVisible())
					return FALSE;
				spvis = spvis->m_spvisParent;
			}
			return TRUE;
		}
		BOOL TinyVisualDocument::IsEnable(TinyVisual* spvis) const
		{
			if (spvis == NULL)
				return TRUE;
			for (;;)
			{
				if (!spvis->IsEnable())
					return FALSE;
				spvis = spvis->m_spvisParent;
			}
			return TRUE;
		}
		BOOL TinyVisualDocument::IsActive(TinyVisual* spvis) const
		{
			if (spvis == NULL)
				return TRUE;
			for (;;)
			{
				if (!spvis->IsActive())
					return FALSE;
				spvis = spvis->m_spvisParent;
			}
			return TRUE;
		}
		TinyVisual*	TinyVisualDocument::GetVisualByName(const TinyString& name)
		{
			return GetVisualByName1(m_spvisWindow, name);
		}
		TinyVisual*	TinyVisualDocument::GetVisualByName1(TinyVisual* spvis, const TinyString& name)
		{
			while (spvis != NULL)
			{
				TinyVisual* hspvis = GetVisualByName2(spvis, name);
				if (hspvis != NULL)
				{
					return hspvis;
				}
				spvis = spvis->m_spvisNext;
			}
			return NULL;
		}
		TinyVisual*	TinyVisualDocument::GetVisualByName2(TinyVisual* spvis, const TinyString& name)
		{
			if (!spvis)
				return NULL;
			if (spvis->GetName() == name)
				return spvis;
			return GetVisualByName1(spvis->m_spvisChild, name);
		}
		TinyVisual*	TinyVisualDocument::GetVisualByPos(INT x, INT y)
		{
			return GetVisualByPos1(m_spvisWindow, x, y);
		}
		void TinyVisualDocument::ConvertToVisualPos(TinyVisual* spvis, TinyPoint& pos)
		{
			ASSERT(m_pWindow && spvis);
			TinyVisual* pv = spvis;
			while (pv != NULL)
			{
				TinyPoint pvPos = pv->GetPosition();
				pos.Offset(-pvPos.x, -pvPos.y);
				pv = pv->m_spvisParent;
			}
		}
		TinyVisual*	TinyVisualDocument::GetVisualByPos1(TinyVisual* spvis, INT x, INT y)
		{
			while (spvis != NULL)
			{
				TinyVisual* hspvis = GetVisualByPos2(spvis, x, y);
				if (hspvis != NULL)
				{
					return hspvis;
				}
				spvis = spvis->m_spvisNext;
			}
			return NULL;
		}
		TinyVisual*	TinyVisualDocument::GetVisualByPos2(TinyVisual* spvis, INT x, INT y)
		{
			if (!spvis || !spvis->IsVisible() || !spvis->IsEnable())
			{
				return NULL;
			}
			POINT pos = { x, y };
			TinyRectangle rectangle;
			rectangle.SetRect(GetWindowPos(spvis), spvis->GetSize());
			if (!PtInRect((LPRECT)&rectangle, pos))
			{
				return NULL;
			}
			if (spvis->m_hrgnClip != NULL && !PtInRegion(spvis->m_hrgnClip, x, y))
			{
				return NULL;
			}
			TinyVisual* hspvis = GetVisualByPos1(spvis->m_spvisChild, x, y);
			if (hspvis != NULL)
				return hspvis;
			return spvis;
		}
		TinyVisual* TinyVisualDocument::GetCapture() const
		{
			return m_spvisCapture;
		}
		TinyVisual*	TinyVisualDocument::SetCapture(TinyVisual* pNew)
		{
			ASSERT(m_pWindow);
			TinyVisual* pv = m_spvisCapture;
			if (pNew != pv)
			{
				if (m_spvisCapture)
				{
					m_spvisCapture->OnCapture(FALSE);
				}
				m_spvisCapture = pNew;
				if (m_spvisCapture)
				{
					m_spvisCapture->OnCapture(TRUE);
				}
			}
			::SetCapture(m_pWindow->Handle());
			return pv;
		}
		BOOL TinyVisualDocument::ReleaseCapture()
		{
			m_spvisCapture = NULL;
			return ::ReleaseCapture();
		}
		TinyVisual* TinyVisualDocument::GetFocus() const
		{
			return m_spvisFocus;
		}
		TinyVisual*	TinyVisualDocument::SetFocus(TinyVisual* pNew)
		{
			ASSERT(m_pWindow);
			TinyVisual* spvis = m_spvisFocus;
			if (pNew != spvis)
			{
				if (m_spvisFocus)
				{
					m_spvisFocus->OnFocus(FALSE);
				}
				m_spvisFocus = pNew;
				if (m_spvisFocus)
				{
					m_spvisFocus->OnFocus(TRUE);
				}
			}
			::SetFocus(m_pWindow->Handle());
			return spvis;
		}
		TinyVisual*	TinyVisualDocument::SetActive(TinyVisual* pNew)
		{
			ASSERT(m_pWindow);
			TinyVisual* spvis = m_spvisActive;
			if (pNew != spvis)
			{
				if (m_spvisActive)
				{
					m_spvisActive->OnActive(FALSE);
				}
				m_spvisFocus = pNew;
				if (m_spvisActive)
				{
					m_spvisActive->OnActive(TRUE);
				}
			}
			::SetActiveWindow(m_pWindow->Handle());
			return spvis;
		}
		TinyVisual* TinyVisualDocument::GetActive() const
		{
			return m_spvisActive;
		}
		TinyPoint TinyVisualDocument::GetWindowPos(const TinyVisual* spvis)
		{
			TinyPoint pos = spvis->GetPosition();
			TinyVisual* ps = spvis->m_spvisParent;
			while (ps != NULL)
			{
				TinyPoint s = ps->GetPosition();
				pos.Offset(s);
				ps = ps->m_spvisParent;
			}
			return pos;
		}
		TinyRectangle TinyVisualDocument::GetWindowRect(const TinyVisual* spvis)
		{
			TinySize size = spvis->GetSize();
			TinyPoint pos = GetWindowPos(spvis);
			return TinyRectangle(pos, size);
		}
		TinyPoint TinyVisualDocument::GetScreenPos(const TinyVisual* spvis)
		{
			TinyPoint pos = GetWindowPos(spvis);
			ClientToScreen(m_pWindow->Handle(), &pos);
			return pos;
		}
		BOOL TinyVisualDocument::Invalidate(RECT *lpRect)
		{
			ASSERT(m_pWindow);
			return ::InvalidateRect(m_pWindow->Handle(), lpRect, FALSE);
		}
		BOOL TinyVisualDocument::Redraw(RECT *lprcUpdate, HRGN hrgnUpdate)
		{
			ASSERT(m_pWindow);
			return ::RedrawWindow(m_pWindow->Handle(), lprcUpdate, hrgnUpdate, RDW_INVALIDATE | RDW_UPDATENOW);
		}
		void TinyVisualDocument::Draw(TinyVisualCacheDC* ps, const RECT& rcPaint)
		{
			TinyRectangle clipBox;
			::GetClipBox(ps->GetMemDC(), &clipBox);
			if (::IntersectRect(&clipBox, &clipBox, &rcPaint))
			{
				this->Draw(m_spvisWindow, ps->GetMemDC(), clipBox);
				ps->Render(clipBox);
			}
		}
		void TinyVisualDocument::Draw(TinyVisual* spvis, HDC hDC, const RECT& rcPaint)
		{
			ASSERT(m_pWindow && m_pWindow->m_cacheDC);
			while (spvis != NULL && spvis->IsVisible())
			{
				if (spvis->m_spvisParent)
				{
					TinyRectangle clipAncestor = GetWindowRect(spvis->m_spvisParent);
					if (::IntersectRect(&clipAncestor, &clipAncestor, &rcPaint))
					{
						TinyRectangle clip = GetWindowRect(spvis);
						if (::IntersectRect(&clip, &clip, &clipAncestor))
						{
							spvis->OnDraw(hDC, clip);
							Draw(spvis->m_spvisChild, hDC, clip);
						}
					}
				}
				else
				{
					TinyRectangle clip = GetWindowRect(spvis);
					if (::IntersectRect(&clip, &clip, &rcPaint))
					{
						spvis->OnDraw(hDC, clip);
						Draw(spvis->m_spvisChild, hDC, clip);
					}
				}
				spvis = spvis->m_spvisNext;
			}
		}
		HRESULT	TinyVisualDocument::OnMouseMove(const TinyPoint& pos, DWORD dwFlags)
		{
			TinyVisual* spvis = m_spvisCapture;
			if (spvis != NULL)
			{
				TinyPoint pt = pos;
				ConvertToVisualPos(spvis, pt);
				return spvis->OnMouseMove(pt, dwFlags);
			}
			else
			{
				spvis = GetVisualByPos(pos.x, pos.y);
				if (spvis != NULL)
				{
					if (m_spvisLastMouse != spvis)
					{
						spvis->OnMouseEnter();
						if (m_spvisLastMouse)
							m_spvisLastMouse->OnMouseLeave();
						m_spvisLastMouse = spvis;
					}
					TinyPoint pt = pos;
					ConvertToVisualPos(spvis, pt);
					return spvis->OnMouseMove(pt, dwFlags);
				}
			}
			return FALSE;
		}
		HRESULT	TinyVisualDocument::OnMouseWheel(const TinyPoint& pos, SHORT zDelta, DWORD dwFlags)
		{
			TinyVisual* spvis = m_spvisFocus;
			if (spvis != NULL)
			{
				return spvis->OnMouseWheel(pos, zDelta, dwFlags);
			}
			return FALSE;
		}
		HRESULT	TinyVisualDocument::OnMouseLeave()
		{
			if (m_spvisLastMouse)
				m_spvisLastMouse->OnMouseLeave();
			return FALSE;
		}
		HRESULT TinyVisualDocument::OnLButtonDown(const TinyPoint& pos, DWORD dwFlags)
		{
			TinyVisual* spvis = m_spvisCapture;
			if (spvis != NULL)
			{
				TinyPoint pt = pos;
				ConvertToVisualPos(spvis, pt);
				return spvis->OnLButtonDown(pt, dwFlags);
			}
			else
			{
				spvis = GetVisualByPos(pos.x, pos.y);
				if (spvis != NULL)
				{
					TinyPoint pt = pos;
					ConvertToVisualPos(spvis, pt);
					return spvis->OnLButtonDown(pt, dwFlags);
				}
			}
			return FALSE;
		}
		HRESULT TinyVisualDocument::OnLButtonUp(const TinyPoint& pos, DWORD dwFlags)
		{
			TinyVisual* spvis = m_spvisCapture;
			if (spvis != NULL)
			{
				TinyPoint pt = pos;
				ConvertToVisualPos(spvis, pt);
				return spvis->OnLButtonUp(pt, dwFlags);
			}
			else
			{
				spvis = GetVisualByPos(pos.x, pos.y);
				if (spvis != NULL)
				{
					TinyPoint pt = pos;
					ConvertToVisualPos(spvis, pt);
					return spvis->OnLButtonUp(pt, dwFlags);
				}
			}
			return FALSE;
		}
		HRESULT TinyVisualDocument::OnRButtonDown(const TinyPoint& pos, DWORD dwFlags)
		{
			TinyVisual* spvis = m_spvisCapture;
			if (spvis != NULL)
			{
				TinyPoint pt = pos;
				ConvertToVisualPos(spvis, pt);
				return spvis->OnRButtonDown(pt, dwFlags);
			}
			else
			{
				spvis = GetVisualByPos(pos.x, pos.y);
				if (spvis != NULL)
				{
					TinyPoint pt = pos;
					ConvertToVisualPos(spvis, pt);
					return spvis->OnRButtonDown(pt, dwFlags);
				}
			}
			return FALSE;
		}
		HRESULT TinyVisualDocument::OnRButtonUp(const TinyPoint& pos, DWORD dwFlags)
		{
			TinyVisual* spvis = m_spvisCapture;
			if (spvis != NULL)
			{
				TinyPoint pt = pos;
				ConvertToVisualPos(spvis, pt);
				return spvis->OnRButtonUp(pt, dwFlags);
			}
			else
			{
				spvis = GetVisualByPos(pos.x, pos.y);
				if (spvis != NULL)
				{
					TinyPoint pt = pos;
					ConvertToVisualPos(spvis, pt);
					return spvis->OnRButtonUp(pt, dwFlags);
				}
			}
			return FALSE;
		}
		HRESULT TinyVisualDocument::OnMButtonDown(const TinyPoint& pos, DWORD dwFlags)
		{
			TinyVisual* spvis = m_spvisCapture;
			if (spvis != NULL)
			{
				TinyPoint pt = pos;
				ConvertToVisualPos(spvis, pt);
				return spvis->OnMButtonDown(pt, dwFlags);
			}
			else
			{
				spvis = GetVisualByPos(pos.x, pos.y);
				if (spvis != NULL)
				{
					TinyPoint pt = pos;
					ConvertToVisualPos(spvis, pt);
					return spvis->OnMButtonDown(pt, dwFlags);
				}
			}
			return FALSE;
		}
		HRESULT	TinyVisualDocument::OnMButtonUp(const TinyPoint& pos, DWORD dwFlags)
		{
			TinyVisual* spvis = m_spvisCapture;
			if (spvis != NULL)
			{
				TinyPoint pt = pos;
				ConvertToVisualPos(spvis, pt);
				return spvis->OnMButtonUp(pt, dwFlags);
			}
			else
			{
				spvis = GetVisualByPos(pos.x, pos.y);
				if (spvis != NULL)
				{
					TinyPoint pt = pos;
					ConvertToVisualPos(spvis, pt);
					return spvis->OnMButtonUp(pt, dwFlags);
				}
			}
			return FALSE;
		}
		HRESULT	TinyVisualDocument::OnKeyDown(DWORD dwChar, DWORD dwRepCnt, DWORD dwFlags)
		{
			TinyVisual* spvis = m_spvisFocus;
			if (spvis != NULL)
			{
				return spvis->OnKeyDown(dwChar, dwRepCnt, dwFlags);
			}
			return FALSE;
		}
		HRESULT	TinyVisualDocument::OnKeyUp(DWORD dwChar, DWORD dwRepCnt, DWORD dwFlags)
		{
			TinyVisual* spvis = m_spvisFocus;
			if (spvis != NULL)
			{
				return spvis->OnKeyUp(dwChar, dwRepCnt, dwFlags);
			}
			return FALSE;
		}
		LRESULT	TinyVisualDocument::OnChar(DWORD dwChar, DWORD dwRepCnt, DWORD dwFlags)
		{
			TinyVisual* spvis = m_spvisFocus;
			if (spvis != NULL)
			{
				return spvis->OnChar(dwChar, dwRepCnt, dwFlags);
			}
			return FALSE;
		}
		HRESULT	TinyVisualDocument::OnSetCursor(HWND hWND, DWORD dwHitTest, DWORD dwMessage)
		{
			POINT pos;
			GetCursorPos(&pos);
			ScreenToClient(hWND, &pos);
			TinyVisual* spvis = GetVisualByPos(pos.x, pos.y);
			if (spvis != NULL)
			{
				return spvis->OnSetCursor(hWND, dwHitTest, dwMessage);
			}
			return FALSE;
		}
		HRESULT	TinyVisualDocument::OnSetFocus(HWND hWND)
		{
			return FALSE;
		}
		HRESULT	TinyVisualDocument::OnKillFocus(HWND hWND)
		{
			SetFocus(NULL);
			return FALSE;
		}
		TinyVisualDocument::TinyVisualFactory::TinyVisualFactory(TinyVisualDocument* document)
			:m_document(document)
		{

		}
		BOOL TinyVisualDocument::TinyVisualFactory::Destory(TinyVisual* spvis)
		{
			ASSERT(m_document);
			if (!spvis) return FALSE;
			TinyVisual* spvisNext = NULL;
			TinyVisual* spvisChild = NULL;
			spvisChild = spvis->m_spvisChild;
			while (spvisChild != NULL)
			{
				spvisNext = spvisChild->m_spvisNext;
				Destory(spvisChild);
				spvisChild = spvisNext;
			}
			if (spvis->m_spvisParent)
			{
				m_document->UnlinkVisual(spvis, &(spvis->m_spvisParent->m_spvisChild));
			}
			spvis->OnDestory();
			SAFE_DELETE(spvis);
			return TRUE;
		}
#ifdef _DEBUG
		void TinyVisualDocument::Dump()
		{
			TRACE("Dump-----\n");
			TinyRectangle rect;
			m_pWindow->GetWindowRect(rect);
			TRACE("window:%d,%d,%d,%d\n", rect.left, rect.top, rect.right, rect.bottom);
			INT deep = 0;
			TinyVisual* spvis = this->GetParent(NULL);
			TinyVisual* ps = spvis->m_spvisChild;
			while (ps)
			{
				Dump(ps, deep);
				ps = ps->m_spvisNext;
				deep = 0;
			}
			TRACE("Dump-----\n");
		}
		void TinyVisualDocument::Dump(TinyVisual* spvis, INT& deep)
		{
			++deep;
			if (!spvis) return;
			TinyString className = spvis->RetrieveTag();
			TinyString name = spvis->GetName();
			TinyString str;
			for (INT i = 0; i < deep; i++)
			{
				str += "-";
			}
			str += "Tag:%s,Name:%s,Rectangle(%d,%d,%d,%d)\n";
			TinyRectangle bounds = GetWindowRect(spvis);
			TRACE(str.STR(), className.STR(), name.STR(), bounds.left, bounds.top, bounds.right, bounds.bottom);
			TinyVisual* ps = spvis->m_spvisChild;
			while (ps)
			{
				Dump(ps, deep);
				ps = ps->m_spvisNext;
			}
		}
#endif // _DEBUG
	}
}
