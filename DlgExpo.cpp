// DlgExpo.cpp : implementation file
//

#include "stdafx.h"
#include "idb.h"
#include "DlgExpo.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgExpo dialog


CDlgExpo::CDlgExpo(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgExpo::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgExpo)
	m_Speed = 0.0;
	//}}AFX_DATA_INIT
}


void CDlgExpo::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgExpo)
	DDX_Text(pDX, IDC_EDIT1, m_Speed);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgExpo, CDialog)
	//{{AFX_MSG_MAP(CDlgExpo)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgExpo message handlers
