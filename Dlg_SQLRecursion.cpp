// Dlg_SQLRecursion.cpp : implementation file
//

#include "stdafx.h"
#include "idb.h"
#include "Dlg_SQLRecursion.h"


// Dlg_SQLRecursion dialog

IMPLEMENT_DYNAMIC(Dlg_SQLRecursion, CDialog)
Dlg_SQLRecursion::Dlg_SQLRecursion(CWnd* pParent /*=NULL*/)
	: CDialog(Dlg_SQLRecursion::IDD, pParent)
	, m_ViewName(_T(""))
	, m_Select1(_T(""))
	, m_From1(_T(""))
	, m_Where1(_T(""))
	, m_Select2(_T(""))
	, m_From2(_T(""))
	, m_Where2(_T(""))
	, POS_ID(0)
{
}

Dlg_SQLRecursion::~Dlg_SQLRecursion()
{
}

void Dlg_SQLRecursion::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_RECUR_VIEW, m_ViewName);
	DDX_Text(pDX, IDC_RECUR_SEL1, m_Select1);
	DDX_Text(pDX, IDC_RECUR_FROM1, m_From1);
	DDX_Text(pDX, IDC_RECUR_WHERE1, m_Where1);
	DDX_Text(pDX, IDC_RECUR_SEL2, m_Select2);
	DDX_Text(pDX, IDC_RECUR_FROM2, m_From2);
	DDX_Text(pDX, IDC_RECUR_WHERE2, m_Where2);
	DDX_Text(pDX, IDC_POS_ID, POS_ID);
}


BEGIN_MESSAGE_MAP(Dlg_SQLRecursion, CDialog)
	ON_BN_CLICKED(IDC_SQLRecSave, OnBnSave)
	ON_BN_CLICKED(IDC_SQLRecLoad, OnBnLoad)
	ON_BN_CLICKED(IDC_SQLRecClear, OnBnClear)
	ON_BN_CLICKED(IDC_BtnFirst, OnBnClickedBtnfirst)
	ON_BN_CLICKED(IDC_BtnPrev, OnBnClickedBtnprev)
	ON_BN_CLICKED(IDC_BtnNext, OnBnClickedBtnnext)
	ON_BN_CLICKED(IDC_BtnLast, OnBnClickedBtnlast)
	ON_BN_CLICKED(IDC_BtnSave, OnBnClickedBtnsave)
	ON_BN_CLICKED(IDC_BtnAdd, OnBnClickedBtnadd)
	ON_BN_CLICKED(IDC_BtnDelete, OnBnClickedBtndelete)
END_MESSAGE_MAP()


// Dlg_SQLRecursion message handlers

void Dlg_SQLRecursion::FileSave(CString fullFileName)
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
		outputFile.WriteString("begin %RECURSION%\n\n");
		for (int pos_id=0; pos_id<m_ViewName_List.GetCount(); pos_id++)
		{
			outputFile.WriteString("VIEW " + m_ViewName_List[pos_id] + "\n");
			outputFile.WriteString("SELECT1 " + m_Select1_List[pos_id] + "\n");
			outputFile.WriteString("FROM1 " + m_From1_List[pos_id] + "\n");
			outputFile.WriteString("WHERE1 " + m_Where1_List[pos_id] + "\n");
			outputFile.WriteString("SELECT2 " + m_Select2_List[pos_id] + "\n");
			outputFile.WriteString("FROM2 " + m_From2_List[pos_id] + "\n");
			outputFile.WriteString("WHERE2 " + m_Where2_List[pos_id] + "\n");
		}

		outputFile.WriteString("end %RECURSION%");
	}

	outputFile.Close();  
}

