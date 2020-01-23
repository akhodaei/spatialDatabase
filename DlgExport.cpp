// DlgExport.cpp : implementation file
//

#include "stdafx.h"
#include "idb.h"
#include "DlgExport.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgExport dialog


CDlgExport::CDlgExport(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgExport::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgExport)
	m_sDescriptive = _T("");
	m_sSpatial = _T("");
	//}}AFX_DATA_INIT
}


void CDlgExport::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgExport)
	DDX_Text(pDX, IDC_EDIT_DESCRIPTIVE, m_sDescriptive);
	DDX_Text(pDX, IDC_EDIT_SPATIAL, m_sSpatial);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgExport, CDialog)
	//{{AFX_MSG_MAP(CDlgExport)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgExport message handlers
