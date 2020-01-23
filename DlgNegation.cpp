// DlgNegation.cpp : implementation file
//

#include "stdafx.h"
#include "idb.h"
#include "DlgNegation.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgNegation dialog


CDlgNegation::CDlgNegation(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgNegation::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgNegation)
	m_XRange = _T("");
	m_YRange = _T("");
	//}}AFX_DATA_INIT
}


void CDlgNegation::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgNegation)
	DDX_Text(pDX, IDC_XRange, m_XRange);
	DDX_Text(pDX, IDC_YRange, m_YRange);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgNegation, CDialog)
	//{{AFX_MSG_MAP(CDlgNegation)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgNegation message handlers
