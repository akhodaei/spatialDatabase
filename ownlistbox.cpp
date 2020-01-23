// OwnListBox.cpp : implementation file
//

#include "stdafx.h"
#include "idb.h"
#include "OwnListBox.h"

#include "DB.h"
#include <fstream.h>
#include "IdbDoc.h"
#include "IdbView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// COwnListBox

COwnListBox::COwnListBox()
{
}

COwnListBox::~COwnListBox()
{
}


BEGIN_MESSAGE_MAP(COwnListBox, CListBox)
	//{{AFX_MSG_MAP(COwnListBox)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// COwnListBox message handlers

void COwnListBox::DrawItem(LPDRAWITEMSTRUCT lpDIS) 
{
	COLORREF colorStart, colorEnd;
	CIdbView* pView = (CIdbView*)GetParent();
	ASSERT(pView != NULL);
	CIdbDoc* pDoc = pView->GetDocument();
	ASSERT(pDoc != NULL);

    DB* dataBase =  &(pDoc->m_dataBase);
	if (lpDIS->itemID >= (UINT)(dataBase->numRels))
		return;
	SlistIter<Relation> relIter(*((*dataBase).m_pRelationList));
	Relation* pR;

	UINT i=0;
	pR = relIter();
	while (i < lpDIS->itemID)
	{	
		pR = relIter();
		i++;
	}
	
	colorStart = pR->m_colorStart;
	colorEnd = pR->m_colorEnd;

	CDC* pDC = CDC::FromHandle(lpDIS->hDC);
	CRect rectDraw( lpDIS->rcItem.left,
					lpDIS->rcItem.top,
					lpDIS->rcItem.left + (lpDIS->rcItem.bottom-lpDIS->rcItem.top)-1,
					lpDIS->rcItem.bottom);
	CRect rectDrawEnd( lpDIS->rcItem.left + (lpDIS->rcItem.bottom-lpDIS->rcItem.top)+1,
					lpDIS->rcItem.top,
					lpDIS->rcItem.left + (lpDIS->rcItem.bottom-lpDIS->rcItem.top)*2,
					lpDIS->rcItem.bottom);
	CRect rectDrawLegend( lpDIS->rcItem.left,
					lpDIS->rcItem.top,
					lpDIS->rcItem.left + (lpDIS->rcItem.bottom-lpDIS->rcItem.top)-1,
					lpDIS->rcItem.bottom);

	int x = lpDIS->rcItem.left + (lpDIS->rcItem.bottom - lpDIS->rcItem.top)*2;
	int y = lpDIS->rcItem.top;
	CRect rectText( x, y, lpDIS->rcItem.right, lpDIS->rcItem.bottom);
	CString strOut((LPCSTR)(lpDIS->itemData));

	if (lpDIS->itemAction & ODA_DRAWENTIRE)
	{
		// Paint the color item in the color requested
		CBrush br(colorStart);
		pDC->FillRect(&rectDraw, &br);
		CBrush brEnd(colorEnd);
		pDC->FillRect(&rectDrawEnd, &brEnd);
		pDC->TextOut(x, y, strOut);

		pDC->SetBkColor(RGB(255,255,255));
	}

	if ((lpDIS->itemState & ODS_SELECTED) &&
		(lpDIS->itemAction & (ODA_SELECT | ODA_DRAWENTIRE)))
	{
		// item has been selected - hilite frame
		COLORREF colorBack = pDC->GetBkColor();
		COLORREF colorFore = pDC->GetTextColor();
		CBrush brBack(colorFore);
		pDC->FillRect(&rectText, &brBack);
		COLORREF crHilite = RGB(255-GetRValue(colorStart),
						255-GetGValue(colorStart), 
						255-GetBValue(colorStart));
		CBrush br(crHilite);
		pDC->FrameRect(&rectDraw, &br);
		COLORREF crHiliteEnd = RGB(255-GetRValue(colorEnd),
						255-GetGValue(colorEnd), 
						255-GetBValue(colorEnd));
		CBrush brEnd(crHiliteEnd);
		pDC->FrameRect(&rectDrawEnd, &brEnd);
		COLORREF colorDefault = pDC->SetTextColor(colorBack);
		pDC->SetBkColor(colorFore);
		pDC->ExtTextOut(x, y, ETO_OPAQUE, &rectText, strOut, NULL);
		pDC->SetBkColor(colorBack);
		pDC->SetTextColor(colorDefault);
	}

	if (!(lpDIS->itemState & ODS_SELECTED) &&
		(lpDIS->itemAction & ODA_SELECT))
	{
		// Item has been de-selected -- remove frame
		COLORREF colorBack = pDC->GetBkColor();
		COLORREF colorFore = pDC->GetTextColor();
		CBrush brBack(colorBack);
		pDC->FillRect(&rectText, &brBack);
		CBrush br(colorStart);
		pDC->FrameRect(&rectDraw, &br);
		CBrush brEnd(colorEnd);
		pDC->FrameRect(&rectDrawEnd, &brEnd);
		pDC->TextOut(x, y, strOut);
	}
}

int COwnListBox::GetIndex(CPoint point, int* nColorOrInfo)
{
	for (int nNum=0; nNum<GetCount(); nNum++)
	{
		CRect rect;
		GetItemRect(nNum, &rect);
		CRect rectColor(rect.left, rect.top, (rect.bottom-rect.top)-1, rect.bottom);
		CRect rectColorEnd(rect.left + (rect.bottom-rect.top)+1, rect.top, (rect.bottom-rect.top)*2, rect.bottom);
		if (rect.PtInRect(point))
		{
			if (rectColor.PtInRect(point))
				*nColorOrInfo = 1;
			else if (rectColorEnd.PtInRect(point))
				*nColorOrInfo = 3;
			else
				*nColorOrInfo = 2;
			return nNum;
		}
	}
	return -1;
}

