// DlgGenN.cpp : implementation file
//

#include "stdafx.h"
#include "idb.h"
#include "DlgGenN.h"

#include "slist.h"
#include "db.h"
#include <fstream.h>
#include "IdbDoc.h"

#include "relation.h"
//#include "matrix.h"
//#include "vector.h"
#include "dlist.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgGenN dialog


CDlgGenN::CDlgGenN(CIdbDoc* pDoc, CWnd* pParent /*=NULL*/)
	: CDialog(CDlgGenN::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgGenN)
	m_strRel = _T("");
	m_strID = _T("");
	//}}AFX_DATA_INIT
	m_pDoc = pDoc;
}


void CDlgGenN::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgGenN)
	DDX_Control(pDX, IDC_COMBO1, m_combRel);
	DDX_CBString(pDX, IDC_COMBO1, m_strRel);
	DDX_Text(pDX, IDC_EDIT2, m_strID);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgGenN, CDialog)
	//{{AFX_MSG_MAP(CDlgGenN)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgGenN message handlers

BOOL CDlgGenN::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	m_strID = CString("1");

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
