// DlgInsR.cpp : implementation file
//

#include "stdafx.h"
#include "idb.h"
#include "DlgInsR.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgInsR dialog


CDlgInsR::CDlgInsR(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgInsR::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgInsR)
	m_strText = _T("");
	//}}AFX_DATA_INIT
}


void CDlgInsR::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgInsR)
	DDX_Text(pDX, IDC_EDIT1, m_strText);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgInsR, CDialog)
	//{{AFX_MSG_MAP(CDlgInsR)
	ON_BN_CLICKED(ID_SAVE, OnSave)
	ON_BN_CLICKED(ID_READ, OnRead)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgInsR message handlers

void CDlgInsR::FileSave(CString fullFileName)
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
		outputFile.WriteString("begin %DATALOG%\n");
		outputFile.WriteString(m_strText + "\n");
		outputFile.WriteString("end %DATALOG%");
	}

	outputFile.Close();  
}

void CDlgInsR::OnSave() 
{
	// TODO: Add your control notification handler code here
	char szFilters[] = "Text Documents (*.txt)|| ";
	CFileDialog dlg(false,"txt","*.txt", OFN_OVERWRITEPROMPT, szFilters, this); 

	if(dlg.DoModal() == IDOK)
	{
		UpdateData();

		CString fullFileName = dlg.GetPathName();
		FileSave(fullFileName);

		// save to Last_InsertRelation.txt
		CString strTemp("C:\\");
		fullFileName = strTemp + "\\Last_InsertRelation.txt";
		FileSave(fullFileName);
	}	
	
}

void CDlgInsR::FileRead(CString fullFileName)
{
	CString str;
	CString strIns("");
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
		while(inputFile.ReadString(str) != false)
		{
			//str.MakeUpper();
			if(str.Find("begin")==-1 && str.Find("end")==-1)
				strIns = strIns + str + "\n";
		}
		inputFile.Close();  
	}
	
	m_strText = strIns.Left(strIns.GetLength()-1);
}

void CDlgInsR::OnRead() 
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
