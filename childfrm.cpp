// ChildFrm.cpp : implementation of the CChildFrame class
//

#include "stdafx.h"
#include "idb.h"
#include "db.h"
#include "ChildFrm.h"
#include <fstream.h>
#include "IdbDoc.h"
#include "GraphView.h"
#include "MatrixView.h"
#include "PointView.h"
#include "OwnListBox.h"
#include "IdbView.h"
#include "Ex29aView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

const double cdZoomRate	= 1.5;

/////////////////////////////////////////////////////////////////////////////
// CChildFrame

IMPLEMENT_DYNCREATE(CChildFrame, CMDIChildWnd)

BEGIN_MESSAGE_MAP(CChildFrame, CMDIChildWnd)
	//{{AFX_MSG_MAP(CChildFrame)
	ON_COMMAND(ID_VIEW_ZOOMIN, OnViewZoomin)
	ON_COMMAND(ID_VIEW_ZOOMOUT, OnViewZoomout)
	ON_COMMAND(ID_RECTMAG, OnRectmag)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CChildFrame construction/destruction

CChildFrame::CChildFrame()
{
	// TODO: add member initialization code here
	
}

CChildFrame::~CChildFrame()
{
}

BOOL CChildFrame::OnCreateClient( LPCREATESTRUCT lpcs,
	CCreateContext* pContext)
{
	// create a splitter with 2 row, 1 columns
	if (!m_wndSplitter.CreateStatic(this, /*1*/ 2, /*2*/ 1))
	{
		TRACE0("Failed to CreateStaticSplitter\n");
		return FALSE;
	}

	m_wndSplitter.SetRowInfo(0, lpcs->cy*2/3, 20);
	// add the second splitter pane - which is a nested splitter with 2 rows
	if (!m_wndSplitter2.CreateStatic(
		&m_wndSplitter,     // our parent window is the first splitter
		1, 2,               // the new splitter is 1 rows, 2 column
		WS_CHILD | WS_VISIBLE | WS_BORDER,  // style, WS_BORDER is needed
		m_wndSplitter.IdFromRowCol(0, 0)
			// new splitter is in the first row, first column of first splitter
	   ))
	{
		TRACE0("Failed to create nested splitter\n");
		return FALSE;
	}

	// now create the two views inside the nested splitter
	int cyText = max(lpcs->cy*2/3, 20);    // height

	if (!m_wndSplitter2.CreateView(0, 0,
		pContext->m_pNewViewClass, CSize(lpcs->cx/3, cyText), pContext))
	{
		TRACE0("Failed to create IdbView pane\n");
		return FALSE;
	}
/*	if (!m_wndSplitter2.CreateView(1, 0,
		RUNTIME_CLASS(CMatrixView), CSize(lpcs->cx/3, cyText/2), pContext))
	{
		TRACE0("Failed to create third pane\n");
		return FALSE;
	}
	if (!m_wndSplitter2.CreateView(1/*2*, 0,
		RUNTIME_CLASS(CPointView), CSize(lpcs->cx/3, cyText/* /2*), pContext))
	{
		TRACE0("Failed to create third pane\n");
		return FALSE;
	}
*/
	// add the default view in column 1
	if (!m_wndSplitter2.CreateView(0, 1,
		RUNTIME_CLASS(CGraphView), CSize(lpcs->cx*2/3, cyText), pContext))
	{
		TRACE0("Failed to create GraphView pane\n");
		return FALSE;
	}

	if (!m_wndSplitter.CreateView(1, 0,
		RUNTIME_CLASS(CEx29aView), CSize(lpcs->cx, lpcs->cy/3), pContext))
	{
		TRACE0("Failed to create RowView pane\n");
		return FALSE;
	}
/*
	CIdbView* pView = (CIdbView*)(m_wndSplitter2.GetPane(0,0));
	CRect rect;
	pView->GetWindowRect(&rect);
	LPARAM lp;
	lp = (LPARAM)((long)(rect.Size().cy)*65536 + rect.Size().cx);
	pView->PostMessage(WM_SIZE, 0, lp);
*/
	// it all worked, we now have two splitter windows which contain
	//  four different views
	((CIdbApp*)AfxGetApp())->p_Frame = this;
	return TRUE;
}

BOOL CChildFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CMDIChildWnd::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CChildFrame diagnostics

#ifdef _DEBUG
void CChildFrame::AssertValid() const
{
	CMDIChildWnd::AssertValid();
}

void CChildFrame::Dump(CDumpContext& dc) const
{
	CMDIChildWnd::Dump(dc);
}

#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CChildFrame message handlers

void CChildFrame::OnViewZoomin() 
{
	CGraphView* pGraphView = (CGraphView*)m_wndSplitter2.GetPane(0,1);
	ASSERT(pGraphView != NULL);
	if (pGraphView->m_dZoom < 10000)
		pGraphView->OnZoom(cdZoomRate);
}

void CChildFrame::OnViewZoomout() 
{
	CGraphView* pGraphView = (CGraphView*)m_wndSplitter2.GetPane(0,1);
	ASSERT(pGraphView != NULL);
	if (pGraphView->m_dZoom > 0.0001)
		pGraphView->OnZoom(1.0/cdZoomRate);
}

void CChildFrame::ActivateFrame(int nCmdShow) 
{
	CMDIChildWnd::ActivateFrame(nCmdShow);
}

CFrameWnd* CChildFrame::GetActiveFrame() 
{
	// TODO: Add your specialized code here and/or call the base class
	
	return CMDIChildWnd::GetActiveFrame();
}

void CChildFrame::OnRectmag() 
{
	CGraphView* pGraphView = (CGraphView*)m_wndSplitter2.GetPane(0,1);
	ASSERT(pGraphView != NULL);
	pGraphView->m_bRectmag = TRUE;
}
