// IdbView.cpp : implementation file
//

#include "stdafx.h"
#include "idb.h"

#include "db.h"
#include "relation.h"
#include "slist.h"
#include <fstream.h>
#include "IdbDoc.h"
#include "OwnListBox.h"
#include "IdbView.h"
#include "MainFrm.h"

#include "DlgArea.h"
#include "DlgArea2.h"
#include "DlgBuffer.h"
#include "DlgName.h"
#include "DlgBlock.h"
//#include "DlgNegation.h"  //Shasha

#include "DlgBuffer.h"  //RUICHEN
#include "DlgColor.h"   //RUICHEN

#include "Render.h"   // Syed
#include "OnSetReg.h" // Syed
#include "DlgApproximation.h" //SRA TJP

extern float anglebetn(float,float);
extern float rect_area(float,float,float,float);
extern bool ImportLineFlag;		//global flag for Import Line

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

COLORREF CIdbView::colorList[] = { RGB(242, 168, 13),
								RGB(0,  0, 255),
							    RGB(0, 255, 0),
								RGB(255, 0,   128),
								RGB(255, 128,  64),
								RGB(  0, 255, 255),
								RGB(  0, 128, 128),
								RGB(  0, 128, 192),
								RGB(255,   0, 255),
								RGB(  0,  64, 128),
								RGB( 64,   0, 192),
								RGB(128,  64,  64)
							};

/////////////////////////////////////////////////////////////////////////////
// CIdbView

IMPLEMENT_DYNCREATE(CIdbView, CFormView)

CIdbView::CIdbView()
	: CFormView(CIdbView::IDD)
{
	//{{AFX_DATA_INIT(CIdbView)
	//}}AFX_DATA_INIT
}

CIdbView::~CIdbView()
{
}

void CIdbView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CIdbView)
	DDX_Control(pDX, IDC_LIST1, m_listRecord);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CIdbView, CFormView)
	//{{AFX_MSG_MAP(CIdbView)
	ON_WM_SIZE()
	ON_LBN_SELCHANGE(IDC_LIST1, OnSelchangeList1)
	ON_WM_CONTEXTMENU()
	ON_COMMAND(ID_OP_INTERSECTION, OnOpIntersection)
	ON_COMMAND(ID_OP_UNION, OnOpUnion)
	ON_COMMAND(ID_OP_AREA, OnOpArea)
	ON_COMMAND(ID_BUFFER, OnBuffer)
	ON_COMMAND(ID_OP_COMPLEMENT, OnOpComplement)
	ON_COMMAND(ID_OP_MINUS, OnOpMinus)
	ON_COMMAND(ID_OP_BLOCK, OnOpBlock)
	ON_COMMAND(ID_OP_COLLIDE, OnOpCollide)
	ON_COMMAND(ID_COLOR_RELATION, OnColorRelation)
	ON_UPDATE_COMMAND_UI(ID_COLOR_RELATION, OnUpdateColorRelation)
	ON_COMMAND(ID_OP_COLOR, OnOpColor)
	ON_UPDATE_COMMAND_UI(ID_OP_COMPLEMENT, OnUpdateOpComplement)
	ON_UPDATE_COMMAND_UI(ID_OP_MINUS, OnUpdateOpMinus)
	ON_COMMAND(ID_REGRESION, OnRegresion)
	ON_COMMAND(ID_BUTTON_DEL, OnDel_Relations)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CIdbView diagnostics

#ifdef _DEBUG
void CIdbView::AssertValid() const
{
	CFormView::AssertValid();
}

void CIdbView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}

CIdbDoc* CIdbView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CIdbDoc)));
	return (CIdbDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CIdbView message handlers

void CIdbView::OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint) 
{
	CIdbDoc* pDoc = GetDocument();
	ASSERT(pDoc!= NULL);
	DB* pDataBase = &(pDoc->m_dataBase);

	int test = m_listRecord.GetCount();
	
	if (pDataBase->numRels != m_listRecord.GetCount()  ||  pDoc->m_bAddRelation)
	{
		pDoc->m_listRelation.RemoveAll();
		SetupList();
		pDoc->m_bAddRelation = FALSE;
	}
	else
		CFormView::OnUpdate(pSender, lHint, pHint);  //hugew
}

void CIdbView::SetupList()
{
	CIdbDoc* pDoc = GetDocument();
	ASSERT(pDoc!= NULL);

	DB* dataBase = &(pDoc->m_dataBase);
	
	if (!(*dataBase).numRels) 
		return; 
	else
	{
		m_listRecord.ResetContent();
		int nNum = 0;
		SlistIter<Relation> relationListIter(*(*dataBase).m_pRelationList);
		//const Relation* p_r1;
		Relation* p_r; 
		while(p_r = (Relation*)relationListIter())
		{
			CString strOut("");
			String strName = p_r->Name();

			if (ImportLineFlag==TRUE)	// for Import Line
			{
				strOut += " ";
				strOut += (p_r->m_sName).GetText();
				goto out;
			}							// until here and also out was added

			//strOut += "'";
			strOut += strName.GetText();
			//strOut += "'  Arity: ";
			if(p_r->SatisFlag()==0)
			{
				char cTemp[20];
				//sprintf(cTemp, "%d ", p_r->Arity());
				//strOut += cTemp;
				sprintf(cTemp, " (%d rows)", p_r->NumberOfMatrixes());
				strOut += cTemp;
			}
			else if(p_r->SatisFlag()==1)
                strOut += " (univeral Satisfiable)";
			else  
				strOut += " (0 row)";

out:
			sprintf(p_r->m_sOutput, "%s", strOut);
			m_listRecord.AddString(p_r->m_sOutput);

			if (!pDoc->m_bColorRead)
			{
					p_r->m_colorStart = GetDrawColor(nNum);
					p_r->m_colorEnd = p_r->m_colorStart;
					p_r->m_color = p_r->m_colorStart;
			}
			p_r->m_color = p_r->m_colorStart;
			if(!(*dataBase).GIS)	SetMatrixColor(p_r);    //RUICHEN modify
			//SetMatrixColor(p_r);
			nNum++;
       }
	}
}


void CIdbView::SetMatrixColor(Relation* pR)
{

	if( pR->SatisFlag() != SATISFIABLE ) 
		return;
	Matrix<float>* p_matrix;
	DFIter<Matrix<float> >  matrixIter(*(pR->m_tablePtr));
	while(p_matrix =  matrixIter()) 
	{    
//		p_matrix->Trace(); 
		if((*dataBase).GIS) p_matrix->m_color=pR->m_color;  // RUICHEN add
		else p_matrix->m_color = GetDrawColor(  (int)(*p_matrix)[0][1] ); 
	};
	return;			
}

void CIdbView::OnInitialUpdate() 
{
	CRect rect;
	GetWindowRect(&rect);
	LPARAM lp;
	lp = (LPARAM)((long)(rect.Size().cy)*65536 + rect.Size().cx);
	PostMessage(WM_SIZE, 0, lp);

	CFormView::OnInitialUpdate();

	SetupList();
}


void CIdbView::OnSize(UINT nType, int cx, int cy) 
{
	CFormView::OnSize(nType, cx, cy);
	
	SetScrollSizes(MM_TEXT, CSize(cx, cy));

	if (m_listRecord.m_hWnd != NULL)
	{
//		CRect rect;
//		m_listRecord.GetWindowRect(&rect);
//		CPoint p = rect.TopLeft();
//		m_listRecord.SetWindowPos(&wndTop, p.x, p.y, cx-p.x, cy-p.y, SWP_SHOWWINDOW);
//		m_listRecord.MoveWindow(p.x, p.y, cx-p.x, cy-p.y, TRUE);
		m_listRecord.MoveWindow(0, 0, cx, cy, TRUE);
	}
}

