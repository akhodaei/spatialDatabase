// basicsqldialogbox.cpp : implementation file
//

#include "stdafx.h"
#include "idb.h"
#include "basicsqldialogbox.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// basicsqldialogbox dialog


basicsqldialogbox::basicsqldialogbox(CIdbDoc* pDoc , CWnd* pParent /*=NULL*/)
	: CDialog(basicsqldialogbox::IDD, pParent)
{
	pDocTemp = pDoc;	

	//{{AFX_DATA_INIT(basicsqldialogbox)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void basicsqldialogbox::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(basicsqldialogbox)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(basicsqldialogbox, CDialog)
	//{{AFX_MSG_MAP(basicsqldialogbox)
	ON_BN_CLICKED(IDC_BUTTONBSQL, OnButtonbsql)
	ON_BN_CLICKED(IDC_BUTTONASQL, OnButtonasql)
	ON_BN_CLICKED(IDC_BUTTONSSQL, OnButtonssql)
	ON_BN_CLICKED(IDC_BUTTONNSQL, OnButtonnsql)
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_BUTTONSQLR, OnBnSqlRec)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// basicsqldialogbox message handlers

void basicsqldialogbox::OnButtonbsql() 
{
	pDocTemp->OnSql();
}


void basicsqldialogbox::OnButtonasql() 
{
	// TODO: Add your control notification handler code here
	pDocTemp->OnSqlAggregation();
}

void basicsqldialogbox::OnButtonssql() 
{
	// TODO: Add your control notification handler code here
	pDocTemp->OnSqlsets();
}

void basicsqldialogbox::OnButtonnsql() 
{
	// TODO: Add your control notification handler code here
	pDocTemp->NestedSql();
}

void basicsqldialogbox::OnBnSqlRec()
{
	// TODO: Add your control notification handler code here
	pDocTemp->OnBnSqlRecursion();
}
