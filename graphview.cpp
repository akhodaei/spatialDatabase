// GraphView.cpp : implementation file
//

#include "stdafx.h"

#include "idb.h"

#include "slist.h"
#include "db.h"
#include <fstream.h>
#include "IdbDoc.h"
#include "GraphView.h"
#include "MainFrm.h"
#include "OwnListBox.h"
#include "IdbView.h"

#include "relation.h"
#include "matrix.h"
#include "vector.h"
#include "dlist.h"

#include "scdrawobj.h"
#include "scdrawtool.h"

#include "DlgGenN.h"
#include "hulstruct.h"
#include "DlgName.h"

#include "BitmapFile.h"

#include "range.h"         //ylu

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CGraphView

IMPLEMENT_DYNCREATE(CGraphView, CScrollView)

CGraphView::CGraphView()
{
	m_dZoom = 1.0;
	m_dZoomWin = 1.0;
	m_bInit = FALSE;
	m_bResetMode = TRUE;
	m_sizeInit = CSize(100, 100);
	m_sizeWin = m_sizeInit;

	m_bRectmag = FALSE;	//by Kefei Wang. Shasha: It will be set by Childfrm.cpp
	m_xRectmag = 0; //added by Kefei Wang
	m_yRectmag = 0; //added by Kefei Wang

	m_pointOrg = CPoint(50, 50);
}

CGraphView::~CGraphView()
{
}


BEGIN_MESSAGE_MAP(CGraphView, CScrollView)
	//{{AFX_MSG_MAP(CGraphView)
	ON_WM_MOUSEMOVE()
	ON_WM_CONTEXTMENU()
	ON_COMMAND(ID_DRAW_LINE, OnDrawLine)
	ON_COMMAND(ID_DRAW_POLY, OnDrawPoly)
	ON_UPDATE_COMMAND_UI(ID_DRAW_LINE, OnUpdateDrawLine)
	ON_UPDATE_COMMAND_UI(ID_DRAW_POLY, OnUpdateDrawPoly)
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_LBUTTONDBLCLK()
	ON_COMMAND(ID_DRAW_RECT, OnDrawRect)
	ON_UPDATE_COMMAND_UI(ID_DRAW_RECT, OnUpdateDrawRect)
	ON_COMMAND(ID_DRAW_SELECT, OnDrawSelect)
	ON_UPDATE_COMMAND_UI(ID_DRAW_SELECT, OnUpdateDrawSelect)
	ON_WM_SIZE()
	ON_COMMAND(ID_GENERATE_REL, OnGenerateRel)
	ON_UPDATE_COMMAND_UI(ID_GENERATE_REL, OnUpdateGenerateRel)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

//	ON_COMMAND(ID_RECTMAG, OnRectmag)
//ON_UPDATE_COMMAND_UI(ID_RECTMAG, OnUpdateRectmag)

/////////////////////////////////////////////////////////////////////////////
// CGraphView drawing

void CGraphView::OnInitialUpdate()
{
	if (!m_bInit)
	{
		CRect rect;
		GetClientRect(&rect);
		m_sizeInit = rect.Size();
		SetScrollSizes(MM_TEXT, m_sizeInit);
		m_pointOrg = CPoint(m_sizeInit.cx/2, m_sizeInit.cy/2);

		GetMaxXY(&m_dMaxX, &m_dMinX, &m_dMaxY, &m_dMinY);
		double dTempX = max(fabs(m_dMaxX),fabs(m_dMinX))*2 / m_sizeInit.cx;
		double dTempY = max(fabs(m_dMaxY),fabs(m_dMinY))*2 / m_sizeInit.cy;
//		if (max(dTempX, dTempY) < 1.0)
//		{
			m_dZoomWin = 0.9/*1.0*/ / max(dTempY, dTempX);
			m_sizeWin = m_sizeInit;

//		}
/*		else
		{
			m_dZoomWin = 1.0;
			m_sizeWin.cx = (int)(max(fabs(m_dMaxX),fabs(m_dMinX))*2*m_dZoomWin);
			m_sizeWin.cy = (int)(max(fabs(m_dMaxY),fabs(m_dMinY))*2*m_dZoomWin);
		}
*/
		OnZoom();
		m_bInit = TRUE;
	}

	CScrollView::OnInitialUpdate();
}

static double fValidGraduations[] =
{
	0.01, 0.02, 0.05, 0.1, 0.2, 0.5, 1, 2, 5, 10, 20, 50, 100, 200, 500, 1000, 2000, 5000, 10000, 100000, 1000000, 10000000, 0
};

double GetTickValue(double fMaxValue, int nNumDiv)
{
	// Determine values for vertical ticks
	double fValuePerTick = fMaxValue / nNumDiv;
	for (int i = 0; fValidGraduations[i] > 0; i++)
		if (fValidGraduations[i] >= fValuePerTick)
			return fValidGraduations[i];
	return fValidGraduations[i-1];
}

