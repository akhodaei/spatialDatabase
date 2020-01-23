// OnNestedSql.cpp : implementation file
//

#include "stdafx.h"
#include "idb.h"
#include "OnNestedSql.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// OnNestedSql dialog


OnNestedSql::OnNestedSql(CWnd* pParent /*=NULL*/)
	: CDialog(OnNestedSql::IDD, pParent)
{
	//{{AFX_DATA_INIT(OnNestedSql)
	m_Create = _T("");
	m_Select1 = _T("");
	m_From1 = _T("");
	m_Where1 = _T("");
	m_Select2 = _T("");
	m_From2 = _T("");
	m_Where2 = _T("");
	m_Operator = _T("");

	m_strCreate = _T("CREATE_VIEW");
	m_strSelect1 = _T("SELECT1");
	m_strFrom1 = _T("FROM1");
	m_strWhere1 = _T("WHERE1");
	m_strSelect2 = _T("SELECT2");
	m_strFrom2 = _T("FROM2");
	m_strWhere2 = _T("WHERE2");
	m_strOperator = _T("OPERATOR");
	//}}AFX_DATA_INIT
}


void OnNestedSql::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(OnNestedSql)
	DDX_Text(pDX, IDC_EDIT1, m_Create);
	DDX_Text(pDX, IDC_EDIT2, m_Select1);
	DDX_Text(pDX, IDC_EDIT3, m_From1);
	DDX_Text(pDX, IDC_EDIT4, m_Where1);
	DDX_Text(pDX, IDC_EDIT6, m_Select2);
	DDX_Text(pDX, IDC_EDIT7, m_From2);
	DDX_Text(pDX, IDC_EDIT8, m_Where2);
	DDX_Text(pDX, IDC_EDIT5, m_Operator);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(OnNestedSql, CDialog)
	//{{AFX_MSG_MAP(OnNestedSql)
	ON_BN_CLICKED(ID_SAVE, OnSave)
	ON_BN_CLICKED(ID_READ, OnRead)
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_CLEAR, OnClear)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// OnNestedSql message handlers

void OnNestedSql::FileSave(CString fullFileName)
{
	CStdioFile outputFile;
	CFileException FileExc;
	int nOpenFlags = CFile::modeWrite | CFile::modeCreate;
	if(!outputFile.Open(fullFileName,nOpenFlags, &FileExc))
	{
		FileExc.ReportError();
		return;
	}
	else
	{
		m_Where1.Replace("\n", " ");
		m_Where2.Replace("\n", " ");

		outputFile.WriteString("begin %NEST%\n\n");
		outputFile.WriteString(m_strCreate + " " + m_Create + "\n\n");
		outputFile.WriteString(m_strSelect1 + " " + m_Select1 + "\n\n");
		outputFile.WriteString(m_strFrom1 + " " + m_From1 + "\n\n");
		outputFile.WriteString(m_strWhere1 + " " + m_Where1 + "\n\n");
		outputFile.WriteString(m_strOperator + " " + m_Operator + "\n\n");
		outputFile.WriteString(m_strSelect2 + " " + m_Select2 + "\n\n");
		outputFile.WriteString(m_strFrom2 + " " + m_From2 + "\n\n");
		outputFile.WriteString(m_strWhere2 + " " + m_Where2 + "\n\n");
		outputFile.WriteString("end %NEST%");
	}

	outputFile.Close();  
}

void OnNestedSql::OnSave() 
{
	// TODO: Add your control notification handler code here
	char szFilters[] = "Text Documents (*.txt)|| ";
	CFileDialog dlg(false,"txt","*.txt", OFN_OVERWRITEPROMPT, szFilters, this); 

	if(dlg.DoModal() == IDOK)
	{
		UpdateData();

		CString fullFileName = dlg.GetPathName();
		FileSave(fullFileName);

		// save to Last_NestedSql.txt
		CString strTemp("C:\\");
		fullFileName = strTemp + "\\Last_NestedSql.txt";
		FileSave(fullFileName);
	}	
	
}

