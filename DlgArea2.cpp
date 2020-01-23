// DlgArea2.cpp : implementation file
//

#include "stdafx.h"
#include "idb.h"
#include "DlgArea2.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgArea2 dialog


CDlgArea2::CDlgArea2(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgArea2::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgArea2)
	m_Time = 0.0;
	//}}AFX_DATA_INIT
}


void CDlgArea2::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgArea2)
	DDX_Text(pDX, IDC_EDIT1, m_Time);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgArea2, CDialog)
	//{{AFX_MSG_MAP(CDlgArea2)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgArea2 message handlers
