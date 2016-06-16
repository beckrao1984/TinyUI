#include "../stdafx.h"
#include "TinyVisualTree.h"
#include "TinyVisualManage.h"
#include "TinyVisualCaption.h"

namespace TinyUI
{
	namespace Windowless
	{
		TinyVisualSysButton::TinyVisualSysButton(TinyVisual* spvisParent, TinyVisualTree* vtree)
			:TinyVisual(spvisParent, vtree)
		{

		}
		TinyVisualSysButton::~TinyVisualSysButton()
		{

		}
		TinyString TinyVisualSysButton::RetrieveTag() const
		{
			return TinyVisualTag::SYSBUTTON;
		}
		HRESULT TinyVisualSysButton::OnDraw(TinyCanvas& canvas)
		{
			TinyImage& image = m_images[NORMAL];
			if (image.IsEmpty()) return S_FALSE;
			canvas.DrawImage(image, m_windowRect, 0, 0, 30, 30);
			return S_OK;
		}
		HRESULT TinyVisualSysButton::OnMouseMove(POINT pos)
		{
			TRACE("TinyVisualSysButton-OnMouseMove\n");
			return FALSE;
		}

		HRESULT TinyVisualSysButton::OnLButtonDown(POINT pos)
		{
			TRACE("TinyVisualSysButton-OnLButtonDown\n");
			return FALSE;
		}

		HRESULT TinyVisualSysButton::OnLButtonUp(POINT pos)
		{
			TRACE("TinyVisualSysButton-OnLButtonUp\n");
			return FALSE;
		}

		HRESULT TinyVisualSysButton::OnRButtonDown(POINT pos)
		{
			return FALSE;
		}

		HRESULT TinyVisualSysButton::OnRButtonUp(POINT pos)
		{
			return FALSE;
		}
		//////////////////////////////////////////////////////////////////////////
		TinyVisualCaption::TinyVisualCaption(TinyVisual* spvisParent, TinyVisualTree* vtree)
			:TinyVisual(spvisParent, vtree)
		{

		}
		TinyVisualCaption::~TinyVisualCaption()
		{

		}
		TinyString TinyVisualCaption::RetrieveTag() const
		{
			return TinyVisualTag::CAPTION;
		}
		void TinyVisualCaption::Resize()
		{
			TinyVisual* spvisParent = m_spvisParent;
		}
		HRESULT TinyVisualCaption::OnDraw(TinyCanvas& canvas)
		{
			TinyVisual* spvis = m_vtree->GetVisual(this, CMD_CHILD);
			while (spvis)
			{
				spvis->OnDraw(canvas);
				spvis = m_vtree->GetVisual(spvis, CMD_NEXT);
			}
			return S_OK;
		}
		HRESULT TinyVisualCaption::OnMouseMove(POINT pos)
		{
			TRACE("TinyVisualCaption-OnMouseMove\n");
			return FALSE;
		}
		HRESULT TinyVisualCaption::OnLButtonDown(POINT pos)
		{
			return FALSE;
		}
		HRESULT TinyVisualCaption::OnLButtonUp(POINT pos)
		{
			return FALSE;
		}
		HRESULT TinyVisualCaption::OnRButtonDown(POINT pos)
		{
			return FALSE;
		}
		HRESULT TinyVisualCaption::OnRButtonUp(POINT pos)
		{
			return FALSE;
		}
	}
}