void CGraphView::DrawCoordinator(CDC* pDC, double dMaxX, double dMinX, double dMaxY, double dMinY)
{
	const cnTicks = 4;
	const cnHeight = 20;
	CPen penGrid(PS_SOLID, 1, RGB(192,192,292));
	CPen penCoor(PS_SOLID, 1, RGB(128,128,128));
	CPen* pOldPen = pDC->SelectObject(&penGrid);

	double dXRange = max(fabs(dMaxX), fabs(dMinX));
	double dYRange = max(fabs(dMaxY), fabs(dMinY));

	double dTickX = GetTickValue(dXRange, cnTicks);
	double dTickY = GetTickValue(dYRange, cnTicks);
	double dTick = max(dTickX, dTickY);

	dXRange = max(dXRange, dTick*cnTicks);
	dYRange = max(dYRange, dTick*cnTicks);

	char cOut[24];
	CPoint point;
	UINT nTextAlign = pDC->GetTextAlign();
	double x = -dTick*cnTicks;
	while (x <= dTick*cnTicks  &&  x <= dXRange)
	{
		if (x==0)
			pDC->SelectObject(&penCoor);
		pDC->MoveTo(LPToDP(x, dYRange));
		pDC->LineTo(LPToDP(x, -dYRange));
		if (x==0)
			pDC->SelectObject(&penGrid);
		if (dTick > 1)
			sprintf(cOut, "%.f", x);
		else
			sprintf(cOut, "%.2f", x);
		point = LPToDP(x, 0);
		pDC->SetTextAlign(TA_TOP | TA_CENTER);
		pDC->TextOut(point.x, point.y, cOut);
		x += dTick;
	}
	double y = -dTick*cnTicks;
	while (y <= dTick*cnTicks  &&  y <= dYRange)
	{
		if (y==0)
			pDC->SelectObject(&penCoor);
		pDC->MoveTo(LPToDP(dXRange, y));
		pDC->LineTo(LPToDP(-dXRange, y));
		if (y==0)
			pDC->SelectObject(&penGrid);
		if (dTick > 1)
			sprintf(cOut, "%.f", y);
		else
			sprintf(cOut, "%.2f", y);
		point = LPToDP(0, y);
		pDC->SetTextAlign(TA_BASELINE | TA_RIGHT);
		pDC->TextOut(point.x, point.y, cOut);
		y += dTick;
	}

	pDC->SetTextAlign(nTextAlign);
	if (pOldPen != NULL)
		pDC->SelectObject(pOldPen);
	GetMaxXY(&m_dMaxX, &m_dMinX, &m_dMaxY, &m_dMinY);

//  Syed Appended

	COLORREF colorTable[401];
	colorTable[0] = (1<<16) + (1<<8) + 255;
	int i;
	for (i=0; i<80; i++) {
		colorTable[i+1] = (1<<16) + (((int)((1-i/79.0)*1 + (i/79.0)*255))<<8) + 255;
	} // from red to yellow
	for (i=0; i<80; i++) {
		colorTable[i+81] = (1<<16) + (255<<8) + (int)((1-i/79.0)*255 + i/79.0*1);
	} // from yellow to green
	for (i=0; i<80; i++) {
		colorTable[i+161] = (((int)((1-i/79.0)*1 + (i/79.0)*255))<<16) + (255<<8) + 1;
	} // from green to turquoise
	for (i=0; i<80; i++) {
		colorTable[i+241] = (255<<16) + (((int)((1-i/79.0)*255 + (i/79.0)*1))<<8) + 1;
	} // from turquoise to blue
	for (i=0; i<80; i++) {
		colorTable[i+321] = (255<<16) + (1<<8) + (int)((1-i/79.0)*1 + i/79.0*255);
	} // from blue to purple 

	CIdbDoc* pDoc = GetDocument();
	ASSERT(pDoc != NULL);
	CString ls;
	CString le,lm;
	CString ls1, le1;

	if(pDoc->m_legend==1)
	{
		ls.Format("%d",pDoc->m_legendS);
		le.Format("%d",pDoc->m_legendE);
		ls1.Format("%d",pDoc->m_legendS + (pDoc->m_legendE - pDoc->m_legendS)/4);
		le1.Format("%d",pDoc->m_legendS + (pDoc->m_legendE - pDoc->m_legendS)*3/4);
		lm.Format("%d", pDoc->m_legendS + (pDoc->m_legendE - pDoc->m_legendS)/2);

		CPoint tempdp = LPToDP((m_dMaxX + m_dMinX)/2.0,m_dMinY);
		CPoint tempdp1;
		tempdp1.x = tempdp.x - 200;
		tempdp1.y = tempdp.y;

		pDC->TextOut(tempdp1.x,tempdp1.y+130,ls);
		pDC->TextOut(tempdp1.x+100,tempdp1.y+130,ls1);
		pDC->TextOut(tempdp1.x+200,tempdp1.y+130,lm);
		pDC->TextOut(tempdp1.x+300,tempdp1.y+130,le1);
		pDC->TextOut(tempdp1.x+400,tempdp1.y+130,le);

		int k = 0;
		for(int j=0;j<400;j++)
		{
			pDC->FillSolidRect(tempdp1.x+j,tempdp1.y+100,1,20,colorTable[k]);
			k++;
		}
	}
	
}

void CGraphView::GetMaxXY(double* dMaxX, double* dMinX, double* dMaxY, double* dMinY)
{
	*dMaxX = 0;
	*dMinX = 0;
	*dMaxY = 0;
	*dMinY = 0;
	CIdbDoc* pDoc = GetDocument();
	ASSERT(pDoc!= NULL);

    DB* dataBase =  &(pDoc->m_dataBase);
    SlistIter<Relation> relIter(*((*dataBase).m_pRelationList));
	Relation* pR;
	
	BOOL bInit = FALSE;

	while((pR = relIter())!= NULL)
	{
		const Matrix<float>* p_matrix;
		DFIter<Matrix<float> >  matrixIter(*(pR->m_tablePtr));
		while(p_matrix =  matrixIter()) 
		{ 
			Slist<ParaPoint>* pointList = p_matrix->m_pList;
			if (pointList != NULL)
			{
				Snode<ParaPoint>* nPtr = pointList->headPtr ;
				int i = 0;
				while(i < pointList->len)
				{
					ParaPoint* pPoint = (ParaPoint*)(nPtr->itemPtr);
					/*
					double dX1 = (double)(pPoint->m_fXa * p_matrix->m_nTimeS + pPoint->m_fXb);
					double dX2 = (double)(pPoint->m_fXa * p_matrix->m_nTimeE + pPoint->m_fXb);
					double dY1 = (double)(pPoint->m_fYa * p_matrix->m_nTimeS + pPoint->m_fYb);
					double dY2 = (double)(pPoint->m_fYa * p_matrix->m_nTimeE + pPoint->m_fYb);
					*/
					double dX1 = (double)(pPoint->m_fXa + pPoint->m_fXb);
					double dX2 = (double)(pPoint->m_fXa + pPoint->m_fXb);
					double dY1 = (double)(pPoint->m_fYa + pPoint->m_fYb);
					double dY2 = (double)(pPoint->m_fYa + pPoint->m_fYb);

					if (!bInit)
					{

						*dMaxX = *dMinX = dX1;
						*dMaxY = *dMinY = dY1;
						bInit = TRUE;
					}

					if (dX1 < *dMinX)
						*dMinX = dX1;
					if (dX1 > *dMaxX)
						*dMaxX = dX1;
					if (dX2 < *dMinX)
						*dMinX = dX2;
					if (dX2 > *dMaxX)
						*dMaxX = dX2;

					if (dY1 < *dMinY)
						*dMinY = dY1;
					if (dY1 > *dMaxY)
						*dMaxY = dY1;
					if (dY2 < *dMinY)
						*dMinY = dY2;
					if (dY2 > *dMaxY)
						*dMaxY = dY2;

					i++;	
					nPtr = nPtr->nextPtr ;
				}
			}
		}
	}
	dataBase->Mval=500000;//max(max(*dMaxX,*dMaxY),max(fabs(*dMinX),fabs(*dMinY)));
}


