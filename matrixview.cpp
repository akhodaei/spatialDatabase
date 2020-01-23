// MatrixView.cpp : implementation file
//

#include "stdafx.h"
#include "idb.h"

#include "slist.h"
#include "db.h"
#include "relation.h"
#include "matrix.h"
#include "vector.h"
#include "dlist.h"
#include <fstream.h>
#include "IdbDoc.h"
#include "MatrixView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMatrixView

IMPLEMENT_DYNCREATE(CMatrixView, CScrollView)

CMatrixView::CMatrixView()
{
}

CMatrixView::~CMatrixView()
{
}


BEGIN_MESSAGE_MAP(CMatrixView, CScrollView)
	//{{AFX_MSG_MAP(CMatrixView)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMatrixView drawing

void CMatrixView::OnInitialUpdate()
{
	CScrollView::OnInitialUpdate();

	CSize sizeTotal;
	// TODO: calculate the total size of this view
	sizeTotal.cx = 240;
	sizeTotal.cy = 300;
	SetScrollSizes(MM_TEXT, sizeTotal);
}

void CMatrixView::OnDraw(CDC* pDC)
{
	CIdbDoc* pDoc = GetDocument();
	ASSERT(pDoc != NULL);

	CString strOut;
	char cOut[32];
	int nY = 0;
	int nYStep = 16;

	POSITION pos = pDoc->m_listRelation.GetHeadPosition();
    Relation* pR;
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
			Vector<float> vector;
			DFIter<Matrix<float> >  matrixIter(*(pR->m_tablePtr));

			while(p_matrix =  matrixIter()) 
			{
				for(int i=0; i< p_matrix->Rows(); i++)
				{   
					strOut = CString("");
					vector = (*p_matrix)[i];
					for(int j=2; j< vector.Size(); j++)
					{
						if (vector[j]-(int)(vector[j]) != 0)
							sprintf(cOut, "%.2f ", vector[j]);
						else
							sprintf(cOut, "%.f ", vector[j]);
						strOut += cOut;
					}
					switch ((int)(vector[0]))
					{
					case 0 :	strOut += "= ";
								break;
					case 1 :	strOut += "< ";
								break;
					case 2 :	strOut += "<= ";
								break;
					case 3 :	strOut += "> ";
								break;
					case 4 :	strOut += ">= ";
								break;
					case 5 :	strOut += "= ";
								break;
					}
					if (vector[1]-(int)(vector[1]) != 0)
						sprintf(cOut, "%.2f", vector[1]);
					else
						sprintf(cOut, "%.f", vector[1]);
					strOut += cOut;
					pDC->TextOut(0, nY, strOut);
					nY += nYStep;
				}
				nY += nYStep;
			}
		}
	}

	SetScrollSizes(MM_TEXT, CSize(640, nY));
}

/////////////////////////////////////////////////////////////////////////////
// CMatrixView diagnostics

#ifdef _DEBUG
void CMatrixView::AssertValid() const
{
	CScrollView::AssertValid();
}

void CMatrixView::Dump(CDumpContext& dc) const
{
	CScrollView::Dump(dc);
}

CIdbDoc* CMatrixView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CIdbDoc)));
	return (CIdbDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMatrixView message handlers