void CIdbView::OnSelchangeList1() 
{
	CIdbDoc* pDoc = GetDocument();
	ASSERT(pDoc != NULL);

//	AfxMessageBox("OK");

	int nNewSel = m_listRecord.GetSelCount();
	int nOldSel = pDoc->m_listRelation.GetCount();
	//ASSERT(abs(nNewSel-nOldSel)==1);  //--->WSS: Allow multiselection in one process

	// If none of the selections changed, stop here.
	// If you continue, you'll crash
	if( nNewSel == nOldSel )
		return;
	BOOL bAdd = (nNewSel > nOldSel);
	CPtrList listCopy;
	POSITION pos = pDoc->m_listRelation.GetHeadPosition();
	while (pos != NULL)
		listCopy.AddTail(pDoc->m_listRelation.GetNext(pos));

    DB* dataBase =  &(pDoc->m_dataBase);
    SlistIter<Relation> relIter(*((*dataBase).m_pRelationList));
	Relation* pR;

	for (int i=0; i<m_listRecord.GetCount(); i++)
	{
		pR = relIter();
		if (m_listRecord.GetSel(i))
		{
			POSITION pos = listCopy.Find(pR);
			if (pos != NULL)
				listCopy.RemoveAt(pos);
			else
			{	
				pDoc->m_listRelation.AddTail(pR);
				//break;     //--->WSS: Allow multiselection in one process
			}
		}
	}

	if (!bAdd)
	{
		//ASSERT(listCopy.GetCount()==1);
		if (listCopy.GetCount()>0)
		{
		Relation* pRelation = (Relation*)listCopy.GetHead();
		POSITION pos = pDoc->m_listRelation.Find(pRelation);
		ASSERT(pos != NULL);
		pDoc->m_listRelation.RemoveAt(pos);
		}
	}
	
	if (pDoc->m_listRelation.GetCount() > 0)
	{
		Relation* pR = (Relation*)(pDoc->m_listRelation.GetTail());
		CString strQuery = "select * from ";
		String strName = pR->Name();
		strQuery += strName.GetText();
		pDoc->m_strQuery = strQuery;
		pDoc->OnRequery();
	}		

//	pDoc->m_bResetDrawObj = TRUE;
	pDoc->UpdateAllViews(this);
}

void CIdbView::OnContextMenu(CWnd* pWnd, CPoint point) 
{
	ScreenToClient(&point);

	int nColorOrInfo;
	int nNum = m_listRecord.GetIndex(point, &nColorOrInfo);

	if (nNum != -1)
	{
		CIdbDoc* pDoc = GetDocument();
		ASSERT(pDoc != NULL);

		DB* dataBase =  &(pDoc->m_dataBase);
		SlistIter<Relation> relIter(*((*dataBase).m_pRelationList));
		Relation* pR;

		int i=0;
		pR = relIter();
		while (i < nNum)
		{	
			pR = relIter();
			i++;
		}

		if (nColorOrInfo == 1)		// color
		{
			COLORREF colorStart = pR->m_colorStart;
			CColorDialog dlg(colorStart);
			dlg.DoModal();
			colorStart = dlg.GetColor();
			if (colorStart != pR->m_colorStart)
			{
				pR->m_colorStart = colorStart;
				pR->m_color = colorStart;
				pDoc->UpdateAllViews(NULL);
				colorList[i] = colorStart;

				if((*dataBase).GIS){
					pR->m_bSameMatrixColor=true;  //RUICHEN
					SetMatrixColor(pR);   //RUICHEN
				}
//				pDoc->SetModifiedFlag();
			}
		}
		else if (nColorOrInfo == 2)		// info
		{	
			CIdbDoc* pDoc = GetDocument();
			ASSERT(pDoc != NULL);
			pDoc->ShowRelationInfo(pR, NULL);
		}
		else if (nColorOrInfo == 3)		// colorEnd
		{
			COLORREF colorEnd = pR->m_colorEnd;
			CColorDialog dlg(colorEnd);
			dlg.DoModal();
			colorEnd = dlg.GetColor();
			if (colorEnd != pR->m_colorEnd)
			{
				pR->m_colorEnd = colorEnd;
				pDoc->UpdateAllViews(NULL);
//				pDoc->SetModifiedFlag();
				colorList[i] = colorEnd;
			}
		}
	}
}


void CIdbView::OnOpIntersection() 
{
	CIdbDoc* pDoc = GetDocument();
	ASSERT(pDoc != NULL);
	if((pDoc->m_dataBase).STDB==TRUE)
	{
		if (pDoc->m_listRelation.GetCount() < 2)
		{
			AfxMessageBox("You should select at least 2 relations!");
			return;
		}

		//add intersection op.
		Relation* pR;
		POSITION pos = pDoc->m_listRelation.GetHeadPosition();


		//RUI CHEN add for name
		CDlgName dlg;
		if (dlg.DoModal() == IDOK)
		{ 
			CString str = dlg.m_newRelName;
		
			//const String s = String("tempInters");
			const String s = dlg.m_newRelName;


			//const String s = String((char *)str);"tempInter");
			//Relation* ptempRel =  new Relation((String)s);  
			Relation* ptempRel;  
			//ptempRel->m_Satisfiable = -1;//DRK
			
			ptempRel = (Relation*)(pDoc->m_listRelation.GetNext(pos));//memory problem here!!

			while (pos != NULL)
			{
				pR = (Relation*)(pDoc->m_listRelation.GetNext(pos));
				ptempRel = ptempRel->RelationIntersect(pR);
			}
			ptempRel->m_sName=(String)s;
			DB* dataBase = &(pDoc->m_dataBase);

			if(ptempRel->NumberOfMatrixes()==0)
				ptempRel->m_Satisfiable = -1;

			ptempRel->m_strAtriList.AddTail(CString("i"));
			ptempRel->m_strAtriList.AddTail(CString("x1"));
			ptempRel->m_strAtriList.AddTail(CString("y1"));
			ptempRel->m_strAtriList.AddTail(CString("x2"));
			ptempRel->m_strAtriList.AddTail(CString("y2"));
			ptempRel->m_strAtriList.AddTail(CString("t"));
			ptempRel->m_strAtriList.AddTail(CString("p"));
			ptempRel->m_strAtriList.AddTail(CString("s"));

			dataBase->numRels++;
			dataBase->m_pRelationList->GotoTail();		//new line 6/23
			dataBase->m_pRelationList->AppendHere(*ptempRel);
			pDoc->SetMatrixTime(dataBase);//DRK	
			pDoc->m_nDBCurrent=pDoc->m_nDBTimeS - 1;//DRK
			pDoc->DoReCalculate(pDoc->m_nDBTimeS);//DRK	
			//later modify this to recalculate for just 
			//the new relation instead of all DRK
		//	pDoc->m_bResetDrawObj = TRUE;
			pDoc->UpdateAllViews(NULL);
		}
	}
	else
	{
		if (pDoc->m_listRelation.GetCount() < 2)
		{
			AfxMessageBox("You should select at least 2 relations!");
			return;
		}

		//add intersection op.
		Relation* pR;
		POSITION pos = pDoc->m_listRelation.GetHeadPosition();

		//RUI CHEN add for name
		CDlgName dlg;
		if (dlg.DoModal() == IDOK)
		{ 
			CString str = dlg.m_newRelName;
		
			//const String s = String("tempInters");
			const String s = dlg.m_newRelName;


			Relation* ptempRel =  new Relation(s);
			
			while (pos != NULL)
			{
				pR = (Relation*)(pDoc->m_listRelation.GetNext(pos));
				ptempRel = ptempRel->CombineRelation(pR);
			}
			DB* dataBase = &(pDoc->m_dataBase);



			
			ptempRel->m_strAtriList.AddTail(CString("i"));
			ptempRel->m_strAtriList.AddTail(CString("x"));
			ptempRel->m_strAtriList.AddTail(CString("y"));
			dataBase->numRels++;
			dataBase->m_pRelationList->AppendHere(*ptempRel);
				
				
		//	pDoc->m_bResetDrawObj = TRUE;
			pDoc->UpdateAllViews(NULL);
		}
	}
}