void CGraphView::DoDraw(CDC* pDC)
{
	CIdbDoc* pDoc = GetDocument();
	ASSERT(pDoc != NULL);
	
	CBrush* pBrushDemo;

	if (pDoc->m_bResetDrawObj)
	{
		pDoc->m_bResetDrawObj = FALSE;
		m_bInit = FALSE;
		OnInitialUpdate();
		m_bInit = TRUE;

		pDoc->ClearDrawObjList();
		m_selection.RemoveAll();
	}

	Relation* pR;
	POSITION pos = pDoc->m_listRelation.GetHeadPosition();

	int nNum=-1;
	while (pos != NULL)
	{
		pR = (Relation*)(pDoc->m_listRelation.GetNext(pos));
		nNum++;

		pBrushDemo = new CBrush(pR->m_color);
		CBrush* pOldBrush = pDC->SelectObject(pBrushDemo);
		CPen pen(PS_SOLID, 1, pR->m_color);
		CPen* pOldPen = pDC->SelectObject(&pen);

		switch (pR->SatisFlag())
		{
		case 1  :	//strOut = "Universally Satisfiable";
					//pDC->TextOut(0, nY+=nYStep, strOut);
					break;
		case -1 :	//strOut = "Unsatisfiable";
					//pDC->TextOut(0, nY+=nYStep, strOut);
					break;
		default :
			Matrix<float>* p_matrix;
			DFIter<Matrix<float> >  matrixIter(*(pR->m_tablePtr));
			while(p_matrix =  matrixIter()) 
			{
				
				if (!(p_matrix->m_nTimeS == -1  &&  p_matrix->m_nTimeE == -1))
				{
					if(p_matrix->m_Period!=(-1))
					{
						if(pDoc->m_nDBCurrent < p_matrix->m_PeriodStart)
							continue;
						if (((pDoc->m_nDBCurrent - p_matrix->m_PeriodStart) % p_matrix->m_Period + p_matrix->m_PeriodStart) < p_matrix->m_nTimeS  
						||  ((pDoc->m_nDBCurrent - p_matrix->m_PeriodStart) % p_matrix->m_Period + p_matrix->m_PeriodStart) > p_matrix->m_nTimeE)
							continue;
					}
					else
						if ((pDoc->m_nDBCurrent) < p_matrix->m_nTimeS  
						||  (pDoc->m_nDBCurrent) > p_matrix->m_nTimeE)
						continue;//changed by DRK
				}
				Slist<ParaPoint>* pointList = p_matrix->m_pList;
				/*  Come from relation.cpp's AddMatrix()
				if (pointList == NULL) {
					if(p_matrix->Cols() >= 4)
					{	
						if((*dataBase).GIS==TRUE && p_matrix->Cols()>5)   //RUICHEN
							;
						else
						{
							int cols = p_matrix->Cols();
							if (cols>4)
								cols --; 

							Vector<float> vec1 = Vector<float>(cols);
							Matrix<float>* p_m = new Matrix<float>();
							if((*dataBase).GIS) p_m->m_color=p_matrix->m_color;  //RUICHEN
							for(int i=0; i< p_matrix->Rows(); i++)
							{   
								if (p_matrix->Cols()==4) //Shasha: no id variable in original vector
									vec1=(*p_matrix)[i];
								else {
									if ((*p_matrix)[i][2]!=0) continue;  //Shasha: Remove id variable

									vec1[0]=(*p_matrix)[i][0];
									vec1[1]=(*p_matrix)[i][1];
									vec1[2]=(*p_matrix)[i][3];
									vec1[3]=(*p_matrix)[i][4];

									for (int nTemp=4; nTemp<cols; nTemp++)
										vec1[nTemp] = (*p_matrix)[i][nTemp+1];
								}

								(*dataBase).AddVectorToMatrix(p_m,&vec1);
							}
							
							p_matrix->m_pList = (*dataBase).HulConvt(p_m);
							delete p_m;
							pointList = p_matrix->m_pList;
						}
					}
				}
				*/
				if (pointList != NULL)
				{
					
					LPPOINT pPoints = (LPPOINT) new POINT[pointList->len];

					Snode<ParaPoint>* nPtr = pointList->headPtr ;
					int nPointCount = 0;
					for(int i=0; i < pointList->len; i++)
					{
						if (((ParaPoint*)(nPtr->itemPtr))->m_bShow)
						{
							pPoints[nPointCount] = LPToDP(((ParaPoint*)(nPtr->itemPtr))->m_fX,
													((ParaPoint*)(nPtr->itemPtr))->m_fY);
							nPointCount++;
						}
						nPtr = nPtr->nextPtr;
					}
					if (nPointCount > 0 && ((pDoc->m_dataBase).STDB==TRUE))
					{
						if (/*pointList->len*/nPointCount == 1)
						{
							pDC->SetPixel(pPoints[0], pR->m_color);
							//CSCDrawPoly
						}
						else
						{	
							//DRK
								CRect rect(((LPPOINT)pPoints)[0],((LPPOINT)pPoints)[1]);				
								pDC->Rectangle(rect);
							//pDC->Polygon((LPPOINT)pPoints, /*pointList->len*/nPointCount);
	//						p_matrix->m_pDrawObj = new CSCDrawPoly(pointList->len, pPoints);
	//						if (pDoc->m_bResetDrawObj)
	//							pDoc->AddDrawObj(p_matrix->m_pDrawObj);
						}
					}
					else
					{
						if (/*pointList->len*/nPointCount == 1)
						{
							pDC->SetPixel(pPoints[0], pR->m_color);
							//CSCDrawPoly
						}
						else
						{	//modifed by DRK for Import Line start here
							if(nPointCount==2 && pPoints[0].x==pPoints[1].x && pPoints[0].y==pPoints[1].y)
								pDC->SetPixel(pPoints[0], pR->m_color);
							else
							pDC->Polygon((LPPOINT)pPoints, /*pointList->len*/nPointCount);
	//						p_matrix->m_pDrawObj = new CSCDrawPoly(pointList->len, pPoints);
	//						if (pDoc->m_bResetDrawObj)
	//							pDoc->AddDrawObj(p_matrix->m_pDrawObj);
						}
					}
					delete [] (LPPOINT)pPoints;
				}
			}
		}
		
		if (pOldPen != NULL)
			pDC->SelectObject(pOldPen);

		if (pOldBrush != NULL)
			pDC->SelectObject(pOldBrush);

		pBrushDemo->DeleteObject();
		delete pBrushDemo;
	}

	if (pDoc->m_bResetDrawObj)	
		pDoc->m_bResetDrawObj = FALSE;

	if (m_selection.GetCount() > 0)
	{
		CSCDrawObj* pObj = (CSCDrawObj*)(m_selection.GetTail());
		if (pObj != NULL)
			pObj->Draw(this, pDC);
	}
}

