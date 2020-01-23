// DlgRelName.cpp : implementation file
//

#include "stdafx.h"
#include "idb.h"
#include "DlgRelName.h"

#include "slist.h"
#include "db.h"
#include <fstream.h>
#include "IdbDoc.h"

#include "relation.h"
#include "dlist.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgRelName dialog


CDlgRelName::CDlgRelName(CIdbDoc* pDoc, CWnd* pParent /*=NULL*/)
	: CDialog(CDlgRelName::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgRelName)
	m_strRel = _T("");
	//}}AFX_DATA_INIT
	m_pDoc = pDoc;
}


void CDlgRelName::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgRelName)
	DDX_Control(pDX, IDC_COMBO1, m_combRel);
	DDX_CBString(pDX, IDC_COMBO1, m_strRel);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgRelName, CDialog)
	//{{AFX_MSG_MAP(CDlgRelName)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgRelName message handlers

BOOL CDlgRelName::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	DB* dataBase = &(m_pDoc->m_dataBase);
	
	if (!(*dataBase).numRels) 
		return TRUE;
	else
	{
		int nNum = 0;
		SlistIter<Relation> relationListIter(*(*dataBase).m_pRelationList);
		Relation* p_r; 
		while(p_r = (Relation*)relationListIter())
		{
			String strName = p_r->Name();
			CString strOut("");
			strOut += strName.GetText();

			m_combRel.AddString(strOut);
			nNum++;
		}
	}
			
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