void CIdbView::OnOpUnion() 
{
	CIdbDoc* pDoc = GetDocument();
	ASSERT(pDoc != NULL);
	if((pDoc->m_dataBase).STDB==TRUE)
	{
		int timeS=32000,timeE=0;//DRK

		if (pDoc->m_listRelation.GetCount() < 2)
		{
			AfxMessageBox("You should select at least 2 relations!");
			return;
		}

		//add union op.
		Relation* pR;
		POSITION pos = pDoc->m_listRelation.GetHeadPosition();

		//RUI CHEN add for name
		CDlgName dlg;
		if (dlg.DoModal() == IDOK)
		{ 
			CString str = dlg.m_newRelName;
		
			//const String s = String("tempInters");
			const String s = dlg.m_newRelName;


			//const String s = String("tempUnion");
			Relation* ptempRel =  new Relation((String)s);  
			ptempRel->m_Satisfiable = -1;
			ptempRel->m_nTimeS=timeS;//DRK
			ptempRel->m_nTimeE=timeE;//DRK
			
			while (pos != NULL)
			{
				pR = (Relation*)(pDoc->m_listRelation.GetNext(pos));
				if(pR->NumberOfMatrixes()!=0)
					ptempRel->UnionRelation(pR);
				ptempRel->m_nTimeS=min(ptempRel->m_nTimeS,pR->m_nTimeS);//DRK
				ptempRel->m_nTimeE=max(ptempRel->m_nTimeE,pR->m_nTimeE);//DRK
			}
			DB* dataBase = &(pDoc->m_dataBase);



			
			ptempRel->m_strAtriList.AddTail(CString("i"));
			ptempRel->m_strAtriList.AddTail(CString("x1"));
			ptempRel->m_strAtriList.AddTail(CString("y1"));
			ptempRel->m_strAtriList.AddTail(CString("x2"));
			ptempRel->m_strAtriList.AddTail(CString("y2"));
			ptempRel->m_strAtriList.AddTail(CString("t"));
			ptempRel->m_strAtriList.AddTail(CString("p"));
			ptempRel->m_strAtriList.AddTail(CString("s"));

			dataBase->numRels++;
			dataBase->m_pRelationList->GotoTail();		//new line 6/23
			dataBase->m_pRelationList->AppendHere(*ptempRel);
			pDoc->SetMatrixTime(dataBase);//DRK	
			pDoc->m_nDBCurrent=pDoc->m_nDBTimeS - 1;//DRK
			pDoc->DoReCalculate(pDoc->m_nDBTimeS);//DRK	
			//later modify this to recalculate for just 
			//the new relation instead of all DRK
		//	pDoc->m_bResetDrawObj = TRUE;
			pDoc->UpdateAllViews(NULL);
		}
	}
	else
	{
		if (pDoc->m_listRelation.GetCount() < 2)
		{
			AfxMessageBox("You should select at least 2 relations!");
			return;
		}

		//add union op.
		Relation* pR;
		POSITION pos = pDoc->m_listRelation.GetHeadPosition();
		
		//RUI CHEN add for name
		CDlgName dlg;
		if (dlg.DoModal() == IDOK)
		{ 
			CString str = dlg.m_newRelName;
		
			//const String s = String("tempInters");
			const String s = dlg.m_newRelName;


			Relation* ptempRel =  new Relation(s);  
			ptempRel->m_Satisfiable = -1;

			
			while (pos != NULL)
			{
				pR = (Relation*)(pDoc->m_listRelation.GetNext(pos));
				ptempRel->UnionRelation(pR);
			}
			DB* dataBase = &(pDoc->m_dataBase);



			
			ptempRel->m_strAtriList.AddTail(CString("i"));
			ptempRel->m_strAtriList.AddTail(CString("x"));
			ptempRel->m_strAtriList.AddTail(CString("y"));
			dataBase->numRels++;
			dataBase->m_pRelationList->AppendHere(*ptempRel);
				
				
		//	pDoc->m_bResetDrawObj = TRUE;
			pDoc->UpdateAllViews(NULL);
		}
	}
}

void CIdbView::OnOpArea() 
{
	CIdbDoc* pDoc = GetDocument();
	ASSERT(pDoc != NULL);
	if((pDoc->m_dataBase).STDB==TRUE)
	{
		if (pDoc->m_listRelation.GetCount() != 1)
		{
			AfxMessageBox("You should select 1 relation!");
			return;
		}
		
		int mTime;
		float mArea=0.0;
		
		CDlgArea2 dlg;
		if (dlg.DoModal() == IDOK)
			mTime=(int)dlg.m_Time;
		else
			return;

		Relation* pR = (Relation*)(pDoc->m_listRelation.GetHead());
		mArea=pR->GetArea(mTime);

		char strarea[100];
		sprintf(strarea,"Area at t = %d : \n%.2f sq. units",mTime,mArea);
		AfxMessageBox(strarea);
		
		//	pDoc->m_bResetDrawObj = TRUE;
		pDoc->UpdateAllViews(NULL);
	}
	else
	{
		if (pDoc->m_listRelation.GetCount() != 1)
		{
			AfxMessageBox("You should select one relation!");
			return;
		}

		CDlgArea dlg;
		if (dlg.DoModal() != IDOK)
			return;

		//RUI CHEN add for name
		CDlgName dlg_name;
		if (dlg_name.DoModal() == IDOK)
		{ 
			CString str = dlg_name.m_newRelName;
		
			//const String s = String("tempInters");
			const String output_name = dlg_name.m_newRelName;

			// add area caculation

			Relation* pR = (Relation*)(pDoc->m_listRelation.GetHead());
			ASSERT(pR != NULL);
			String strName = pR->Name();
			pDoc->m_dataBase.AreaHandler3(output_name, strName, (float)(dlg.m_dStep), (float)(dlg.m_dMinX), (float)(dlg.m_dMaxX));


		//	pDoc->m_bResetDrawObj = TRUE;
			pDoc->UpdateAllViews(NULL);
		}
	}
}

void CIdbView::OnBuffer() 
{
	// TODO: Add your command handler code here
	CIdbDoc* pDoc = GetDocument();
	ASSERT(pDoc != NULL);

	if (pDoc->m_listRelation.GetCount() != 1)
	{
		AfxMessageBox("You should select one relation!");
		return;
	}

	CDlgBuffer dlg(pDoc);
	if (dlg.DoModal() != IDOK)
		return;

	// add buffer

	Relation* pR = (Relation*)(pDoc->m_listRelation.GetHead());
	ASSERT(pR != NULL);
	String strName = pR->Name();
	String strD = String( dlg.m_strRel);
	pDoc->m_dataBase.BuffHandler(strName, strD, dlg.m_fDistance );


	pDoc->m_bResetDrawObj = TRUE;
	pDoc->UpdateAllViews(NULL);	
}

CString DoNegation(CString cs)
{
	if (cs.Replace(">=","<")==0) 
	{if (cs.Replace("<=",">")==0)
	{if (cs.Replace("<",">=")==0)
	{if (cs.Replace(">","<=")==0)
	;}}}
	return cs;
}

void RecurTuples(int tp_no, CString bound, FILE * fp_out, CString * cs, int * tp, int* cst, CString head)
{
	if ((tp[tp_no]==0)&&(tp_no!=0)) { //end of tuples
		fwrite(head, strlen(head), 1,fp_out);
		fputc(0x0a,fp_out);
		CString Temp;
		fwrite(bound, strlen(bound), 1,fp_out);
		for (int i=0; i<tp_no-1; i++){
			Temp = DoNegation(cs[cst[i]])+",";
			fwrite(Temp, strlen(Temp), 1,fp_out);
			fputc(0x0a,fp_out);
		}
		Temp = DoNegation(cs[cst[i]])+".";
		fwrite(Temp, strlen(Temp), 1,fp_out);
		fputc(0x0a,fp_out);
		//fwrite(" ", strlen(" "), 1,fp_out);
		//fputc(0x0a,fp_out);
	}
	else {
		if (tp[tp_no+1]>0)
		for(int i=tp[tp_no]; i<tp[tp_no+1]; i++){
			cst[tp_no] = i;
			RecurTuples(tp_no+1, bound, fp_out, cs, tp, cst, head);
		}
		else
		for(int i=tp[tp_no]; (i<100)&&(cs[i]!=""); i++){
			cst[tp_no] = i;
			RecurTuples(tp_no+1, bound, fp_out, cs, tp, cst, head);
		}
	}
}

