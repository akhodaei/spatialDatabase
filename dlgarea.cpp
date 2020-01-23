// DlgArea.cpp : implementation file
//

#include "stdafx.h"
#include "idb.h"
#include "DlgArea.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgArea dialog


CDlgArea::CDlgArea(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgArea::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgArea)
	m_dMaxX = 0.0;
	m_dMinX = 0.0;
	m_dStep = 0.0;
	//}}AFX_DATA_INIT
}


void CDlgArea::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgArea)
	DDX_Text(pDX, IDC_EDIT_MAX, m_dMaxX);
	DDX_Text(pDX, IDC_EDIT_MIN, m_dMinX);
	DDX_Text(pDX, IDC_EDIT_STEP, m_dStep);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgArea, CDialog)
	//{{AFX_MSG_MAP(CDlgArea)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgArea message handlers
