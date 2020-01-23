// DlgBlock.cpp : implementation file
//

#include "stdafx.h"
#include "idb.h"
#include "DlgBlock.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgBlock dialog


CDlgBlock::CDlgBlock(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgBlock::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgBlock)
	m_strName = _T("");
	m_Time = 0;
	//}}AFX_DATA_INIT
}


void CDlgBlock::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgBlock)
	DDX_Text(pDX, IDC_EDIT1, m_strName);
	DDX_Text(pDX, IDC_EDIT2, m_Time);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgBlock, CDialog)
	//{{AFX_MSG_MAP(CDlgBlock)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgBlock message handlers