static double myfValidGraduations[] =
{
	0.01, 0.02, 0.05, 0.1, 0.2, 0.5, 1, 2, 5, 10, 20, 50, 100, 200, 500, 1000, 2000, 5000, 10000, 100000, 1000000, 10000000, 0
};

double myGetTickValue(double fMaxValue, int nNumDiv)
{
	// Determine values for vertical ticks
	double fValuePerTick = fMaxValue / nNumDiv;
	for (int i = 0; myfValidGraduations[i] > 0; i++)
		if (myfValidGraduations[i] >= fValuePerTick)
			return myfValidGraduations[i];
	return myfValidGraduations[i-1];
}

void CIdbView::OnOpComplement() 
{
	CIdbDoc* pDoc = GetDocument();
	ASSERT(pDoc != NULL);

	if (pDoc->m_listRelation.GetCount() != 1)
	{
		AfxMessageBox("You should select 1 relation!");
		return;
	}

	Relation* pR;
	POSITION pos = pDoc->m_listRelation.GetHeadPosition();

	CDlgName dlg;
	CString s;

	if (dlg.DoModal() == IDOK)
		s = dlg.m_newRelName;
	else
		return;


	if (!(pDoc->m_dataBase).STDB){
    Relation* ptpRel;  
	ptpRel = (Relation*)(pDoc->m_listRelation.GetNext(pos));//memory problem here!!
	
	CString cs_Param2;
	cs_Param2 = ptpRel->m_sName.GetText() ;
	//AfxMessageBox(cs_Param2);
	DB* dataBase = &(pDoc->m_dataBase);
	if (!(*dataBase).numRels) 
		return; 
	else
	{
	SlistIter<Relation> relationListIter(*(*dataBase).m_pRelationList);
	Relation* p_r; 
	while(p_r = (Relation*)relationListIter())
	{
		CString strOut("");
		String strName = p_r->Name();
		strOut = strName.GetText();
		//AfxMessageBox(strOut);
		if (cs_Param2==strOut)
		{
			//AfxMessageBox(strOut) ;
			//pView->m_listRecord.SetSel(IncludeIdx,true);
			FILE * fp_out;
			if ((fp_out = fopen("wsstmp.txt","wt"))==NULL)
			{
				AfxMessageBox("Error creating file !");
				return;
			}

			pDoc->SaveRelationInfo(p_r, NULL, fp_out);
			fclose(fp_out);
			break;
		}

	}
	}
		FILE * fp_in;
		if ((fp_in = fopen("wsstmp.txt","rt"))==NULL)
		{
			AfxMessageBox("Error creating file !");
			return;
		}
		else {
			int ct, i;
			CString line;
			char ch;

			CString head;
			CString cs[100]; //Number of constraint in Original relation must less than 100
			int tp[100];
			int cst[100];

			//int nn=100;
			//CString *cs = new CString(nn); //WSS
			//int *tp = new int(nn);
			//int *cst= new int(nn);

			line="";
			head="";
			ct=0;
			for (i=0; i<100; i++){
				cs[i]="";
				tp[i]=0;
				cst[i]=0;
			}

			i=0;
			ch = (char)fgetc(fp_in);
			while( !feof( fp_in ) ){
			if (ch!=0x0a)
				line += ch;
			else{
				//AfxMessageBox(line);
				if (((line.Find(",")==-1)&&(line.Find(".")==-1))||((line.Find("x")==-1)&&(line.Find("y")==-1)))
					;
				else if (line.Find(":-")>0){
					if ( head==""){
						int tpi;
						tpi = line.Find('(',0);
						CString id_str;
						id_str = line.Mid(tpi+1, line.Find(',',0)-tpi-1);
						head = line.Left(tpi);
						line.Replace(head, s);
						head = line.Left(line.GetLength()-1);
					}
					tp[ct]=i;
					ct++;
				}
				else{
					cs[i] = line.Left(line.GetLength()-2);
					i++;
				}
				line="";
			}
			ch = (char)fgetc(fp_in);
			}

			FILE * fp_out;
			if ((fp_out = fopen("wsstmp1.txt","wt"))==NULL)
			{
				AfxMessageBox("Error creating file !");
				return;
			}
			
			fwrite("begin %temp%",strlen("begin %temp%"),1,fp_out);
			fputc(0x0a,fp_out);
/////////Find Max and Min value//////////////////////////////////////
/*
	double dMaxX = 0;
	double dMinX = 0;
	double dMaxY = 0;
	double dMinY = 0;
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
					double dX1 = (double)(pPoint->m_fXa * p_matrix->m_nTimeS + pPoint->m_fXb);
					double dX2 = (double)(pPoint->m_fXa * p_matrix->m_nTimeE + pPoint->m_fXb);
					double dY1 = (double)(pPoint->m_fYa * p_matrix->m_nTimeS + pPoint->m_fYb);
					double dY2 = (double)(pPoint->m_fYa * p_matrix->m_nTimeE + pPoint->m_fYb);

					if (!bInit)
					{
						dMaxX = dMinX = dX1;
						dMaxY = dMinY = dY1;
						bInit = TRUE;
					}

					if (dX1 < dMinX)
						dMinX = dX1;
					if (dX1 > dMaxX)
						dMaxX = dX1;
					if (dX2 < dMinX)
						dMinX = dX2;
					if (dX2 > dMaxX)
						dMaxX = dX2;

					if (dY1 < dMinY)
						dMinY = dY1;
					if (dY1 > dMaxY)
						dMaxY = dY1;
					if (dY2 < dMinY)
						dMinY = dY2;
					if (dY2 > dMaxY)
						dMaxY = dY2;

					i++;	
					nPtr = nPtr->nextPtr ;
				}
			}
		}
	}
	double dXRange = max(fabs(dMaxX), fabs(dMinX));
	double dYRange = max(fabs(dMaxY), fabs(dMinY));

	double dTickX = myGetTickValue(dXRange, 4);
	double dTickY = myGetTickValue(dYRange, 4);
	double dTick = max(dTickX, dTickY);

	dXRange = max(dXRange, dTick*4);
	dYRange = max(dYRange, dTick*4);

  */
	char number[10];
	CString bound_cst;
	bound_cst = "";
	_gcvt( 50000, 7, number );
	bound_cst += "x>=-" + (CString)number +"0, x<=" + (CString)number +"0,";
	_gcvt( 50000, 7, number );
	bound_cst += "y>=-" + (CString)number +"0, y<=" + (CString)number +"0,";
	/*
	CDlgNegation dlg;
	if (dlg.DoModal() == IDOK) {
	CString bound_cst;
	bound_cst += "x>=-" + dlg.m_XRange +", x<=" + dlg.m_XRange +",";
	bound_cst += "y>=-" + dlg.m_YRange +", y<=" + dlg.m_YRange +",";
	*/
	//AfxMessageBox(bound_cst);
///////////////////////////////////////////////

			RecurTuples(0, bound_cst, fp_out, cs, tp, cst, head);

			fwrite("end %temp%",strlen("end %temp%"),1,fp_out);
			fclose(fp_out);
			pDoc->DoCalculate("wsstmp1.txt");
			pDoc->UpdateAllViews(NULL);
		}
	}
	//}
	else {

	//const String s = String((char *)str);"tempInter");
    //Relation* ptempRel =  new Relation((String)s);  
    Relation* ptempRel;  
	//ptempRel->m_Satisfiable = -1;//DRK
	
	ptempRel = (Relation*)(pDoc->m_listRelation.GetNext(pos));//memory problem here!!
	pR = ptempRel->RelationComplement(ptempRel);
	
	pR->m_sName=(String)s;
	//DB* dataBase = &(pDoc->m_dataBase);

	if(pR->NumberOfMatrixes()==0)
		pR->m_Satisfiable = -1;

	pR->m_strAtriList.AddTail(CString("i"));
	pR->m_strAtriList.AddTail(CString("x1"));
	pR->m_strAtriList.AddTail(CString("y1"));
	pR->m_strAtriList.AddTail(CString("x2"));
	pR->m_strAtriList.AddTail(CString("y2"));
	pR->m_strAtriList.AddTail(CString("t"));
	pR->m_strAtriList.AddTail(CString("p"));
	pR->m_strAtriList.AddTail(CString("s"));

	dataBase->numRels++;
	dataBase->m_pRelationList->GotoTail();		//new line 6/23
    dataBase->m_pRelationList->AppendHere(*pR);
	pDoc->SetMatrixTime(dataBase);//DRK	
	pDoc->m_nDBCurrent=pDoc->m_nDBTimeS - 1;//DRK
	pDoc->DoReCalculate(pDoc->m_nDBTimeS);//DRK	
	//later modify this to recalculate for just 
	//the new relation instead of all DRK
//	pDoc->m_bResetDrawObj = TRUE;
	pDoc->UpdateAllViews(NULL);
	}
}

