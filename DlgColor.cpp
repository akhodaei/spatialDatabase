// DlgColor.cpp : implementation file
//
//RUICHEN create

#include "stdafx.h"
#include "idb.h"
#include "db.h"
#include <fstream.h>
#include "IdbDoc.h"
#include "DlgColor.h"
#include "DlgRange.h"
#include "range.h"  //RUICHEN

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgColor dialog


CDlgColor::CDlgColor(CIdbDoc* pDoc, CWnd* pParent /*=NULL*/)
	: CDialog(CDlgColor::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgColor)
	m_Cur_RangeList = _T("");
	//}}AFX_DATA_INIT

	m_pDoc=pDoc;
}


void CDlgColor::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgColor)
	DDX_Control(pDX, IDC_RANGE_LIST, m_RangeList);
	DDX_LBString(pDX, IDC_RANGE_LIST, m_Cur_RangeList);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgColor, CDialog)
	//{{AFX_MSG_MAP(CDlgColor)
	ON_BN_CLICKED(IDC_ADD, OnAdd)
	ON_BN_CLICKED(IDC_DELETE, OnDelete)
	ON_LBN_SELCHANGE(IDC_RANGE_LIST, OnSelchangeRangeList)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgColor message handlers

BOOL CDlgColor::OnInitDialog() 
{
	CDialog::OnInitDialog();

	if(m_pDoc->m_ranges.GetCount()==0)
		return TRUE;

	char tempstr[100];
	Range* pRange;
	POSITION pos;

	for(pos = m_pDoc->m_ranges.GetHeadPosition(); pos != NULL; ) {
		pRange=(Range*)m_pDoc->m_ranges.GetNext(pos);
		sprintf(tempstr,"%12.2f  --->  %12.2f   Color: #%02X%02X%02X", (*pRange).left, (*pRange).right, GetRValue((*pRange).color),GetGValue((*pRange).color),GetBValue((*pRange).color));
        m_RangeList.AddString(CString(tempstr));
	}

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgColor::OnAdd() 
{
	CDlgRange aDlgRange;
	if(aDlgRange.DoModal()!=IDOK)
		return;

	char tempstr[100];
	float temp;
	if(aDlgRange.m_RangeLeft>aDlgRange.m_RangeRight){
		temp=aDlgRange.m_RangeLeft;
		aDlgRange.m_RangeLeft=aDlgRange.m_RangeRight;
		aDlgRange.m_RangeRight=temp;
	}
    sprintf(tempstr,"%12.2f  --->  %12.2f   Color: #%02X%02X%02X", aDlgRange.m_RangeLeft, aDlgRange.m_RangeRight, GetRValue(aDlgRange.m_SelectColor),GetGValue(aDlgRange.m_SelectColor),GetBValue(aDlgRange.m_SelectColor));
	m_RangeList.AddString(CString(tempstr));

	Range* pRange=new Range(aDlgRange.m_RangeLeft,aDlgRange.m_RangeRight,aDlgRange.m_SelectColor);
	m_pDoc->m_ranges.AddTail(pRange);
}

void CDlgColor::OnDelete() 
{
	char tempstr[100];
	Range* pRange;
	POSITION pos,temp_pos;

	int index=m_RangeList.GetCurSel(); 
	if(index==LB_ERR) return;

	m_RangeList.GetText(index,m_Cur_RangeList);

	for(pos = m_pDoc->m_ranges.GetHeadPosition(); pos != NULL; ) {
		temp_pos=pos;
		pRange=(Range*)m_pDoc->m_ranges.GetNext(pos);
		sprintf(tempstr,"%12.2f  --->  %12.2f   Color: #%02X%02X%02X", (*pRange).left, (*pRange).right, GetRValue((*pRange).color),GetGValue((*pRange).color),GetBValue((*pRange).color));
		if(!m_Cur_RangeList.Compare(CString(tempstr))){ 
			m_pDoc->m_ranges.RemoveAt(temp_pos);
			delete pRange;
			m_RangeList.DeleteString(index);
		}
	}	
}

void CDlgColor::OnSelchangeRangeList() 
{
	char tempstr[100];
	Range* pRange;
	POSITION pos;
	CBrush* pbr;

	m_RangeList.GetText(m_RangeList.GetCurSel(),m_Cur_RangeList);

	for(pos = m_pDoc->m_ranges.GetHeadPosition(); pos != NULL; ) {
		pRange=(Range*)m_pDoc->m_ranges.GetNext(pos);
		sprintf(tempstr,"%12.2f  --->  %12.2f   Color: #%02X%02X%02X", (*pRange).left, (*pRange).right, GetRValue((*pRange).color),GetGValue((*pRange).color),GetBValue((*pRange).color));

		if(!m_Cur_RangeList.Compare(CString(tempstr))){ 
			pbr=new CBrush((*pRange).color);
			CPaintDC dc(this);
			CWnd* pWnd=GetDlgItem(IDC_CUR_COLOR);
			CDC* pControlDC=pWnd->GetDC();
			pWnd->Invalidate();
			pWnd->UpdateWindow();
			pControlDC->FillRect(CRect(2,2,43,21),pbr);
			pWnd->ReleaseDC(pControlDC);
			break;
		}
	}
}
