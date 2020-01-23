
#include "slist.h"
#include "db.h"
#include <fstream.h>
#include <io.h>
#include "idbDoc.h"


#if !defined(AFX_BASICSQLDIALOGBOX_H__ADF330AF_1E53_4FF5_89C6_7D34F36C4001__INCLUDED_)
#define AFX_BASICSQLDIALOGBOX_H__ADF330AF_1E53_4FF5_89C6_7D34F36C4001__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// basicsqldialogbox.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// basicsqldialogbox dialog

class basicsqldialogbox : public CDialog
{
// Construction
public:
	basicsqldialogbox(CIdbDoc* pDoc , CWnd* pParent = NULL);   // standard constructor
	CIdbDoc* pDocTemp;
// Dialog Data
	//{{AFX_DATA(basicsqldialogbox)
	enum { IDD = IDD_SQLDIALOGBOX };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(basicsqldialogbox)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(basicsqldialogbox)
	afx_msg void OnButtonbsql();
	afx_msg void OnButtonasql();
	afx_msg void OnButtonssql();
	afx_msg void OnButtonnsql();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnSqlRec();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_BASICSQLDIALOGBOX_H__ADF330AF_1E53_4FF5_89C6_7D34F36C4001__INCLUDED_)