void CIdbView::OnOpMinus() 
{
	// TODO: Add your command handler code here
	CIdbDoc* pDoc = GetDocument();
	ASSERT(pDoc != NULL);

	if (!(pDoc->m_dataBase).STDB){
		AfxMessageBox("This function is noly for PReSTO databases!");
		return;
	}

	if (pDoc->m_listRelation.GetCount() != 2)
	{
		AfxMessageBox("You should select 2 relations!");
		return;
	}

	Relation* pR;
	POSITION pos = pDoc->m_listRelation.GetHeadPosition();

	CDlgName dlg;
	CString s;
	if (dlg.DoModal() == IDOK)
		s = dlg.m_newRelName;
	else
		return;

	//const String s = String((char *)str);"tempInter");
    //Relation* ptempRel =  new Relation((String)s);  
    Relation* ptempRel;  
	//ptempRel->m_Satisfiable = -1;//DRK
	
	ptempRel = (Relation*)(pDoc->m_listRelation.GetNext(pos));//memory problem here!!
	pR=(Relation*)(pDoc->m_listRelation.GetNext(pos));
	
	pR = pR->RelationComplement(pR);
	ptempRel=ptempRel->RelationIntersect(pR);
	
	ptempRel->m_sName=(String)s;
	DB* dataBase = &(pDoc->m_dataBase);

	if(ptempRel->NumberOfMatrixes()==0)
		ptempRel->m_Satisfiable = -1;

	ptempRel->m_strAtriList.AddTail(CString("i"));
	ptempRel->m_strAtriList.AddTail(CString("x1"));
	ptempRel->m_strAtriList.AddTail(CString("y1"));
	ptempRel->m_strAtriList.AddTail(CString("x2"));
	ptempRel->m_strAtriList.AddTail(CString("y2"));
	ptempRel->m_strAtriList.AddTail(CString("t"));
	ptempRel->m_strAtriList.AddTail(CString("p"));
	ptempRel->m_strAtriList.AddTail(CString("s"));

	dataBase->numRels++;
	dataBase->m_pRelationList->GotoTail();		//new line 6/23
    dataBase->m_pRelationList->AppendHere(*ptempRel);
	pDoc->SetMatrixTime(dataBase);//DRK	
	pDoc->m_nDBCurrent=pDoc->m_nDBTimeS - 1;//DRK
	pDoc->DoReCalculate(pDoc->m_nDBTimeS);//DRK	
	//later modify this to recalculate for just 
	//the new relation instead of all DRK
//	pDoc->m_bResetDrawObj = TRUE;
	pDoc->UpdateAllViews(NULL);
}



	

void CIdbView::OnOpBlock() 
{
	CIdbDoc* pDoc = GetDocument();
	ASSERT(pDoc != NULL);
	if (!(pDoc->m_dataBase).STDB){
		AfxMessageBox("This function is noly for PReSTO databases!");
		return;
	}

	if (pDoc->m_listRelation.GetCount() != 2)
	{
		AfxMessageBox("You should select 2 relations!");
		return;
	}

	Relation* pR;
	POSITION pos = pDoc->m_listRelation.GetHeadPosition();

	CDlgBlock dlg;
	CString s;
	int mTime;
	if (dlg.DoModal() == IDOK)
	{
		s = dlg.m_strName;
		mTime=dlg.m_Time;
	}
	else
		return;

	//const String s = String((char *)str);"tempInter");
    //Relation* ptempRel =  new Relation((String)s);  
    Relation* ptempRel;  
	//ptempRel->m_Satisfiable = -1;//DRK
	
	ptempRel = (Relation*)(pDoc->m_listRelation.GetNext(pos));//memory problem here!!
	pR=(Relation*)(pDoc->m_listRelation.GetNext(pos));
	
	//pR = pR->RelationComplement(pR);
	//ptempRel=ptempRel->RelationIntersect(pR);

	//ptempRel=ptempRel->RelationBlock(pR,mTime);  //Mengchu deleted
	ptempRel=ptempRel->RelationBlockRelation(pR,mTime); //Mengchu added

	ptempRel->m_sName=(String)s;
	DB* dataBase = &(pDoc->m_dataBase);

	if(ptempRel->NumberOfMatrixes()==0)
		ptempRel->m_Satisfiable = -1;
	else
	{
		DFIter<Matrix<float> > matIter(*(ptempRel->m_tablePtr));
		Matrix<float>* mat;
		while(mat=matIter())
		{
			mat->m_nTimeS=mTime;
			(*mat)[5][1]=(float)((-1)*mTime);
		}
	}

	ptempRel->m_strAtriList.AddTail(CString("i"));
	ptempRel->m_strAtriList.AddTail(CString("x1"));
	ptempRel->m_strAtriList.AddTail(CString("y1"));
	ptempRel->m_strAtriList.AddTail(CString("x2"));
	ptempRel->m_strAtriList.AddTail(CString("y2"));
	ptempRel->m_strAtriList.AddTail(CString("t"));
	ptempRel->m_strAtriList.AddTail(CString("p"));
	ptempRel->m_strAtriList.AddTail(CString("s"));

	dataBase->numRels++;
	dataBase->m_pRelationList->GotoTail();		//new line 6/23
    dataBase->m_pRelationList->AppendHere(*ptempRel);
	pDoc->SetMatrixTime(dataBase);//DRK	
	pDoc->m_nDBCurrent=pDoc->m_nDBTimeS - 1;//DRK
	pDoc->DoReCalculate(pDoc->m_nDBTimeS);//DRK	
	//later modify this to recalculate for just 
	//the new relation instead of all DRK
//	pDoc->m_bResetDrawObj = TRUE;
	pDoc->UpdateAllViews(NULL);
}

