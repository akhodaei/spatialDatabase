// DlgApproximation.cpp : implementation file
//

#include "stdafx.h"
#include "idb.h"
#include "DlgApproximation.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgApproximation dialog


CDlgApproximation::CDlgApproximation(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgApproximation::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgApproximation)
	m_UseApproximation = FALSE;
	m_ApproxValue = 0;
	m_ApproxType = -1;
	//}}AFX_DATA_INIT
}


void CDlgApproximation::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgApproximation)
	DDX_Check(pDX, IDC_APPROX_TRUE, m_UseApproximation);
	DDX_Text(pDX, IDC_APPROX_VALUE, m_ApproxValue);
	DDV_MinMaxLong(pDX, m_ApproxValue, 0, 2147483647);
	DDX_Radio(pDX, IDC_RADIO_LOWER_BOUND, m_ApproxType);
	//}}AFX_DATA_MAP
}



BEGIN_MESSAGE_MAP(CDlgApproximation, CDialog)
	//{{AFX_MSG_MAP(CDlgApproximation)
	ON_BN_CLICKED(IDC_APPROX_TRUE, OnApproxChecked)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgApproximation message handlers

void CDlgApproximation::OnApproxChecked() 
{
	CWnd *edtVal;
	// TODO: Add your control notification handler code here
	UpdateData();
	//if (m_UseApproximation) 
	//{
		//enable BoundValue control
		TRACE("We checked it!\n");
		edtVal = GetDlgItem(IDC_APPROX_VALUE);
		edtVal->EnableWindow();
	//}
	//else
	//{
		//disable BoundValue control
	//	TRACE("We unchecked it!\n");
	//	edtVal = GetDlgItem(IDC_APPROX_VALUE);
	//	edtVal->EnableWindow(false);
	//}
	
}

void CDlgApproximation::OnOK() 
{
	// TODO: Add extra validation here
	
	CDialog::OnOK();
}