void Dlg_SQLRecursion::FileRead(CString fullFileName)
{
	int nLineNumber=0;
	CArray<CString> arrStr;
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
		CString readinstr;
		while(inputFile.ReadString(readinstr) != false)
		{
			arrStr.Add(readinstr);
		}
		inputFile.Close();  
	}

	//for(int i=0; i<nLineNumber; i++)
	//	arrStr[i].MakeUpper();
	CString tmpstr;
	CString title="begin %RECURSION%";
	nLineNumber = 0;
	if(!FindByKey(title, tmpstr, &arrStr, &nLineNumber))
	{
		AfxMessageBox("This is not a valid Recursive SQL file");
		return;
	}

	BOOL bFindAll = true;
	CString ReadValue;

	m_ViewName_List.RemoveAll();
	m_Select1_List.RemoveAll();
	m_From1_List.RemoveAll();
	m_Where1_List.RemoveAll();
	m_Select2_List.RemoveAll();
	m_From2_List.RemoveAll();
	m_Where2_List.RemoveAll();
	
	m_ViewName_List.FreeExtra();
	m_Select1_List.FreeExtra();
	m_From1_List.FreeExtra();
	m_Where1_List.FreeExtra();
	m_Select2_List.FreeExtra();
	m_From2_List.FreeExtra();
	m_Where2_List.FreeExtra();

	while (nLineNumber < arrStr.GetCount())
	{
		if(!FindByKey("VIEW ", ReadValue, &arrStr, &nLineNumber))
		{
			bFindAll = false;
			break;
		}
		m_ViewName_List.Add(ReadValue);

		if(!FindByKey("SELECT1 ", ReadValue, &arrStr, &nLineNumber))
			bFindAll = false;
		m_Select1_List.Add(ReadValue);

		if(!FindByKey("FROM1 ", ReadValue, &arrStr, &nLineNumber))
			bFindAll = false;
		m_From1_List.Add(ReadValue);

		if(!FindByKey("WHERE1 ", ReadValue, &arrStr, &nLineNumber))
			bFindAll = false;
		m_Where1_List.Add(ReadValue);

		if(!FindByKey("SELECT2 ", ReadValue, &arrStr, &nLineNumber))
			bFindAll = false;
		m_Select2_List.Add(ReadValue);

		if(!FindByKey("FROM2 ", ReadValue, &arrStr, &nLineNumber))
			bFindAll = false;
		m_From2_List.Add(ReadValue);

		if(!FindByKey("WHERE2 ", ReadValue, &arrStr, &nLineNumber))
			bFindAll = false;
		m_Where2_List.Add(ReadValue);
	}
	POS_ID=0;
	DisplayRule(0, false);
	//UpdateData(false);
}

BOOL Dlg_SQLRecursion::FindByKey(CString key, CString& value, CArray<CString>* pArrStr, int* nLineNumber)
{
	BOOL bFind = false;
	value = "";
	for(int i=*nLineNumber; i<pArrStr->GetCount(); i++)
	{
		CString str = pArrStr->GetAt(i);
		if(str.Find(key) != -1)
		{
			bFind = true;
			value = str.Right(str.GetLength()-key.GetLength());
			value.Trim();
			*nLineNumber = i+1;
			break;
		}
	}
	if (!bFind)
		*nLineNumber = pArrStr->GetCount();
	return bFind;
}

void Dlg_SQLRecursion::OnBnSave()
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
		fullFileName = strTemp + "\\Last_SqlRecursion.txt";
		FileSave(fullFileName);
	}	
}

void Dlg_SQLRecursion::OnBnLoad()
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

void Dlg_SQLRecursion::OnBnClear()
{
	// TODO: Add your control notification handler code here
	m_ViewName = "";
	m_Select1 = "";
	m_From1 = "";
	m_Where1 = "";
	m_Select2 = "";
	m_From2 = "";
	m_Where2 = "";
	UpdateData(false);
}

void Dlg_SQLRecursion::DisplayRule(int pos_id, BOOL update)
{
	if (pos_id>=m_ViewName_List.GetCount())
		pos_id=m_ViewName_List.GetCount()-1;

	if (pos_id<0)
	{
		m_ViewName = "";
		m_Select1 = "";
		m_From1 = "";
		m_Where1 = "";
		m_Select2 = "";
		m_From2 = "";
		m_Where2 = "";
		POS_ID=-1;
	}
	else 
	{
		m_ViewName = m_ViewName_List[pos_id];
		m_Select1 = m_Select1_List[pos_id];
		m_From1 = m_From1_List[pos_id];
		m_Where1 = m_Where1_List[pos_id];
		m_Select2 = m_Select2_List[pos_id];
		m_From2 = m_From2_List[pos_id];
		m_Where2 = m_Where2_List[pos_id];
	}
	if (update)
		UpdateData(false);
}