void CIdbView::OnOpCollide() 
{
	float m1,m2,tc;
	CIdbDoc* pDoc = GetDocument();
	ASSERT(pDoc != NULL);
	if (!(pDoc->m_dataBase).STDB){
		AfxMessageBox("This function is noly for PReSTO databases!");
		return;
	}

	if (pDoc->m_listRelation.GetCount() != 2)
	{
		AfxMessageBox("You should select 2 relations!");
		return;
	}

	Relation* pR;
	POSITION pos = pDoc->m_listRelation.GetHeadPosition();

	CDlgName dlg;
	CString s;
	if (dlg.DoModal() == IDOK)
		s = dlg.m_newRelName;
	else
		return;

    	//const String s = String((char *)str);"tempInter");
		//Relation* ptempRel =  new Relation((String)s);  
		Relation* m_tmp;  
		//ptempRel->m_Satisfiable = -1;//DRK
		
		m_tmp = (Relation*)(pDoc->m_listRelation.GetNext(pos));//memory problem here!!
		Relation *ptempRel=new Relation();
		m1=(*(m_tmp->m_tablePtr->Cur()))[9][1];
		while (pos != NULL)
		{
			pR = (Relation*)(pDoc->m_listRelation.GetNext(pos));
			m2=(*(pR->m_tablePtr->Cur()))[9][1];
			ptempRel = m_tmp->RelationIntersect(pR);
		}

	ptempRel->m_sName="tempinter";//(String)s;
	DB* dataBase = &(pDoc->m_dataBase);

	if(ptempRel->NumberOfMatrixes()==0)
	{
		ptempRel->m_Satisfiable = -1;
		return;
	}

	ptempRel->m_strAtriList.AddTail(CString("i"));
	ptempRel->m_strAtriList.AddTail(CString("x1"));
	ptempRel->m_strAtriList.AddTail(CString("y1"));
	ptempRel->m_strAtriList.AddTail(CString("x2"));
	ptempRel->m_strAtriList.AddTail(CString("y2"));
	ptempRel->m_strAtriList.AddTail(CString("t"));
	ptempRel->m_strAtriList.AddTail(CString("p"));
	ptempRel->m_strAtriList.AddTail(CString("s"));
	ptempRel->m_strAtriList.AddTail(CString("m"));
	
	dataBase->numRels++;
	dataBase->m_pRelationList->GotoTail();		//new line 6/23
    dataBase->m_pRelationList->AppendHere(*ptempRel);
	pDoc->SetMatrixTime(dataBase);				//DRK	
	ptempRel=(Relation *)dataBase->RetrieveRelation("tempinter");
	tc=(float)ptempRel->m_nTimeS;						//got the time of collision tc
	dataBase->DeleteRelation("tempinter");
	dataBase->numRels--;
	float vx1,vy1,vx2,vy2;
	vx1=(*(m_tmp->m_tablePtr->Cur()))[1][7] * (-1);
	vy1=(*(m_tmp->m_tablePtr->Cur()))[2][7] * (-1);
	vx2=(*(pR->m_tablePtr->Cur()))[1][7] * (-1);
	vy2=(*(pR->m_tablePtr->Cur()))[2][7] * (-1);
	float x1,y1,x2,y2,xt1,yt1,xt2,yt2,xt3,yt3,xt4,yt4;
	xt1=(*(m_tmp->m_tablePtr->Cur()))[1][1] - (*(m_tmp->m_tablePtr->Cur()))[1][7] * tc;
	yt1=(*(m_tmp->m_tablePtr->Cur()))[2][1] - (*(m_tmp->m_tablePtr->Cur()))[2][7] * tc;
	xt2=(*(m_tmp->m_tablePtr->Cur()))[3][1] - (*(m_tmp->m_tablePtr->Cur()))[3][7] * tc;
	yt2=(*(m_tmp->m_tablePtr->Cur()))[4][1] - (*(m_tmp->m_tablePtr->Cur()))[4][7] * tc;
	x1=(xt1+xt2)/2;								//coordinates of centre of mass1
	y1=(yt1+yt2)/2;
	xt3=(*(pR->m_tablePtr->Cur()))[1][1] - (*(pR->m_tablePtr->Cur()))[1][7] * tc;
	yt3=(*(pR->m_tablePtr->Cur()))[2][1] - (*(pR->m_tablePtr->Cur()))[2][7] * tc;
	xt4=(*(pR->m_tablePtr->Cur()))[3][1] - (*(pR->m_tablePtr->Cur()))[3][7] * tc;
	yt4=(*(pR->m_tablePtr->Cur()))[4][1] - (*(pR->m_tablePtr->Cur()))[4][7] * tc;
	x2=(xt3+xt4)/2;								//coordinates of centre of mass2
	y2=(yt3+yt4)/2;

	float slope=(y2-y1)/(x2-x1);
	float tangent=(-1)/slope;
	float theta1,theta2,mag1,mag2,ang1,ang2;
	ang1=(float)atan(vy1/vx1);
	ang2=(float)atan(vy2/vx2);
	theta1=anglebetn(slope,vy1/vx1);
	theta2=anglebetn(slope,vy2/vx2);
	mag1=(float)sqrt(vx1*vx1+vy1*vy1);
	mag2=(float)sqrt(vx2*vx2+vy2*vy2);
	float oldv1,oldv2;
	oldv1= (float) (mag1 * cos(theta1));
	oldv2= (float) (mag2 * cos(theta2));
	
	int sx1,sy1,sx2,sy2;
	if(slope>0)
	{
		if(vx1>=0 && vy1>=0) {}
		if(vx1<0 && vy1<0) oldv1=(-1)*oldv1;
		if(vx1>=0 && vy1<0) {if(ang1<tangent) oldv1=(-1)*oldv1;}
		if(vx1<0 && vy1>=0) {if(ang1>tangent) oldv1=(-1)*oldv1;}
		if(vx2>=0 && vy2>=0) {}
		if(vx2<0 && vy2<0) oldv2=(-1)*oldv2;
		if(vx2>=0 && vy2<0) {if(ang2<tangent) oldv2=(-1)*oldv2;}
		if(vx2<0 && vy2>=0) {if(ang2>tangent) oldv2=(-1)*oldv2;}

		float newv1,newv2,newang1,newang2;
		newv1=oldv1*(m1-m2)/(m1+m2) + oldv2*2*m2/(m1+m2);
		newv2=oldv1*2*m1/(m1+m2) + oldv2*(m2-m1)/(m1+m2);
		
		newv1=newv1-oldv1;
		newv2=newv2-oldv2;

		if(newv1>=0)	{sx1=1;sy1=1;}
		if(newv1<0)		{sx1=-1;sy1=-1;newv1=(float)fabs(newv1);}
		if(newv2>=0)	{sx2=1;sy2=1;}
		if(newv2<0)		{sx2=-1;sy2=-1;newv2=(float)fabs(newv2);}

		newang1=(float)atan(slope);
		newang2=(float)atan(slope);
		
		float newvx1,newvx2,newvy1,newvy2;
		newvx1=vx1 + sx1*newv1*(float)fabs(cos(newang1));
		newvy1=vy1 + sy1*newv1*(float)fabs(sin(newang1));
		newvx2=vx2 + sx2*newv2*(float)fabs(cos(newang2));
		newvy2=vy2 + sy2*newv2*(float)fabs(sin(newang2));
		ptempRel=new Relation();
		ptempRel=ptempRel->RelationCollide(m_tmp,pR,newvx1,newvy1,newvx2,newvy2,tc,xt1,yt1,xt2,yt2,xt3,yt3,xt4,yt4);
	}
	if(slope<0)
	{
		if(vx1>=0 && vy1>=0) {if(ang1<tangent) oldv1=(-1)*oldv1;}
		if(vx1<0 && vy1<0) {if(ang1>tangent) oldv1=(-1)*oldv1;}
		if(vx1>=0 && vy1<0) oldv1=(-1)*oldv1;
		if(vx1<0 && vy1>=0) {};
		if(vx2>=0 && vy2>=0) {if(ang2<tangent) oldv2=(-1)*oldv2;}
		if(vx2<0 && vy2<0) {if(ang2>tangent) oldv2=(-1)*oldv2;}
		if(vx2>=0 && vy2<0) oldv2=(-1)*oldv2;
		if(vx2<0 && vy2>=0) {};

		float newv1,newv2,newang1,newang2;
		newv1=oldv1*(m1-m2)/(m1+m2) + oldv2*2*m2/(m1+m2);
		newv2=oldv1*2*m1/(m1+m2) + oldv2*(m2-m1)/(m1+m2);
		
		newv1=newv1-oldv1;
		newv2=newv2-oldv2;

		if(newv1>=0)	{sx1=-1;sy1=1;}
		if(newv1<0)		{sx1=1;sy1=-1;newv1=(float)fabs(newv1);}
		if(newv2>=0)	{sx2=-1;sy2=1;}
		if(newv2<0)		{sx2=1;sy2=-1;newv2=(float)fabs(newv2);}

		newang1=(float)atan(slope);
		newang2=(float)atan(slope);
		
		float newvx1,newvx2,newvy1,newvy2;
		newvx1=vx1 + sx1*newv1*(float)fabs(cos(newang1));
		newvy1=vy1 + sy1*newv1*(float)fabs(sin(newang1));
		newvx2=vx2 + sx2*newv2*(float)fabs(cos(newang2));
		newvy2=vy2 + sy2*newv2*(float)fabs(sin(newang2));
		ptempRel=new Relation();
		ptempRel=ptempRel->RelationCollide(m_tmp,pR,newvx1,newvy1,newvx2,newvy2,tc,xt1,yt1,xt2,yt2,xt3,yt3,xt4,yt4);
	}
	ptempRel->Trace();
	ptempRel->m_sName=(String)s;

	if(ptempRel->NumberOfMatrixes()==0)
	{
		ptempRel->m_Satisfiable = -1;
		return;
	}
	ptempRel->m_strAtriList.AddTail(CString("i"));
	ptempRel->m_strAtriList.AddTail(CString("x1"));
	ptempRel->m_strAtriList.AddTail(CString("y1"));
	ptempRel->m_strAtriList.AddTail(CString("x2"));
	ptempRel->m_strAtriList.AddTail(CString("y2"));
	ptempRel->m_strAtriList.AddTail(CString("t"));
	ptempRel->m_strAtriList.AddTail(CString("p"));
	ptempRel->m_strAtriList.AddTail(CString("s"));
	ptempRel->m_strAtriList.AddTail(CString("m"));
	dataBase->numRels++;
	dataBase->m_pRelationList->GotoTail();		//new line 6/23
    dataBase->m_pRelationList->AppendHere(*ptempRel);
	pDoc->SetMatrixTime(dataBase);//DRK	
	pDoc->m_nDBCurrent=pDoc->m_nDBTimeS - 1;//DRK
	pDoc->DoReCalculate(pDoc->m_nDBTimeS);//DRK	
	//later modify this to recalculate for just 
	//the new relation instead of all DRK
//	pDoc->m_bResetDrawObj = TRUE;
	pDoc->UpdateAllViews(NULL);
}