void CGraphView::DoDrawDifferentMatrixColor(CDC* pDC)
{
	CIdbDoc* pDoc = GetDocument();
	ASSERT(pDoc != NULL);
	
	CBrush* pBrushDemo;

	if (pDoc->m_bResetDrawObj)
	{
		pDoc->m_bResetDrawObj = FALSE;
		m_bInit = FALSE;
		OnInitialUpdate();
		m_bInit = TRUE;

		pDoc->ClearDrawObjList();
		m_selection.RemoveAll();
	}

	Relation* pR;
	POSITION pos = pDoc->m_listRelation.GetHeadPosition();

	int nNum=-1;
	while (pos != NULL)
	{
		pR = (Relation*)(pDoc->m_listRelation.GetNext(pos));
		nNum++;

		pBrushDemo = new CBrush(pR->m_color);
		CBrush* pOldBrush = pDC->SelectObject(pBrushDemo);
		CPen pen(PS_SOLID, 1, pR->m_color);
		CPen* pOldPen = pDC->SelectObject(&pen);
		pBrushDemo->DeleteObject();
		//delete pBrushDemo;   //ylu 

		switch (pR->SatisFlag())
		{
		case 1  :	//strOut = "Universally Satisfiable";
					//pDC->TextOut(0, nY+=nYStep, strOut);
					break;
		case -1 :	//strOut = "Unsatisfiable";
					//pDC->TextOut(0, nY+=nYStep, strOut);
					break;
		default :
			Matrix<float>* p_matrix;
			DFIter<Matrix<float> >  matrixIter(*(pR->m_tablePtr));
			while(p_matrix =  matrixIter()) 
			{ 
				if (!(p_matrix->m_nTimeS == -1  &&  p_matrix->m_nTimeE == -1)
					&& 	(pDoc->m_nDBCurrent < p_matrix->m_nTimeS  
						||  pDoc->m_nDBCurrent > p_matrix->m_nTimeE))
					continue;

				pBrushDemo = new CBrush(p_matrix->m_color);
				CBrush* pOldBrush;
				pOldBrush = pDC->SelectObject(pBrushDemo);
				CPen pen(PS_SOLID, 1, p_matrix->m_color);
				pDC->SelectObject(&pen);

				Slist<ParaPoint>* pointList = p_matrix->m_pList;
				if (pointList != NULL)
				{
					LPPOINT pPoints = (LPPOINT) new POINT[pointList->len];

					Snode<ParaPoint>* nPtr = pointList->headPtr ;
					int i = 0;
					int nPointCount = 0;
					while(i < pointList->len)
					{
						if (((ParaPoint*)(nPtr->itemPtr))->m_bShow)
						{
							pPoints[nPointCount] = LPToDP(((ParaPoint*)(nPtr->itemPtr))->m_fX,
													((ParaPoint*)(nPtr->itemPtr))->m_fY);
							nPointCount++;
						}
						i++;
						nPtr = nPtr->nextPtr;
					}
					if (nPointCount > 0)
					{
						if (/*pointList->len*/nPointCount == 1)
						{
							pDC->SetPixel(pPoints[0], pR->m_color);
							//CSCDrawPoly
						}
						else
						{
							pDC->Polygon((LPPOINT)pPoints, /*pointList->len*/nPointCount);
	//						p_matrix->m_pDrawObj = new CSCDrawPoly(pointList->len, pPoints);
	//						if (pDoc->m_bResetDrawObj)
	//							pDoc->AddDrawObj(p_matrix->m_pDrawObj);
						}
					}
					delete [] (LPPOINT)pPoints;
					if (pOldBrush != NULL)
						pDC->SelectObject(pOldBrush);
					//delete pBrushDemo;   //ylu 
				}
				pBrushDemo->DeleteObject();
			}
		}
		
		if (pOldPen != NULL)
			pDC->SelectObject(pOldPen);

		if (pOldBrush != NULL)
			pDC->SelectObject(pOldBrush);

//		pBrushDemo->DeleteObject();
//		delete pBrushDemo;
	}

	if (pDoc->m_bResetDrawObj)	
		pDoc->m_bResetDrawObj = FALSE;

	if (m_selection.GetCount() > 0)
	{
		CSCDrawObj* pObj = (CSCDrawObj*)(m_selection.GetTail());
		if (pObj != NULL)
			pObj->Draw(this, pDC);
	}

	/***************************************ylu add**************************************/
 	/*********This part is used to draw legend of map*************************************/
	char strcount[10];
    char tmpstr1[100];
	Range* pRange;
    const cnTicks = 1;
	const cnHeight = 10;
	CPen penGrid(PS_SOLID, 1, RGB(192,192,292));
	CPen penCoor(PS_SOLID, 1, RGB(128,128,128));
	CPen* pOldPen = pDC->SelectObject(&penGrid);

	char cOut[24];

 	CDC dc;
	CDC* pDrawDC = pDC;

    CRect bound;
    int leng;
    pos = pDoc->m_ranges.GetHeadPosition();
   
   
   if (pos != NULL){
   	//for(pos = pDoc->m_ranges.GetHeadPosition(); pos != NULL; ) {
       for (leng = 0; leng<pDoc->m_ranges.GetCount(); leng++){
		   pRange=(Range*)pDoc->m_ranges.GetNext(pos);
           sprintf(tmpstr1,"%5.2f --- %5.2f", (*pRange).left, (*pRange).right);
		   bound =CRect(1,leng*20+1,20,20+20*leng);
		  // if(pos != NULL){
            //pDC->FillSolidRect(bound, (GetGValue((*pRange).color),GetBValue((*pRange).color),GetRValue((*pRange).color)));
              pDC->FillSolidRect(bound, (*pRange).color);
			  pDC->TextOut(22, 2+leng*20, tmpstr1);
		  // }
	   }
   }
   
   /*********************ylu end**************************************************************/
}

void CGraphView::OnDraw(CDC* pDC)
{
	CIdbDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	CDC dc;
	CDC* pDrawDC = pDC;
	CBitmap bitmap;
	CBitmap* pOldBitmap;

	// only paint the rect that needs repainting
	CRect client;
	pDC->GetClipBox(&client);

	client.InflateRect(1,1);

	CRect rect = client;
	DocToClient(rect);

	if (!pDC->IsPrinting())
	{
		// draw to offscreen bitmap for fast looking repaints
		if (dc.CreateCompatibleDC(pDC))
		{
			if (bitmap.CreateCompatibleBitmap(pDC, rect.Width(), rect.Height()))
			{
				OnPrepareDC(&dc, NULL);
				pDrawDC = &dc;

				// offset origin more because bitmap is just piece of the whole drawing
				dc.OffsetViewportOrg(-rect.left, -rect.top);
				pOldBitmap = dc.SelectObject(&bitmap);
				dc.SetBrushOrg(rect.left % 8, rect.top % 8);

				// might as well clip to the same rectangle
				dc.IntersectClipRect(client);
			}
		}
	}

	// paint background
	CBrush brush;
	if (!brush.CreateSolidBrush(RGB(255, 255, 255)))
		return;
	brush.UnrealizeObject();
	pDrawDC->FillRect(client, &brush);
	brush.DeleteObject();

	if (!pDC->IsPrinting())
		DrawCoordinator(pDrawDC, m_dMaxX, m_dMinX, m_dMaxY, m_dMinY);

	if( TRUE==pDoc->m_bSameRelationColor) 
		DoDraw(pDrawDC);
	else
		DoDrawDifferentMatrixColor(pDrawDC);
//pDrawDC->GetSafeHdc
//	DoDraw(pDC);


	if (pDrawDC != pDC)
	{
		pDC->SetViewportOrg(0, 0);
		pDC->SetWindowOrg(0,0);
		pDC->SetMapMode(MM_TEXT);

		dc.SetViewportOrg(0, 0);
		dc.SetWindowOrg(0,0);
		dc.SetMapMode(MM_TEXT);
		pDC->BitBlt(rect.left, rect.top, rect.Width(), rect.Height(),
			&dc, 0, 0, SRCCOPY);
		dc.SelectObject(pOldBitmap);
	}

	//pDCView=pDC;

	if (strcmp((char*)(((CIdbApp*)AfxGetApp())->m_graphFileName),"")!=0)
	{
		SaveImage(pDC); 
	}
	
}


void CGraphView::SaveImage(CDC* pDrawDC) 
{
    CString filename;
	filename = (char *)(((CIdbApp*)AfxGetApp())->m_graphFileName);
	//if ((int)(((CIdbApp*)AfxGetApp())->m_animationOUT)==0)
		strcpy((char*)(((CIdbApp*)AfxGetApp())->m_graphFileName),"");

	CBitmapFile obj;
	CWnd *pWnd;
	pWnd = pDrawDC->GetWindow();
	//obj.SaveDesktopAsFile("e:\\desktop.jpg", JPG_FILE);
	//obj.SaveWindowAsFile((LPCSTR)filename, pWnd, JPG_FILE);
	filename.Replace(".jpg",".bmp");
    obj.SaveWindowAsFile((LPCSTR)filename, pWnd, BMP_FILE);

	//(int)(((CIdbApp*)AfxGetApp())->m_animationOUT)=0;
}

