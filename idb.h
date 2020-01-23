// idb.h : main header file for the IDB application
//

#if !defined(AFX_IDB_H__2BC8E994_3B7D_11D1_BDA8_00A0C96C8797__INCLUDED_)
#define AFX_IDB_H__2BC8E994_3B7D_11D1_BDA8_00A0C96C8797__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols
#include "ServerSocket.h"

#include "GlobalVar.h"
//#define MAX_FILE_OPEN	50
//#define MAX_USER	100

////////////////////////////////////////////////////////////////////////////
// CIdbApp:
// See idb.cpp for the implementation of this class
//
class Compiler;
class Scanner;

typedef struct USER_S
{
	CString cs_UserName;
	CString cs_DocName[MAX_FILE_OPEN];
	void * p_Doc[MAX_FILE_OPEN];
	void * p_View[MAX_FILE_OPEN];
	void * p_Frame[MAX_FILE_OPEN];
	int  preSelIndex[MAX_FILE_OPEN];
} USER_T;

class CIdbApp : public CWinApp
{
public:
	CServerSocket m_srvrSocket;
	void * p_Doc;
	void * p_View;
	void * p_Frame;
	char m_graphFileName[128];
	int m_animationOUT;
	int m_finishSaving;
	
	USER_T	m_User[MAX_USER];

	CIdbApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CIdbApp)
	public:
	virtual BOOL InitInstance();
	virtual CDocument* OpenDocumentFile(LPCTSTR lpszFileName);
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CIdbApp)
	afx_msg void OnAppAbout();
	afx_msg void OnListen();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_IDB_H__2BC8E994_3B7D_11D1_BDA8_00A0C96C8797__INCLUDED_)