BOOL OnNestedSql::FindByKey(CString& key, CString& value, CString* pArrStr, int nLineNumber)
{
	BOOL bFind = false;
	for(int i=0; i<nLineNumber; i++)
	{
		CString str = *(pArrStr+i);
		if(str.Find(key) != -1)
		{
			bFind = true;
			value = str.Right(str.GetLength()-key.GetLength());
			while(value.GetAt(0) == ' ')
			{
				value = value.Right(value.GetLength()-1);
			}
			break;
		}
	}


	return bFind;
	
}

void OnNestedSql::FileRead(CString fullFileName)
{
	int nLineNumber=0;
	CString arrStr[1000];
	CStdioFile inputFile;
	CFileException FileExc;
	int nOpenFlags = CFile::modeRead;

	if(!inputFile.Open(fullFileName, nOpenFlags, &FileExc))
	{
//		FileExc.ReportError();
		return;
	}
	else
	{
		while(inputFile.ReadString(arrStr[nLineNumber]) != false)
		{
			nLineNumber ++;
		}
		inputFile.Close();  
	}

	//for(int i=0; i<nLineNumber; i++)
	//	arrStr[i].MakeUpper();
	CString tmpstr;
	CString title="begin %NEST%";
	if(!FindByKey(title, tmpstr, arrStr, nLineNumber))
	{
		AfxMessageBox("This is not a valid Nested SQL file");
		return;
	}

	BOOL bFindAll = true;
	CString selValue1;
	if(!FindByKey(m_strSelect1, selValue1, arrStr, nLineNumber))
	{
		bFindAll = false;
//		AfxMessageBox("Can not find \"SELECT1\" clause");
//		return;
	}
	else
		m_Select1 = selValue1;

	CString createValue;
	if(!FindByKey(m_strCreate, createValue, arrStr, nLineNumber))
	{
		bFindAll = false;
//		AfxMessageBox("Can not find \"CREATE_VIEW\" clause");
//		return;
	}
	else
		m_Create = createValue;

	CString fromValue1;
	if(!FindByKey(m_strFrom1, fromValue1, arrStr, nLineNumber))
	{
		bFindAll = false;
//		AfxMessageBox("Can not find \"FROM1\" clause");
//		return;
	}
	else
		m_From1 = fromValue1;

	CString whereValue1;
	if(!FindByKey(m_strWhere1, whereValue1, arrStr, nLineNumber))
	{
		bFindAll = false;
//		AfxMessageBox("Can not find \"WHERE1\" clause");
		// return;
	}
	else
		m_Where1 = whereValue1;

	CString ope;
	if(!FindByKey(m_strOperator, ope, arrStr, nLineNumber))
	{
		bFindAll = false;
//		AfxMessageBox("Can not find \"OPERATOR\" clause");
//		return;
	}
	else
		m_Operator = ope;

	CString selValue2;
	if(!FindByKey(m_strSelect2, selValue2, arrStr, nLineNumber))
	{
		bFindAll = false;
//		AfxMessageBox("Can not find \"SELECT2\" clause");
//		return;
	}
	else
		m_Select2	 = selValue2;


	CString fromValue2;
	if(!FindByKey(m_strFrom2, fromValue2, arrStr, nLineNumber))
	{
		bFindAll = false;
//		AfxMessageBox("Can not find \"FROM2\" clause");
//		return;
	}
	else
		m_From2 = fromValue2;

	CString whereValue2;
	if(!FindByKey(m_strWhere2, whereValue2, arrStr, nLineNumber))
	{
		bFindAll = false;
//		AfxMessageBox("Can not find \"WHERE2\" clause");
		// return;
	}
	else
		m_Where2 = whereValue2;

}

void OnNestedSql::OnRead() 
{
	// TODO: Add your control notification handler code here

	char szFilters[] = "Text Documents (*.txt)|| ";
	CFileDialog dlg(TRUE,"txt", "*.txt", OFN_FILEMUSTEXIST | OFN_HIDEREADONLY, szFilters, this);

	if(dlg.DoModal() == IDOK)
	{
		CString fullFileName = dlg.GetPathName();
		FileRead(fullFileName);	
		UpdateData(false);
	}

}

void OnNestedSql::OnClear()
{
	// TODO: Add your control notification handler code here
	m_Create = "";
	m_Select1 = "";
	m_From1 = "";
	m_Where1 = "";
	m_Select2 = "";
	m_From2 = "";
	m_Where2 = "";
	m_Operator = "";
	UpdateData(false);
}
