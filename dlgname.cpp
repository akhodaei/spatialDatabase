// DlgName.cpp : implementation file
//

#include "stdafx.h"
#include "idb.h"
#include "DlgName.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgName dialog


CDlgName::CDlgName(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgName::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgName)
	m_newRelName = _T("");
	//}}AFX_DATA_INIT
}


void CDlgName::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgName)
	DDX_Text(pDX, IDC_EDIT1, m_newRelName);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgName, CDialog)
	//{{AFX_MSG_MAP(CDlgName)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgName message handlers
