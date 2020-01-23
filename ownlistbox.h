#if !defined(AFX_OWNLISTBOX_H__DF6365B4_4A44_11D1_90BC_00A0C9392AD1__INCLUDED_)
#define AFX_OWNLISTBOX_H__DF6365B4_4A44_11D1_90BC_00A0C9392AD1__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// OwnListBox.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// COwnListBox window

class COwnListBox : public CListBox
{
// Construction
public:
	COwnListBox();

// Attributes
public:

// Operations
public:
	int GetIndex(CPoint point, int* nColorOrInfo);	// return the item Index at point

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(COwnListBox)
	public:
	virtual void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~COwnListBox();

	// Generated message map functions
protected:
	//{{AFX_MSG(COwnListBox)
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_OWNLISTBOX_H__DF6365B4_4A44_11D1_90BC_00A0C9392AD1__INCLUDED_)