void CGraphView::OnZoom(double dRate, int nOriX, int nOriY)
{
	CPoint pScroll = GetScrollPosition();
	m_dZoom *= dRate;
	CSize size;
	size.cx = (int)((double)(m_sizeInit.cx)*m_dZoom);
	size.cy = (int)((double)(m_sizeInit.cy)*m_dZoom);
	CSize sizePage(10,10);
	CSize sizeLine(5,5);
	SetScrollSizes(MM_TEXT, size, sizePage, sizeLine);
	m_pointOrg = CPoint(size.cx/2, size.cy/2);

	m_bResetMode = TRUE;

	RedrawWindow();

	POINT pt;
	pt.x = (long)(((double)(pScroll.x + nOriX)) * dRate);
	pt.y = (long)(((double)(pScroll.y + nOriY)) * dRate);
	ScrollToPosition(pt);
}

void CGraphView::ZoomRectZoom(CRect rect)
{
	/*
	char x1[20], x2[20], y1[20], y2[20];
	_itoa( rect.left, x1, 10);
	_itoa( rect.top, y1, 10);
	_itoa( rect.right, x2, 10);
	_itoa( rect.bottom, y2, 10);
	AfxMessageBox(x1);
	AfxMessageBox(y1);
	AfxMessageBox(x2);
	AfxMessageBox(y2);
	*/

	rect.NormalizeRect();
	CRect rectClient;
	GetClientRect(&rectClient);

	double dZoom = min(((double)(rectClient.Width()))/rect.Width(),
					   ((double)(rectClient.Height()))/rect.Height());
	if (dZoom >= 50)
	{
		AfxMessageBox("Please make a bigger box!");
		return;
	}
	if (dZoom <= 1)
	{
		RedrawWindow();
		return;
	}

	OnZoom(dZoom, rect.TopLeft().x, rect.TopLeft().y);
}

CPoint CGraphView::LPToDP(double x, double y)
{
	return CPoint(m_pointOrg.x + (int)(x*m_dZoomWin*m_dZoom),
				  m_pointOrg.y - (int)(y*m_dZoomWin*m_dZoom));
}

CPoint CGraphView::DPToLP(CPoint dp, double* dx, double* dy)
{
	CPoint pt;
	*dx = (double)(dp.x-m_pointOrg.x)/m_dZoom/m_dZoomWin;
	*dy = -(double)(dp.y-m_pointOrg.y)/m_dZoom/m_dZoomWin;
	pt.x = (int)(*dx);
	pt.y = (int)(*dy);
	return pt;
}

/////////////////////////////////////////////////////////////////////////////
// CGraphView diagnostics

#ifdef _DEBUG
void CGraphView::AssertValid() const
{
	CScrollView::AssertValid();
}

void CGraphView::Dump(CDumpContext& dc) const
{
	CScrollView::Dump(dc);
}

CIdbDoc* CGraphView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CIdbDoc)));
	return (CIdbDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CGraphView message handlers

void CGraphView::OnPrepareDC(CDC* pDC, CPrintInfo* pInfo) 
{
	CScrollView::OnPrepareDC(pDC, pInfo);

//	if (m_bResetMode)
	{
//		CSize size = GetTotalSize();
//		pDC->SetMapMode(MM_ISOTROPIC);
//		pDC->SetWindowExt(m_sizeWin);
//		pDC->SetWindowOrg(0, 0);
//		pDC->SetViewportExt(size.cx, -size.cy);
//		pDC->SetViewportOrg(size.cx/2, size.cy/2);
//		m_bResetMode = FALSE;
	}

	pDC->SetMapMode(MM_TEXT);
}

void CGraphView::OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint) 
{
	switch (lHint)
	{
	case HINT_UPDATE_WINDOW:    // redraw entire window
		Invalidate(FALSE);
		break;

	case HINT_UPDATE_DRAWOBJ:   // a single object has changed
		InvalObj((CSCDrawObj*)pHint);
		break;

	case HINT_UPDATE_SELECTION: // an entire selection has changed
		{
			CPtrList* pList = pHint != NULL ?
				(CPtrList*)pHint : &m_selection;
			POSITION pos = pList->GetHeadPosition();
			while (pos != NULL)
				InvalObj((CSCDrawObj*)(pList->GetNext(pos)));
		}
		break;

	case HINT_DELETE_SELECTION: // an entire selection has been removed
		if (pHint != &m_selection)
		{
			CPtrList* pList = (CPtrList*)pHint;
			POSITION pos = pList->GetHeadPosition();
			while (pos != NULL)
			{
				CSCDrawObj* pObj = (CSCDrawObj*)(pList->GetNext(pos));
				InvalObj(pObj);
//				Remove(pObj);   // remove it from this view's selection
			}
		}
		break;

	case HINT_UPDATE_OLE_ITEMS:
/*		{
			CSCDrawDoc* pDoc = GetDocument();
			POSITION pos = pDoc->GetObjects()->GetHeadPosition();
			while (pos != NULL)
			{
				CSCDrawObj* pObj = pDoc->GetObjects()->GetNext(pos);
				if (pObj->IsKindOf(RUNTIME_CLASS(CSCDrawOleObj)))
					InvalObj(pObj);
			}
		}
		break;
*/
	default:
		ASSERT(FALSE);
		break;
	}
}

void CGraphView::OnActivateView(BOOL bActivate, CView* pActivateView, CView* pDeactiveView) 
{
	// TODO: Add your specialized code here and/or call the base class
/*	extern DB* dataBase;
	CDocument* pDoc = (CIdbDoc*)GetDocument();
	dataBase =  &(((CIdbDoc*)pDoc)->m_dataBase);
*/	
	CScrollView::OnActivateView(bActivate, pActivateView, pDeactiveView);

}

void CGraphView::DoShowAttributions(CPoint point)
{
	CIdbDoc* pDoc = GetDocument();
	ASSERT(pDoc != NULL);

	Relation* pR;
	Matrix<float>* p_matrix;
	if (FindRelationMatrix(point, pR, p_matrix))
	{
		CString strQuery = "select * from ";
		String strName = pR->Name();
		strQuery += strName.GetText();
		strQuery += " where id=";
		char cOut[32];
		sprintf(cOut, "%.f", (*p_matrix)[0][1]);
		strQuery += cOut;
		pDoc->m_strQuery = strQuery;
		pDoc->OnRequery();
	}
}

void CGraphView::OnContextMenu(CWnd* pWnd, CPoint point) 
{
	CIdbDoc* pDoc = GetDocument();
	ASSERT(pDoc != NULL);

	CPoint pt = point;
	ScreenToClient(&pt);
	CPoint ptScroll = GetScrollPosition();
	pt.x += ptScroll.x;
	pt.y += ptScroll.y;

	Relation* pR;
	Matrix<float>* p_matrix;
	if (FindRelationMatrix(pt, pR, p_matrix))
		pDoc->ShowRelationInfo(pR, p_matrix);
}

