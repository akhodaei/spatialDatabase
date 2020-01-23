// MainFrm.h : interface of the CMainFrame class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_MAINFRM_H__2BC8E998_3B7D_11D1_BDA8_00A0C96C8797__INCLUDED_)
#define AFX_MAINFRM_H__2BC8E998_3B7D_11D1_BDA8_00A0C96C8797__INCLUDED_

// #include "XStatusBar.h"
// #include "XPaneText.h"

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

class CMainFrame : public CMDIFrameWnd
{
	DECLARE_DYNAMIC(CMainFrame)
public:
	CMainFrame();

// Attributes
public:

// Operations
public:
	void ShowPosition(CPoint point, double dx, double dy);	// Show Graph Position at Status Bar
	void ShowTime(char* str);	// Show Time 
	void ShowAnimation(int nNum, int nTotal);  // show the step nNum of nTotal, for animation
	void ShowLegend();
	void ApproxDlg();
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMainFrame)
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CMainFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:  // control bar embedded members
	CStatusBar  m_wndStatusBar;
	CToolBar    m_wndToolBar;
	CToolBar	m_wndDrawBar;

// Generated message map functions
protected:
	//{{AFX_MSG(CMainFrame)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnRender();
	afx_msg void OnShapeAnim();
	//}}AFX_MSG
	afx_msg void OnApproximation();
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MAINFRM_H__2BC8E998_3B7D_11D1_BDA8_00A0C96C8797__INCLUDED_)
