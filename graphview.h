#if !defined(AFX_GRAPHVIEW_H__AD687991_3CF6_11D1_BDC2_00A0C96EF3EF__INCLUDED_)
#define AFX_GRAPHVIEW_H__AD687991_3CF6_11D1_BDC2_00A0C96EF3EF__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// GraphView.h : header file
//

// Hints for UpdateAllViews/OnUpdate
#define HINT_UPDATE_WINDOW      0
#define HINT_UPDATE_DRAWOBJ     1
#define HINT_UPDATE_SELECTION   2
#define HINT_DELETE_SELECTION   3
#define HINT_UPDATE_OLE_ITEMS   4

/////////////////////////////////////////////////////////////////////////////
// CGraphView view
class Relation;
class CSCDrawObj;
class CSCDrawPoly;
class CGraphView : public CScrollView
{
protected:
	CGraphView();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CGraphView)

// Attributes
public:
	CIdbDoc* GetDocument();
	CPtrList m_selection;	// selected Objext( transform from Matrix
	int		point_num;      //indicate the number of points for drawing
	CPoint	drawpoint[2];
	int		draw_mode;

	double	m_dZoom;		// zoom view
	double	m_dZoomWin;		// zoom window 
	BOOL	m_bInit;		// Init Window View Zoom
	BOOL	m_bResetMode;	// reset map mode

	CSize	m_sizeInit;		// Total Size init (Viewport)
	CSize	m_sizeWin;		// window size
	double	m_dMaxX;
	double	m_dMinX;
	double	m_dMaxY;
	double	m_dMinY;

	CPoint	m_pointOrg;		// Cood Org Position;

	BOOL m_bRectmag; //added by Kefei Wang
	UINT m_xRectmag; //added by Kefei Wang
	UINT m_yRectmag; //added by Kefei Wang

// Operations
public:
	void ownLineTo(HDC hdc, int x1,int y1, int x2, int y2); //Huicheng
	void saveImageInfo(CString fileName);					//Huicheng
	void DrawCoordinator(CDC* pDC, double dMaxX, double dMinX, double dMaxY, double dMinY);
	void GetMaxXY(double* dMaxX, double* dMinX, double* dMaxY, double* dMinY);
	void OnZoom(double dRate = 1.0, int nOriX = 0, int nOriY = 0);
	void ZoomRectZoom(CRect rect);

	CPoint LPToDP(double x, double y);
	CPoint DPToLP(CPoint dp, double* dx, double* dy);

	void ClientToDoc(CRect& rect);
	void ClientToDoc(CPoint& point);
	void DocToClient(CPoint& point);
	void DocToClient(CRect& rect);

	void Select(CSCDrawObj* pObj, BOOL bAdd=FALSE);
	void SelectWithinRect(CRect rect, BOOL bAdd);
	void Deselect(CSCDrawObj* pObj);
	void CloneSelection();
	void InvalObj(CSCDrawObj* pObj);
	BOOL IsSelected(const CObject* pDocItem);
	CSCDrawObj* ObjectAt(const CPoint&  point);
	Relation* PointsToConstraints(Relation*,CSCDrawPoly*,float);
	void DoDraw(CDC* pDC);
	void DoDrawDifferentMatrixColor(CDC* pDC);

	BOOL FindRelationMatrix(CPoint point, Relation*& pR, Matrix<float>*& p_matrix);
	void DoShowAttributions(CPoint point);
	
	void SaveImage(CDC* pDrawDC); //, CString filename); //WSS
	CDC* pDCView;


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CGraphView)
	public:
	virtual void OnPrepareDC(CDC* pDC, CPrintInfo* pInfo = NULL);
	protected:
	virtual void OnDraw(CDC* pDC);      // overridden to draw this view
	virtual void OnInitialUpdate();     // first time after construct
	virtual void OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint);
	virtual void OnActivateView(BOOL bActivate, CView* pActivateView, CView* pDeactiveView);
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CGraphView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
	//{{AFX_MSG(CGraphView)
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	afx_msg void OnDrawLine();
	afx_msg void OnDrawPoly();
	afx_msg void OnUpdateDrawLine(CCmdUI* pCmdUI);
	afx_msg void OnUpdateDrawPoly(CCmdUI* pCmdUI);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	afx_msg void OnDrawRect();
	afx_msg void OnUpdateDrawRect(CCmdUI* pCmdUI);
	afx_msg void OnDrawSelect();
	afx_msg void OnUpdateDrawSelect(CCmdUI* pCmdUI);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnGenerateRel();
	afx_msg void OnUpdateGenerateRel(CCmdUI* pCmdUI);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in idbView.cpp
inline CIdbDoc* CGraphView::GetDocument()
   { return (CIdbDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_GRAPHVIEW_H__AD687991_3CF6_11D1_BDC2_00A0C96EF3EF__INCLUDED_)

