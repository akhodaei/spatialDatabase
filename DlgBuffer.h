#if !defined(AFX_DLGBUFFER_H__EE72B713_F4A7_11D1_B553_00A0C9934E86__INCLUDED_)
#define AFX_DLGBUFFER_H__EE72B713_F4A7_11D1_B553_00A0C9934E86__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// DlgBuffer.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgBuffer dialog
class CIdbDoc;

class CDlgBuffer : public CDialog
{
// Construction
public:
	CDlgBuffer(CIdbDoc* pDoc, CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgBuffer)
	enum { IDD = IDD_DIALOG_BUFFER };
	CComboBox	m_combRel;
	CString	m_strRel;
	float	m_fDistance;
	//}}AFX_DATA
	CIdbDoc* m_pDoc;


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgBuffer)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgBuffer)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGBUFFER_H__EE72B713_F4A7_11D1_B553_00A0C9934E86__INCLUDED_)
