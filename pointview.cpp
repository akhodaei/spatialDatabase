// PointView.cpp : implementation file
//

#include "stdafx.h"
#include "idb.h"

#include "db.h"
#include <fstream.h>
#include "IdbDoc.h"

#include "PointView.h"


#include "relation.h"
#include "matrix.h"
#include "vector.h"
#include "dlist.h"
#include "slist.h"
#include "hulstruct.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPointView

IMPLEMENT_DYNCREATE(CPointView, CScrollView)

CPointView::CPointView()
{
}

CPointView::~CPointView()
{
}


BEGIN_MESSAGE_MAP(CPointView, CScrollView)
	//{{AFX_MSG_MAP(CPointView)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPointView drawing

void CPointView::OnInitialUpdate()
{
	CScrollView::OnInitialUpdate();

	CSize sizeTotal;
	// TODO: calculate the total size of this view
	sizeTotal.cx = sizeTotal.cy = 100;
	SetScrollSizes(MM_TEXT, sizeTotal);
}

void CPointView::OnDraw(CDC* pDC)
{
	CIdbDoc* pDoc = GetDocument();
	ASSERT(pDoc != NULL);

	CString strOut;
	char cOut[32];
	int nY = 0;
	int nYStep = 16;

    Relation* pR;
	POSITION pos = pDoc->m_listRelation.GetHeadPosition();
	while(pos != NULL)
	{
		pR = (Relation*)(pDoc->m_listRelation.GetNext(pos));

		switch (pR->SatisFlag())
		{
		case 1  :	strOut = "Universally Satisfiable";
					pDC->TextOut(0, nY+=nYStep, strOut);
					break;
		case -1 :	strOut = "Unsatisfiable";
					pDC->TextOut(0, nY+=nYStep, strOut);
					break;
		default :
			const Matrix<float>* p_matrix;
			DFIter<Matrix<float> >  matrixIter(*(pR->m_tablePtr));
			while(p_matrix =  matrixIter()) 
			{ 
				Slist<ParaPoint>* pointList = p_matrix->m_pList;
				if (pointList != NULL)
				{
					sprintf(cOut, "%d", pointList->Size());
					pDC->TextOut(0, nY, cOut);
					nY += nYStep;
	
					Snode<ParaPoint>* nPtr = pointList->headPtr ;
					int i = 0;
					while(i++ < pointList->len)
					{
						if (((Point*)(nPtr->itemPtr))->m_x - (int)(((Point*)(nPtr->itemPtr))->m_x) != 0)
							sprintf(cOut, "(%.2f, %.2f)", 
								((Point*)(nPtr->itemPtr))->m_x,
								((Point*)(nPtr->itemPtr))->m_y);
						else
							sprintf(cOut, "(%.f, %.f)", 
								((Point*)(nPtr->itemPtr))->m_x,
								((Point*)(nPtr->itemPtr))->m_y);
						pDC->TextOut(0, nY, cOut);
						nY += nYStep;
						nPtr = nPtr->nextPtr ;
					}
					nY += nYStep; 
				}
			}
		}
	}

	SetScrollSizes(MM_TEXT, CSize(100, nY));
}

/////////////////////////////////////////////////////////////////////////////
// CPointView diagnostics

#ifdef _DEBUG
void CPointView::AssertValid() const
{
	CScrollView::AssertValid();
}

void CPointView::Dump(CDumpContext& dc) const
{
	CScrollView::Dump(dc);
}

CIdbDoc* CPointView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CIdbDoc)));
	return (CIdbDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CPointView message handlers
