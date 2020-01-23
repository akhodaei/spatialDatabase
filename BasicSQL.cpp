// BasicSQL1.cpp : implementation file
//

#include "stdafx.h"
#include "idb.h"
#include "BasicSQL.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// BasicSQL dialog

#include <direct.h>

BasicSQL::BasicSQL(CWnd* pParent /*=NULL*/)
	: CDialog(BasicSQL::IDD, pParent)
{
	//{{AFX_DATA_INIT(BasicSQL)
	m_Create = _T("");
	m_Select = _T("");
	m_From = _T("");
	m_Where = _T("");

	m_strCreate = _T("CREATE_VIEW");
	m_strSelect = _T("SELECT");
	m_strFrom = _T("FROM");
	m_strWhere = _T("WHERE");
	//}}AFX_DATA_INIT
}


void BasicSQL::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(BasicSQL)
	DDX_Text(pDX, IDC_EDIT1, m_Create);
	DDX_Text(pDX, IDC_EDIT2, m_Select);
	DDX_Text(pDX, IDC_EDIT3, m_From);
	DDX_Text(pDX, IDC_EDIT4, m_Where);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(BasicSQL, CDialog)
	//{{AFX_MSG_MAP(BasicSQL)
	ON_BN_CLICKED(ID_SAVE, OnSave)
	ON_BN_CLICKED(ID_READ, OnRead)
	//}}AFX_MSG_MAP
//	ON_BN_CLICKED(IDC_CLEAR, OnBnClickedClear)
ON_BN_CLICKED(IDC_CLEAR, OnClear)
ON_BN_CLICKED(IDC_CLEAR, OnClear)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// BasicSQL message handlers

int BasicSQL::DoModal() 
{
	// TODO: Add your specialized code here and/or call the base class
	
	return CDialog::DoModal();
}

BOOL BasicSQL::OnCommand(WPARAM wParam, LPARAM lParam) 
{
	// TODO: Add your specialized code here and/or call the base class
	
	return CDialog::OnCommand(wParam, lParam);
}

void BasicSQL::FileSave(CString fullFileName)
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
		m_Where.Replace("\n", " ");
		outputFile.WriteString("begin %basic%\n\n");
		outputFile.WriteString(m_strCreate + " " + m_Create + "\n\n");
		outputFile.WriteString(m_strSelect + " " + m_Select + "\n\n");
		outputFile.WriteString(m_strFrom + " " + m_From + "\n\n");
		outputFile.WriteString(m_strWhere + " " + m_Where + "\n\n");
		outputFile.WriteString("end %basic%");
	}

	outputFile.Close();  
}

void BasicSQL::OnSave() 
{
	// TODO: Add your control notification handler code here
	char szFilters[] = "Text Documents (*.txt)|| ";
	CFileDialog dlg(false,"txt","*.txt", OFN_OVERWRITEPROMPT, szFilters, this); 

	if(dlg.DoModal() == IDOK)
	{
		UpdateData();

		CString fullFileName = dlg.GetPathName();
		FileSave(fullFileName);

		// save to Last_BasicSql.txt
		CString strTemp("C:\\");
		fullFileName = strTemp + "\\Last_BasicSql.txt";
		FileSave(fullFileName);
	}	
}

BOOL BasicSQL::FindByKey(CString& key, CString& value, CString* pArrStr, int nLineNumber)
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

void BasicSQL::FileRead(CString fullFileName)
{
	int nLineNumber=0;
	CString arrStr[1000];
	CStdioFile inputFile;
	CFileException FileExc;
	int nOpenFlags = CFile::modeRead;

	if(!inputFile.Open(fullFileName, nOpenFlags, &FileExc))
	{
		// FileExc.ReportError();
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
	CString title="begin %basic%";
	if(!FindByKey(title, tmpstr, arrStr, nLineNumber))
	{
		AfxMessageBox("This is not a valid Basic SQL file");
		return;
	}

	BOOL bFindAll = true;
	CString selValue;
	if(!FindByKey(m_strSelect, selValue, arrStr, nLineNumber))
	{
		bFindAll = false;
		// AfxMessageBox("Can not find \"SELECT\" clause");
		// return;
	}
	else
		m_Select = selValue;

	CString createValue;
	if(!FindByKey(m_strCreate, createValue, arrStr, nLineNumber))
	{
		bFindAll = false;
		// AfxMessageBox("Can not find \"CREATE_VIEW\" clause");
		// return;
	}
	else
		m_Create = createValue;

	CString fromValue;
	if(!FindByKey(m_strFrom, fromValue, arrStr, nLineNumber))
	{
		bFindAll = false;
		// AfxMessageBox("Can not find \"FROM\" clause");
		// return;
	}
	else
		m_From = fromValue;

	CString whereValue;
	if(!FindByKey(m_strWhere, whereValue, arrStr, nLineNumber))
	{
		bFindAll = false;
		// AfxMessageBox("Can not find \"WHERE\" clause");
		// return;
	}
	else
		m_Where = whereValue;
}

void BasicSQL::OnRead() 
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

void BasicSQL::OnClear()
{
	// TODO: Add your control notification handler code here
	m_Create = "";
	m_Select = "";
	m_From = "";
	m_Where = "";

	UpdateData(false);
}