void CIdbView::OnColorRelation()  //RUICHEN
{
	CIdbDoc* pDoc = GetDocument();
	ASSERT(pDoc!= NULL);

	//add color op.
	Relation *pr, *ptempRel;
	DB* dataBase = &(pDoc->m_dataBase);
	POSITION pos = pDoc->m_listRelation.GetHeadPosition();
	const String s = String("Color_");
	
	while (pos != NULL)
	{
		pr = (Relation*)(pDoc->m_listRelation.GetNext(pos));
		if(pr->m_Arity < 4) continue;

		ptempRel =  new Relation(s + pr->m_sName);  
		//ptempRel->m_Satisfiable = 0;
		//ptempRel->evalFlag = pr->evalFlag;
		

		ptempRel->MakeColorRelation(pr, &(pDoc->m_ranges));
		ptempRel->m_Arity=(pr->m_Arity > 3 ? 3 : pr->m_Arity-1);
		ptempRel->m_strAtriList.AddTail(CString("i"));
		ptempRel->m_strAtriList.AddTail(CString("x"));
		ptempRel->m_strAtriList.AddTail(CString("y"));
		
		//dataBase->numRels++;
		//dataBase->m_pRelationList->AppendHere(*ptempRel);

		//RUICHEN add
		dataBase->numRels++;
		dataBase->m_pRelationList->GotoTail();		//new line 6/23
		dataBase->m_pRelationList->AppendHere(*ptempRel);
		pDoc->SetMatrixTime(dataBase);//DRK	
		pDoc->m_nDBCurrent=pDoc->m_nDBTimeS - 1;//DRK
		pDoc->DoReCalculate(pDoc->m_nDBTimeS);//DRK	
		pDoc->m_bResetDrawObj = TRUE;
		pDoc->UpdateAllViews(NULL);

		//RUICHEN end
	}

	//pDoc->UpdateAllViews(NULL);
}


void CIdbView::OnOpColor()  //RUICHEN
{
	CIdbDoc* pDoc = GetDocument();
	ASSERT(pDoc != NULL);

	CDlgColor aDlgColor(pDoc);
	if(aDlgColor.DoModal()!=IDOK)
		return;

}

void CIdbView::OnUpdateColorRelation(CCmdUI* pCmdUI)  //RUICHEN
{
	CIdbDoc* pDoc = GetDocument();
	ASSERT(pDoc != NULL);

	pCmdUI->Enable(pDoc->m_ranges.GetCount()>0);	
}

void CIdbView::OnUpdateOpComplement(CCmdUI* pCmdUI) 
{
	//Shasha: Make available also in MLPQ
	//CIdbDoc* pDoc = GetDocument();
	//ASSERT(pDoc != NULL);

	//pCmdUI->Enable((pDoc->m_dataBase).STDB);
}

void CIdbView::OnUpdateOpMinus(CCmdUI* pCmdUI) 
{
	CIdbDoc* pDoc = GetDocument();
	ASSERT(pDoc != NULL);

	pCmdUI->Enable((pDoc->m_dataBase).STDB);
}


