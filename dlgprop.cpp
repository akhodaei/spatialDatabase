// DlgProp.cpp : implementation file
//

#include "stdafx.h"
#include "idb.h"
//#include "idbdoc.h"
#include "DlgProp.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgProp dialog


CDlgProp::CDlgProp(CIdbDoc* pDoc , CWnd* pParent /*=NULL*/)
	: CDialog(CDlgProp::IDD, pParent)
	, RelName(_T(""))
{
	//{{AFX_DATA_INIT(CDlgProp)
	m_strOut = _T("");
	//}}AFX_DATA_INIT
	pDocTemp = pDoc;
}


void CDlgProp::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgProp)
	DDX_Text(pDX, IDC_EDIT1, m_strOut);
	//}}AFX_DATA_MAP
	DDX_Control(pDX, IDC_BTNTable, TableBtn);
	DDX_Text(pDX, IDC_EDIT2, RelName);
}


BEGIN_MESSAGE_MAP(CDlgProp, CDialog)
	//{{AFX_MSG_MAP(CDlgProp)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_BTNTable, OnBnClickedBtntable)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgProp message handlers

void CDlgProp::OnBnClickedBtntable()
{
	
	//CIdbDoc* pDoc = GetDocument();
	FILE* fp_out;
	CFileDialog fileDlg (FALSE, "txt", "*.txt");
	if( fileDlg.DoModal ()==IDOK )
	{
		CString orgfileName = fileDlg.GetPathName();
		if ((fp_out = fopen(orgfileName, "wt"))==NULL)
		{
			AfxMessageBox("Error creating file !");
			return ;
		}	
		CString head="begin%"+RelName+"%\n\n";
		fwrite(head, sizeof(char), head.GetLength(),fp_out);
		pDocTemp->SaveRelationInfo(pDocTemp->FindRelation(RelName),NULL,fp_out);
		head="end%"+RelName+"%";
		fwrite(head, sizeof(char), head.GetLength(),fp_out);
		fclose(fp_out);
	}
	
}

