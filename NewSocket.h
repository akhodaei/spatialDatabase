#if !defined(AFX_NEWSOCKET_H__D09CCC57_5DF4_43EB_9ACA_BE00F67D7BE3__INCLUDED_)
#define AFX_NEWSOCKET_H__D09CCC57_5DF4_43EB_9ACA_BE00F67D7BE3__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// NewSocket.h : header file
//

#include "AfxSock.h"

#include "GlobalVar.h"
//#define BUFFER_SIZE	256
//#define OPEN_DOCUMENT	2001
//#define OP_DATALOG		2002
//#define OP_BASIC_SQL	2003

/////////////////////////////////////////////////////////////////////////////
// CNewSocket command target

class CNewSocket : public CAsyncSocket
{
// Attributes
public:
	BOOL m_bConnected;
	UINT m_nLength;
	char m_szBuffer[256];

    CString CMD_FILE_NAME; //"C:\\Inetpub\\wwwroot\\dbs\\Cmd.txt";
	CString SOURCE_DB_DIR;	//"C:\\Inetpub\\wwwroot\\dbs\\";
	CString OUTPUT_DIR;

// Operations
public:
	CNewSocket();
	virtual ~CNewSocket();

// Overrides
public:
	int getPreSelIndex(CString cs_User, CString cs_Doc);
	void getParameters(char * str_Input, CString & cs_Cmd,CString & cs_User, CString & cs_Param1,CString & cs_Param2,CString & cs_Param3,CString & cs_Param4,CString & cs_Param5,CString & cs_Param6,CString & cs_Param7,CString & cs_Param8,CString & cs_Param9);
	int getDocIndex(int userIndex, CString cs_Doc);
	int getUserIndex(CString cs_User);

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CNewSocket)
	public:
	virtual void OnReceive(int nErrorCode);
	virtual void OnSend(int nErrorCode);
	//}}AFX_VIRTUAL

	// Generated message map functions
	//{{AFX_MSG(CNewSocket)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

// Implementation
protected:
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_NEWSOCKET_H__D09CCC57_5DF4_43EB_9ACA_BE00F67D7BE3__INCLUDED_)