BOOL CGraphView::FindRelationMatrix(CPoint pt, Relation*& pR, Matrix<float>*& p_matrix)
{
	BOOL bRetn = FALSE;

	CIdbDoc* pDoc = GetDocument();
	ASSERT(pDoc != NULL);
	
	POSITION pos = pDoc->m_listRelation.GetTailPosition();

	int nNum=-1;
	while (pos != NULL  &&  !bRetn)
	{
		pR = (Relation*)(pDoc->m_listRelation.GetPrev(pos));
		nNum++;

		switch (pR->SatisFlag())
		{
		case 1  :	//strOut = "Universally Satisfiable";
					//pDC->TextOut(0, nY+=nYStep, strOut);
					break;
		case -1 :	//strOut = "Unsatisfiable";
					//pDC->TextOut(0, nY+=nYStep, strOut);
					break;
		default :
			DFIter<Matrix<float> >  matrixIter(*(pR->m_tablePtr));
			while(p_matrix =  matrixIter()) 
			{ 
				if (!(p_matrix->m_nTimeS == -1  &&  p_matrix->m_nTimeE == -1)
					&& 	(p_matrix->m_nCurrent != pDoc->m_nDBCurrent))
					continue;

				Slist<ParaPoint>* pointList = p_matrix->m_pList;
				if (pointList != NULL  &&  pointList->len >= 1)
				{
					LPPOINT pPoints = (LPPOINT) new POINT[pointList->len];

					Snode<ParaPoint>* nPtr = pointList->headPtr ;
					int i = 0;
					while(i < pointList->len)
					{
						pPoints[i] = LPToDP(((ParaPoint*)(nPtr->itemPtr))->m_fX,
											((ParaPoint*)(nPtr->itemPtr))->m_fY);
//						pPoints[i].x = (long)((Point*)(nPtr->itemPtr))->m_x;
//						pPoints[i].y = (long)((Point*)(nPtr->itemPtr))->m_y;
						i++;
						nPtr = nPtr->nextPtr ;
					}
//					CPoint pt = DPToLP(point);
					CRgn rgn;
					switch (pointList->len)
					{
					case 1:	
						if (pt == pPoints[0])
							pDoc->ShowRelationInfo(pR, p_matrix);
						break;
					default:
						if (pointList->len == 2)
						{
							LPPOINT pNew = (LPPOINT) new POINT[4];
							pNew[0] = pPoints[0];
							pNew[3] = pPoints[1];
							if (pPoints[0].y == pPoints[1].y)
							{
								pNew[1].x = pPoints[0].x;
								pNew[1].y = pPoints[0].y+1;
								pNew[2].x = pPoints[1].x;
								pNew[2].y = pPoints[1].y+1;
							}
							else
							{
								pNew[1].x = pPoints[0].x+1;
								pNew[1].y = pPoints[0].y;
								pNew[2].x = pPoints[1].x+1;
								pNew[2].y = pPoints[1].y;
							}
							rgn.CreatePolygonRgn(pNew, 4, WINDING);
							delete [] (LPPOINT)pNew;
						}
						else
							rgn.CreatePolygonRgn((LPPOINT)pPoints, pointList->len, WINDING);

						if (rgn.PtInRegion(pt))
						{
							bRetn = TRUE;
							break;
						}
					}
					delete [] (LPPOINT)pPoints;
				}
				if (bRetn)
					break;
			}
		}
	}
	return bRetn;
}

void CGraphView::InvalObj(CSCDrawObj* pObj)
{
	CRect rect = pObj->m_position;
	
//	int	scale = m_zoomScale%100 ? (m_zoomScale/100 + 1): m_zoomScale/100;
	int scale = 1;

	DocToClient(rect);
	if (/*m_bActive && */IsSelected(pObj))
	{
		rect.left -= 4*scale;
		rect.top -= 5*scale;
		rect.right += 5*scale;
		rect.bottom += 4*scale;
	}
	rect.InflateRect(1, 1); // handles CDrawOleObj objects

	InvalidateRect(rect, FALSE);
}

void CGraphView::DocToClient(CRect& rect)
{
	CClientDC dc(this);
	OnPrepareDC(&dc, NULL);
	dc.LPtoDP(rect);
	rect.NormalizeRect();
}

void CGraphView::DocToClient(CPoint& point)
{
	CClientDC dc(this);
	OnPrepareDC(&dc, NULL);
	dc.LPtoDP(&point);
}

void CGraphView::ClientToDoc(CPoint& point)
{
	CClientDC dc(this);
	OnPrepareDC(&dc, NULL);
	dc.DPtoLP(&point);
}

void CGraphView::ClientToDoc(CRect& rect)
{
	CClientDC dc(this);
	OnPrepareDC(&dc, NULL);
	dc.DPtoLP(rect);
	ASSERT(rect.left <= rect.right);
	ASSERT(rect.top <= rect.top);
}

void CGraphView::OnLButtonDown(UINT nFlags, CPoint point) 
{
	//added by Kefei Wang, May 2003
	if(m_bRectmag==TRUE) {
		m_xRectmag = point.x; //added by Kefei Wang
		m_yRectmag = point.y; //added by Kefei Wang
		drawpoint[0] = drawpoint[1] =point;
		CScrollView::OnLButtonDown(nFlags, point);
		return;
	} //end May 2003

	if(CSCDrawTool::c_drawShape == poly){
		CSCDrawTool* pTool = CSCDrawTool::FindTool(CSCDrawTool::c_drawShape);
		if (pTool != NULL)
			pTool->OnLButtonDown(this, nFlags, point);
	}
	else if((CSCDrawTool::c_drawShape == line) || (CSCDrawTool::c_drawShape == rectangle)){
		if(point_num==0){
			SetCapture();

			CDC *pDC=GetDC();
			draw_mode=pDC->SetROP2(R2_NOT);

			CPoint local=point;
			ClientToDoc(local);
			drawpoint[point_num]=local;
			point_num++;
			drawpoint[point_num]=local;
		}
		else if(point_num==1){
			ReleaseCapture();

			CDC *pDC=GetDC();
			pDC->SetROP2(draw_mode);
			
			CPoint local=point;
			ClientToDoc(local);
			drawpoint[point_num]=local;
			point_num++;
		
			//Create the line relation		
			CIdbDoc* pDoc = GetDocument();
			ASSERT(pDoc != NULL);

			CDlgName dlg;
			if (dlg.DoModal() == IDOK)
			{ 
				ofstream outFile("TEMPTEMP.TXT");
				if (!outFile)
					AfxMessageBox("Internal File Error!");
				else
				{
					outFile << "begin%Temp%\n";
					outFile << dlg.m_newRelName <<"(id, x, y) :- id=1,\n";

					double x1, x2, y1, y2;
					DPToLP(drawpoint[0], &x1, &y1);
					DPToLP(drawpoint[1], &x2, &y2);

					if(CSCDrawTool::c_drawShape == line){
						//Create the line relation
						//(y2-y1)x-(x2-x1)y=x1*y2-x2*y1;

						if(x1==x2) outFile << "x=" <<x1<<",\n";
						else if(y1==y2) outFile << "y=" <<y1<<",\n";
						else if(x2>x1) outFile << y2-y1 <<"x-" <<x2-x1 <<"y=" <<x1*y2-x2*y1<<",\n";
						else outFile << y2-y1 <<"x+" <<x1-x2 <<"y=" <<x1*y2-x2*y1<<",\n";
						
						if(x1==x2){
							if(y1<=y2) outFile << "y>="<<y1<<", y<="<<y2<<".\n";
							else outFile << "y>="<<y2<<", y<="<<y1<<".\n";
						}
						else{
							if(x1<=x2) outFile << "x>="<<x1<<", x<="<<x2<<".\n";
							else outFile << "x>="<<x2<<", x<="<<x1<<".\n";
						}
					}
					else if(CSCDrawTool::c_drawShape == rectangle){
						//Create the rectangle relation

						if(x1<=x2) outFile << "x>="<<x1<<", x<="<<x2<<",\n";
						else outFile << "x>="<<x2<<", x<="<<x1<<",\n";

						if(y1<=y2) outFile << "y>="<<y1<<", y<="<<y2<<".\n";
						else outFile << "y>="<<y2<<", y<="<<y1<<".\n";
					}

					outFile << "end%Temp%\n";
					outFile.close();

					pDoc->DoCalculate("TEMPTEMP.TXT");
					pDoc->UpdateAllViews(NULL);
				}
			}
			CSCDrawTool::c_drawShape = selection;
		}		
	}
	CScrollView::OnLButtonDown(nFlags, point);
}

