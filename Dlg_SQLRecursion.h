#pragma once
#include "afxtempl.h"

// Dlg_SQLRecursion dialog

class Dlg_SQLRecursion : public CDialog
{
	DECLARE_DYNAMIC(Dlg_SQLRecursion)

public:
	Dlg_SQLRecursion(CWnd* pParent = NULL);   // standard constructor
	virtual ~Dlg_SQLRecursion();

// Dialog Data
	enum { IDD = IDD_DLG_SQLRecursion };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	CArray<CString> m_ViewName_List;
	CArray<CString> m_Select1_List;
	CArray<CString> m_From1_List;
	CArray<CString> m_Where1_List;
	CArray<CString> m_Select2_List;
	CArray<CString> m_From2_List;
	CArray<CString> m_Where2_List;

	CString m_ViewName;
	CString m_Select1;
	CString m_From1;
	CString m_Where1;
	CString m_Select2;
	CString m_From2;
	CString m_Where2;

	void FileSave(CString fullFileName);
	void FileRead(CString fullFileName);
	BOOL FindByKey(CString key, CString& value, CArray<CString>* pArrStr, int* nLineNumber);
	void DisplayRule(int pos_id, BOOL update=true);
	void SaveRule(int pos_id);
	BOOL CheckModification(int pos_id);
	
	afx_msg void OnBnSave();
	afx_msg void OnBnLoad();
	afx_msg void OnBnClear();
	int POS_ID;
	afx_msg void OnBnClickedBtnfirst();
	afx_msg void OnBnClickedBtnprev();
	afx_msg void OnBnClickedBtnnext();
	afx_msg void OnBnClickedBtnlast();
	afx_msg void OnBnClickedBtnsave();
	afx_msg void OnBnClickedBtnadd();
	afx_msg void OnBnClickedBtndelete();
};
