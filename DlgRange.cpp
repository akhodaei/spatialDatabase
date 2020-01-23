// DlgRange.cpp : implementation file
//
//RUICHEN create

#include "stdafx.h"
#include "idb.h"
#include "DlgRange.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgRange dialog


CDlgRange::CDlgRange(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgRange::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgRange)
	m_RangeLeft = 0.0f;
	m_RangeRight = 0.0f;
	//}}AFX_DATA_INIT

	m_SelectColor=RGB(255,255,255);
}


void CDlgRange::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgRange)
	DDX_Text(pDX, IDC_RANGE_LEFT, m_RangeLeft);
	DDX_Text(pDX, IDC_RANGE_RIGHT, m_RangeRight);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgRange, CDialog)
	//{{AFX_MSG_MAP(CDlgRange)
	ON_BN_CLICKED(IDC_RANGE_COLOR_SELECT, OnRangeColorSelect)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgRange message handlers

void CDlgRange::OnRangeColorSelect() 
{
	CColorDialog dlg;
	dlg.DoModal();
	m_SelectColor= dlg.GetColor();

	CBrush* pbr=new CBrush(m_SelectColor);
	CPaintDC dc(this);
	CWnd* pWnd=GetDlgItem(IDC_RANGE_COLOR);
	CDC* pControlDC=pWnd->GetDC();
	pWnd->Invalidate();
	pWnd->UpdateWindow();
	pControlDC->FillRect(CRect(2,2,43,22),pbr);
	pWnd->ReleaseDC(pControlDC);
}	