void CGraphView::OnLButtonUp(UINT nFlags, CPoint point) 
{
	//added by Kefei Wang, May 2003
	if(m_bRectmag==TRUE) {
		ZoomRectZoom(CRect(m_xRectmag,m_yRectmag,point.x,point.y));
		m_bRectmag = FALSE;
		m_xRectmag = m_yRectmag = 0;
		CIdbDoc* pDoc = GetDocument();
		ASSERT(pDoc != NULL);
		pDoc->UpdateAllViews(NULL);
		return;
	} //end May 2003

	if(CSCDrawTool::c_drawShape == poly){
		CSCDrawTool* pTool = CSCDrawTool::FindTool(CSCDrawTool::c_drawShape);
		if (pTool != NULL)
			pTool->OnLButtonUp(this, nFlags, point);
	}
	
	CScrollView::OnLButtonUp(nFlags, point);
}

void CGraphView::OnMouseMove(UINT nFlags, CPoint point) 
{
	//added by Kefei Wang, May 2003
	if((m_bRectmag==TRUE)&&(m_xRectmag!=0)&&(m_xRectmag!=0)) {
		CDC* pDC=GetDC();
		pDC->SetROP2(R2_NOTXORPEN);
		pDC->Rectangle(drawpoint[0].x, drawpoint[0].y, drawpoint[1].x, drawpoint[1].y);
		pDC->Rectangle(drawpoint[0].x, drawpoint[0].y, point.x, point.y);
		drawpoint[1]=point;
		CScrollView::OnMouseMove(nFlags, point);
		return;
	} //end May 2003

	CPoint pointKeep = point;
	CClientDC dc(this);
	OnPrepareDC(&dc);
	double dx, dy;
	dc.DPtoLP(&point);
	CPoint dp = DPToLP(point, &dx, &dy);

	((CMainFrame*)(AfxGetApp()->GetMainWnd()))->ShowPosition(dp, dx, dy);
	
	if(CSCDrawTool::c_drawShape == poly){
		CSCDrawTool* pTool = CSCDrawTool::FindTool(CSCDrawTool::c_drawShape);
		if (pTool != NULL)
			pTool->OnMouseMove(this, nFlags, pointKeep);
	}
	else if((CSCDrawTool::c_drawShape == line) || (CSCDrawTool::c_drawShape == rectangle)){
		if(point_num==1){
			CPoint local=point;
			ClientToDoc(local);

			CDC* pDC=GetDC();
			pDC->SetROP2(R2_NOTXORPEN);

			if(CSCDrawTool::c_drawShape == line){
				//Release the previous line
				pDC->MoveTo(drawpoint[0]);
				pDC->LineTo(drawpoint[1]);

				//Draw the line
				pDC->MoveTo(drawpoint[0]);
				pDC->LineTo(local);
			}
			else if(CSCDrawTool::c_drawShape == rectangle){				
				pDC->SelectStockObject(GRAY_BRUSH);

				//Release the previous rectangle
				pDC->Rectangle(drawpoint[0].x, drawpoint[0].y, drawpoint[1].x, drawpoint[1].y);

				//Draw the rectangle
				pDC->Rectangle(drawpoint[0].x, drawpoint[0].y, local.x, local.y);
			}
			drawpoint[1]=local;
		}
	}

	CScrollView::OnMouseMove(nFlags, point);
}

void CGraphView::OnLButtonDblClk(UINT nFlags, CPoint point) 
{
	if(CSCDrawTool::c_drawShape == poly){
		CSCDrawTool* pTool = CSCDrawTool::FindTool(CSCDrawTool::c_drawShape);
		if (pTool != NULL)
		{
			switch (pTool->m_drawShape)
			{
			case selection :
				DoShowAttributions(point);
				break;
			default :
				pTool->OnLButtonDblClk(this, nFlags, point);
				OnGenerateRel(); // After drawing polygon, genereate the relation.
				break;
			}
		}
	}
	
//	CScrollView::OnLButtonDblClk(nFlags, point);
}

void CGraphView::Select(CSCDrawObj* pObj, BOOL bAdd)
{
	if (!bAdd)
	{
		OnUpdate(NULL, NULL, NULL/*, HINT_UPDATE_SELECTION, NULL*/);
		m_selection.RemoveAll();
	}

	if (pObj == NULL || IsSelected(pObj))
		return;

	m_selection.AddTail(pObj);
	InvalObj(pObj);
}

void CGraphView::SelectWithinRect(CRect rect, BOOL bAdd)
{
	if (!bAdd)
		Select(NULL);

	ClientToDoc(rect);

	POSITION posObj = GetDocument()->m_objects.GetHeadPosition();
	while (posObj != NULL)
	{
		CSCDrawObj* pObj = (CSCDrawObj*)(GetDocument()->m_objects.GetNext(posObj));
		if (pObj->Intersects(rect))
			Select(pObj, TRUE);
	}
}

void CGraphView::Deselect(CSCDrawObj* pObj)
{
	POSITION pos = m_selection.Find(pObj);
	if (pos != NULL)
	{
		InvalObj(pObj);
		m_selection.RemoveAt(pos);
	}
}

void CGraphView::CloneSelection()
{
	POSITION pos = m_selection.GetHeadPosition();
	while (pos != NULL)
	{
		CSCDrawObj* pObj = (CSCDrawObj*)(m_selection.GetNext(pos));
		pObj->Clone(pObj->m_pDocument);
			// copies object and adds it to the document
	}
}

BOOL CGraphView::IsSelected(const CObject* pDrawObj)
{
	return m_selection.Find((void*)pDrawObj) != NULL;
}

CSCDrawObj* CGraphView::ObjectAt(const CPoint&  point)
{
	CRect rect(point, CSize(1, 1));
	POSITION pos = GetDocument()->m_objects.GetTailPosition();
	while (pos != NULL)
	{
		CSCDrawObj* pObj = (CSCDrawObj*)(GetDocument()->m_objects.GetPrev(pos));
		if (pObj->Intersects(rect))
			return pObj;
	}

	return NULL;
}

void CGraphView::OnDrawSelect() 
{
	CSCDrawTool::c_drawShape = selection;
}

void CGraphView::OnUpdateDrawSelect(CCmdUI* pCmdUI) 
{
	pCmdUI->SetRadio(CSCDrawTool::c_drawShape == selection);
}

void CGraphView::OnDrawLine() 
{
	CSCDrawTool::c_drawShape = line;
	point_num=0;
}

void CGraphView::OnDrawRect() 
{
	CSCDrawTool::c_drawShape = rectangle;
	point_num=0;
}

void CGraphView::OnDrawPoly() 
{
	CSCDrawTool::c_drawShape = poly;
}