void Dlg_SQLRecursion::SaveRule(int pos_id)
{
	UpdateData(true);
	if ((pos_id>=m_ViewName_List.GetCount())||(pos_id<0))
		return;
	m_ViewName_List[pos_id] = m_ViewName;
	m_Select1_List[pos_id] = m_Select1;
	m_From1_List[pos_id] = m_From1;
	m_Where1_List[pos_id] = m_Where1;
	m_Select2_List[pos_id] = m_Select2;
	m_From2_List[pos_id] = m_From2;
	m_Where2_List[pos_id] = m_Where2;
}

BOOL Dlg_SQLRecursion::CheckModification(int pos_id)
{
	if ((pos_id>=m_ViewName_List.GetCount())||(pos_id<0))
		return true;
	UpdateData(true);
	BOOL modified = ((m_ViewName != m_ViewName_List[pos_id])||
        (m_Select1 != m_Select1_List[pos_id]) ||
        (m_From1 != m_From1_List[pos_id]) ||
        (m_Where1 != m_Where1_List[pos_id]) ||
        (m_Select2 != m_Select2_List[pos_id]) ||
        (m_From2 != m_From2_List[pos_id]) ||
        (m_Where2 != m_Where2_List[pos_id]));
	if (modified)
	{
		int boxresult = AfxMessageBox("Do you want to save changes?", MB_YESNOCANCEL);
		switch (boxresult) 
		{
			case IDYES:		SaveRule(pos_id); return true;
			case IDNO:		return true;
			case IDCANCEL:	return false;
		}
	}
	else 
		return true;

}

void Dlg_SQLRecursion::OnBnClickedBtnfirst()
{
	// TODO: Add your control notification handler code here
	if (!CheckModification(POS_ID))
		return;
	POS_ID = 0;
	DisplayRule(POS_ID);
}


void Dlg_SQLRecursion::OnBnClickedBtnprev()
{
	// TODO: Add your control notification handler code here
	if (!CheckModification(POS_ID))
		return;
	if (POS_ID>0)
	{
		POS_ID --;
		DisplayRule(POS_ID);
	}
}

void Dlg_SQLRecursion::OnBnClickedBtnnext()
{
	// TODO: Add your control notification handler code here
	if (!CheckModification(POS_ID))
		return;
	if (POS_ID < m_ViewName_List.GetCount()-1)
	{
		POS_ID ++;
		DisplayRule(POS_ID);
	}
}

void Dlg_SQLRecursion::OnBnClickedBtnlast()
{
	// TODO: Add your control notification handler code here
	if (!CheckModification(POS_ID))
		return;
	POS_ID = m_ViewName_List.GetCount()-1;
	DisplayRule(POS_ID);
}

void Dlg_SQLRecursion::OnBnClickedBtnsave()
{
	// TODO: Add your control notification handler code here
	SaveRule(POS_ID);
}

void Dlg_SQLRecursion::OnBnClickedBtnadd()
{
	// TODO: Add your control notification handler code here
	m_ViewName = "";
	m_Select1 = "";
	m_From1 = "";
	m_Where1 = "";
	m_Select2 = "";
	m_From2 = "";
	m_Where2 = "";
	
	POS_ID=m_ViewName_List.Add(m_ViewName);
	m_Select1_List.Add(m_Select1);
	m_From1_List.Add(m_From1);
	m_Where1_List.Add(m_Where1);
	m_Select2_List.Add(m_Select2);
	m_From2_List.Add(m_From2);
	m_Where2_List.Add(m_Where2);
	
	UpdateData(false);
}

void Dlg_SQLRecursion::OnBnClickedBtndelete()
{
	// TODO: Add your control notification handler code here
	if (POS_ID<0)
		return;
	m_ViewName_List.RemoveAt(POS_ID);
	m_Select1_List.RemoveAt(POS_ID);
	m_From1_List.RemoveAt(POS_ID);
	m_Where1_List.RemoveAt(POS_ID);
	m_Select2_List.RemoveAt(POS_ID);
	m_From2_List.RemoveAt(POS_ID);
	m_Where2_List.RemoveAt(POS_ID);
	if (POS_ID >= m_ViewName_List.GetCount())
		POS_ID --;
	DisplayRule(POS_ID);
}
