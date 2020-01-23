// DlgMaxMin.cpp : implementation file
//

#include "stdafx.h"
#include "idb.h"
#include "DlgMaxMin.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgMaxMin dialog


CDlgMaxMin::CDlgMaxMin(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgMaxMin::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgMaxMin)
	m_maxmin_name = _T("");
	m_maxmin_function = _T("");
	m_maxmin_constant = 0.0f;
	//}}AFX_DATA_INIT
}


void CDlgMaxMin::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgMaxMin)
	DDX_Text(pDX, IDC_MAXMIN_NAME, m_maxmin_name);
	DDX_Text(pDX, IDC_MAXMIN_FUNCTION, m_maxmin_function);
	DDX_Text(pDX, IDC_MAXMIN_CONSTANT, m_maxmin_constant);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgMaxMin, CDialog)
	//{{AFX_MSG_MAP(CDlgMaxMin)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgMaxMin message handlers