void CIdbView::OnRegresion() 
{
	// TODO: Add your command handler code here

//	fstream out;
//	out.open("lilo.txt",ios::out);

	COLORREF colorTable[410];
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
	
	if (pDoc->m_listRelation.GetCount() != 1)
	{
		AfxMessageBox("You should select one relation!");
		return;
	}
	
	
	Render ren(pDoc);	
	
	if (ren.DoModal() != IDOK)
		return;
	
	SlistIter<Relation> relIter( *(pDoc->m_dataBase.m_pRelationList) );

	Relation* pR;
	Relation* pR1;
	POSITION pos1 = pDoc->m_listRelation.GetHeadPosition();
	String RelName;
	while (pos1 != NULL)
	{
		pR1 = (Relation*)(pDoc->m_listRelation.GetNext(pos1));
		RelName = pR1->Name();
	}
				
	char idValue[1000][100];
	int idvk = 0;
	int idvi = 0;
	CString AttryInfo("");
	
	while(pR =relIter()) 
	{
		Matrix<float>* p_matrix;
		p_matrix = NULL;
		BOOL bShowR = (p_matrix==NULL);
		CString strOut("");
		String strName = pR->Name();

		if(!strcmp(RelName.GetText(),strName.GetText()))
		{
		
			DFIter<Matrix<float> >  matrixIter;
			if (bShowR)
			{
				matrixIter = DFIter<Matrix<float> >(*(pR->m_tablePtr));
				p_matrix =  matrixIter();
			}
			char chktemp[100];
			while (p_matrix != NULL )
			{
				CString tito("");
				CString Artito("");
				POSITION pos = pR->m_strAtriList.GetHeadPosition();
				int i = pR->m_strAtriList.GetCount();
				while (pos != NULL)
				{
					pR->m_strAtriList.GetNext(pos);
					if (i-- >1 );
				}
				pDoc->GetEquationInfo(pR, p_matrix, tito);
				pDoc->UpdateAllViews(NULL);
				pDoc->GetAttryInfo(pR , p_matrix,Artito);
				if (bShowR)
					p_matrix =  matrixIter();
				else
					break;

				int flag = 0;
				char * temp = (char *) (LPCTSTR) tito;
				strtok(temp,",");
				if(!strcmp(temp,chktemp))
					continue;
				for(size_t i1=0;i1<strlen(temp);i1++)
				{
					if(temp[i1]=='=')
					{
						flag = 1;
						continue;
					}
					if(flag == 1)
						idValue[idvi][idvk++]= temp[i1];
					if(i1==0)
						AttryInfo +=Artito;
				}
				idvi++;
				idvk = 0;
				strcpy(chktemp,temp);
			}
		}
	}

	char * temp = (char *) (LPCTSTR) AttryInfo;
	strtok(temp,")");
	
	char Attr[1000];
	int ati = 0;
	int flag = 0;
	for(size_t i1=0;i1<strlen(temp);i1++)
	{
		if(temp[i1]=='(')
		{
			flag = 1;
			continue;
		}
		if(flag == 1)
			Attr[ati++]= temp[i1];
	}
	Attr[ati] = '\0';
	
	CString  ChangeRel[1000];
	int cri = 0;

	ofstream outFile("TEMPTEMP.TXT");
	if (!outFile)
		AfxMessageBox("Internal File Error!");
	else
	{
		outFile << "begin%Temp%\n";
		outFile << "Temp(t) :- t >=" <<ren.m_StartTime <<", t <= "<<ren.m_EndTime <<"."<<endl; 
		int tempdup = 0;
		for(int i=0;i<idvi;i++)
		{
			if(tempdup==atoi(idValue[i]))
				continue;
			outFile << RelName<<atoi(idValue[i])<<"(" << Attr << ") :- " << RelName <<"(" << Attr << "), id = "<<atoi(idValue[i])<<", Temp(t)."<<endl;
			ChangeRel[cri] += CString(RelName.GetText());
//			ChangeRel[cri] +="_";
			ChangeRel[cri++] +=(idValue[i]);
			tempdup = atoi(idValue[i]);
			
		}
		outFile << "\nend%Temp%\n";
		outFile.close();
		pDoc->DoCalculate("TEMPTEMP.TXT");
		pDoc->UpdateAllViews(NULL);
	}


// Sleep(400);

	CIdbDoc* pDoc1 = GetDocument();
	ASSERT(pDoc1 != NULL);

	Relation* pR2;
	float maxpvalue = 0;
	float minpvalue = 0;
	float pValueS[1000];
	float pValueE[1000];
	int pvaluesi = 0;
	int pvalueei = 0;

	SlistIter<Relation> relIter1( *(pDoc1->m_dataBase.m_pRelationList) );
	
	while(pR2 =relIter1()) 
	{
		String strName;
		Matrix<float>* p_matrix;
		p_matrix = NULL;
		BOOL bShowR = (p_matrix==NULL);
		CString strOut("");
		
		DFIter<Matrix<float> >  matrixIter;
		if (bShowR)
		{
			matrixIter = DFIter<Matrix<float> >(*(pR2->m_tablePtr));
			p_matrix =  matrixIter();
		}
		
		while (p_matrix != NULL )
		{
			strName = pR2->Name();
			{
				POSITION pos = pR2->m_strAtriList.GetHeadPosition();
				int i = pR2->m_strAtriList.GetCount();
				while (pos != NULL)
				{
					//char temp[100];
					pR->m_strAtriList.GetNext(pos);
					if (i-- >1 );
				}
				pDoc->GetEquationInfo(pR2, p_matrix, strOut);
				if (bShowR)
					p_matrix =  matrixIter();
				else
					break;
			}
		}

//		out << strOut << endl;

		for(int i2=0;i2<cri;i2++)
		{
			char tChangeRel[100];
			int tcr=0;
			for(int i3=0;i3<ChangeRel[i2].GetLength();i3++)
			{
				if(ChangeRel[i2][i3]==' ')
					continue;
				tChangeRel[tcr++]=ChangeRel[i2][i3];
			}
			tChangeRel[tcr]='\0';
			if(!strcmp(tChangeRel,strName.GetText()))
			{
				char tempBuffer[100];
				int flag =0;
				int k=0;
				for(int i1=0;i1<strOut.GetLength();i1++)
				{
					if(strOut[i1]==' ') continue;
					if(strOut[i1]==',')
					{
						tempBuffer[k]='\0';
						for(size_t j=0;j<strlen(tempBuffer);j++)
						{
							if(tempBuffer[j]=='t')
							{
								flag = 1;
								break;
							}
						}
						k=0;
						if(flag ==1)
							break;
						continue;
					}
					tempBuffer[k++]=strOut[i1];
				}
				char equation[10][100];
				int ek=0;
				int ei=0;
				for(size_t i=0;i<strlen(tempBuffer);i++)
				{
					if(tempBuffer[i] >='a' && tempBuffer[i] <='z')
					{
						equation[ei][ek]='\0';
						ek=0;
						ei++;
						continue;
					}
					if(tempBuffer[i]=='=')
					{
						equation[ei][ek]='\0';
						ek=0;
						ei++;
						continue;
					}
					equation[ei][ek++]=tempBuffer[i];
				}
				equation[ei][ek]='\0';
				float b;
				if(atof(equation[1])==0)
				{
					if(equation[1][0]=='-')
						b = -1;
					else
						b = 1;
				}
				else
					b = (float)atof(equation[1]); 
				
				double Start = (float) (atof(equation[3]) - atof(equation[0])*atof(ren.m_StartTime)) / (float) b ;
				double End = (float) (atof(equation[3]) - atof(equation[0])*atof(ren.m_EndTime)) / (float) b ;
						
				pValueS[pvaluesi++] = (float)Start;
				pValueE[pvalueei++] = (float)End;

//				pR2->m_colorStart = colorTable[(int)abs((int)Start % 400)];
//				pR2->m_colorEnd = colorTable[(int)abs((int)End % 400)];
//				pR2->m_color = pR2->m_colorStart;
				pDoc1->UpdateAllViews(NULL);
			}
		}
	}



	minpvalue = pValueS[0];
	maxpvalue = pValueE[0];

	for(int xpx=1;xpx<pvaluesi;xpx++)
		if(pValueS[xpx] < minpvalue)
			minpvalue = pValueS[xpx];

	for(int xpy=1;xpy<pvalueei;xpy++)
		if(pValueE[xpy] > maxpvalue)
			maxpvalue = pValueE[xpy];


	CIdbDoc* pDoc2 = GetDocument();
	ASSERT(pDoc2 != NULL);
	SlistIter<Relation> relIter2( *(pDoc2->m_dataBase.m_pRelationList) );

	Relation* pR3;
	int pvs = 0;
	int pve = 0;
	while(pR3 =relIter2()) 
	{
		for(int i2=0;i2<cri;i2++)
		{
		char tChangeRel[100];
		int tcr=0;
		for(int i3=0;i3<ChangeRel[i2].GetLength();i3++)
		{
			if(ChangeRel[i2][i3]==' ')
				continue;
			tChangeRel[tcr++]=ChangeRel[i2][i3];
		}
		tChangeRel[tcr]='\0';
		String strName = pR3->Name();
		if(!strcmp(tChangeRel,strName.GetText()))
		{
			double S = (pValueS[pvs] - minpvalue) / ( maxpvalue - minpvalue) * 400 ; 
			double E = (pValueE[pve] - minpvalue) / ( maxpvalue - minpvalue) * 400 ; 
			if((int)E == 400)
				E = 399;
			pR3->m_colorStart = colorTable[(int) S];
			pR3->m_colorEnd = colorTable[(int) E];
			pR3->m_color = pR3->m_colorStart;
			pvs++;
			pve++;
		}
		}
	}

	pDoc->m_nDBTimeS = atoi(ren.m_StartTime);
	pDoc->m_nDBTimeE = atoi(ren.m_EndTime);

	pDoc->m_legendS = (int)minpvalue;
	pDoc->m_legendE = (int)maxpvalue;
	pDoc->UpdateAllViews(NULL);
	pDoc->m_legend = 1;
	pDoc->RemoveRelation("Temp");

}



void CIdbView::OnActivateView(BOOL bActivate, CView* pActivateView, CView* pDeactiveView) 
{
	// TODO: Add your specialized code here and/or call the base class
	((CIdbApp*)AfxGetApp())->p_View = this;

//	AfxMessageBox("OK");
	CFormView::OnActivateView(bActivate, pActivateView, pDeactiveView);
}

void CIdbView::callSelChange()
{
	//OnUpdate(this, 0, NULL);
		OnSelchangeList1();
}

void CIdbView::callColorRelation()
{
	OnColorRelation();
}

void CIdbView::OnDel_Relations()
{
	CIdbDoc* pDoc = GetDocument();
	ASSERT(pDoc != NULL);

	DB* dataBase = &(pDoc->m_dataBase);
	if (!(*dataBase).numRels) 
		return; 
	else	{
		if (m_listRecord.GetSelCount()==0)
		{
			AfxMessageBox("No relation selected!");
			return;
		}
		SlistIter<Relation> relationListIter(*(*dataBase).m_pRelationList);
		Relation* p_r; 
		int i=0;
		CString OutMsg="Are you sure you want to REMOVE all following relations?\n";
		CString Rels("");
		while(p_r = (Relation*)relationListIter())
		{
			if (m_listRecord.GetSel(i))
			{
			CString strOut("");
			String strName = p_r->Name();
			strOut = strName.GetText();
			OutMsg += "    "+strOut+"\n";
			Rels += strOut+";";
			//AfxMessageBox(strOut);
			}
			i++;
		}
		i=0;
		int j=0;
		CString str;
		if (AfxMessageBox(OutMsg, MB_OKCANCEL)==IDOK)
		{
			while (true)
			{
				i= Rels.Find(";",i);
				if (i==-1) break;
				str = Rels.Mid(j,i-j);
				i++;
				j=i;
				pDoc->RemoveRelation(str);
			}
		}
	}
}