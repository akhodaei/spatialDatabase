// DlgNtime.cpp : implementation file
//

#include "stdafx.h"
#include "idb.h"
#include "DlgNtime.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgNtime dialog


CDlgNtime::CDlgNtime(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgNtime::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgNtime)
	m_Start = 0.0;
	m_End = 0.0;
	m_Speed = 0.0;
	m_NoOfStep = 0.0;
	m_Step = 0.0;
	//}}AFX_DATA_INIT
}


void CDlgNtime::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgNtime)
	DDX_Text(pDX, IDC_EDIT1, m_Start);
	DDX_Text(pDX, IDC_EDIT4, m_End);
	DDX_Text(pDX, IDC_EDIT5, m_Speed);
	DDX_Text(pDX, IDC_EDIT2, m_NoOfStep);
	DDX_Text(pDX, IDC_EDIT3, m_Step);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgNtime, CDialog)
	//{{AFX_MSG_MAP(CDlgNtime)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgNtime message handlers