void CGraphView::OnUpdateDrawLine(CCmdUI* pCmdUI) 
{
	pCmdUI->SetRadio(CSCDrawTool::c_drawShape == line);

	CIdbDoc* pDoc = GetDocument();
	ASSERT(pDoc!= NULL);
	pCmdUI->Enable(!(pDoc->m_dataBase.STDB));
}

void CGraphView::OnUpdateDrawRect(CCmdUI* pCmdUI) 
{
	pCmdUI->SetRadio(CSCDrawTool::c_drawShape == rectangle);

	CIdbDoc* pDoc = GetDocument();
	ASSERT(pDoc!= NULL);
	pCmdUI->Enable(!(pDoc->m_dataBase.STDB));
}

void CGraphView::OnUpdateDrawPoly(CCmdUI* pCmdUI) 
{
	pCmdUI->SetRadio(CSCDrawTool::c_drawShape == poly);

	CIdbDoc* pDoc = GetDocument();
	ASSERT(pDoc!= NULL);
	pCmdUI->Enable(!(pDoc->m_dataBase.STDB));
}

void CGraphView::OnSize(UINT nType, int cx, int cy) 
{
	CScrollView::OnSize(nType, cx, cy);
}

void CGraphView::OnGenerateRel() 
{
	CIdbDoc* pDoc = GetDocument();
	ASSERT(pDoc != NULL);

	if (m_selection.GetCount() > 0)
	{
		CSCDrawPoly* pObj = (CSCDrawPoly*)(m_selection.GetTail());

		CDlgGenN dlg(pDoc);
		if (dlg.DoModal() != IDOK)
			return;

		if ( (dlg.m_strRel).IsEmpty()  ||  (dlg.m_strID).IsEmpty())
		{
			MessageBox("Relation Name and ID must not be empty!");
			return;
		}
	
		Relation* pRel = NULL;
		DB* dataBase = &(pDoc->m_dataBase);
		if ((*dataBase).numRels) 
		{
			int nNum = 0;
			SlistIter<Relation> relationListIter(*(*dataBase).m_pRelationList);
			Relation* p_r; 
			while(p_r = (Relation*)relationListIter())
			{
				String strName = p_r->Name();
				if (strName == dlg.m_strRel)
				{
					pRel = p_r;
					break;
				}
				nNum++;
			}
		}

		BOOL b_existR = TRUE;
		if (pRel == NULL)
		{
			    String s = String(dlg.m_strRel);
		    	pRel = new Relation(s);
				b_existR = FALSE;
		}
		float id = (float)atof(dlg.m_strID);
		pRel = PointsToConstraints(pRel, pObj, id);
		pRel->m_Arity = 3;
		if(!b_existR)
		{
		   pRel->m_strAtriList.AddTail(CString("i"));
		   pRel->m_strAtriList.AddTail(CString("x"));
		   pRel->m_strAtriList.AddTail(CString("y"));
	       dataBase->numRels++;
           dataBase->m_pRelationList->AppendHere(*pRel);
		}
		
		pDoc->m_bResetDrawObj = TRUE;
		pDoc->UpdateAllViews(NULL);
	}
}

void CGraphView::OnUpdateGenerateRel(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(m_selection.GetCount() > 0);
}

Relation* CGraphView::PointsToConstraints(Relation*   p_r, 
										  CSCDrawPoly* Obj, float id)
{	
	CIdbDoc* pDoc = GetDocument();
	ASSERT(pDoc != NULL);
	Relation* pRel = NULL;
	DB* dataBase = &(pDoc->m_dataBase);
	Point p[3];
	double dx, dy;
	switch (Obj->m_nPoints) 
	{
	case 0:
		return p_r;
	case 1:
		DPToLP(Obj->m_points[0], &dx, &dy);
		p[0].m_x = (float)dx;
		p[0].m_y = (float)dy;
		p[1].m_x = (float)dx;
		p[1].m_y = (float)dy;
		p[2].m_x = (float)dx;
		p[2].m_y = (float)dy;
		p_r->AddMatrix(*(dataBase->GetMatrixFromIDPoints(id, p[0], p[1], p[2])));
		return p_r;
	case 2:
		DPToLP(Obj->m_points[0], &dx, &dy);
		p[0].m_x = (float)dx;
		p[0].m_y = (float)dy;
		DPToLP(Obj->m_points[1], &dx, &dy);
		p[1].m_x = (float)dx;
		p[1].m_y = (float)dy;
		p[2].m_x = (float)dx;
		p[2].m_y = (float)dy;
		p_r->AddMatrix(*(dataBase->GetMatrixFromIDPoints(id, p[0], p[1], p[2])));
		return p_r;
	default:
		for(int i = 1; i<= (Obj->m_nPoints-2); i++)
		{
			DPToLP(Obj->m_points[0], &dx, &dy);
			p[0].m_x = (float)dx;
			p[0].m_y = (float)dy;
			DPToLP(Obj->m_points[i], &dx, &dy);
			p[1].m_x = (float)dx;
			p[1].m_y = (float)dy;
			DPToLP(Obj->m_points[i+1], &dx, &dy);
			p[2].m_x = (float)dx;
			p[2].m_y = (float)dy;
			p_r->AddMatrix(*(dataBase->GetMatrixFromIDPoints(id, p[0], p[1], p[2])));
        }
		return p_r; 				
	}	
	return p_r;
}


void CGraphView::saveImageInfo(CString fileName)
{

	//SaveImage(pDCView);
		CIdbDoc* pDoc = GetDocument();
		ASSERT(pDoc != NULL);
		m_bInit = FALSE;
		OnInitialUpdate();
		m_bInit = TRUE;
		pDoc->ClearDrawObjList();
		m_selection.RemoveAll();

	return;

}


void CGraphView::ownLineTo(HDC hdc, int x1, int y1, int x2, int y2)
{
	CBrush* pBrushDemo;

	pBrushDemo = new CBrush();
	pBrushDemo->CreateSolidBrush(RGB(200,123,55));
	CBrush* pOldBrush = (CBrush*)::SelectObject(hdc,pBrushDemo);
	CPen pen(PS_SOLID, 1, RGB(192,192,292));
	CPen* pOldPen = (CPen*)::SelectObject(hdc,&pen);

	double k,d;
	double dx1,dx2,dy1,dy2;
	
	dx1=x1;
	dx2=x2;
	dy1=y1;
	dy2=y2;

	int minx,miny,maxx,maxy;

	if (x1>=x2)
	{
		minx=x2;
		maxx=x1;
	}
	else
	{
		minx=x1;
		maxx=x2;
	}

	if (y1>=y2)
	{
		miny=y2;
		maxy=y1;
	}
	else
	{
		miny=y1;
		maxy=y2;
	}

	if (x1==x2)
	{
		for (int y=miny; y<=maxy; y++)
		{
			::SetPixel(hdc,x1,y,RGB(192,100,247));
		}

		return;
	}


	k = (dy1-dy2)/(dx1-dx2);

	d = (dy2*dx1-dx2*dy1)/(dx1-dx2);


	for (int x=minx; x<=maxx; x++)
	{
		for (int y=miny; y<=maxy; y++)
		{
			float y_temp = (float)(k*x+d);
			if (abs(y_temp-y)<=0.5)
				::SetPixel(hdc,x,y,RGB(192,100,247));
		}
	}

}

