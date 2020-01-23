// MainFrm.cpp : implementation of the CMainFrame class
//

#include "stdafx.h"
#include "idb.h"

#include "MainFrm.h"
#include "Render.h"
#include "DlgApproximation.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMainFrame

IMPLEMENT_DYNAMIC(CMainFrame, CMDIFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CMDIFrameWnd)
	//{{AFX_MSG_MAP(CMainFrame)
	ON_WM_CREATE()
	ON_COMMAND(ID_SHAPE_ANIM, OnShapeAnim)
	//}}AFX_MSG_MAP
	ON_COMMAND(ID_APPROXIMATION, OnApproximation)
END_MESSAGE_MAP()

static UINT indicators[] =
{
	ID_SEPARATOR,           // status line indicator
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	ID_INDICATOR_SCRL,
//	ID_INDICATOR_POS,
};

/////////////////////////////////////////////////////////////////////////////
// CMainFrame construction/destruction

CMainFrame::CMainFrame()
{
	// TODO: add member initialization code here
	
}

CMainFrame::~CMainFrame()
{
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CMDIFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	if (!m_wndToolBar.Create(this) ||
		!m_wndToolBar.LoadToolBar(IDR_MAINFRAME))
	{
		TRACE0("Failed to create toolbar\n");
		return -1;      // fail to create
	}

	if (!m_wndStatusBar.Create(this) ||
		!m_wndStatusBar.SetIndicators(indicators,
		  sizeof(indicators)/sizeof(UINT)))
	{
		TRACE0("Failed to create status bar\n");
		return -1;      // fail to create
	}

	// TODO: Remove this if you don't want tool tips or a resizeable toolbar
	m_wndToolBar.SetBarStyle(m_wndToolBar.GetBarStyle() |
		CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC);

	if (!m_wndDrawBar.Create(this, WS_CHILD | WS_VISIBLE | CBRS_SIZE_DYNAMIC |
			CBRS_TOP | (CBRS_TOOLTIPS | CBRS_FLYBY))  ||
		!m_wndDrawBar.LoadToolBar(IDR_DRAWTOOLS)
		//||		!m_wndDebugBar.SetButtons(DebugButtons, sizeof(DebugButtons)/sizeof(UINT))
		)
	{
		TRACE0("Failed to create drawbar\n");
		return -1;      // fail to create
	}

	// TODO: Delete these three lines if you don't want the toolbar to
	//  be dockable
	m_wndToolBar.EnableDocking(CBRS_ALIGN_ANY);
	m_wndDrawBar.EnableDocking(CBRS_ALIGN_ANY);
	EnableDocking(CBRS_ALIGN_ANY);
	DockControlBar(&m_wndToolBar);
//	DockControlBar(&m_wndDrawBar);

//	((CIdbApp*)AfxGetApp())->p_Frame = this;
	return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CMDIFrameWnd::PreCreateWindow(cs);
}

void CMainFrame::ShowPosition(CPoint point, double dx, double dy)
{
	char cPos[32];
	sprintf(cPos,"(%.3f, %.3f)", dx, dy);
	m_wndStatusBar.SetPaneText(0,cPos);
}

void CMainFrame::ShowLegend()
{

}
void CMainFrame::ShowTime(char* str)
{
//	char cPos[32];
//printf(cPos,"(%.3f)", dx);
	AfxMessageBox(str);
}


void CMainFrame::ShowAnimation(int nNum, int nTotal)
{
	char cPos[100];  //32 //RUICHEN modify
	sprintf(cPos,"(%d / %d)", nNum, nTotal);
	m_wndStatusBar.SetPaneText(0, cPos);
	m_wndStatusBar.UpdateWindow();
}


/////////////////////////////////////////////////////////////////////////////
// CMainFrame diagnostics

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CMDIFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CMDIFrameWnd::Dump(dc);
}

#endif //_DEBUG


/////////////////////////////////////////////////////////////////////////////
// CMainFrame message handlers

void CMainFrame::OnRender() 
{

}

void CMainFrame::OnShapeAnim() 
{
	// TODO: Add your command handler code here
	
}

void CMainFrame::OnApproximation() 
{
	ApproxDlg();
}

void CMainFrame::ApproxDlg()
{
	CDlgApproximation boundDlg;
    extern bool globalApproxST;
    extern float globalApproxBoundST;
	extern int globalApproxTypeST;
	boundDlg.m_UseApproximation = globalApproxST;
	boundDlg.m_ApproxValue = globalApproxBoundST;
	boundDlg.m_ApproxType = globalApproxTypeST; //added 2005 SA

	if (boundDlg.DoModal() == IDOK) 
	{
		globalApproxST = boundDlg.m_UseApproximation;
		if (boundDlg.m_UseApproximation)
		{
			//We are doing approximation: 
			//Set a global property USE_APPROXIMATION = true
			//Set a global property APPROXIMATION_VALUE = atoi(boundDlg.m_CBoundValue)
			TRACE("Checked: %d, Value = %s", boundDlg.m_UseApproximation, boundDlg.m_ApproxValue);
			if(boundDlg.m_ApproxType == 0) {
				globalApproxTypeST = 0;
			}
			else if (boundDlg.m_ApproxType == 1) {
				globalApproxTypeST = 1;
			}
			else {
				globalApproxTypeST = 0;
			}
			if(boundDlg.m_ApproxValue == 0) {
				// Approx bound needs to be positive
				AfxMessageBox("Approximation has not been enabled; you must enter a bound greater than 0.",MB_OK,0);
				boundDlg.m_UseApproximation = false;
				globalApproxST = boundDlg.m_UseApproximation;
			}
			else globalApproxBoundST = boundDlg.m_ApproxValue;
			
		}
	}
}