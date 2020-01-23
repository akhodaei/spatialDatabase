// idbDoc.cpp : implementation of the CIdbDoc class
//

#include "stdafx.h"
#include "triangulate.h"
#include "interface.h"
#include "idb.h"
#include "basicsqldialogbox.h"
/*
#include "slist.h"
#include "db.h"
#include <fstream.h>
#include <io.h>
#include "idbDoc.h"
*/

#include "GraphView.h"
#include "MainFrm.h"


#include "relation.h"
#include "matrix.h"
#include "vector.h"
#include "dlist.h"
#include "range.h"  //RUICHEN

#include "scanner.h"
#include "parser.h"
#include "engine.h"

#include "DlgInsR.h"
#include "DlgProp.h"
#include "DlgInput.h"  //LEIZHANG
#include "DlgExpo.h"

#include "SCDrawObj.h"
#include "DlgRelName.h"
#include "tablesel.h"
#include "DlgExport.h"
#include "DlgMaxMin.h"

#include "DlgNtime.h"
#include "BasicSQL.h"

#include "Render.h"
#include "list.h"

#include "SqlAggregation.h"
#include "SqlSets.h"
#include "OnNestedSql.h"
#include "SqlDialogBox.h"
#include "Dlg_SQLRecursion.h"


#include "myparse.h"			//data structures for the Import Line
#include "idbdoc.h"
extern "C" double **simCal(int, struct pic_t *, struct pic_t *);
struct pic_t Ppic[1],*Dpic,*dp;
struct Line *pp, *nextp;
int m_option=1;//,m_LineNum=8;
int m_i;
double **tot_cost;

DB* dBaseTemp;

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

static int nAniSleep = 0;	// for animation speed
clock_t last_db_time=0;   //kpp
clock_t last_wrap_time =0;
clock_t last_query_time =0;
bool ImportLineFlag;		//global flag for Import Line

/////////////////////////////////////////////////////////////////////////////
// CIdbDoc

IMPLEMENT_DYNCREATE(CIdbDoc, CDocument)

BEGIN_MESSAGE_MAP(CIdbDoc, CDocument)
//{{AFX_MSG_MAP(CIdbDoc)
ON_COMMAND(ID_EDIT_INSRELATION, OnEditInsrelation)
ON_COMMAND(ID_VIEW_TIME, OnViewTime)
ON_COMMAND(ID_VIEW_GOEND, OnViewGoend)
ON_COMMAND(ID_VIEW_GOHEAD, OnViewGohead)
ON_COMMAND(ID_VIEW_NEXTSTEP, OnViewNextstep)
ON_COMMAND(ID_VIEW_PLAY, OnViewPlay)
ON_COMMAND(ID_VIEW_PLAYBACK, OnViewPlayback)
ON_COMMAND(ID_VIEW_PRIORSTEP, OnViewPriorstep)
ON_COMMAND(ID_VIEW_EXECUTIONTIME, OnViewExecutiontime)
ON_COMMAND(ID_VIEW_SAMERELATIONCOLOR, OnViewSamerelationcolor)
ON_UPDATE_COMMAND_UI(ID_VIEW_SAMERELATIONCOLOR, OnUpdateViewSamerelationcolor)
ON_UPDATE_COMMAND_UI(ID_VIEW_TIME, OnUpdateViewTime)
ON_UPDATE_COMMAND_UI(ID_VIEW_PRIORSTEP, OnUpdateViewPriorstep)
ON_UPDATE_COMMAND_UI(ID_VIEW_GOEND, OnUpdateViewGoend)
ON_UPDATE_COMMAND_UI(ID_VIEW_GOHEAD, OnUpdateViewGohead)
ON_UPDATE_COMMAND_UI(ID_VIEW_NEXTSTEP, OnUpdateViewNextstep)
ON_UPDATE_COMMAND_UI(ID_VIEW_PLAY, OnUpdateViewPlay)
ON_UPDATE_COMMAND_UI(ID_VIEW_PLAYBACK, OnUpdateViewPlayback)
ON_COMMAND(ID_BUTTON_MIN, OnButtonMin)
ON_COMMAND(ID_BUTTON_MAX, OnButtonMax)
ON_COMMAND(ID_IMPORT_POLYGON, OnFileImport)
ON_COMMAND(ID_IMPORT_MDB, OnImportMdb)
ON_COMMAND(ID_FILE_IMPORTFILE_POINT, OnFileImportfilePoint)
ON_COMMAND(ID_FILE_EXPORT, OnFileExport)
ON_COMMAND(ID_BUTTON_SIM_QUERY, OnButtonSimQuery)
ON_COMMAND(ID_IMPORT_LINE, OnImportLine)
ON_COMMAND(ID_FILE_IMPORTFILE_ELEVATION, OnFileImportfileElevation)
ON_UPDATE_COMMAND_UI(ID_BUTTON_MAX, OnUpdateButtonMax)
ON_UPDATE_COMMAND_UI(ID_BUTTON_MIN, OnUpdateButtonMin)
ON_COMMAND(ID_SQL_DIALOG, OnSqlDialogBox)
ON_COMMAND(ID_SHAPE_ANIM, OnShapeAnim)
ON_COMMAND(ID_SHAPE_NEXTSTEP, OnViewShapeNext)
ON_COMMAND(ID_VIEW_SHAPEPRIOR, OnViewShapeprior)
	ON_COMMAND(ID_VIEW_SHAPEGOHEAD, OnViewShapegohead)
	ON_COMMAND(ID_VIEW_SHAPEGOEND, OnViewShapegoend)
	ON_COMMAND(ID_VIEW_PLAYSHAPEBACK, OnViewPlayshapeback)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CIdbDoc construction/destruction

CIdbDoc::CIdbDoc()
{
	//	m_CurRelation = 0;
	
	m_listRelation.RemoveAll();
	ClearDrawObjList();
	m_bResetDrawObj = FALSE;
	
    m_bConnected = FALSE;
    m_pRecordset = NULL;
    m_nFields = 0;
    m_nRowCount = 0;
	m_nDatabaseType = MDB;
	
	m_nDBTimeS = 0;
	m_nDBTimeE = 0;
	m_nDBCurrent = 0;
	m_bSameRelationColor = TRUE;	
	
	m_strColorFileName = "";
	m_bColorRead = FALSE;
	
	m_strRangeFileName = "";  //RUICHEN
	
	m_bAddRelation = FALSE;
	m_legendS = 0;
	m_legendE = 0;
	m_legend = 0;
}

CIdbDoc::CIdbDoc(int i)
{

}

CIdbDoc::~CIdbDoc()
{
	if (!m_strColorFileName.IsEmpty())
		ReadWriteColorFile(2, m_strColorFileName);		// 1: read;  2: write
	if (!m_strRangeFileName.IsEmpty())  //RUICHEN
		ReadWriteRangeFile(2, m_strRangeFileName);      //RUICHEN // 1: read;  2: write
	m_listRelation.RemoveAll();
	m_ranges.RemoveAll();  //RUICHEN
	ClearDrawObjList();
}

void CIdbDoc::ClearDrawObjList()
{
	POSITION pos = m_objects.GetHeadPosition();
	while (pos != NULL)
	{
		CSCDrawObj* pObj = (CSCDrawObj*)(m_objects.GetNext(pos));
		delete pObj;
	}
	m_objects.RemoveAll();
}

void CIdbDoc::AddDrawObj(CSCDrawObj* pObj)
{
	ASSERT(pObj != NULL);
	m_objects.AddTail(pObj);
	pObj->m_pDocument = this;
}

BOOL CIdbDoc::OnNewDocument()
{
	extern DB* dataBase;
	dataBase = &m_dataBase;
	if (!CDocument::OnNewDocument())
		return FALSE;
	
    m_strDatabase.Empty(); // in case we're SDI
    m_strConnect.Empty();
    m_strQuery.Empty();
	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)
	
	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CIdbDoc serialization

void CIdbDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		// TODO: add loading code here
	}
}

/////////////////////////////////////////////////////////////////////////////
// CIdbDoc diagnostics

#ifdef _DEBUG
void CIdbDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CIdbDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CIdbDoc commands

DB* dataBase;
Scanner scanner;
Compiler compiler;
Vector<float>* prevquery=new Vector<float>;//DRK
Vector<float>* currquery;//DRK


BOOL CIdbDoc::DoCalculate(LPCTSTR lpszPathName)
{
	dataBase = &m_dataBase;

// Added by SRA and TJP for approximation handling
// The global Approx and ApproxBound come from the DlgApprox popup window
// for the "Apx" icon. (see idb.cpp, DlgApprox.cpp)
    extern bool globalApproxST;
    extern float globalApproxBoundST;	
	extern int globalApproxTypeST;
	m_dataBase.Approx = globalApproxST;
	m_dataBase.ApproxBound = globalApproxBoundST;
	m_dataBase.ApproxType = globalApproxTypeST; //Added 2005 SA for upperbound approximation
// end addition by S/T
	AfxGetApp()->BeginWaitCursor();

again:
	scanner.SwitchStream(lpszPathName);
	last_db_time=clock();             //kpp
	
	while(TRUE)
	{
		int nRetn = compiler.yyparse();
		if (nRetn != 0)
			break;
	}
	//DRK
	currquery=new Vector<float>;
	currquery->Resize((*dataBase).m_pRelationList->Size());
	Snode<Relation> *tmp;
	tmp=(*dataBase).m_pRelationList->headPtr;
	
	for(int i=0;i<currquery->Size();i++)
	{
		(*currquery)[i]=(float)tmp->itemPtr->NumberOfMatrixes();
		//currquery->Trace();
		tmp=tmp->nextPtr;
	}
	if((*dataBase).DBRecursive==TRUE)
	{
		if((*currquery)!=(*prevquery))
		{
			(*prevquery)=(*currquery);
			delete currquery;
			goto again;
		}
	}
		
	SetMatrixTime(dataBase);
	
	AfxGetApp()->EndWaitCursor();
	return TRUE;
}

BOOL CIdbDoc::DoCalculateGroup(LPCTSTR lpszPathName)
{
	dataBase = &m_dataBase;
again://DRK
	scanner.SwitchStream(lpszPathName);
	last_db_time=clock();             //kpp
	
	while(TRUE)
	{
		int nRetn = compiler.yyparse();
		if (nRetn != 0)
			break;
	}
	//DRK
	currquery=new Vector<float>;
	currquery->Resize((*dataBase).m_pRelationList->Size());
	Snode<Relation> *tmp;
	tmp=(*dataBase).m_pRelationList->headPtr;
	
	for(int i=0;i<currquery->Size();i++)
	{
		(*currquery)[i]=(float)tmp->itemPtr->NumberOfMatrixes();
		//currquery->Trace();
		tmp=tmp->nextPtr;
	}
	if((*dataBase).DBRecursive==TRUE)
	{
		if((*currquery)!=(*prevquery))
		{
			(*prevquery)=(*currquery);
			delete currquery;
			goto again;
		}
	}
	
	
	SetMatrixTime(dataBase);
//	OnRegCalT(10,200);
	
	return TRUE;
}


void CIdbDoc::OnRegCalT(CString ChangeRel, int startTime , int endTime) 
{
	// TODO: Add your command handler code here
	fstream out;
	out.open("titolilo.txt",ios::out);
	out << "syed"<<endl;

	char * temp = (char *) (LPCTSTR) ChangeRel;
	char tempChangeRel[100];
	int tcri = 0;
	for(size_t tempi=0;tempi<strlen(temp);tempi++)
	{
		if(temp[tempi]==' ')
			continue;
		tempChangeRel[tcri++] = temp[tempi];
	}
	tempChangeRel[tcri]='\0';

	out << "Syed"<<endl;

	COLORREF colorTable[400];
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
	

	SlistIter<Relation> relIter( *(m_dataBase.m_pRelationList) );
	Relation* pR;
	
	while(pR =relIter()) 
	{
		String strName;
		Matrix<float>* p_matrix;
		p_matrix = NULL;
		BOOL bShowR = (p_matrix==NULL);
		CString strOut("");
		
		DFIter<Matrix<float> >  matrixIter;
		if (bShowR)
		{
			matrixIter = DFIter<Matrix<float> >(*(pR->m_tablePtr));
			p_matrix =  matrixIter();
		}
		
		while (p_matrix != NULL )
		{
			strName = pR->Name();
			POSITION pos = pR->m_strAtriList.GetHeadPosition();
			int i = pR->m_strAtriList.GetCount();
			while (pos != NULL)
			{
				pR->m_strAtriList.GetNext(pos);
				if (i-- >1 );
			}
			GetEquationInfo(pR, p_matrix, strOut);
			if (bShowR)
				p_matrix =  matrixIter();
			else
				break;
		}
		char buffer[1000000];
		strcpy(buffer,strOut);
		char tempBuffer[100];
		int k=0;
		int flag = 0;
		int flagi = 0;
		//char tempBufferT[10][100];
	
		for(size_t l=0;l<strlen(buffer);l++)
		{
			if(buffer[l]==' ')
				continue;
			if(buffer[l]==',')
			{
				tempBuffer[k]='\0';
				for(size_t j=0;j<strlen(tempBuffer);j++)
				{
					if(tempBuffer[j]=='t')
					{
						flag = 1;
					//	strcpy(tempBufferT[flagi++],tempBuffer);
						break;
					}
				}
				k=0;
				continue;
			}
			if(flag ==1)
				break;
			tempBuffer[k++]=buffer[l];
		}
			
		CString tito(strName.GetText());
		CString tito1(tempChangeRel);
		if(!strcmp(tito1,tito))
		{
				//					sqlout << tempBuffer << endl;
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
				b = (float) atof(equation[1]); 
			
			double Start = (float) (atof(equation[3]) - atof(equation[0])*startTime) / (float) b ;
			double End = (float) (atof(equation[3]) - atof(equation[0])*endTime) / (float) b ;

			pR->m_colorStart = colorTable[293];
			pR->m_colorEnd = colorTable[384];
			pR->m_color = pR->m_colorStart;
			UpdateAllViews(NULL);
		}
	}
}


void CIdbDoc::SetMatrixTime(DB* dataBase)	//new line
{
	if (!(*dataBase).numRels) 
		return; 
	else
	{
		BOOL bSet = FALSE;
		
		SlistIter<Relation> relationListIter(*(*dataBase).m_pRelationList);
		//const Relation* p_r1;
		Relation* pR; 
		while(pR = (Relation*)relationListIter())
		{
			if(pR->SatisFlag()==0)
			{
				BOOL bSetRel = FALSE;
				
				DFIter<Matrix<float> >  matrixIter;
				matrixIter = DFIter<Matrix<float> >(*(pR->m_tablePtr));
				Matrix<float>* p_matrix;
				while ((p_matrix = matrixIter()) != NULL)
				{
					if (p_matrix->Cols() <= 5 || ImportLineFlag==TRUE)
					{	// the if condition was modified for "ImportLine"
						p_matrix->m_nTimeS = -1;
						p_matrix->m_nTimeE = -1;
						continue;
					}
					
					BOOL bMinT = FALSE;
					BOOL bMaxT = FALSE;
					if((*dataBase).STDB==TRUE)
					{
						for(int i=0; i< p_matrix->Rows(); i++)
						{
							Vector<float> vector = (*p_matrix)[i];
							
							if (vector[2]==0  &&  vector[3]==0 && vector[4]==0  
								&&  vector[5]==0  &&  vector[6]==0 && vector[7]!=0)	// param of t
							{
								switch ((int)(vector[0]))
								{
								case 0 :	// "= ";
								case 5 :	
									p_matrix->m_nTimeS = (int)(vector[1]/vector[7]);
									p_matrix->m_nTimeE = p_matrix->m_nTimeS;
									bMinT = TRUE;
									bMaxT = TRUE;
									break;
								case 1 :	// "< ";
								case 2 :	// "<= ";
									if (vector[7] < 0)
									{
										p_matrix->m_nTimeS = (int)(vector[1]/vector[7]);
										bMinT = TRUE;
									}
									else
									{
										p_matrix->m_nTimeE = (int)(vector[1]/vector[7]);
										bMaxT = TRUE;
									}
									break;
								case 3 :	// "> ";
								case 4 :	// ">= ";
									if (vector[7] < 0)
									{
										p_matrix->m_nTimeE = (int)(vector[1]/vector[7]);
										bMinT = TRUE;
									}
									else
									{
										p_matrix->m_nTimeS = (int)(vector[1]/vector[7]);
										bMaxT = TRUE;
									}
									break;
								}
							}
							if (vector[8] != 0)
								p_matrix->m_Period=(int)vector[1];
							if (vector[9] != 0)
								p_matrix->m_PeriodStart=(int)vector[1];
						}
					}
					else
					{
						for(int i=0; i< p_matrix->Rows(); i++)
						{
							Vector<float> vector = (*p_matrix)[i];
							
							if (vector[2]==0  &&  vector[3]==0  
								&&  vector[4]==0  &&  vector[5]!=0)	// param of t
							{
								switch ((int)(vector[0]))
								{
								case 0 :	// "= ";
								case 5 :	
									p_matrix->m_nTimeS = (int)(vector[1]/vector[5]);
									p_matrix->m_nTimeE = p_matrix->m_nTimeS;
									bMinT = TRUE;
									bMaxT = TRUE;
									break;
								case 1 :	// "< ";
								case 2 :	// "<= ";
									if (vector[5] < 0)
									{
										p_matrix->m_nTimeS = (int)(vector[1]/vector[5]);
										bMinT = TRUE;
									}
									else
									{
										p_matrix->m_nTimeE = (int)(vector[1]/vector[5]);
										bMaxT = TRUE;
									}
									break;
								case 3 :	// "> ";
								case 4 :	// ">= ";
									if (vector[5] < 0)
									{
										p_matrix->m_nTimeE = (int)(vector[1]/vector[5]);
										bMinT = TRUE;
									}
									else
									{
										p_matrix->m_nTimeS = (int)(vector[1]/vector[5]);
										bMaxT = TRUE;
									}
									break;
								}
							}
						}
					}
					if (!bMinT)
						p_matrix->m_nTimeS = 0;
					if (!bMaxT)
						p_matrix->m_nTimeE = p_matrix->m_nTimeS;
					p_matrix->m_nCurrent = /*p_matrix->m_nTimeS*/ - 1;
					
					if (!bSet)
					{
						m_nDBTimeS = p_matrix->m_nTimeS;
						m_nDBTimeE = p_matrix->m_nTimeE;
						bSet = TRUE;
					}
					else
					{
						if (m_nDBTimeS > p_matrix->m_nTimeS)
							m_nDBTimeS = p_matrix->m_nTimeS;
						if (m_nDBTimeE < p_matrix->m_nTimeE)
							m_nDBTimeE = p_matrix->m_nTimeE;
					}
					
					if (!bSetRel)
					{
						pR->m_nTimeS = p_matrix->m_nTimeS;
						pR->m_nTimeE = p_matrix->m_nTimeE;
						bSetRel = TRUE;
					}
					else
					{
						if (pR->m_nTimeS > p_matrix->m_nTimeS)
							pR->m_nTimeS = p_matrix->m_nTimeS;
						if (pR->m_nTimeE < p_matrix->m_nTimeE)
							pR->m_nTimeE = p_matrix->m_nTimeE;
					}
				}
			}
		}
	}
}

void CIdbDoc::DoShowAnimation(int nTime)
{
	DoReCalculate(nTime);
	UpdateAllViews(NULL);
	POSITION pos = GetFirstViewPosition();
	while (pos != NULL)
	{
		CView* pView = GetNextView(pos);
		if (pView != NULL  &&  pView->IsKindOf(RUNTIME_CLASS(CGraphView)))
		{
			//			pView->OnUpdate(NULL, 0, NUL);
			pView->UpdateWindow();
		}
	}
}

void CIdbDoc::OnViewTime() 
{
	dataBase = &m_dataBase;
	if((*dataBase).STDB==TRUE)
	{
		CDlgNtime dlg;
		dlg.m_Start = m_nDBCurrent;
		dlg.m_Step = 1;
		dlg.m_End = m_nDBTimeE;	
		dlg.m_NoOfStep = (m_nDBTimeE - m_nDBCurrent);
		dlg.m_Speed = 100;
		
		if (dlg.DoModal() == IDOK)
		{
			if (dlg.m_Step < 1)
				AfxMessageBox("Step should be more than 1");
				else if (dlg.m_Start < m_nDBTimeS  /*||  dlg.m_nTimeStart > m_nDBTimeE
					||  dlg.m_nTimeStart+dlg.m_nStep*dlg.m_nNoOfStep > m_nDBTimeE*/
					||  dlg.m_NoOfStep < 0)
				{
					AfxMessageBox("Time out range");
				}
				else
				{
					BeginWaitCursor();
					for (int i=0; i <= dlg.m_NoOfStep; i++)
					{
						//if(i==201)  //Removed by Shasha
						//	i=201;
						DoShowAnimation((int)dlg.m_Start + ((int)dlg.m_Step) * i);
						nAniSleep = 40 * (100 - (int)dlg.m_Speed);
						//((CMainFrame*)(AfxGetApp()->GetMainWnd()))->ShowAnimation(i, dlg.m_NoOfStep);
						((CMainFrame*)(AfxGetApp()->GetMainWnd()))->ShowAnimation(i+(int)dlg.m_Start, (int)dlg.m_NoOfStep+(int)dlg.m_Start);
						if (nAniSleep > 0  &&  i < dlg.m_NoOfStep)
							Sleep(nAniSleep);
					}
					EndWaitCursor();
				}
		}
		return;
	}
	
	//show expo dialog
    CDlgExpo expo;
    expo.m_Speed = 100;
    if(expo.DoModal() == IDOK) {
		int startTime = m_nDBTimeS, endTime = m_nDBTimeE;
		if(startTime == 0)
			startTime = 1;
		BeginWaitCursor();
		for (int i=startTime; i <= endTime; i=i*2)
		{
			DoShowAnimation(i);
			nAniSleep = 40 * (100 - (int)expo.m_Speed);
			
			//((CMainFrame*)(AfxGetApp()->GetMainWnd()))->ShowAnimation(i,dlg.m_nNoOfStep);
			if (nAniSleep > 0)
				Sleep(nAniSleep);
		}
		EndWaitCursor();
    }
	else
	{
		CDlgTime dlg;
		dlg.m_nTimeStart = m_nDBCurrent;
		dlg.m_nStep = 1;
		dlg.m_nNoOfStep = (m_nDBTimeE - m_nDBCurrent);
		dlg.m_nSpeed = 100;
		
		char cOut[32];
		CString strOut = CString("From: ");
		sprintf(cOut, "%d  ", m_nDBTimeS);
		strOut += cOut;
		strOut += CString("To: ");
		sprintf(cOut, "%d", m_nDBTimeE);
		strOut += cOut;
		dlg.m_strTimeRange = strOut;
		
		if (dlg.DoModal() == IDOK)
		{
			if (dlg.m_nStep < 1)
				AfxMessageBox("Step should be more than 1");
			else if (dlg.m_nTimeStart < m_nDBTimeS  ||  dlg.m_nTimeStart > m_nDBTimeE
				||  dlg.m_nTimeStart+dlg.m_nStep*dlg.m_nNoOfStep > m_nDBTimeE
				||  dlg.m_nNoOfStep < 0)
			{
				AfxMessageBox("Time out range");
			}
			else
			{
				BeginWaitCursor();
				for (int i=0; i <= dlg.m_nNoOfStep; i++)
				{
					DoShowAnimation(dlg.m_nTimeStart + dlg.m_nStep * i);
					nAniSleep = 40 * (100 - dlg.m_nSpeed);
					((CMainFrame*)(AfxGetApp()->GetMainWnd()))->ShowAnimation(i, dlg.m_nNoOfStep);
					if (nAniSleep > 0  &&  i < dlg.m_nNoOfStep)
						Sleep(nAniSleep);
				}
				EndWaitCursor();
			}
		}
	}
}

void CIdbDoc::DoReCalculate(int nTime)
{
	AfxGetApp()->BeginWaitCursor();

	dataBase = &m_dataBase;
	
	if (nTime < m_nDBTimeS)
		nTime = m_nDBTimeS;
	else
		if (nTime > m_nDBTimeE && (*dataBase).STDB==FALSE)
			nTime = m_nDBTimeE;
		
		if (nTime == m_nDBCurrent)
			return;
		
		if (m_dataBase.numRels>0) 
		{
			SlistIter<Relation> relationListIter(*(m_dataBase.m_pRelationList));
			Relation* pR; 
			while(pR = (Relation*)relationListIter())
			{
				if(pR->SatisFlag()==0)
				{
					DFIter<Matrix<float> >  matrixIter;
					matrixIter = DFIter<Matrix<float> >(*(pR->m_tablePtr));
					Matrix<float>* p_matrix;
					while ((p_matrix = matrixIter()) != NULL)
					{/* DRK changed this for period*/
						if(p_matrix->m_Period!=(-1))
							p_matrix->RegeneratePoints((nTime - p_matrix->m_PeriodStart) % p_matrix->m_Period + p_matrix->m_PeriodStart);
						else
							p_matrix->RegeneratePoints(nTime);
					}
					
					int nPeriod = pR->m_nTimeE - pR->m_nTimeS;
					if (nPeriod != 0  &&  nTime >= pR->m_nTimeS  &&  nTime <= pR->m_nTimeE)
						pR->m_color = RGB(GetRValue(pR->m_colorStart) + (GetRValue(pR->m_colorEnd)-GetRValue(pR->m_colorStart))*(nTime-pR->m_nTimeS)/nPeriod,
						GetGValue(pR->m_colorStart) + (GetGValue(pR->m_colorEnd)-GetGValue(pR->m_colorStart))*(nTime-pR->m_nTimeS)/nPeriod,
						GetBValue(pR->m_colorStart) + (GetBValue(pR->m_colorEnd)-GetBValue(pR->m_colorStart))*(nTime-pR->m_nTimeS)/nPeriod);
				}
			}
		}
		
		m_nDBCurrent = nTime;//changed for period by DRK
	AfxGetApp()->EndWaitCursor();
}


BOOL CIdbDoc::OnOpenDocument(LPCTSTR lpszPathName) 
{
	FILE* fp_in;
	if ((fp_in = fopen(lpszPathName,"rt"))==NULL)
	{
		AfxMessageBox("Error creating file !");
		return FALSE;
	}
	CString filestr="";
	char ch;
	while( !feof( fp_in ) ){
		ch = (char)fgetc(fp_in);
		if (ch!=-1)
			filestr += ch;
	}
	fclose(fp_in);

	if (str2ansi(&filestr))
	{
		FILE* fp_out;
		if ((fp_out = fopen(lpszPathName,"wt"))==NULL)
		{
			AfxMessageBox("Error creating file !");
			return FALSE;
		}
		fwrite(filestr, sizeof(char), filestr.GetLength(), fp_out);
		fclose(fp_out);
	}
	

	if (!CDocument::OnOpenDocument(lpszPathName))
		return FALSE;
	
	BOOL bCalc = DoCalculate(lpszPathName);
	/*  database   
	if (bCalc)
	{
	PutQuery();
	switch (m_nDatabaseType) {
	case UNK:
	break;
	case MDB:
	char drive[_MAX_DRIVE];
	char dir[_MAX_DIR];
	char fname[_MAX_FNAME];
	char ext[_MAX_EXT];
	_splitpath(lpszPathName, drive, dir, fname, ext);
	
	  m_strDatabase = fname;
	  m_strDatabase += ".MDB";
	  DaoOpenMdb();
	  break;
	  case ISAM:
	  DaoOpenIsam();
	  break;
	  case ODBC:
	  DaoOpenOdbc();
	  break;
	  }
	  return TRUE;
	  }
	  return FALSE;
	*/
	m_nDBCurrent = m_nDBTimeS - 1;
	DoReCalculate(m_nDBTimeS);
	
	char drive[_MAX_DRIVE];
	char dir[_MAX_DIR];
	char fname[_MAX_FNAME];
	char ext[_MAX_EXT];
	_splitpath(lpszPathName, drive, dir, fname, ext);
	
	char szPath[_MAX_PATH];
	_makepath(szPath, drive, dir, fname, "CLR");
	
	m_strColorFileName = CString(szPath);
	
	if (_access(szPath, 0) != -1)
		ReadWriteColorFile(1, szPath);		// 1: read;  2: write
	
	_makepath(szPath, drive, dir, fname, "RNG");  //RUICHEN
	m_strRangeFileName = CString(szPath);       //RUICHEN
	
	if (_access(szPath, 0) != -1)              //RUICHEN
		ReadWriteRangeFile(1, szPath);         //RUICHEN // 1: read;	 2: write

	((CIdbApp*)AfxGetApp())->p_Doc = this;
	
	return bCalc;
}

void CIdbDoc::OnEditInsrelation() 
{
	CDlgInsR dlg;

    CString docpath=GetPathName();
	CString filename=GetTitle();
	
	int pos;
	pos = docpath.ReverseFind('\\');
	docpath = docpath.Left(pos+1);
	pos = filename.Find(".",0);
	if (pos>0) 
		filename = filename.Left(pos);
	filename = filename + "_Datalog.txt";
	docpath = docpath + filename;
	
	dlg.FileRead(docpath);

	if (dlg.DoModal() == IDOK)
	{
		last_query_time=clock();    
		CString str = dlg.m_strText;

		FILE* fp_out;
		if ((fp_out = fopen("TEMPTEMP.TXT","wt"))==NULL)
		{
			AfxMessageBox("Error creating file !");
			return ;
		}
		else {

			// save to Last_InsertRelation.txt -- by TW
			dlg.FileSave(docpath);
			//--end by TW

			str2ansi(&str);
			str = "begin%Temp%\n" + str + "\nend%Temp%\n";
			fwrite(str, sizeof(char), str.GetLength(), fp_out);
			fclose(fp_out);

			DoCalculate("TEMPTEMP.TXT");
			
			UpdateAllViews(NULL);
		}
		SetQueryTime();
	}
}

void CIdbDoc::ShowRelationInfo(Relation* pR, Matrix<float>* p_matrix)
{
	BOOL bShowR = (p_matrix==NULL);
	CString strOut("");
	
	DFIter<Matrix<float> >  matrixIter;
	if (bShowR)
	{
		matrixIter = DFIter<Matrix<float> >(*(pR->m_tablePtr));
		p_matrix =  matrixIter();
	}
	while (p_matrix != NULL)
	{
		GetMatrixInfo(pR, p_matrix, strOut, true);
		
		if (bShowR)
			p_matrix =  matrixIter();
		else
			break;
	}
	
	CDlgProp dlg(this);
	//dlg.m_strOut = strOut;
	dlg.m_strOut = tabledisplay(strOut);
	dlg.RelName = pR->m_sName.GetText();
	dlg.DoModal();
}

void CIdbDoc::SaveRelationInfo(Relation* pR, Matrix<float>* p_matrix, FILE * fp)
{

	if (fp==NULL)
		return;

	BOOL bShowR = (p_matrix==NULL);
	CString strOut("");
	
	DFIter<Matrix<float> >  matrixIter;
	if (bShowR)
	{
		matrixIter = DFIter<Matrix<float> >(*(pR->m_tablePtr));
		p_matrix =  matrixIter();
	}
	while (p_matrix != NULL)
	{
		GetMatrixInfo(pR, p_matrix, strOut, true);
		
		if (bShowR)
			p_matrix =  matrixIter();
		else
			break;
	}

//	AfxMessageBox(LPCSTR(strOut));

	fwrite(LPCSTR(strOut),strOut.GetLength(),1,fp);

//	CDlgProp dlg;
//	dlg.m_strOut = strOut;
//	dlg.DoModal();
}

CString CIdbDoc::ShowRelation(Relation* pR, Matrix<float>* p_matrix)
{
	BOOL bShowR = (p_matrix==NULL);
	CString strOut("");
	
	DFIter<Matrix<float> >  matrixIter;
	if (bShowR)
	{
		matrixIter = DFIter<Matrix<float> >(*(pR->m_tablePtr));
		p_matrix =  matrixIter();
	}
	while (p_matrix != NULL)
	{
		GetAttryInfo(pR, p_matrix, strOut);
		
		if (bShowR)
			p_matrix =  matrixIter();
		else
			break;
	}
	
	return strOut;
	
	//	CDlgProp dlg;
	//	dlg.m_strOut = strOut;
	//	dlg.DoModal();
}



// Syed changed

CString CIdbDoc::ShowEquationInfo(Relation* pR, Matrix<float>* p_matrix)
{
	BOOL bShowR = (p_matrix==NULL);
	CString strOut("");
	
	DFIter<Matrix<float> >  matrixIter;
	if (bShowR)
	{
		matrixIter = DFIter<Matrix<float> >(*(pR->m_tablePtr));
		p_matrix =  matrixIter();
	}
	while (p_matrix != NULL)
	{
//		GetEquationInfo(pR, p_matrix, strOut);
		
		if (bShowR)
			p_matrix =  matrixIter();
		else
			break;
	}
	
	//	CDlgProp dlg;
	//	dlg.m_strOut = strOut;
	//	dlg.DoModal();
	return strOut;
}

void CIdbDoc::GetMatrixInfo(Relation* pR, Matrix<float>* p_matrix, CString& strOut, BOOL bSave /*=false*/)  //RUICHEN modify
{
	if (pR==NULL)
		return;
	
	//Shasha(July 03): Simplify the display. 
	p_matrix->Simplify(true);

	String strName = pR->Name();
	strOut += CString(strName.GetText());
	strOut += "(";
	POSITION pos = pR->m_strAtriList.GetHeadPosition();
	int i = pR->m_strAtriList.GetCount();
	while (pos != NULL)
	{
		strOut += pR->m_strAtriList.GetNext(pos);
		if (i-- >1 )
			strOut += ", ";
	}
	strOut += ") :- \n";
	
	if (p_matrix != NULL)
	{
		char cOut[32];
		
		for(i=0; i< p_matrix->Rows(); i++)
		{   
			POSITION pos1 = pR->m_strAtriList.GetHeadPosition();
			Vector<float> vector = (*p_matrix)[i];
			BOOL bAdd = FALSE;
			for(int j=2; j< vector.Size(); j++)
			{
				CString strAttr = pR->m_strAtriList.GetNext(pos1);
				if (vector[j] == 0)
					continue;
				if (vector[j] > 0  &&  bAdd)
					strOut += "+";
				if (vector[j] == -1)
					strOut += "-";
				else if (vector[j] != 1)
				{
					if (vector[j]-(int)(vector[j]) != 0)
						if (bSave)
							sprintf(cOut, "%.6f", (float)(vector[j]));
						else
							sprintf(cOut, "%.2f", (float)(vector[j]));
					else
						sprintf(cOut, "%.f", (float)(vector[j]));
					strOut += cOut;
				}
				strOut += strAttr;
				//strOut += " ";
				bAdd = TRUE;
			}
			switch ((int)(vector[0]))
			{
			case 0 :	strOut += "=";
				break;
			case 1 :	strOut += "<";
				break;
			case 2 :	strOut += "<=";
				break;
			case 3 :	strOut += ">";
				break;
			case 4 :	strOut += ">=";
				break;
			case 5 :	strOut += "=";
				break;
			}
			//check if text
			if (vector[0]==5.5)							 //DRK
				strOut = strOut + "\""+ (*(*dataBase).m_pTextVec)[(int)vector[1]].GetText()+ "\""; //DRK
			else {if (vector[1]-(int)(vector[1]) != 0)
				if (bSave)
					sprintf(cOut, "%.6f", (float)(vector[1]));
				else
					sprintf(cOut, "%.2f", (float)(vector[1]));
			else
				sprintf(cOut, "%.f", (float)(vector[1]));
			strOut += cOut;}
			if (i== p_matrix->Rows()-1)
				strOut += ".";
			else
				strOut += ", ";
			
			strOut += "\n";
			//strOut += (char)(13);
			//strOut += (char)(10);
		}
		strOut += "\n";
		//strOut += (char)(13);
		//strOut += (char)(10);
		
		if(!bSave){  //RUICHEN only this sentence
			strOut += CString("From: ");
			sprintf(cOut, "%d  ", p_matrix->m_nTimeS);
			strOut += cOut;
			strOut += CString("To: ");
			sprintf(cOut, "%d", p_matrix->m_nTimeE);
			strOut += cOut;
			strOut += "\n";
			//strOut += (char)(13);
			//strOut += (char)(10);
			strOut += CString("Current: ");
			sprintf(cOut, "%d ", p_matrix->m_nCurrent);
			strOut += cOut;
			strOut += "\n";
			//strOut += (char)(13);
			//strOut += (char)(10);
		}
		strOut += "\n";
		//strOut += (char)(13);
		//strOut += (char)(10);
	}
}

void CIdbDoc::GetAttryInfo(Relation* pR, Matrix<float>* p_matrix, CString& strOut, BOOL bSave /*=false*/)  //RUICHEN modify
{
	if (pR==NULL)
		return;
	
	String strName = pR->Name();
	strOut += CString(strName.GetText());
	strOut += "(";
	POSITION pos = pR->m_strAtriList.GetHeadPosition();
	int i = pR->m_strAtriList.GetCount();
	while (pos != NULL)
	{
		strOut += pR->m_strAtriList.GetNext(pos);
		if (i-- >1 )
			strOut += ", ";
	}
	strOut += ")";
}


void CIdbDoc::GetEquationInfo(Relation* pR, Matrix<float>* p_matrix, CString& strOut , BOOL bSave /*=false*/)  //RUICHEN modify
{
	if (pR==NULL)
		return;
	
	String strName = pR->Name();
	//	strOut += CString(strName.GetText());
	//	strOut += "(";
	POSITION pos = pR->m_strAtriList.GetHeadPosition();
	int i = pR->m_strAtriList.GetCount();
	while (pos != NULL)
	{
		//		strOut += pR->m_strAtriList.GetNext(pos);
		pR->m_strAtriList.GetNext(pos);
		//		if (i-- >1 )
		//			strOut += ", ";
	}
	//	strOut += ") :- ";
	//	strOut += (char)(13);
	//	strOut += (char)(10);
	
	if (p_matrix != NULL)
	{
		char cOut[32];
		
		for(i=0; i< p_matrix->Rows(); i++)
		{   
			POSITION pos1 = pR->m_strAtriList.GetHeadPosition();
			Vector<float> vector = (*p_matrix)[i];
			BOOL bAdd = FALSE;
			for(int j=2; j< vector.Size(); j++)
			{
				CString strAttr = pR->m_strAtriList.GetNext(pos1);
				if (vector[j] == 0)
					continue;
				if (vector[j] > 0  &&  bAdd)
					strOut += "+";
				if (vector[j] == -1)
					strOut += "-";
				else if (vector[j] != 1)
				{
					if (vector[j]-(int)(vector[j]) != 0)
						sprintf(cOut, "%.2f ", (float)(vector[j]));
					else
						sprintf(cOut, "%.f ", (float)(vector[j]));
					strOut += cOut;
				}
				strOut += strAttr;
				strOut += " ";
				bAdd = TRUE;
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
			//check if text
			if (vector[0]==5.5)							 //DRK
				strOut += (*(*dataBase).m_pTextVec)[(int)vector[1]].GetText(); //DRK
			else {if (vector[1]-(int)(vector[1]) != 0)
				sprintf(cOut, "%.2f", (float)(vector[1]));
			else
				sprintf(cOut, "%.f", (float)(vector[1]));
			strOut += cOut;}
			if (i== p_matrix->Rows()-1)
				strOut += ".";
			else
				strOut += ",";
			//			strOut += (char)(13);
			//			strOut += (char)(10);
		}
		//		strOut += (char)(13);
		//		strOut += (char)(10);
		/*
		if(!bSave){  //RUICHEN only this sentence
		strOut += CString("From: ");
		sprintf(cOut, "%d  ", p_matrix->m_nTimeS);
		strOut += cOut;
		strOut += CString("To: ");
		sprintf(cOut, "%d", p_matrix->m_nTimeE);
		strOut += cOut;
		strOut += (char)(13);
		strOut += (char)(10);
		strOut += CString("Current: ");
		sprintf(cOut, "%d ", p_matrix->m_nCurrent);
		strOut += cOut;
		strOut += (char)(13);
		strOut += (char)(10);
		}
		*/
//		AfxMessageBox(p_matrix->m_nTimeS);
//		p_matrix->m_nTimeS = start;
//		p_matrix->m_nTimeE = end;
//		strOut += (char)(13);
//		strOut += (char)(10);
	}
}

void CIdbDoc::ChangeEquationInfo(Relation* pR, Matrix<float>* p_matrix, CString& strOut , CString& tempstrOut , BOOL bSave /*=false*/)  //RUICHEN modify
{
	if (pR==NULL)
		return;

	POSITION pos = pR->m_strAtriList.GetHeadPosition();
	int i = pR->m_strAtriList.GetCount();
	while (pos != NULL)
	{
		pR->m_strAtriList.GetNext(pos);
	}


	if (p_matrix != NULL)
	{
		char cOut[32];
	
		for(i=0; i< p_matrix->Rows(); i++)
		{   
			POSITION pos1 = pR->m_strAtriList.GetHeadPosition();
			Vector<float> vector = (*p_matrix)[i];
			BOOL bAdd = FALSE;
			for(int j=2; j< vector.Size(); j++)
			{
				CString strAttr = pR->m_strAtriList.GetNext(pos1);
				if (vector[j] == 0)
					continue;
				if (vector[j] > 0  &&  bAdd)
				{
					strOut += "+";
					tempstrOut += "+";
				}
				if (vector[j] == -1)
				{
					strOut += "-";
					tempstrOut += "-";
				}
				else if (vector[j] != 1)
				{
					if (vector[j]-(int)(vector[j]) != 0)
						sprintf(cOut, "%.2f ", (float)(vector[j]));
					else
						sprintf(cOut, "%.f ", (float)(vector[j]));
					strOut += cOut;
				}
				strOut += strAttr;
				strOut += " ";
				tempstrOut += strAttr;
				tempstrOut += " ";
				bAdd = TRUE;
			}
			switch ((int)(vector[0]))
			{
			case 0 :	strOut += "< ";  // =
						tempstrOut += "> ";
				break;
			case 1 :	strOut += ">= ";  // <
						tempstrOut += ">= ";
				break;
			case 2 :	strOut += "> "; // <=
						tempstrOut += "> ";
				break;
			case 3 :	strOut += "<= "; // >
						tempstrOut += "<= ";
				break;
			case 4 :	strOut += "< "; // >=
						tempstrOut += "< ";
				break;
			case 5 :	strOut += "< "; // =
						tempstrOut += "> " ;
				break;
			}
			//check if text
			if (vector[0]==5.5)							 //DRK
			{
				strOut += (*(*dataBase).m_pTextVec)[(int)vector[1]].GetText(); //DRK
				tempstrOut += (*(*dataBase).m_pTextVec)[(int)vector[1]].GetText(); //DRK
			}
			else {if (vector[1]-(int)(vector[1]) != 0)
				sprintf(cOut, "%.2f", (float)(vector[1]));
			else
				sprintf(cOut, "%.f", (float)(vector[1]));
			strOut += cOut; tempstrOut +=cOut; }
			if (i== p_matrix->Rows()-1)
			{
				strOut += ".";
				tempstrOut += ".";
			}
			else
			{
				strOut += ",";
				tempstrOut += ",";
			}
		}
//		strOut += (char)(13);
//		strOut += (char)(10);
	}
}


////////////////////////////////////////////////
// DAO
// global helper function to display an error message
void DaoErrorMsg(CDaoException* e)
{
    char errorMsg[301];
   	wsprintf(errorMsg, "DAO error %d, SOURCE = %s, DESCR = %s",
        e->m_pErrorInfo->m_lErrorCode,
        (const char*) e->m_pErrorInfo->m_strSource,
        (const char*) e->m_pErrorInfo->m_strDescription);
   	AfxMessageBox(errorMsg);
}

void CIdbDoc::OnCloseDocument() 
{
//	AfxMessageBox("close ok");
    m_strQuery.Empty();
    PutQuery();
    if (m_bConnected) {
		
		if( (NULL!= m_pRecordset) && m_pRecordset->IsOpen())
		{
			m_pRecordset->Close();
		}
		delete m_pRecordset; // Destructor calls Close
		m_daoDB.Close();
		m_bConnected = FALSE;
		m_pRecordset = NULL;
		m_nRowCount = 0;
    }
    CDocument::OnCloseDocument();
}

void CIdbDoc::GetQuery()
{    // get SQL string from dialog bar
	 /*	char text[201];   
	 CDialogBar& rBar = ((CMainFrame*) AfxGetApp()->m_pMainWnd)->m_wndQueryBar;
	 rBar.GetDlgItemText(IDC_QUERY, text, 200);
	 m_strQuery = text;
	*/
	
	m_strQuery = "";
}

void CIdbDoc::PutQuery()
{    // write SQL string to dialog bar
	 /*	CDialogBar& rBar = ((CMainFrame*) AfxGetApp()->m_pMainWnd)->m_wndQueryBar;
	 rBar.SetDlgItemText(IDC_QUERY, m_strQuery);
	*/
}

void CIdbDoc::GetFieldSpecs()
{
	m_nFields = (int) m_pRecordset->GetFieldCount();
	m_arrayFieldName.SetSize(m_nFields);
	m_arrayFieldSize.SetSize(m_nFields);
	CDaoFieldInfo fi;
	for(int i = 0; i < m_nFields; i++) {
		m_pRecordset->GetFieldInfo(i, fi);
		m_arrayFieldName[i] = fi.m_strName;
		m_arrayFieldSize[i] = (short) max(min(fi.m_lSize, 50),
			fi.m_strName.GetLength());
		TRACE("field name = %s\n", fi.m_strName);
	}
}

// helper used by OnFileDaoOpenMdb, OnFileDaoOpenIsam, and OnFileDaoOpenOdbc
bool CIdbDoc::OpenRecordset(CString fileName)
{
    GetQuery();
	/*  if (m_strQuery.IsEmpty()) {
	CTableSelect tableDlg(&m_daoDB);
	if (tableDlg.DoModal() != IDOK) {
	m_daoDB.Close();  // escape route
	return;
	}
	
	  m_strQuery.Format("select * from [%s]", tableDlg.m_strSelection);
      PutQuery();
	  }
	*/
	//	CString str = "land"; 
	//		m_strDatabase.Left(m_strDatabase.GetLength()-3);
	//	str += "pat";
	m_strQuery.Format("select * from [%s]", fileName);
	//	CString strQuery = "select * from ";
	//	String strName = pR->Name();
	//	strQuery += strName.GetText();
	//	pDoc->m_strQuery = strQuery;
	OnRequery();
    m_pRecordset = new CDaoRecordset(&m_daoDB);
    try {	
		m_pRecordset->Open(dbOpenDynaset, m_strQuery, dbReadOnly);
    }
    catch (CDaoException* e) {
		::DaoErrorMsg(e);
		UpdateAllViews(NULL);
		m_bConnected = FALSE;
		e->Delete();
		return false;
    }
    if (!m_pRecordset->IsBOF()) {
		// might be expensive for a really big table
		// View adjusts its m_nRowCount if you supply a big value here
		m_pRecordset->MoveLast(); // to validate record count
    }
    m_nRowCount = m_pRecordset->GetAbsolutePosition() + 2;
    TRACE("m_nRowCount = %d\n", m_nRowCount);
    GetFieldSpecs();
	//   UpdateAllViews(NULL);
    m_bConnected = TRUE;
	return true;
	
}

void CIdbDoc::OpenRecordset()
{
    CString strTable;
	GetQuery();
    if (m_strQuery.IsEmpty()) {
		CTableSelect tableDlg(&m_daoDB);
		if (tableDlg.DoModal() != IDOK) {
			m_daoDB.Close();  // escape route
			return;
		}
		
		m_strQuery.Format("select * from [%s]", tableDlg.m_strSelection);
		strTable = tableDlg.m_strSelection ;
		//PutQuery();
    }
	
    m_pRecordset = new CDaoRecordset(&m_daoDB);
    try {	
		m_pRecordset->Open(dbOpenDynaset, m_strQuery, dbReadOnly);
    }
    catch (CDaoException* e) {
		::DaoErrorMsg(e);
		UpdateAllViews(NULL);
		m_bConnected = FALSE;
		e->Delete();
		return;
    }
    if (!m_pRecordset->IsBOF()) {
		// might be expensive for a really big table
		// View adjusts its m_nRowCount if you supply a big value here
		m_pRecordset->MoveLast(); // to validate record count
    }
    m_nRowCount = m_pRecordset->GetAbsolutePosition() + 2;
    TRACE("m_nRowCount = %d\n", m_nRowCount);
    GetFieldSpecs();
	
	CreateRelationFromAccessTable(strTable); 
	
    UpdateAllViews(NULL);
    m_bConnected = TRUE;
}

bool CIdbDoc::DaoOpenMdb()
{
/*    if (m_strDatabase.IsEmpty()) {
CFileDialog dlg(TRUE, ".mdb", "*.mdb");
if (dlg.DoModal() == IDCANCEL) return;
m_strDatabase = dlg.GetPathName();
}
	*/
	if(m_daoDB.IsOpen())
		m_daoDB.Close();
	
	BeginWaitCursor();
    try {
		// nonexclusive, read-only
		m_daoDB.Open(m_strDatabase, FALSE, TRUE);
    }
    catch (CDaoException* e) {
		::DaoErrorMsg(e);
		EndWaitCursor();
		e->Delete();
		return false;
    }
    m_strDatabase = m_daoDB.GetName();
    TRACE("database name = %s, connect = %s\n",
		(const char*) m_strDatabase, (const char*) m_strConnect);
    //OpenRecordset();
	m_nDatabaseType = MDB;
    EndWaitCursor();
	return true;
}

void CIdbDoc::DaoOpenOdbc()
{
    // can't open ODBC using Access driver
    if (m_strConnect.IsEmpty()) {
		m_strConnect = "ODBC;";
    }
    BeginWaitCursor();
    try {
		// nonexclusive, read-only
		m_daoDB.Open("", FALSE, TRUE, m_strConnect);
    }
    catch (CDaoException* e) {
		::DaoErrorMsg(e);
		EndWaitCursor();
		e->Delete();
		return;
    }
    m_strConnect = m_daoDB.GetConnect();
    TRACE("database name = %s, connect = %s\n",
        (const char*) m_strDatabase,
        (const char*) m_strConnect);
	//    OpenRecordset();
	m_nDatabaseType = ODBC;
    EndWaitCursor();
}

void CIdbDoc::DaoOpenIsam() 
{
/*    BeginWaitCursor();
if (m_strConnect.IsEmpty()) {
CIsamSelect isamDlg;
if (isamDlg.DoModal() != IDOK) {
return;
}
m_strConnect = isamDlg.m_strIsam + ";DATABASE=" +
isamDlg.m_strDirectory;
TRACE("m_strConnect = %s\n", (const char*) m_strConnect);
}
try {
// nonexclusive, read-only
m_daoDB.Open("", FALSE, TRUE, m_strConnect);
}
catch(CDaoException* e) {
::DaoErrorMsg(e);
EndWaitCursor();
e->Delete();
return;
}
m_strConnect = m_daoDB.GetConnect();
TRACE("database name = %s, connect = %s\n",
(const char*) m_strDatabase, (const char*) m_strConnect);
OpenRecordset();
m_nDatabaseType = ISAM;
EndWaitCursor();
	*/
}

void CIdbDoc::OnRequery()
{ 
	//    GetQuery();
    // Requery won't work because we're changing the SQL statement
    BeginWaitCursor();
	if(m_pRecordset == NULL) return;
	if(m_pRecordset->IsOpen()) {
		m_pRecordset->Close();
	}
    try {	
		m_pRecordset->Open(dbOpenDynaset, m_strQuery, dbReadOnly);
    }
    catch (CDaoException* e) {
		//    ::DaoErrorMsg(e);
		m_nRowCount = 0;
		UpdateAllViews(NULL);
		EndWaitCursor();
		e->Delete();
		return;
    }
    if (!m_pRecordset->IsBOF()) {
		m_pRecordset->MoveLast(); // to validate record count
    }
    m_nRowCount = m_pRecordset->GetAbsolutePosition() + 2;
    TRACE("m_nRowCount = %d\n", m_nRowCount);
    GetFieldSpecs();
    UpdateAllViews(NULL); 
    EndWaitCursor();
}

BOOL CIdbDoc::ReadWriteColorFile(int mode, LPCTSTR lpszPathName)
{
	CFile file;
	CFileException fe;
	
	switch (mode)
	{
	case 1:
		if (!file.Open(lpszPathName, CFile::modeRead | CFile::shareExclusive, &fe))
		{
			ReportSaveLoadException(lpszPathName, &fe,
				TRUE, AFX_IDP_INVALID_FILENAME);
			return FALSE;
		}
		break;
	case 2:
		if (!file.Open(lpszPathName, CFile::modeCreate |
			CFile::modeReadWrite | CFile::shareExclusive, &fe))
		{
			ReportSaveLoadException(lpszPathName, &fe,
				TRUE, AFX_IDP_INVALID_FILENAME);
			return FALSE;
		}
		break;
	}
	
	// replace calls to Serialize with SaveDIB function
	BOOL bSuccess = FALSE;
	
	TRY
	{
		BeginWaitCursor();
		bSuccess = DoReadWriteColorFile(mode, file);
		file.Close();
	}
	CATCH (CException, eSave)
	{
		file.Abort(); // will not throw an exception
		EndWaitCursor();
		ReportSaveLoadException(lpszPathName, eSave,
			TRUE, AFX_IDP_FAILED_TO_SAVE_DOC);
		return FALSE;
	}
	END_CATCH
		
		EndWaitCursor();
	SetModifiedFlag(FALSE);     // back to unmodified
	
	if (bSuccess)
		m_bColorRead = TRUE;
	else
	{
		// may be other-style DIB (load supported but not save)
		//  or other problem in SaveDIB
		//		CString strMsg;
		//		strMsg.LoadString(IDS_CANNOT_SAVE_IDB);
		//MessageBox(NULL, "Cannot access .CLR file!", NULL, MB_ICONINFORMATION | MB_OK);  //RUICHEN deleted
	}
	
	return bSuccess;
}

BOOL CIdbDoc::DoReadWriteColorFile(int mode, CFile& file)	// 1: read, 2: write
{
	UINT nArMode = (mode == 1 ? CArchive::load : CArchive::store);
	
	CArchive ar(&file, nArMode);
	
	SlistIter<Relation> relIter( *(m_dataBase.m_pRelationList) );
	Relation* pR;
	
	switch (mode)
	{
	case 1:	// read
		int n;
		ar >> n;
		if (n != m_dataBase.numRels)
		{
			//AfxMessageBox("The .TXT file may be changed! No color load!"); //RUICHEN deleted
			return FALSE;
		}
		while (pR = relIter())
		{
			ar >> pR->m_colorStart;
			ar >> pR->m_colorEnd;
		}
		break;
	case 2:
		ar << m_dataBase.numRels;
		while (pR = relIter())
		{
			ar << pR->m_colorStart;
			ar << pR->m_colorEnd;
		}
		break;
	}
	
	return TRUE;
}

BOOL CIdbDoc::ReadWriteRangeFile(int mode, LPCTSTR lpszPathName)  //RUICHEN
{
	CFile file;
	CFileException fe;
	
	switch (mode)
	{
	case 1:
		if (!file.Open(lpszPathName, CFile::modeRead | CFile::shareExclusive, &fe))
		{
			ReportSaveLoadException(lpszPathName, &fe,
				TRUE, AFX_IDP_INVALID_FILENAME);
			return FALSE;
		}
		break;
	case 2:
		if (!file.Open(lpszPathName, CFile::modeCreate |
			CFile::modeReadWrite | CFile::shareExclusive, &fe))
		{
			ReportSaveLoadException(lpszPathName, &fe,
				TRUE, AFX_IDP_INVALID_FILENAME);
			return FALSE;
		}
		break;
	}
	
	// replace calls to Serialize with SaveDIB function
	BOOL bSuccess = FALSE;
	
	TRY
	{
		BeginWaitCursor();
		bSuccess = DoReadWriteRangeFile(mode, file);
		file.Close();
	}
	CATCH (CException, eSave)
	{
		file.Abort(); // will not throw an exception
		EndWaitCursor();
		ReportSaveLoadException(lpszPathName, eSave,
			TRUE, AFX_IDP_FAILED_TO_SAVE_DOC);
		return FALSE;
	}
	END_CATCH
		
		EndWaitCursor();
	SetModifiedFlag(FALSE);     // back to unmodified
	
	if (!bSuccess)
	{
		// may be other-style DIB (load supported but not save)
		//  or other problem in SaveDIB
		//		CString strMsg;
		//		strMsg.LoadString(IDS_CANNOT_SAVE_IDB);
		MessageBox(NULL, "Cannot access .RNG file!", NULL, MB_ICONINFORMATION | MB_OK);
	}
	
	return bSuccess;
}

BOOL CIdbDoc::DoReadWriteRangeFile(int mode, CFile& file)	//RUICHEN 1: read, 2: write
{
	UINT nArMode = (mode == 1 ? CArchive::load : CArchive::store);
	
	CArchive ar(&file, nArMode);
	
	Range* pRange;
	POSITION pos;
	int i;
	
	switch (mode)
	{
	case 1:	// read
		int count;		
		
		ar >> count;
		for(i=0; i<count; i++) {
			pRange=new Range();
			
			ar >> (*pRange).left;
			ar >> (*pRange).right;
			ar >> (*pRange).color;
			m_ranges.AddTail(pRange);
		}
		
		if(m_dataBase.GIS) m_bSameRelationColor=FALSE; //RUICHEN
		break;
		
	case 2: // write
		ar << m_ranges.GetCount();
		for(pos = m_ranges.GetHeadPosition(); pos != NULL; ) {
			pRange=(Range*)m_ranges.GetNext(pos);
			ar << (*pRange).left;
			ar << (*pRange).right;
			ar << (*pRange).color;
		}
		break;
	}
	
	return TRUE;
}

BOOL CIdbDoc::OnSaveDocument(LPCTSTR lpszPathName)
{
	CFile file;
	CFileException fe;
	
	if (!file.Open(lpszPathName, CFile::modeCreate |
		CFile::modeReadWrite | CFile::shareExclusive, &fe))
	{
		ReportSaveLoadException(lpszPathName, &fe,
			TRUE, AFX_IDP_INVALID_FILENAME);
		return FALSE;
	}
	
	// replace calls to Serialize with SaveDIB function
	BOOL bSuccess = FALSE;
	TRY
	{
		BeginWaitCursor();
		bSuccess = SaveIDBFile(file);
		file.Close();
	}
	CATCH (CException, eSave)
	{
		file.Abort(); // will not throw an exception
		EndWaitCursor();
		ReportSaveLoadException(lpszPathName, eSave,
			TRUE, AFX_IDP_FAILED_TO_SAVE_DOC);
		return FALSE;
	}
	END_CATCH
		
		EndWaitCursor();
	SetModifiedFlag(FALSE);     // back to unmodified
	
	if (!bSuccess)
	{
		// may be other-style DIB (load supported but not save)
		//  or other problem in SaveDIB
		CString strMsg;
		strMsg.LoadString(IDS_CANNOT_SAVE_IDB);
		MessageBox(NULL, strMsg, NULL, MB_ICONINFORMATION | MB_OK);
	}
	
	return bSuccess;
}

BOOL CIdbDoc::SaveIDBFile(CFile& file)
{
	SlistIter<Relation> relIter( *(m_dataBase.m_pRelationList) );
	Relation* pR;
	
	Matrix<float>* p_matrix = NULL;
	BOOL bShowR = (p_matrix==NULL);
	CString strOut("begin%savefile%");
	strOut += (char)(13);
	strOut += (char)(10);
	while(pR =relIter()) {
		
		DFIter<Matrix<float> >  matrixIter;
		if (bShowR)
		{
			matrixIter = DFIter<Matrix<float> >(*(pR->m_tablePtr));
			p_matrix =  matrixIter();
		}
		while (p_matrix != NULL)
		{
			GetMatrixInfo(pR, p_matrix, strOut, true);  //RUICHEN modify //true: for save;   false: for display
			
			if (bShowR)
				p_matrix =  matrixIter();
			else
				break;
		}
	};
	
	strOut += "end%savefile%";
	strOut += (char)(13);
	strOut += (char)(10);
	TRY
	{
		// Write the file 
		file.Write(strOut, strOut.GetLength());
		
	}
	CATCH (CFileException, e)
	{
		
		THROW_LAST();
	}
	END_CATCH
		
		return true;
}

/////////////////////////////////////////////////////////////////////////////
// CDlgTime dialog


CDlgTime::CDlgTime(CWnd* pParent /*=NULL*/)
: CDialog(CDlgTime::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgTime)
	m_strTimeRange = _T("");
	m_nNoOfStep = 0;
	m_nSpeed = 0;
	m_nTimeStart = 0;
	m_nStep = 0;
	//}}AFX_DATA_INIT
}


void CDlgTime::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgTime)
	DDX_Text(pDX, IDC_TIME_RANGE, m_strTimeRange);
	DDX_Text(pDX, IDC_ANI_NOOFSTEP, m_nNoOfStep);
	DDX_Text(pDX, IDC_ANI_SPEED, m_nSpeed);
	DDV_MinMaxInt(pDX, m_nSpeed, 0, 100);
	DDX_Text(pDX, IDC_ANI_START, m_nTimeStart);
	DDX_Text(pDX, IDC_ANI_STEP, m_nStep);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgTime, CDialog)
//{{AFX_MSG_MAP(CDlgTime)
// NOTE: the ClassWizard will add message map macros here
//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgTime message handlers

void CIdbDoc::OnViewGoend() 
{
	DoShowAnimation(m_nDBTimeE);
	((CMainFrame*)(AfxGetApp()->GetMainWnd()))->ShowAnimation(m_nDBCurrent, m_nDBTimeE);
}

void CIdbDoc::OnViewGohead() 
{
	DoShowAnimation(m_nDBTimeS);
	((CMainFrame*)(AfxGetApp()->GetMainWnd()))->ShowAnimation(m_nDBCurrent, m_nDBTimeE);
}

void CIdbDoc::OnViewNextstep() 
{
	if (m_nDBCurrent < m_nDBTimeE)
		DoShowAnimation(m_nDBCurrent + 1);
	else
		DoShowAnimation(m_nDBTimeS);
	((CMainFrame*)(AfxGetApp()->GetMainWnd()))->ShowAnimation(m_nDBCurrent, m_nDBTimeE);
}

void CIdbDoc::OnViewPlay() 
{
	for (int i=m_nDBTimeS; i <= m_nDBTimeE; i++)
	{
		DoShowAnimation(i);
		((CMainFrame*)(AfxGetApp()->GetMainWnd()))->ShowAnimation(i, m_nDBTimeE);
		if (nAniSleep > 0)
			Sleep(nAniSleep);
	}
}

void CIdbDoc::OnViewShapePlay(int StartTime, int EndTime) 
{
	for (int i=StartTime; i <= EndTime; i++)
	{
		DoShowAnimation(i);
		((CMainFrame*)(AfxGetApp()->GetMainWnd()))->ShowAnimation(i, m_nDBTimeE);
		if (nAniSleep > 0)
			Sleep(nAniSleep);
	}
}

void CIdbDoc::OnViewPlayback() 
{
	for (int i=m_nDBTimeE; i >= m_nDBTimeS; i--)
	{
		DoShowAnimation(i);
		((CMainFrame*)(AfxGetApp()->GetMainWnd()))->ShowAnimation(i, m_nDBTimeE);
		if (nAniSleep > 0)
			Sleep(nAniSleep);
	}
}

void CIdbDoc::OnViewPriorstep() 
{
	if (m_nDBCurrent > m_nDBTimeS)
		DoShowAnimation(m_nDBCurrent - 1);
	else
		DoShowAnimation(m_nDBTimeE);
	((CMainFrame*)(AfxGetApp()->GetMainWnd()))->ShowAnimation(m_nDBCurrent, m_nDBTimeE);
}


void CIdbDoc::OnViewExecutiontime() 
{
	// TODO: Add your command handler code here
	char strtime[100];
	char wraptime[100];
	char querytime[100];
	sprintf(strtime, "CPU Time for computation: %gs \n",m_dataBase.m_execution_time/ (double) CLOCKS_PER_SEC );
	sprintf(wraptime, "Wrap time:%gs \n", m_wrap_time/ (double) CLOCKS_PER_SEC);
	sprintf(querytime, "Query time:%gs \n", m_query_time/ (double) CLOCKS_PER_SEC);
	
	strcat(strtime, wraptime);
	strcat(strtime, querytime);
	AfxMessageBox(strtime);
	
}

void CIdbDoc::CreateRelation(ifstream& iStream, CString& fileName)
{
	char sData[30]; 
	
	//char drive[_MAX_DRIVE];
	//char dir[_MAX_DIR];
	//char fname[_MAX_FNAME];
	//char ext[_MAX_EXT];
	//_splitpath(fileName, drive, dir, fname, ext);
	
	//CString strRelName = fname;
	Relation* pRel = NULL;
	DB* dataBase = &m_dataBase;
	if ((*dataBase).numRels) 
	{
		int nNum = 0;
		SlistIter<Relation> relationListIter(*(*dataBase).m_pRelationList);
		Relation* p_r; 
		while(p_r = (Relation*)relationListIter())
		{
			String strName = p_r->Name();
			if (strName == fileName)
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
		b_existR = FALSE;
		String s = String(fileName);
		pRel = new Relation(s);
	}
	
	iStream >> sData;         // get ID of a polygon
	CString strData = sData;
	float id = (float)atof(sData);
	
	while( strData != "END" && strData != "end")
	{
		iStream >> sData;        // read in a label point
		iStream >> sData;
		Slist<Point>* pPointList= new Slist<Point>;
		
		iStream >> sData;
		strData = sData;
		
		while( strData != "END" && strData != "end")
		{
			
			float x = (float)atof(sData);
			
			iStream >> sData;
			float y = (float)atof(sData);
			Point* pPoint = new Point(x,y);
			
			pPointList->AppendHere(*pPoint);
			
			iStream >> sData;
			strData = sData;
			//   SlistIter<Relation> relIter(*((*dataBase).m_pRelationList));
			
		}
		//		float id = (float)atof(dlg.m_strID);
		pRel = PointsAddToRelation(pRel, pPointList, id);
		//pPointList->DeepDestroy();
		delete pPointList;
		
		iStream >> sData;         // get ID of a polygon
		strData = sData;
		id = (float)atof(sData);      
	}
	if( b_existR == FALSE)
	{
		pRel->m_Arity = 3;
		pRel->m_strAtriList.AddTail(CString("i"));
		pRel->m_strAtriList.AddTail(CString("x"));
		pRel->m_strAtriList.AddTail(CString("y"));
		for(int index = 1; index < m_nFields; index ++)
		{
			if (m_arrayFieldName[index] == "From")
			{ 
				pRel->m_strAtriList.AddTail(CString("t"));
				pRel->m_Arity++;
			}
			else if (m_arrayFieldName[index] != "To")
			{
				pRel->m_strAtriList.AddTail(m_arrayFieldName[index]);
				pRel->m_Arity ++;
			}
		}
		
		//	pRel = GetOtherColumns(pRel);
		dataBase->numRels++;
		dataBase->m_pRelationList->AppendHere(*pRel);
	}
	
	m_bResetDrawObj = TRUE;
	//	UpdateAllViews(NULL);
	return;		
}
/**************************************************
Create a relation by read in points information
***************************************************/
void CIdbDoc::CreatePointRelation(ifstream& iStream, CString& fileName)
{
	char sData[30]; 
	
	//char drive[_MAX_DRIVE];
	//char dir[_MAX_DIR];
	//char fname[_MAX_FNAME];
	//char ext[_MAX_EXT];
	//_splitpath(fileName, drive, dir, fname, ext);
	
	//CString strRelName = fname;
	Relation* pRel = NULL;
	DB* dataBase = &m_dataBase;
	if ((*dataBase).numRels) 
	{
		int nNum = 0;
		SlistIter<Relation> relationListIter(*(*dataBase).m_pRelationList);
		Relation* p_r; 
		while(p_r = (Relation*)relationListIter())
		{
			String strName = p_r->Name();
			if (strName == fileName)
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
		b_existR = FALSE;
		String s = String(fileName);
		pRel = new Relation(s);
	}
	
	iStream >> sData;         // get ID of a polygon
	CString strData = sData;
	float id = (float)atof(sData);
	
	/*while( strData != "END" && strData != "end")
	{
	iStream >> sData;        // read in a label point
	iStream >> sData;
	Slist<Point>* pPointList= new Slist<Point>;
	
	  iStream >> sData;
	  strData = sData;
	*/
	while( strData != "END" && strData != "end")
	{
		iStream >> sData;
		float x = (float)atof(sData);
        
		iStream >> sData;
		float y = (float)atof(sData);
		// Point* pPoint = new Point(x,y);
		
		//pPointList->AppendHere(*pPoint);
		Matrix<float>* p_m;   
		//Vector<float>* p_vec;
		Vector<float> vec1;
		//Vector<float> vec2; 
		int iCols = 5;
		//			BOOL bHasTime = bHasFromToAttribute();
		//
		//			if( bHasTime)
		//				iCols = (m_nFields -1) + 2 + 2; // From , To  generate  t attribute,
		//			else 									// id , x, y , OP, rvalue, and other attributes
		//				iCols = m_nFields + 2 + 2;
		
		vec1 = Vector<float>(iCols);
		
		//Point p[3];
		
		p_m = new Matrix<float>();
		
		vec1=0;
		vec1[0] = EQUAL; 
		vec1[1] = id; 
		vec1[2] = 1;
		m_dataBase.AddVectorToMatrix(p_m,&vec1);
		
		vec1=0;
		vec1[0] = EQUAL; 
		vec1[1] = x; 
		vec1[3] = 1;
		m_dataBase.AddVectorToMatrix(p_m,&vec1);
		
		vec1=0;
		vec1[0] = EQUAL; 
		vec1[1] = y; 
		vec1[4] = 1;
		m_dataBase.AddVectorToMatrix(p_m,&vec1);
		
		//			p_m -> Trace();
		pRel->AddMatrix(*p_m);
		
		//iStream >> sData;
		//strData = sData;
		//   SlistIter<Relation> relIter(*((*dataBase).m_pRelationList));
		
		
		//		float id = (float)atof(dlg.m_strID);
		//pRel = PointsAddToRelation(pRel, pPointList, id);
		//pPointList->DeepDestroy();
		//delete pPointList;
		
		iStream >> sData;         // get ID of a polygon
		strData = sData;
		id = (float)atof(sData);      
	}
	if( b_existR == FALSE)
	{
		pRel->m_Arity = 3;
		pRel->m_strAtriList.AddTail(CString("i"));
		pRel->m_strAtriList.AddTail(CString("x"));
		pRel->m_strAtriList.AddTail(CString("y"));
		/*for(int index = 1; index < m_nFields; index ++)
		{
		if (m_arrayFieldName[index] == "From")
		{ 
		pRel->m_strAtriList.AddTail(CString("t"));
		pRel->m_Arity++;
		}
		else if (m_arrayFieldName[index] != "To")
		{
		pRel->m_strAtriList.AddTail(m_arrayFieldName[index]);
		pRel->m_Arity ++;
		}
		}
		*/
		//	pRel = GetOtherColumns(pRel);
		dataBase->numRels++;
		dataBase->m_pRelationList->AppendHere(*pRel);
	}
	
	m_bResetDrawObj = TRUE;
	//	UpdateAllViews(NULL);
	return;		
}

void CIdbDoc::CreateRelationFromAccessTable(CString& fileName)
{
	
	Relation* pRel = NULL;
	DB* dataBase = &m_dataBase;
	if ((*dataBase).numRels) 
	{
		int nNum = 0;
		SlistIter<Relation> relationListIter(*(*dataBase).m_pRelationList);
		Relation* p_r; 
		while(p_r = (Relation*)relationListIter())
		{
			String strName = p_r->Name();
			if (strName == fileName)
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
		b_existR = FALSE;
		String s = String(fileName);
		pRel = new Relation(s);
	}
	pRel = ImportAccessTable(pRel);	
	
	
	if( b_existR == FALSE)
	{
		pRel->m_Arity = m_nFields;
		//	pRel->m_strAtriList.AddTail(CString("i"));
		//	pRel->m_strAtriList.AddTail(CString("x"));
		//	pRel->m_strAtriList.AddTail(CString("y"));
		for(int index = 0; index < m_nFields; index ++)
		{
			pRel->m_strAtriList.AddTail(m_arrayFieldName[index]);
		}
		
		//	pRel = GetOtherColumns(pRel);
		dataBase->numRels++;
		dataBase->m_pRelationList->AppendHere(*pRel);
	}
	
	m_bResetDrawObj = TRUE;
	//	UpdateAllViews(NULL);
	return;		
	
}

Relation* CIdbDoc::GetOtherColumns(Relation* pR)
{
	
    COleVariant var;
    CString str;
    //CIdbDoc* pDoc = GetDocument();
    for (int i = 0; i < m_nFields; i++) {
		var = m_pRecordset->GetFieldValue(i);
		switch (var.vt) {
		case VT_BSTR:
			str = (LPCSTR) var.bstrVal; // narrow characters in DAO
			break;
		case VT_I2:
			str.Format("%d", (int) var.iVal);
			break;
		case VT_I4:
			str.Format("%d", var.lVal);
			break;
		case VT_R4:
			str.Format("%10.2f", (double) var.fltVal);
			break;
		case VT_R8:
			str.Format("%10.2f", var.dblVal);
			break;
		case VT_CY:
			str = COleCurrency(var).Format();
			break;
		case VT_DATE:
			str = COleDateTime(var).Format();
			break;
		case VT_BOOL:
			str = (var.boolVal == 0) ? "FALSE" : "TRUE";
			break;
		case VT_NULL:
			str =  "----";
			break;
		default:
			str.Format("Unk type %d\n", var.vt);
			TRACE("Unknown type %d\n", var.vt);
		}
		//  pDC->TextOut(x, y, str);
		//  x += pDoc->m_arrayFieldSize[i] * m_nCharWidth;
	}
	return pR;
}

Relation* CIdbDoc::PointsAddToRelation(Relation*   p_r, 
									   Slist<Point>* pPList, float& id)
{
	DB* dataBase = &m_dataBase;
	Point p[3];
	double dx, dy;
	Point* p_Point;
    SlistIter<Point>  pIter(*pPList);
	
	switch ( pPList->Size()-1  ) 
	{
	case 0:
		return p_r;
	case 1:
		//		DPToLP(Obj->m_points[0], &dx, &dy);
        p_Point = (Point*) pIter();
        dx = p_Point->Getx();      
        dy = p_Point->Gety();
		
		p[0].m_x = (float)dx;
		p[0].m_y = (float)dy;
		p[1].m_x = (float)dx;
		p[1].m_y = (float)dy;
		p[2].m_x = (float)dx;
		p[2].m_y = (float)dy;
		p_r->AddMatrix(*GetMatrixFromIDPoints(id, p[0], p[1], p[2]));
		return p_r;
	case 2:
        p_Point = (Point*) pIter();
        dx = p_Point->Getx();      
        dy = p_Point->Gety();
		p[0].m_x = (float)dx;
		p[0].m_y = (float)dy;
		
		p_Point = (Point*) pIter();
        dx = p_Point->Getx();      
        dy = p_Point->Gety();
		p[1].m_x = (float)dx;
		p[1].m_y = (float)dy;
		p[2].m_x = (float)dx;
		p[2].m_y = (float)dy;
		p_r->AddMatrix(*GetMatrixFromIDPoints(id, p[0], p[1], p[2]));
		return p_r;
	default:
		int nPoints =  pPList->Size()-1;
		int ncontours = 1;
		int cntr[1];
        double (*vertices)[2]= (double(*)[2])malloc((nPoints+1)*sizeof(double[2]));
		int (*triangles)[3] = (int(*)[3])malloc((nPoints)*sizeof(int[3]));;
		int n, i;
		
		cntr[0] = nPoints;
		
		for(i = nPoints; i >= 1; i--)
		{
			p_Point = (Point*) pIter();
			vertices[i][0] = (double)p_Point->Getx() ; 	
			vertices[i][1] = (double)p_Point->Gety() ; 
		}
		
		n = triangulate_polygon(ncontours, cntr, vertices, triangles);
		
		for(i = 0; i < n; i++)
		{
			
			p[0].m_x = (float)vertices[ triangles[i][0]][0];
			p[0].m_y = (float)vertices[ triangles[i][0]][1];
			p[1].m_x = (float)vertices[ triangles[i][1]][0];
			p[1].m_y = (float)vertices[ triangles[i][1]][1];
			p[2].m_x = (float)vertices[ triangles[i][2]][0];
			p[2].m_y = (float)vertices[ triangles[i][2]][1];
			p_r->AddMatrix(*GetMatrixFromIDPoints(id, p[0], p[1], p[2]));
        }
		free( vertices);
		free( triangles);
		return p_r; 	
		
	} // end of switch
}

Relation* CIdbDoc::ImportAccessTable(Relation* pR)
{
	Matrix<float>* p_m = NULL;   
	//	Vector<float>* p_vec;
	Vector<float> vec1;
	Vector<float> vec2; 
	int iCols;
	
	iCols = m_nFields +2; // From , To  generate  t attribute,
	
	vec1 = Vector<float>(iCols);
	
	
	//	  p_m->Trace();
	// read in other attributes information		    
	for(int nRow=1; nRow < m_nRowCount; nRow++)
	{	
		p_m = new Matrix<float>();
		try {
			m_pRecordset->SetAbsolutePosition(nRow - 1); // adjust for title row
			// SetAbsolutePosition doesn't throw exception until AFTER 
			//  end of set
			if (m_pRecordset->GetAbsolutePosition() == (nRow - 1)) 
			{
				//COleVariant var;
			}
		}
		catch (CDaoException* e) {
			// might be a time delay before delete is seen in this program
			if (e->m_pErrorInfo->m_lErrorCode == 3167) {
				AfxMessageBox("**RECORD DELETED**");
			}
			else {
				m_pRecordset->MoveLast(); // in case m_nRowCount is too big
				m_nRowCount = m_pRecordset->GetAbsolutePosition() + 2;
			}
			e->Delete();
		}
		
		
		// begin to read infomation other than ID
		for (int i = 0; i < m_nFields; i++) 
		{
			//	CString strName = m_arrayFieldName[i];
			COleVariant var;
			var = m_pRecordset->GetFieldValue(i);   
			float fVal;
			switch (var.vt) {
			/*	  case VT_BSTR:
			str = (LPCSTR) var.bstrVal; // narrow characters in DAO
			break;
			case VT_I2:
			str.Format("%d", (int) var.iVal);
			break;
				*/
			case VT_I4:
				fVal = (float)  var.lVal;
				break;
			case VT_R4:
				fVal =  (float) var.fltVal;
				break;
			case VT_R8:
				fVal = (float) var.dblVal;
				break;
				/*		  case VT_CY:
				str = COleCurrency(var).Format();
				break;
				case VT_DATE:
				str = COleDateTime(var).Format();
				break;
				case VT_BOOL:
				str = (var.boolVal == 0) ? "FALSE" : "TRUE";
				break;
				case VT_NULL:
				str =  "----";
				break;
				default:
				str.Format("Unk type %d\n", var.vt);
				TRACE("Unknown type %d\n", var.vt);
				*/
			}
			
			vec1=0;
			vec1[0] = EQUAL; 
			vec1[1] = fVal;
			vec1[i+2] = 1;
			
			m_dataBase.AddVectorToMatrix(p_m,&vec1);
			//		p_m->Trace();
			
		} // end of for-- read other atts
		
		pR->AddMatrix(*p_m);
	}
	return pR;
}

Matrix<float>* CIdbDoc::GetMatrixFromIDPoints(float id, Point p0, Point p1, Point p2)
{
	
	Matrix<float>* p_m;   
	Vector<float>* p_vec;
	Vector<float> vec1;
	Vector<float> vec2; 
	int iCols;
	BOOL bHasTime = bHasFromToAttribute();
	
	if( bHasTime)
		iCols = (m_nFields -1) + 2 + 2; // From , To  generate  t attribute,
	else 									// id , x, y , OP, rvalue, and other attributes
		iCols = m_nFields + 2 + 2;
	
	vec1 = Vector<float>(iCols);
	
	Point p[3];
	
	p_m = new Matrix<float>();
	
	vec1=0;
	vec1[0] = 5; 
	vec1[1] = id; 
	vec1[2] = 1;
	m_dataBase.AddVectorToMatrix(p_m,&vec1);
	
	
	if( (p0==p1)&&(p1==p2)){ // 3 points is same
		vec1=0;
		vec1[0]=5;
		vec1[1]=p0.m_x;
		vec1[3]=1;
		m_dataBase.AddVectorToMatrix(p_m,&vec1);
		vec1=0;
		vec1[0]=5;
		vec1[1]= p0.m_y;
		vec1[4]=1;
		m_dataBase.AddVectorToMatrix(p_m,&vec1);
	}
	else
	{ 
		if( p0==p1) { 
			Point temp = p1;
			p1 = p2;
			p2 = temp;
		} 
		// cout<<p[0]<<p[1]<<p[2]<< endl; 
		if(!CoLine(p0,p1,p2))
		{ 
			p_vec = GetVectorFromPoints(p0,p1,p2);
			vec2 = *p_vec;
			delete p_vec;
			
			vec1=0;
			for(int index = 0; index < vec2.Size(); index++)
			{
				vec1[index] = vec2[index];
			}
			m_dataBase.AddVectorToMatrix(p_m,&vec1);
			p_vec = GetVectorFromPoints(p1,p2,p0);
			vec2 = *p_vec;
			delete p_vec;
			
			vec1=0;
			for( index = 0; index < vec2.Size(); index++)
			{
				vec1[index] = vec2[index];
			}
			m_dataBase.AddVectorToMatrix(p_m,&vec1);
			p_vec = GetVectorFromPoints(p2,p0,p1);
			vec2 = *p_vec;
			delete p_vec;
			
			vec1=0;
			for(index = 0; index < vec2.Size(); index++)
			{
				vec1[index] = vec2[index];
			}
			
			m_dataBase.AddVectorToMatrix(p_m,&vec1);  
		}
		else {  // 3 points coline 
			p_vec = GetVectorFromPoints(p0,p1,p2);
			vec2 = *p_vec;
			delete p_vec;
			
			vec1=0;
			for(int index = 0; index < vec2.Size(); index++)
			{
				vec1[index] = vec2[index];
			}		   
			vec1[0] = 5;
			m_dataBase.AddVectorToMatrix(p_m,&vec1);           
			if(p0.m_x != p1.m_x)
			{
				float min = (p0.m_x < p1.m_x)? p0.m_x : p1.m_x;
				min = (min < p2.m_x)? min : p2.m_x;
				float max = (p0.m_x < p1.m_x)? p1.m_x : p0.m_x;
				max = (max < p2.m_x)? p2.m_x : max;
				vec1 = 0;
				vec1[0]=2; // ">="
				vec1[1] = -min;
				vec1[3] = -1;
				m_dataBase.AddVectorToMatrix(p_m,&vec1);
				vec1 = 0;
				vec1[0]=2; // "<="
				vec1[1] = max;
				vec1[3] = 1;
				m_dataBase.AddVectorToMatrix(p_m,&vec1);
			}
            else{ // x1 == x2
				float min = (p0.m_y < p1.m_y)? p0.m_y : p1.m_y;
				min = (min < p2.m_y)? min : p2.m_y;
				float max = (p0.m_y < p1.m_y)? p1.m_y : p0.m_y;
				max = (max < p2.m_y)? p2.m_y : max;
				vec1 = 0;
				vec1[0]=2; // ">="
				vec1[1] = -min;
				vec1[4] = -1;
				m_dataBase.AddVectorToMatrix(p_m,&vec1);
				vec1 = 0;
				vec1[0]=2; // "<="
				vec1[1] = max;
				vec1[4] = 1;
				m_dataBase.AddVectorToMatrix(p_m,&vec1);
			}                  
		}
	}
	//	  p_m->Trace();
	// read in other attributes information		    
	for(int nRow=1; nRow <= m_nRowCount; nRow++)
	{
		try {
			m_pRecordset->SetAbsolutePosition(nRow - 1); // adjust for title row
			// SetAbsolutePosition doesn't throw exception until AFTER 
			//  end of set
			if (m_pRecordset->GetAbsolutePosition() == (nRow - 1)) 
			{
				COleVariant var;
				//CString str;
				//for (int i = 0; i < m_nFields; i++) {
				var = m_pRecordset->GetFieldValue(0);   // i = ? 
				float fid = (float) var.lVal;
				if( fid == id ) 
					break;
			}
		}
		catch (CDaoException* e) {
			// might be a time delay before delete is seen in this program
			if (e->m_pErrorInfo->m_lErrorCode == 3167) {
				AfxMessageBox("**RECORD DELETED**");
			}
			else {
				m_pRecordset->MoveLast(); // in case m_nRowCount is too big
				m_nRowCount = m_pRecordset->GetAbsolutePosition() + 2;
			}
			e->Delete();
		}
	}
	// begin to read infomation other than ID
	
	for (int i = 1; i < m_nFields; i++) 
	{
		//	CString strName = m_arrayFieldName[i];
		COleVariant var;
		var = m_pRecordset->GetFieldValue(i);   
		float fVal;
		switch (var.vt) {
		/*	  case VT_BSTR:
		str = (LPCSTR) var.bstrVal; // narrow characters in DAO
		break;
		case VT_I2:
		str.Format("%d", (int) var.iVal);
		break;
			*/
		case VT_I4:
			fVal = (float)  var.lVal;
			break;
		case VT_R4:
			fVal =  (float) var.fltVal;
			break;
		case VT_R8:
			fVal = (float) var.dblVal;
			break;
			/*		  case VT_CY:
			str = COleCurrency(var).Format();
			break;
			case VT_DATE:
			str = COleDateTime(var).Format();
			break;
			case VT_BOOL:
			str = (var.boolVal == 0) ? "FALSE" : "TRUE";
			break;
			case VT_NULL:
			str =  "----";
			break;
			default:
			str.Format("Unk type %d\n", var.vt);
			TRACE("Unknown type %d\n", var.vt);
			*/
		}
		if((m_arrayFieldName[i] == "From") && bHasTime)
		{
			vec1=0;
			vec1[0] = LESSEQUAL; 
			vec1[1] = -fVal;
			vec1[i+4] = -1;
		}
		else if((m_arrayFieldName[i] == "To") && bHasTime)
		{
			vec1=0;
			vec1[0] = LESSEQUAL; 
			vec1[1] = fVal;
			vec1[i+3] = 1;
		}
		else 
		{
			vec1=0;
			vec1[0] = EQUAL; 
			vec1[1] = fVal;
			if(bHasTime)
				vec1[i+3] = 1;
			else vec1[i+4] = 1;
		}
		m_dataBase.AddVectorToMatrix(p_m,&vec1);
		//		p_m->Trace();
		
	} // end of for-- read other atts
	
	return   p_m; 
}


void CIdbDoc::OnViewSamerelationcolor() 
{
	m_bSameRelationColor = ! m_bSameRelationColor;
	UpdateAllViews(NULL);
}

void CIdbDoc::OnUpdateViewSamerelationcolor(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(m_bSameRelationColor);	
}

void CIdbDoc::OnUpdateViewTime(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(!(m_nDBTimeS == 0  &&  m_nDBTimeE == 0));
}

void CIdbDoc::OnUpdateViewPriorstep(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(!(m_nDBTimeS == 0  &&  m_nDBTimeE == 0));
}


void CIdbDoc::OnUpdateViewGoend(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(!(m_nDBTimeS == 0  &&  m_nDBTimeE == 0));
}

void CIdbDoc::OnUpdateViewGohead(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(!(m_nDBTimeS == 0  &&  m_nDBTimeE == 0));
}

void CIdbDoc::OnUpdateViewNextstep(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(!(m_nDBTimeS == 0  &&  m_nDBTimeE == 0));
}

void CIdbDoc::OnUpdateViewPlay(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(!(m_nDBTimeS == 0  &&  m_nDBTimeE == 0));
}

void CIdbDoc::OnUpdateViewPlayback(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(!(m_nDBTimeS == 0  &&  m_nDBTimeE == 0));
}

void CIdbDoc::OnButtonMin() 
{
	if (m_listRelation.GetCount() != 1)
	{
		AfxMessageBox("You should select 1 relation!");
		return;
	}
	
	Relation* pR;
	POSITION pos = m_listRelation.GetHeadPosition();
	
	CDlgMaxMin dlg;
	dlg.m_maxmin_constant=0;
	
	if (dlg.DoModal() == IDOK)
	{ 
		while (pos != NULL)
		{
			pR = (Relation*)(m_listRelation.GetNext(pos));
		}
		
		CString atri, atri2;
		pos=pR->m_strAtriList.GetHeadPosition();
		for(int i=0; i<pR->m_Arity; i++){
			atri=pR->m_strAtriList.GetNext(pos);
			
			if(atri2!="") atri2+=", ";
			atri2+=atri;
		}
		
		ofstream outFile("TEMPTEMP.TXT");
		if (!outFile)
			AfxMessageBox("Internal File Error!");
		else
		{
			outFile << "begin%Temp%\n";
			outFile << dlg.m_maxmin_name <<"(MIN(evalfunction)) :-" \
				<< pR->m_sName<<"(" << atri2 <<"),\n" \
				<< dlg.m_maxmin_function <<"- evalfunction ="<<-dlg.m_maxmin_constant<<".\n";
			outFile << "end%Temp%\n";
			outFile.close();
			
			DoCalculate("TEMPTEMP.TXT");
			UpdateAllViews(NULL);
		}
	}	
}

void CIdbDoc::OnButtonMax() 
{
	if (m_listRelation.GetCount() != 1)
	{
		AfxMessageBox("You should select 1 relation!");
		return;
	}
	
	Relation* pR;
	POSITION pos = m_listRelation.GetHeadPosition();
	
	CDlgMaxMin dlg;
	dlg.m_maxmin_constant=0;
	
	if (dlg.DoModal() == IDOK)
	{ 
		while (pos != NULL)
		{
			pR = (Relation*)(m_listRelation.GetNext(pos));
		}
		
		CString atri, atri2;
		pos=pR->m_strAtriList.GetHeadPosition();
		for(int i=0; i<pR->m_Arity; i++){
			atri=pR->m_strAtriList.GetNext(pos);
			
			if(atri2!="") atri2+=", ";
			atri2+=atri;
		}
		
		ofstream outFile("TEMPTEMP.TXT");
		if (!outFile)
			AfxMessageBox("Internal File Error!");
		else
		{
			outFile << "begin%Temp%\n";
			outFile << dlg.m_maxmin_name <<"(MAX(evalfunction)) :-" \
				<< pR->m_sName<<"(" << atri2 <<"),\n" \
				<< dlg.m_maxmin_function <<"- evalfunction ="<<-dlg.m_maxmin_constant<<".\n";
			outFile << "end%Temp%\n";
			outFile.close();
			
			DoCalculate("TEMPTEMP.TXT");
			UpdateAllViews(NULL);
		}
	}	
}

void CIdbDoc::OnUpdateButtonMax(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(!(m_dataBase.STDB));
}

void CIdbDoc::OnUpdateButtonMin(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(!(m_dataBase.STDB));
}

void CIdbDoc::SetWrapTime()
{
	clock_t new_wrap_time = clock();
	
	//  sprintf(strtime, "CPU Time for computation: %gs \n", (new_db_time - last_db_time) / (
	//				double) CLOCKS_PER_SEC);
	m_wrap_time = (new_wrap_time - last_wrap_time); // (double) CLOCKS_PER_SEC;
	//	((CMainFrame*)(AfxGetApp()->GetMainWnd()))->ShowTime(strtime);
	//  last_wrap_time = new_wrap_time;
}

void CIdbDoc::SetQueryTime()
{
	clock_t new_query_time = clock();
	m_query_time = (new_query_time - last_query_time); // (double) CLOCKS_PER_SEC;
}

BOOL CIdbDoc::bHasFromToAttribute()
{
	for ( int i = 0; i< m_nFields; i++)
	{
		if( m_arrayFieldName[i] == "From")
			break;
	}
	if (i == m_nFields) return FALSE;
	
	for ( i = 0; i< m_nFields; i++)
	{
		if( m_arrayFieldName[i] == "To")
			break;
	}
	if (i == m_nFields) return FALSE;
	return TRUE;
}


void CIdbDoc::OnFileImport() 
{
	CString fileName;
	DWORD lFlags = OFN_HIDEREADONLY | OFN_FILEMUSTEXIST | OFN_ALLOWMULTISELECT ; 
	
	BOOL bOpenFileDialog = TRUE;
	CString strFilter;
	CFileDialog dlgFile(bOpenFileDialog);
	dlgFile.m_ofn.Flags |= lFlags;
	
	strFilter += _T("*.pol");
	strFilter += (TCHAR)'\0';   // last string
	dlgFile.m_ofn.lpstrFilter = strFilter;
	dlgFile.m_ofn.lpstrFileTitle  = "*.pol";
	dlgFile.m_ofn.lpstrFile = fileName.GetBuffer(_MAX_PATH);
	//	strcat(dlgFile.m_ofn.lpstrFile, "*.pol");
	dlgFile.m_ofn.lpstrFile[0] = '*';
	dlgFile.m_ofn.lpstrFile[1] = '.';
	dlgFile.m_ofn.lpstrFile[2] = 'p';
	dlgFile.m_ofn.lpstrFile[3] = 'o';
	dlgFile.m_ofn.lpstrFile[4] = 'l';
	dlgFile.m_ofn.lpstrFile[5] = '\0';
	
	
	BOOL bResult = dlgFile.DoModal() == IDOK ? TRUE : FALSE;
	if(TRUE==bResult)
	{	
		CDlgRelName dlg(this);
		if (dlg.DoModal() != IDOK)
			return;
		
		if ( (dlg.m_strRel).IsEmpty()  )
		{
			AfxMessageBox("Relation Name  must not be empty!");
			return;
		}
		
		last_wrap_time=clock();            
		
		//  database operation
		PutQuery();
		m_strDatabase = dlg.m_strRel ;
		m_strDatabase += ".MDB";
		if( ! DaoOpenMdb())
		{
			return;
		}
		
		CString fileName;
		POSITION pos = dlgFile.GetStartPosition( );
		while( pos )
		{
			fileName = dlgFile.GetNextPathName( pos);
			char drive[_MAX_DRIVE];
			char dir[_MAX_DIR];
			char fname[_MAX_FNAME];
			char ext[_MAX_EXT];
			_splitpath(fileName, drive, dir, fname, ext);
			
			if(! OpenRecordset(fname))
			{
				return;
			}
			ifstream* iStream = new ifstream(fileName) ;
			
			if(NULL == iStream)
			{
				TRACE( "Can't open file %s", fileName);
				fileName.ReleaseBuffer();
			}
			else
			{
				
				//char drive[_MAX_DRIVE];
				//char dir[_MAX_DIR];
				//char fname[_MAX_FNAME];
				//char ext[_MAX_EXT];
				//_splitpath(fileName, drive, dir, fname, ext);
				
				
				
				CreateRelation(*iStream, dlg.m_strRel );
				
				m_bAddRelation = TRUE;
				
				//fileName.ReleaseBuffer();
				iStream->close();
				//delete iStream; 
				SetMatrixTime(dataBase);
				DoReCalculate(m_nDBTimeS);
				iStream->close();
				delete iStream;
			}
		}
		SetWrapTime();
		
	}
	else 
	{
		fileName.ReleaseBuffer();
	}
	
	/*	used for debug
	fileName = "D:\\auser\\wyh\\lcsnew\\land.pol";
	ifstream* iStream = new ifstream(fileName) ;	
	CreateRelation(*iStream, fileName);
	iStream->close();
	return;
	*/
	UpdateAllViews(NULL);				
	return;
}


void CIdbDoc::OnImportMdb() 
{
	m_strDatabase.Empty();
    if (m_strDatabase.IsEmpty()) {
		CFileDialog dlg(TRUE, ".mdb", "*.mdb");
		if (dlg.DoModal() == IDCANCEL) return;
		m_strDatabase = dlg.GetPathName();
    }
	
	if(m_daoDB.IsOpen())
		m_daoDB.Close();
    BeginWaitCursor();
    try {
		// nonexclusive, read-only
		m_daoDB.Open(m_strDatabase, FALSE, TRUE);
    }
    catch (CDaoException* e) {
		::DaoErrorMsg(e);
		EndWaitCursor();
		e->Delete();
		return;
    }
    m_strDatabase = m_daoDB.GetName();
    TRACE("database name = %s, connect = %s\n",
		(const char*) m_strDatabase, (const char*) m_strConnect);
    OpenRecordset();
	m_nDatabaseType = MDB;
    EndWaitCursor();	
}

void CIdbDoc::OnFileImportfilePoint() 
{
	CString fileName;
	DWORD lFlags = OFN_HIDEREADONLY | OFN_FILEMUSTEXIST | OFN_ALLOWMULTISELECT ; 
	
	BOOL bOpenFileDialog = TRUE;
	CString strFilter;
	CFileDialog dlgFile(bOpenFileDialog);
	dlgFile.m_ofn.Flags |= lFlags;
	
	strFilter += _T("*.pol");
	strFilter += (TCHAR)'\0';   // last string
	dlgFile.m_ofn.lpstrFilter = strFilter;
	dlgFile.m_ofn.lpstrFileTitle  = "*.pol";
	dlgFile.m_ofn.lpstrFile = fileName.GetBuffer(_MAX_PATH);
	//	strcat(dlgFile.m_ofn.lpstrFile, "*.pol");
	dlgFile.m_ofn.lpstrFile[0] = '*';
	dlgFile.m_ofn.lpstrFile[1] = '.';
	dlgFile.m_ofn.lpstrFile[2] = 'p';
	dlgFile.m_ofn.lpstrFile[3] = 'n';
	dlgFile.m_ofn.lpstrFile[4] = 't';
	dlgFile.m_ofn.lpstrFile[5] = '\0';
	
	
	BOOL bResult = dlgFile.DoModal() == IDOK ? TRUE : FALSE;
	if(TRUE==bResult)
	{	
		CDlgRelName dlg(this);
		if (dlg.DoModal() != IDOK)
			return;
		
		if ( (dlg.m_strRel).IsEmpty()  )
		{
			AfxMessageBox("Relation Name  must not be empty!");
			return;
		}
		
		last_wrap_time=clock();            
		
		//  database operation
		/*		 PutQuery();
		m_strDatabase = dlg.m_strRel ;
		m_strDatabase += ".MDB";
		if( ! DaoOpenMdb())
		{
		return;
		}
		*/
		CString fileName;
		POSITION pos = dlgFile.GetStartPosition( );
		while( pos )
		{
			fileName = dlgFile.GetNextPathName( pos);
			char drive[_MAX_DRIVE];
			char dir[_MAX_DIR];
			char fname[_MAX_FNAME];
			char ext[_MAX_EXT];
			_splitpath(fileName, drive, dir, fname, ext);
			
			//			if(! OpenRecordset(fname))
			//			{
			//				return;
			//			}
			ifstream* iStream = new ifstream(fileName) ;
			
			if(NULL == iStream)
			{
				TRACE( "Can't open file %s", fileName);
				fileName.ReleaseBuffer();
			}
			else
			{
				
				//char drive[_MAX_DRIVE];
				//char dir[_MAX_DIR];
				//char fname[_MAX_FNAME];
				//char ext[_MAX_EXT];
				//_splitpath(fileName, drive, dir, fname, ext);
				
				
				
				CreatePointRelation(*iStream, dlg.m_strRel );
				
				m_bAddRelation = TRUE;
				
				//fileName.ReleaseBuffer();
				iStream->close();
				//delete iStream; 
				SetMatrixTime(dataBase);
				DoReCalculate(m_nDBTimeS);
				iStream->close();
				delete iStream;
			}
		}
		SetWrapTime();
		
	}
	else 
	{
		fileName.ReleaseBuffer();
	}
	
	/*	used for debug
	fileName = "D:\\auser\\wyh\\lcsnew\\land.pol";
	ifstream* iStream = new ifstream(fileName) ;	
	CreateRelation(*iStream, fileName);
	iStream->close();
	return;
	*/
	UpdateAllViews(NULL);				
	return;	
}

void CIdbDoc::OnFileExport() 
{
	CDlgExport dlg;
	if (dlg.DoModal() != IDOK)
		return;
	
	if ( (dlg.m_sSpatial).IsEmpty()  )
	{
		AfxMessageBox("Spatial information file name  must not be empty!");
		return;
	}
	
	if (m_listRelation.GetCount() != 1)
	{
		AfxMessageBox("You should select one relation!");
		return;
	}
	
	ofstream outFile(dlg.m_sSpatial);
	if (!outFile)
		AfxMessageBox("Internal File Error!");
	
	Relation* pR;
	POSITION pos = m_listRelation.GetHeadPosition();
	
	//	int nNum=-1;
	while (pos != NULL)
	{
		pR = (Relation*)(m_listRelation.GetNext(pos));
		//		nNum++;
		
		ASSERT(pR != NULL);
		String strName = pR->Name();
		
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
					&& 	(m_nDBCurrent < p_matrix->m_nTimeS  
					||  m_nDBCurrent > p_matrix->m_nTimeE))
					continue;
				
				Slist<ParaPoint>* pointList = p_matrix->m_pList;
				if (pointList != NULL)
				{
					
					for(int i=0; i< p_matrix->Rows(); i++)
					{
						Vector<float> vector = (*p_matrix)[i];
						if(vector[2] == 1 && vector[0] == EQUAL)
						{
							outFile << vector[1] << ", AUTO" << endl;
							break;
						}
					}
					
					Snode<ParaPoint>* nPtr = pointList->headPtr ;
					i = 0;
					int nPointCount = 0;
					while(i < pointList->len)
					{
						if (((ParaPoint*)(nPtr->itemPtr))->m_bShow)
						{
							outFile << ((ParaPoint*)(nPtr->itemPtr))->m_fX;
							outFile << "	";
							outFile << 	((ParaPoint*)(nPtr->itemPtr))->m_fY;
							outFile << endl;
						}
						i++;
						nPtr = nPtr->nextPtr;
					}
					outFile << "END" << endl;
				}
			} // while
		} // switch
	} // while	
	outFile << "END" << endl;
	outFile.close();	
}

void CIdbDoc::OnButtonSimQuery() 
{
	CIdbDoc* pDoc = this;//GetDocument();
	ASSERT(pDoc != NULL);
	if (pDoc->m_listRelation.GetCount() != 1)
	{
		AfxMessageBox("You should select one prototype!");
		return;
	}
	
	Vector<String>* m_pProtoVec=new Vector<String>; 
	
	Relation* pR;
	POSITION pos = pDoc->m_listRelation.GetHeadPosition();
	
	while (pos != NULL)
	{
		pR = (Relation*)(pDoc->m_listRelation.GetNext(pos));
		int size = m_pProtoVec->Size();
		m_pProtoVec->Resize(size+1);
		(*m_pProtoVec)[size]= pR->m_sName;		
	}
	DB* dataBase = &(pDoc->m_dataBase);
	
	///////////////////////////////////////
	//assignment starts from here onwards//
	///////////////////////////////////////
	
	Ppic[0].nextp=NULL;
	pp=(struct Line *)malloc(sizeof(struct Line));
	DFIter<Matrix<float> >  pR_matrixIter(*(pR->m_tablePtr));
	Matrix<float> * pR_matrix;
	pR_matrix=pR_matrixIter();
	const ParaPoint *pt1=(pR_matrix->m_pList)->GotoHead();
	const ParaPoint *pt2=(pR_matrix->m_pList)->Next();
	pp->x1=pt1->m_fX;
	pp->y1=pt1->m_fY;
	pp->x2=pt2->m_fX;
	pp->y2=pt2->m_fY;
	pp->nextl=NULL;
	Ppic->lseg=pp;
	nextp=pp;
	for(m_i=1;m_i<pR->NumberOfMatrixes();m_i++)
	{
		pp=(struct Line *)malloc(sizeof(struct Line));
		pR_matrix=pR_matrixIter();
		const ParaPoint *pt1=(pR_matrix->m_pList)->GotoHead();
		const ParaPoint *pt2=(pR_matrix->m_pList)->Next();
		pp->x1=pt1->m_fX;
		pp->y1=pt1->m_fY;
		pp->x2=pt2->m_fX;
		pp->y2=pt2->m_fY;
		pp->nextl=NULL;
		nextp->nextl=pp;
		pp->nextl=NULL;
		nextp=nextp->nextl;
	}
	
	Dpic=(struct pic_t *)malloc(sizeof(struct pic_t));
	dp=Dpic;
	dp->nextp=NULL;
	SlistIter<Relation> relationListIter(*(*dataBase).m_pRelationList);
	Relation* p_r; 
	int ctr=0;
	while(p_r = (Relation*)relationListIter())
	{
		String strName = p_r->Name();
		int position = m_pProtoVec->Search(strName);
		if(position==-1)
		{
			pp=(struct Line *)malloc(sizeof(struct Line));
			DFIter<Matrix<float> >  pR_matrixIter(*(p_r->m_tablePtr));
			//Matrix<float> * pR_matrix;
			pR_matrix=pR_matrixIter();
			const ParaPoint *pt1=(pR_matrix->m_pList)->GotoHead();
			const ParaPoint *pt2=(pR_matrix->m_pList)->Next();
			pp->x1=pt1->m_fX;
			pp->y1=pt1->m_fY;
			pp->x2=pt2->m_fX;
			pp->y2=pt2->m_fY;
			pp->nextl=NULL;
			dp->lseg=pp;
			nextp=pp;
			for(m_i=1;m_i<pR->NumberOfMatrixes();m_i++)
			{
				pp=(struct Line *)malloc(sizeof(struct Line));
				pR_matrix=pR_matrixIter();
				const ParaPoint *pt1=(pR_matrix->m_pList)->GotoHead();
				const ParaPoint *pt2=(pR_matrix->m_pList)->Next();
				pp->x1=pt1->m_fX;
				pp->y1=pt1->m_fY;
				pp->x2=pt2->m_fX;
				pp->y2=pt2->m_fY;
				pp->nextl=NULL;
				nextp->nextl=pp;
				//pp->nextl=NULL;
				nextp=nextp->nextl;
			}
			ctr++;
			if(ctr<((*dataBase).numRels-1))
			{
				dp->nextp=(struct pic_t *)malloc(sizeof(struct pic_t));
				dp=dp->nextp;
				dp->nextp=NULL;
			}
			else
				dp->nextp=NULL;
		}
	}
	tot_cost=simCal(m_option,Ppic,Dpic);
	
	relationListIter.Reset();
	m_i=0;
	while(p_r = (Relation*)relationListIter())
	{
		int position = m_pProtoVec->Search(p_r->m_sName);
		CString strOut(" ");
		if(position==-1)
		{
			strOut += (p_r->m_sName).GetText();
			strOut += " (";
			char cTemp[10];
			sprintf(cTemp, "%6.2lf ", tot_cost[0][m_i]);
			strOut += cTemp;
			strOut += ")";
			sprintf(p_r->m_sOutput, "%s", strOut);
			m_i++;
		}
		else
		{
			strOut += (p_r->m_sName).GetText();
			strOut += " (Prototype)";
			sprintf(p_r->m_sOutput, "%s", strOut);
		}
	}
	delete m_pProtoVec;
	UpdateAllViews(NULL);
}

void CIdbDoc::OnImportLine() 
{
	CString fileName;
	DWORD lFlags = OFN_HIDEREADONLY | OFN_FILEMUSTEXIST | OFN_ALLOWMULTISELECT ; 
	
	BOOL bOpenFileDialog = TRUE;
	CString strFilter;
	CFileDialog dlgFile(bOpenFileDialog);
	dlgFile.m_ofn.Flags |= lFlags;
	
	strFilter += _T("*.lin");
	strFilter += (TCHAR)'\0';   // last string
	dlgFile.m_ofn.lpstrFilter = strFilter;
	dlgFile.m_ofn.lpstrFileTitle  = "*.lin";
	dlgFile.m_ofn.lpstrFile = fileName.GetBuffer(_MAX_PATH);
	//	strcat(dlgFile.m_ofn.lpstrFile, "*.pol");
	dlgFile.m_ofn.lpstrFile[0] = '*';
	dlgFile.m_ofn.lpstrFile[1] = '.';
	dlgFile.m_ofn.lpstrFile[2] = 'l';
	dlgFile.m_ofn.lpstrFile[3] = 'i';
	dlgFile.m_ofn.lpstrFile[4] = 'n';
	dlgFile.m_ofn.lpstrFile[5] = '\0';
	
	
	BOOL bResult = dlgFile.DoModal() == IDOK ? TRUE : FALSE;
	if(TRUE==bResult)
	{	
		CDlgRelName dlg(this);
		if (dlg.DoModal() != IDOK)
			return;
		
		if ( (dlg.m_strRel).IsEmpty()  )
		{
			AfxMessageBox("Relation Name  must not be empty!");
			return;
		}
		
		last_wrap_time=clock();            
		
		CString fileName;
		POSITION pos = dlgFile.GetStartPosition( );
		while( pos )
		{
			fileName = dlgFile.GetNextPathName( pos);
			char drive[_MAX_DRIVE];
			char dir[_MAX_DIR];
			char fname[_MAX_FNAME];
			char ext[_MAX_EXT];
			_splitpath(fileName, drive, dir, fname, ext);
			
			ifstream* iStream = new ifstream(fileName) ;
			
			if(NULL == iStream)
			{
				TRACE( "Can't open file %s", fileName);
				fileName.ReleaseBuffer();
			}
			else
			{
				
				//AfxMessageBox("I got here!!");
				//return;
				CreateLineRelations(*iStream, dlg.m_strRel);
				
				m_bAddRelation = TRUE;
				
				//fileName.ReleaseBuffer();
				iStream->close();
				//delete iStream; 
				SetMatrixTime(dataBase);
				DoReCalculate(m_nDBTimeS);
				iStream->close();
				delete iStream;
			}
		}
		SetWrapTime();
		
	}
	else 
	{
		fileName.ReleaseBuffer();
	}
	
	UpdateAllViews(NULL);				
	return;
}

//////////////////////////////////////////////////////////
/* Create relations by reading in the lines information */
//////////////////////////////////////////////////////////
void CIdbDoc::CreateLineRelations(ifstream& iStream, CString& fileName)
{
	char sData[30]; 
	int ctr=1;		
	
	DB* dataBase = &m_dataBase;
	ImportLineFlag=TRUE;
	/*if ((*dataBase).numRels) 
	{
	int nNum = 0;
	SlistIter<Relation> relationListIter(*(*dataBase).m_pRelationList);
	Relation* p_r; 
	while(p_r = (Relation*)relationListIter())
	{
	String strName = p_r->Name();
	if (strName == fileName)
	{
				pRel = p_r;
				break;
				}
				nNum++;
				}
}*/
again:
	
	Relation* pRel = NULL;
	BOOL b_existR = TRUE;
	
	if (pRel == NULL)
	{
		b_existR = FALSE;
		String s = String(fileName);
		CString stmp;
		char ctmp[32];
		sprintf(ctmp,"%d",ctr);
		stmp += s.GetText();
		stmp += ctmp;
		stmp += "\0";
		s=(String)stmp;
		pRel = new Relation(s);
	}
	
	//iStream >> sData;         // get ID of a polygon
	//CString strData = sData;
	float id = (float)ctr;
	
	
	while(1)
	{
		if(iStream.eof())
			goto out;
		iStream >> sData;
		CString strData=sData;
		if (strData=="END" || strData=="end")
			break;
		float x1 = (float)atof(sData);
		iStream >> sData;
		float y1 = (float)atof(sData);
		iStream >> sData;
		float x2 = (float)atof(sData);
		iStream >> sData;
		float y2 = (float)atof(sData);
		// Point* pPoint = new Point(x,y);
		
		//pPointList->AppendHere(*pPoint);
		Matrix<float>* p_m;   
		//Vector<float>* p_vec;
		Vector<float> vec1;
		//Vector<float> vec2; 
		int iCols = 7;
		
		vec1 = Vector<float>(iCols);
		
		//Point p[3];
		
		p_m = new Matrix<float>();
		
		vec1=0;
		vec1[0] = EQUAL; 
		vec1[1] = id; 
		vec1[2] = 1;
		m_dataBase.AddVectorToMatrix(p_m,&vec1);
		
		vec1=0;
		vec1[0] = EQUAL; 
		vec1[1] = x1; 
		vec1[3] = 1;
		m_dataBase.AddVectorToMatrix(p_m,&vec1);
		
		vec1=0;
		vec1[0] = EQUAL; 
		vec1[1] = y1; 
		vec1[4] = 1;
		m_dataBase.AddVectorToMatrix(p_m,&vec1);
		
		vec1=0;
		vec1[0] = EQUAL; 
		vec1[1] = x2; 
		vec1[5] = 1;
		m_dataBase.AddVectorToMatrix(p_m,&vec1);
		
		vec1=0;
		vec1[0] = EQUAL; 
		vec1[1] = y2; 
		vec1[6] = 1;
		m_dataBase.AddVectorToMatrix(p_m,&vec1);
		//p_m -> Trace();
		pRel->AddMatrix(*p_m);
		
		
		//iStream >> sData;
		//strData = sData;
		//   SlistIter<Relation> relIter(*((*dataBase).m_pRelationList));
		
		
		//		float id = (float)atof(dlg.m_strID);
		//pRel = PointsAddToRelation(pRel, pPointList, id);
		//pPointList->DeepDestroy();
		//delete pPointList;
		
		//iStream >> sData;         // get ID of a polygon
		//strData = sData;
		//id = (float)atof(sData);      
	}
	if( b_existR == FALSE)
	{
		pRel->m_Arity = 5;
		pRel->m_strAtriList.AddTail(CString("i"));
		pRel->m_strAtriList.AddTail(CString("x"));
		pRel->m_strAtriList.AddTail(CString("y"));
		pRel->m_strAtriList.AddTail(CString("x2"));
		pRel->m_strAtriList.AddTail(CString("y2"));
		/*for(int index = 1; index < m_nFields; index ++)
		{
		if (m_arrayFieldName[index] == "From")
		{ 
		pRel->m_strAtriList.AddTail(CString("t"));
		pRel->m_Arity++;
		}
		else if (m_arrayFieldName[index] != "To")
		{
		pRel->m_strAtriList.AddTail(m_arrayFieldName[index]);
		pRel->m_Arity ++;
		}
		}
		*/
		//	pRel = GetOtherColumns(pRel);
		dataBase->numRels++;
		dataBase->m_pRelationList->AppendHere(*pRel);
		int size = dataBase->m_pRelNameVec->Size();
		dataBase->m_pRelNameVec->Resize(size+1);
		(*(dataBase->m_pRelNameVec))[size]= pRel->m_sName;;
		//pRel->Trace();
	}
	ctr++;
	//delete pRel;
	goto again;
out:
	//delete pRel;
	m_bResetDrawObj = TRUE;
	//	UpdateAllViews(NULL);
	return;	
}

///////////////////////////////////////////////////////////////////// 
//Display ARC/INFO Elevation Data.
//(1) Input .net file. 
void CIdbDoc::OnFileImportfileElevation()   //LEIZHANG
{
	CString fileName;
	DWORD lFlags = OFN_HIDEREADONLY | OFN_FILEMUSTEXIST | OFN_ALLOWMULTISELECT ; 
	
	BOOL bOpenFileDialog = TRUE;
	CString strFilter;
	CFileDialog dlgFile(bOpenFileDialog);
	dlgFile.m_ofn.Flags |= lFlags;
	
	strFilter += _T("*.net");
	strFilter += (TCHAR)'\0';   // last string
	dlgFile.m_ofn.lpstrFilter = strFilter;
	dlgFile.m_ofn.lpstrFileTitle  = "*.net";
	dlgFile.m_ofn.lpstrFile = fileName.GetBuffer(_MAX_PATH);
	dlgFile.m_ofn.lpstrFile[0] = '*';
	dlgFile.m_ofn.lpstrFile[1] = '.';
	dlgFile.m_ofn.lpstrFile[2] = 'n';
	dlgFile.m_ofn.lpstrFile[3] = 'e';
	dlgFile.m_ofn.lpstrFile[4] = 't';
	dlgFile.m_ofn.lpstrFile[5] = '\0';
	
	BOOL bResult = dlgFile.DoModal() == IDOK ? TRUE : FALSE;
	if(TRUE==bResult)
	{	
		CDlgRelName dlg(this);
		if (dlg.DoModal() != IDOK)
			return;
		
		if ( (dlg.m_strRel).IsEmpty()  )
		{
			AfxMessageBox("Relation Name  must not be empty!");
			return;
		}
		
		last_wrap_time=clock();            
		
		CString fileName;
		POSITION pos = dlgFile.GetStartPosition( );
		while( pos )
		{
			fileName = dlgFile.GetNextPathName(pos);
			char drive[_MAX_DRIVE];
			char dir[_MAX_DIR];
			char fname[_MAX_FNAME];
			char ext[_MAX_EXT];
			_splitpath(fileName, drive, dir, fname, ext);
			
			ifstream* iStream = new ifstream(fileName) ;
			
			if(NULL == iStream)
			{
				TRACE( "Can't open file %s", fileName);
				fileName.ReleaseBuffer();
			}
			else
			{ 
				//iStream is input stream, dlg.m_strRel is name of output file.
				CreateElevationRelation(*iStream, dlg.m_strRel);
				m_bAddRelation = TRUE;
				
				iStream->close();
				delete iStream;
			}
		}
	}
	else 
	{
		fileName.ReleaseBuffer();
	}
	
	UpdateAllViews(NULL);				
	return;
}

//(2) Compute the relations for edges and elevation of all triangles.
// and output to filename.
void CIdbDoc::CreateElevationRelation(ifstream& iStream, CString& fileName)   //LEIZHANG
{
    //nodef, edgef, trianglef are for reading ARC/INFO TIN data.
    char sData[30];
    int i, j, k;
	int symbol=0;  //symbol=0, in fetching process; symbol=1, end.
	int num_node, num_edge, num_triangle;
    float nodef[500][4];
	int edgef[1000][4], trianglef[500][4];
    int temp[500][7];  //triangle vs. node_number
    float tn[500][4][4];
	CString strData;
	
	//Step (a): Data Read from file
    //fetch node data.
    iStream >> sData;         //get "NODES".
	
	i=0; //counter
	while(symbol==0)
	{
		iStream >> sData;        // read node number.
		strData=sData;
		
		if (strData != "EDGES")
		{
			i++;  //counter for the number of nodes
			
			iStream >> sData;
			nodef[i][0] = (float)atof(sData); //x value
			
			iStream >> sData;
			nodef[i][1] = (float)atof(sData); //y value
			
			iStream >> sData;
			nodef[i][2] = (float)atof(sData); //z value
		}
		else
		{
			symbol=1;
		}
	} 
    num_node=i;
	
	i=0;
	symbol=0;
	//fetch edge data.
	while(symbol==0)
	{
		iStream >> sData;        // read edge number.
		strData=sData;
		if (strData != "TRIANGLES")
		{
			i++;  //counter for the number of edges.
			
			iStream >> sData;
			edgef[i][0] = (int)atoi(sData); //start node
			
			iStream >> sData;
			edgef[i][1] = (int)atoi(sData); //end node
			
			iStream >> sData;
			edgef[i][2] = (int)atoi(sData); //symbol for in or bound.
		}
		else
		{
			symbol=1;
		}
	} 
    num_edge=i;
	
	i=0;
	symbol=0;
	//fetech triangle data.
	while(symbol==0)
	{
		iStream >> sData;        // read triangle number.
		strData=sData;
		if (strData != "END")
		{
			i++;  //counter for the number of triangles.
			
			iStream >> sData;
			trianglef[i][0] = (int)atoi(sData); //edge 1.
			
			iStream >> sData;
			trianglef[i][1] = (int)atoi(sData); //edge 2.
			
			iStream >> sData;
			trianglef[i][2] = (int)atoi(sData); //edge 3.
		}
		else
		{
			symbol=1;
		}
	} 
    num_triangle=i;
	
	i=0;
	symbol=0;
	
	int t1, t2, t3; //three edges of one triangle.
    //Step (b): Find point(x,y,z) value of triangle.
    for (i=1;i<=num_triangle;i++)
	{
		t1=trianglef[i][0];
		t2=trianglef[i][1];
		t3=trianglef[i][2];
		
		temp[i][0]=edgef[t1][0];
		temp[i][1]=edgef[t1][1];
		
		temp[i][2]=edgef[t2][0];
		temp[i][3]=edgef[t2][1];
		
		temp[i][4]=edgef[t3][0];
		temp[i][5]=edgef[t3][1];
		
		//search three points of triangle (temp[i][0~2]).
		for (j=2;j<=5;j++)
		{
			if ((temp[i][j] != temp[i][0])&&(temp[i][j] != temp[i][1]))
			{
				temp[i][2]=temp[i][j];
			}
		}
    }
	
	//triangle_node[i][j][k]. i is triangle #, j is node # and k is axis # (x,y,z).
    for (i=1;i<=num_triangle;i++)
    {
		for (j=0;j<=2;j++)
		{
			t1=temp[i][j];
			for (k=0;k<=2;k++)
			{
				tn[i][j][k]=nodef[t1][k];
			}
		}
	}
	
	CDlgInput dlginput;
	int flag=0;
	float xtest, ytest, ztest; //data for verfifying mlpq and ARC/INFO.
    CString as_file;
	if (dlginput.DoModal()==IDOK)
	{
		xtest=(float)(dlginput.m_xvalue);
		ytest=(float)(dlginput.m_yvalue);
		as_file=(CString)(dlginput.m_as);
		flag=1;
	}
	ztest=0;
	
	//Read aspect and slope data from ARC/INFO output file (tinxx_ascii)
	ifstream as;
	float slope[2000], aspect[2000];
    as.open(as_file);
	float reader;
	for (i=1;i<=num_triangle;i++)
	{
		as>>reader;
		as>>reader;
		slope[i]=reader;
		as>>reader;
		aspect[i]=reader;
	}
	as.close();
	
	//Write Relation into file "filename".
	CString fname=fileName+".txt";
	ofstream fout(fname);
	fout<<"begin%"<<fileName<<"%\n";
    float a, b, c, d, ip, x, lhs, rhs; //lhs=Left Hand Side, rhs=Right Hand Side.
    int iq;
	
	int sig1, sig2, sig3; //identifying satification of three ineqality.
	
	for (i=1;i<=num_triangle;i++)
	{
		sig1=0;
		sig2=0;
		sig3=0;
		
		fout<<fileName<<"(id,x,y,z,aspect,slope) :-  \n"; //relation name output.
		fout<<"id="<<i<<",\n"; //id number output
		
		//2-Spaghetti Data Model.
		//(1) generate the first line relation.
		a=tn[i][2][1]-tn[i][1][1];
		b=tn[i][2][0]-tn[i][1][0];
		lhs=a*tn[i][0][0]-b*tn[i][0][1];
		rhs=-b*tn[i][1][1]+a*tn[i][1][0];
		
		//divide the same number at two sides of equation.
		
		if (fabsf(a)>=fabs(b))
		{    ip=fabsf(a); }
		else //|a|<|b|
		{	  ip=fabsf(b);  }
		
		iq=0;
		x=float(1);
		while ((ip/10.0)>1)
		{ 
			iq++;  
			x=float(10*x);
			ip=float(ip/10.0);
		}//test how many digits (iq+1) 
		
		a=a/x;
		b=b/x;
		lhs=lhs/x;
		rhs=rhs/x;
		
		if (lhs<rhs) //satisfy condition
		{ 
			if ((a*xtest-b*ytest)<=rhs)
			{ sig1=1;} //if (xtest,ytest) satisfy, give signal.
			
			if (a != 0)
			{   fout<<a<<"x";  }
			
			if (b<0)
			{  fout<<"+"<<(-b)<<"y <= "<<long(rhs)<<", \n";		}
			else 
			{
				if (b>0)
				{  fout<<"-"<<b<<"y <= "<<long(rhs)<<", \n";		}
				else //b=0
				{  fout<<" <= "<<long(rhs)<<", \n";		}
			}
		}
		else //lhs>rhs
		{
			if ((a*xtest-b*ytest)>=rhs)
			{ sig1=1;} //if (xtest,ytest) satisfy, give signal.
			
			if (a != 0)
			{   fout<<a<<"x";  }
			
			if (b<0)
			{  fout<<"+"<<(-b)<<"y >= "<<long(rhs)<<", \n";		}
			else 
			{
				if (b>0)
				{  fout<<"-"<<b<<"y >= "<<long(rhs)<<", \n";		}
				else //b=0
				{  fout<<" >= "<<long(rhs)<<", \n";		}
			}
		}
		
		//(2) generate the second line relation.
		a=tn[i][1][1]-tn[i][0][1];
		b=tn[i][1][0]-tn[i][0][0];
		lhs=a*tn[i][2][0]-b*tn[i][2][1];
		rhs=-b*tn[i][0][1]+a*tn[i][0][0];
		
		//divide the same number at two sides of equation.
		if (fabsf(a)>=fabs(b))
		{    ip=fabsf(a); }
		else //|a|<|b|
		{	  ip=fabsf(b);  }
		
		iq=0;
		x=float(1);
		while ((ip/10.0)>1)
		{ 
			iq++;  
			x=float(10*x);
			ip=float(ip/10.0);
		}//test how many digits (iq+1) 
		
		a=a/x;
		b=b/x;
		lhs=lhs/x;
		rhs=rhs/x;
		
		if (lhs<rhs) //satisfy condition
		{
			if ((a*xtest-b*ytest)<=rhs)
			{ sig2=1;} //if (xtest,ytest) satisfy, give signal.
			
			if (a != 0)
			{   fout<<a<<"x";  }
			
			if (b<0)
			{  fout<<"+"<<(-b)<<"y <= "<<long(rhs)<<", \n";	}
			else 
			{
				if (b>0)
				{  fout<<"-"<<b<<"y <= "<<long(rhs)<<", \n";		}
				else //b=0
				{  fout<<" <= "<<long(rhs)<<", \n";		}
			}
		}
		else //lhs>rhs
		{
			if ((a*xtest-b*ytest)>=rhs)
			{ sig2=1;} //if (xtest,ytest) satisfy, give signal.
			
			if (a != 0)
			{   fout<<a<<"x";  }
			
			if (b<0)
			{  fout<<"+"<<(-b)<<"y >= "<<long(rhs)<<", \n";		}
			else 
			{
				if (b>0)
				{  fout<<"-"<<b<<"y >= "<<long(rhs)<<", \n";		}
				else //b=0
				{  fout<<" >= "<<long(rhs)<<", \n";		}
			}
		}
		
		//(3) generate the third line relation.
		a=tn[i][2][1]-tn[i][0][1];
		b=tn[i][2][0]-tn[i][0][0];
		lhs=a*tn[i][1][0]-b*tn[i][1][1];
		rhs=-b*tn[i][0][1]+a*tn[i][0][0];
		
		//divide the same number at two sides of equation.
		if (fabsf(a)>=fabs(b))
		{    ip=fabsf(a); }
		else //|a|<|b|
		{	  ip=fabsf(b);  }
		
		iq=0;
		x=float(1);
		while ((ip/10.0)>1)
		{ 
			iq++;  
			x=float(10*x);
			ip=float(ip/10.0);
		}//test how many digits (iq+1) 
		
		a=a/x;
		b=b/x;
		lhs=lhs/x;
		rhs=rhs/x;
		
		if (lhs<rhs) //satisfy condition
		{
			if ((a*xtest-b*ytest)<=rhs)
			{ sig3=1;} //if (xtest,ytest) satisfy, give signal.
			
			if (a != 0)
			{   fout<<a<<"x";  }
			
			if (b<0)
			{  fout<<"+"<<(-b)<<"y <= "<<long(rhs)<<", \n";		}
			else 
			{
				if (b>0)
				{  fout<<"-"<<b<<"y <= "<<long(rhs)<<", \n";		}
				else //b=0
				{  fout<<" <= "<<long(rhs)<<", \n";		}
			}
		}
		else //lhs>rhs
		{
			if ((a*xtest-b*ytest)>=rhs)
			{ sig3=1;} //if (xtest,ytest) satisfy, give signal.
			
			if (a != 0)
			{   fout<<a<<"x";  }
			
			if (b<0)
			{  fout<<"+"<<(-b)<<"y >= "<<long(rhs)<<", \n";		}
			else 
			{
				if (b>0)
				{  fout<<"-"<<b<<"y >= "<<long(rhs)<<", \n";		}
				else //b=0
				{  fout<<" >= "<<long(rhs)<<", \n";		}
			}
		}
		
		//(4) generate elevation relation : ax+by+cz=d.
		a=tn[i][0][1]*tn[i][1][2]-tn[i][0][2]*tn[i][1][1];
		b=tn[i][0][2]*tn[i][1][0]-tn[i][0][0]*tn[i][1][2];
		c=tn[i][0][0]*tn[i][1][1]-tn[i][0][1]*tn[i][1][0];
		d=a*tn[i][2][0]+b*tn[i][2][1]+c*tn[i][2][2];
		
		//get the smallest one of a,b,c.
		float min=fabsf(c);
		if ((fabsf(b)<min)&&(b != 0))
		{  min=fabsf(b); }
		if ((fabsf(a)<min)&&(a != 0))
		{  min=fabsf(a); }
		
		if(c != 0)
		{
			c=c/min;
			b=b/min;
			a=a/min;
			d=d/min;
			
			if (a != 0)
			{
				fout<<a<<"x";
			}
			
			if (b<0)
			{  fout<<"-"<<(-b)<<"y";		}
			else 
			{
				if (b>0)
				{  fout<<"+"<<b<<"y";		}
			}   
			
			if(c<0)
			{   fout<<"-"<<(-c)<<"z";	}
			else
			{    fout<<"+"<<c<<"z";    }
			
			if ((a != 0)||(b != 0)||(c != 0))
			{   fout<<" = "<<long(d)<<",\n"; }
		}
		else //c==0 
		{
			if (a != 0)
			{    fout<<a<<"x"; }
			if (b<0)
			{  fout<<"-"<<(-b)<<"y";		}
			else 
			{
				if (b>0)
				{  fout<<"+"<<b<<"y";		}
			}   
			
			if ((a != 0)||(b != 0)||(c != 0))
			{  fout<<" = "<<d<<".\n\n"; }
			else  //a=b=c=d=0
			{   fout<<"0x+0y+0z=0, \n"; }
		}
		
		//compute z test value.
		if ((sig1==1)&&(sig2==1)&&(sig3==1))
		{
			ztest=float((d-a*xtest-b*ytest)/c);
		}
		
		//ouput aspect and slope
		fout<<"aspect="<<aspect[i]<<",\n";
		fout<<"slope="<<slope[i]<<".\n\n";
		
	} //end of for loop
	fout<<"end%"<<fileName<<"%\n";
	fout.close();
	
	//output elevation data.
	if ((flag==1)&&(ztest != 0))
    {
		ofstream ft("zdata.txt");
		ft<<ztest;
		ft.close();
		AfxMessageBox("You have elevation data at file (zdata.txt) !");
    }
	else
    {
		if (ztest==0)
		{AfxMessageBox("There is no such (x,y,z) point !"); }
	}
	
	return;
}
/////////////////////////////////////////////////////////////////////

// syed added
// Syed appended the below code till the end of the file
		

void CIdbDoc::OnSql() 
{
	// TODO: Add your command handler code here
	BasicSQL bSql;
    CString docpath=GetPathName();
	CString filename=GetTitle();

	int pos;
	pos = docpath.ReverseFind('\\');
	docpath = docpath.Left(pos+1);
	pos = filename.Find(".",0);
	if (pos>0) 
		filename = filename.Left(pos);
	filename = filename + "_BSql.txt";
	docpath = docpath + filename;

	bSql.FileRead(docpath);

	if (bSql.DoModal() == IDOK)
	{
		// save to Last_BasicSql.txt -- by BH
		bSql.FileSave(docpath);
		//-- end by BH

		last_query_time=clock();    
		DoSql(bSql.m_Create,bSql.m_Select,bSql.m_From,bSql.m_Where);
		SetQueryTime();
		ShowResult(bSql.m_Create);
	}

}

/*******************************************************
 * Name:	 CIdbDoc::str2ansi(CString input)
 * Author:   Shasha
 * Time:	 02/2005
 * Descrpn:	 Replace any control character (except "\n") by blank character
 * Usage:    It is used in OnEditInsrelation, OnSQL, OnSQLset, OnSQLAggregation, NestedSQL.
 *******************************************************/
BOOL CIdbDoc::str2ansi(CString *input)
{
	BOOL changed=FALSE;
	char ch;
	CString mathch="`~!@#$%^&*()_+-*/=,.;'<>?:[]{}|\\ \"\n";
	for( int i=0; i<input->GetLength(); i++)
	{
		ch = input->GetAt(i);
		if ((ch>='A' && ch<='Z')||(ch>='a' && ch<='z')||(ch>='0'&&ch<='9')||mathch.Find(ch)>=0)
			continue;
		else { 
			changed = TRUE;
			switch (ch)
			{
			case -106: input->SetAt(i, '-'); break; //char '-' in MS Word 
			default : input->SetAt(i, ' ');
			}
		}
	}

	return changed;
}

void CIdbDoc::OnShapeAnimation(int StartTime, int EndTime, int nStep) 
{
	int nNoOfStep = EndTime - m_nDBCurrent;
	int nSpeed = 100;
	
	if (nStep < 1)
		AfxMessageBox("Step should be more than 1");
	else if ( nNoOfStep < 0)
	{
		AfxMessageBox("Time out range");
	}
	else
	{
		BeginWaitCursor();
		for (int i=0; i <= nNoOfStep; i++)
		{
			DoShowAnimation(StartTime + nStep * i);
			nAniSleep = 40 * (100 - nSpeed);
			((CMainFrame*)(AfxGetApp()->GetMainWnd()))->ShowAnimation(i, nNoOfStep);
			if (nAniSleep > 0  &&  i < nNoOfStep)
				Sleep(nAniSleep);
		}
		EndWaitCursor();
	}

}


void CIdbDoc::OnSqlAggregation() 
{
	// TODO: Add your command handler code here

	SqlAggregation sagre;

    CString docpath=GetPathName();
	CString filename=GetTitle();

	int pos;
	pos = docpath.ReverseFind('\\');
	docpath = docpath.Left(pos+1);
	pos = filename.Find(".",0);
	if (pos>0) 
		filename = filename.Left(pos);
	filename = filename + "_ASql.txt";
	docpath = docpath + filename;

	sagre.FileRead(docpath);

	if (sagre.DoModal() == IDOK)
	{
		// save to Last_SqlAggregation.txt -- by BH
		sagre.FileSave(docpath);
		//--end by BH

		last_query_time=clock();    
		DoSqlAggregation(sagre.m_Create,sagre.m_Select, sagre.m_From, sagre.m_Where, sagre.m_Group, sagre.m_Having);
		SetQueryTime();
		ShowResult(sagre.m_Create);
	}
	
}

void CIdbDoc::OnSqlsets() 
{
	// TODO: Add your command handler code here

	SqlSets ssets;

    CString docpath=GetPathName();
	CString filename=GetTitle();
	
	int pos;
	pos = docpath.ReverseFind('\\');
	docpath = docpath.Left(pos+1);
	pos = filename.Find(".",0);
	if (pos>0) 
		filename = filename.Left(pos);
	filename = filename + "_SSql.txt";
	docpath = docpath + filename;
	
	ssets.FileRead(docpath);

	if (ssets.DoModal() == IDOK)
	{
		// save to Last_SqlAggregation.txt -- by BH
		ssets.FileSave(docpath);
		//--end by BH

		last_query_time=clock();    
		DoSqlsets(ssets.m_Create,ssets.m_Select1,ssets.m_From1,
			ssets.m_Where1,ssets.m_IntUnion,ssets.m_Select2,
			ssets.m_From2,ssets.m_Where2);
		SetQueryTime();
		ShowResult(ssets.m_Create);
	}

}

void CIdbDoc::NestedSql() 
{
	// TODO: Add your command handler code here
	OnNestedSql nSql;
	
    CString docpath=GetPathName();
	CString filename=GetTitle();
	
	int pos;
	pos = docpath.ReverseFind('\\');
	docpath = docpath.Left(pos+1);
	pos = filename.Find(".",0);
	if (pos>0) 
		filename = filename.Left(pos);
	filename = filename + "_NSql.txt";
	docpath = docpath + filename;
	
	nSql.FileRead(docpath);

	if (nSql.DoModal() == IDOK)
	{
		// save to Last_SqlAggregation.txt -- by BH
		nSql.FileSave(docpath);
		//--end by BH

		last_query_time=clock();    
		DoNestedSql(nSql.m_Create,nSql.m_Select1,nSql.m_From1,nSql.m_Where1,
			nSql.m_Operator,nSql.m_Select2,nSql.m_From2,nSql.m_Where2);
		SetQueryTime();
		ShowResult(nSql.m_Create);
	}

}

void CIdbDoc::OnSqlDialogBox() 
{
	// TODO: Add your command handler code here
	dBaseTemp = &m_dataBase;
	basicsqldialogbox ssb(this);
	ssb.DoModal();
}


void CIdbDoc::OnShapeAnim() 
{
	// TODO: Add your command handler code here
	for (int i=m_nDBTimeS; i <= m_nDBTimeE; i++)
	{
		DoShowShapeAnimation(i);
		((CMainFrame*)(AfxGetApp()->GetMainWnd()))->ShowAnimation(i, m_nDBTimeE);
		if (nAniSleep > 0)
			Sleep(nAniSleep);
	}
}

void CIdbDoc::DoShowShapeAnimation(int nTime)
{
	DoReCalculateShape(nTime);
	UpdateAllViews(NULL);
	POSITION pos = GetFirstViewPosition();
	while (pos != NULL)
	{
		CView* pView = GetNextView(pos);
		if (pView != NULL  &&  pView->IsKindOf(RUNTIME_CLASS(CGraphView)))
		{
			//			pView->OnUpdate(NULL, 0, NUL);
			pView->UpdateWindow();
		}
	}
}

void CIdbDoc::DoReCalculateShape(int nTime)
{

	dataBase = &m_dataBase;
	
	if (nTime < m_nDBTimeS)
		nTime = m_nDBTimeS;
	else
		if (nTime > m_nDBTimeE && (*dataBase).STDB==FALSE)
			nTime = m_nDBTimeE;
		
		if (nTime == m_nDBCurrent)
			return;

		if (m_dataBase.numRels>0) 
		{
			SlistIter<Relation> relationListIter(*(m_dataBase.m_pRelationList));
			Relation* pR; 

			POSITION pos = m_listRelation.GetHeadPosition();
	
			while (pos != NULL)
			{
					pR = (Relation*)(m_listRelation.GetNext(pos));
//			while(pR = (Relation*)relationListIter())
//			{
				if(pR->SatisFlag()==0)
				{
					DFIter<Matrix<float> >  matrixIter;
					matrixIter = DFIter<Matrix<float> >(*(pR->m_tablePtr));
					Matrix<float>* p_matrix;
					while ((p_matrix = matrixIter()) != NULL)
					{/* DRK changed this for period*/
						if(p_matrix->m_Period!=(-1))
							p_matrix->RegeneratePoints((nTime - p_matrix->m_PeriodStart) % p_matrix->m_Period + p_matrix->m_PeriodStart);
						else
							p_matrix->RegeneratePoints(nTime);
					}
					
					int nPeriod = pR->m_nTimeE - pR->m_nTimeS;

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

	double tempindex;
	int tempindexs = 0;
	int tempindexe = 0;

					for(int colind=0;colind<400;colind++)
						if(colorTable[colind]==pR->m_colorStart)
						{
							tempindexs = colind;
							break;
						}
					for(int colind1=0;colind1<400;colind1++)
						if(colorTable[colind1]==pR->m_colorEnd)
						{
							tempindexe = colind1;
							break;
						}

	tempindex = (double)tempindexs + (double)((double)(nTime - pR->m_nTimeS) * (double)( tempindexe - tempindexs) / (double)(pR->m_nTimeE - pR->m_nTimeS)) ;

					if (nPeriod != 0  &&  nTime >= pR->m_nTimeS  &&  nTime <= pR->m_nTimeE)
						pR->m_color = colorTable[(int)tempindex];

				}
			}
		}
		
		m_nDBCurrent = nTime;//changed for period by DRK
}

void CIdbDoc::OnViewShapeNext() 
{
	// TODO: Add your command handler code here
	if (m_nDBCurrent < m_nDBTimeE)
		DoShowShapeAnimation(m_nDBCurrent + 1);
	else
		DoShowShapeAnimation(m_nDBTimeS);
	((CMainFrame*)(AfxGetApp()->GetMainWnd()))->ShowAnimation(m_nDBCurrent, m_nDBTimeE);
}

void CIdbDoc::OnViewShapeprior() 
{
	// TODO: Add your command handler code here
if (m_nDBCurrent > m_nDBTimeS)
		DoShowShapeAnimation(m_nDBCurrent - 1);
	else
		DoShowShapeAnimation(m_nDBTimeE);
	((CMainFrame*)(AfxGetApp()->GetMainWnd()))->ShowAnimation(m_nDBCurrent, m_nDBTimeE);	
}

void CIdbDoc::OnViewShapegohead() 
{
	// TODO: Add your command handler code here
	DoShowAnimation(m_nDBTimeS);
	((CMainFrame*)(AfxGetApp()->GetMainWnd()))->ShowAnimation(m_nDBCurrent, m_nDBTimeE);	
}

void CIdbDoc::OnViewShapegoend() 
{
	// TODO: Add your command handler code here
	DoShowAnimation(m_nDBTimeE);
	((CMainFrame*)(AfxGetApp()->GetMainWnd()))->ShowAnimation(m_nDBCurrent, m_nDBTimeE);	
}

void CIdbDoc::OnViewPlayshapeback() 
{
	// TODO: Add your command handler code here
	for (int i=m_nDBTimeE; i >= m_nDBTimeS; i--)
	{
		DoShowShapeAnimation(i);
		((CMainFrame*)(AfxGetApp()->GetMainWnd()))->ShowAnimation(i, m_nDBTimeE);
		if (nAniSleep > 0)
			Sleep(nAniSleep);
	}	
}

void CIdbDoc::DoSql(CString cs_Create, CString cs_Select, CString cs_From, CString cs_Where)
{
	// TODO: Add your command handler code here
	str2ansi(&cs_Create);
	str2ansi(&cs_Select);
	str2ansi(&cs_From);
	str2ansi(&cs_Where);

	CString newRelation = "begin %TEMPSQL%\n";
	newRelation += SQL2Datalog(cs_Create, cs_Select, cs_From, cs_Where)+"\n";
	newRelation += "end %TEMPSQL%";
	FILE* fp_out;
	if ((fp_out = fopen("TEMSQL.txt","wt"))==NULL)
	{
		AfxMessageBox("Error creating file !");
		return;
	}

	fwrite(newRelation, sizeof(char), newRelation.GetLength(), fp_out);
	fclose(fp_out);
	DoCalculate("TEMSQL.txt");
	UpdateAllViews(NULL);
}

void CIdbDoc::DoSqlsets(CString cs_View, CString cs_Select1, CString cs_From1, CString cs_Where1, CString cs_Operation, CString cs_Select2, CString cs_From2, CString cs_Where2)
{
	str2ansi(&cs_View);
	str2ansi(&cs_Select1);
	str2ansi(&cs_From1);
	str2ansi(&cs_Where1);
	str2ansi(&cs_Select2);
	str2ansi(&cs_From2);
	str2ansi(&cs_Where2);

	CString newRelation = "begin %TEMPSQL%\n";
	newRelation += SQL2Datalog(cs_View, cs_Select1, cs_From1, cs_Where1);

	cs_Operation.Trim();
	cs_Operation.MakeLower();
	if (cs_Operation=="union")
	{
		newRelation = newRelation + "\n";
		newRelation += SQL2Datalog(cs_View, cs_Select2, cs_From2, cs_Where2)+"\n";
	}
	else
	{
		CString tempRelation = SQL2Datalog(cs_View, cs_Select2, cs_From2, cs_Where2)+"\n";
		tempRelation.Delete(0, tempRelation.Find(":-")+2);
		//AfxMessageBox(tempRelation);
		
		newRelation.Trim();
		newRelation.SetAt(newRelation.GetLength()-1, ',');
		//AfxMessageBox(newRelation);
		newRelation += tempRelation;
		//AfxMessageBox(newRelation);
	}

	newRelation += "end %TEMPSQL%";

	FILE* fp_out;
	if ((fp_out = fopen("TEMSQL.txt","wt"))==NULL)
	{
		AfxMessageBox("Error creating file !");
		return;
	}
	fwrite(newRelation, sizeof(char), newRelation.GetLength(), fp_out);
	fclose(fp_out);
	
	DoCalculate("TEMSQL.txt");
	UpdateAllViews(NULL);
}

//Insert a string to a string list in ascend order
void InsertStr(CArray<CString>* list, CString str)
{
	for (int i=0; i<list->GetCount(); i++)
	{
		if (str<list->GetAt(i))
		{
			list->InsertAt(i, str);
			return ;
		}
	}
	list->Add(str);
}

void DoAggFunc(CArray<CString>* list, CString selhead, CString groupby)
{
	CString AggreFunc[]=
	{
		"count(",
		"max(",
		"min(",
		"sum(",
		"avg("
	};
	int AggFuncId=-1;

	selhead.Replace(" ", "");
	selhead.MakeLower();
	groupby.Replace(" ", "");
	groupby.MakeLower();
	
	CString rtoken;
	int pos=0;
	rtoken = selhead.Tokenize(",", pos);
	int Aggpos=1;
	int grouppos=1;
	while (rtoken!="")
	{
		if (rtoken.Find("count(")!=-1)
			AggFuncId = 0;
		else if (rtoken.Find("max(")!=-1)
			AggFuncId = 1;
		else if (rtoken.Find("min(")!=-1)
			AggFuncId = 2;
		else if (rtoken.Find("sum(")!=-1)
			AggFuncId = 3;
		else if (rtoken.Find("avg(")!=-1)
			AggFuncId = 4;

		if (groupby.Find(rtoken)==-1)
			grouppos = Aggpos-1;

		if (AggFuncId>-1)
			break;
		
		rtoken = selhead.Tokenize(",", pos);
		Aggpos++;
	}

	if (AggFuncId>-1)
	{
		CString groupStr;
		CString oldgroupStr="##";
		CString AggStr;
		CString tuple;
		CString oldtuple="##";
		int count;
		float sum;
		int i=0;

		if (grouppos==0)
		{
			CString rst;
			CString maxv;
			CString minv;
			switch (AggFuncId)
			{
			case 0: 
				rst.Format("%30d",list->GetCount());
				break;
			case 1: //max
				maxv="";
				for (int k=0; k<list->GetCount(); k++)
				{
					AggStr = list->GetAt(k).Mid(31*(Aggpos-1),30);
					if (maxv<AggStr)
						maxv = AggStr;
				}
				rst.Format("%30s", maxv);
				break;
			case 2: //min
				minv=list->GetAt(0).Mid(31*(Aggpos-1),30);
				for (int k=0; k<list->GetCount(); k++)
				{
					AggStr = list->GetAt(k).Mid(31*(Aggpos-1),30);
					if (minv>AggStr)
						minv = AggStr;
				}
				rst.Format("%30s", minv);
				break;
			case 3: 
				sum = 0;
				for (int k=0; k<list->GetCount(); k++)
				{
					AggStr = list->GetAt(k).Mid(31*(Aggpos-1),30);
					sum += atof(AggStr);
				}
				rst.Format("%25.4f", sum);
				break;
			case 4: 
				sum = 0;
				for (int k=0; k<list->GetCount(); k++)
				{
					AggStr = list->GetAt(k).Mid(31*(Aggpos-1),30);
					sum += atof(AggStr);
				}
				rst.Format("%25.4f", sum/list->GetCount());
				break;
			}
			list->RemoveAll();
			list->FreeExtra();
			list->Add(rst);
			return;
		}

		tuple.Format("%100s", "##");
		list->Add(tuple);
		CString maxinv; // = list->GetAt(0).Mid(31*(Aggpos-1),30);

		while (i<list->GetCount())
		{
			tuple = list->GetAt(i);
			groupStr = tuple.Left(31*grouppos);
			AggStr = tuple.Mid(31*(Aggpos-1),30);
			tuple = tuple.Left(31*(Aggpos-1));

			if (groupStr==oldgroupStr)
			{
				switch (AggFuncId)
				{
				case 0: count++;
					break;
				case 1: //max
					if (maxinv<AggStr)
						maxinv = AggStr;
					break;
				case 2: 
					if (maxinv>AggStr)
						maxinv = AggStr;
					break;
				case 3: sum += atof(AggStr);
					break;
				case 4: count++;   sum += atof(AggStr);
					break;
				}
				list->RemoveAt(i);
			}
			else
			{
				if (oldtuple!="")
				{
					CString rst;
					switch (AggFuncId)
					{
					case 0: 
						rst.Format("%s%30d.", oldtuple, count);
						break;
					case 1: 
						rst.Format("%s%s.", oldtuple, maxinv);
						break;
					case 2: 
						rst.Format("%s%s.", oldtuple, maxinv);
						break;
					case 3: 
						rst.Format("%s%30.4f.", oldtuple, sum);
						break;
					case 4: 
						rst.Format("%s%30.4f.", oldtuple, sum/count);
						break;
					}
					list->SetAt(i, rst);
				}
				count=1;
				maxinv = AggStr;
				sum = atof(AggStr);
				oldgroupStr = groupStr;
				oldtuple = tuple;
				i++;
			}
		}
		list->RemoveAt(0);
	}
}

//Rewrite by Shasha in Nov 2004
void CIdbDoc::DoSqlAggregation(CString cs_Create, CString cs_Select, CString cs_From, CString cs_Where, CString cs_Group, CString cs_Having)
{
	str2ansi(&cs_Create);
	str2ansi(&cs_Select);
	str2ansi(&cs_From);
	str2ansi(&cs_Where);
	str2ansi(&cs_Group);
	str2ansi(&cs_Having);
	
	if(strlen(cs_Create)==0)
	{
		AfxMessageBox("Create View field is Blank");
		return;
	}
	cs_Where.Replace("'", "\"");
	//cs_Where = FormalizeTuple(cs_Where);
	cs_Having = FormalizeTuple(cs_Having);


	CString AggreFunc[]=
	{
		"count(",
		"max(",
		"min(",
		"sum(",
		"avg("
	};
	int AggFuncId=-1;

	CString cs_Select1 = cs_Select;
	cs_Select1.MakeLower(); //use lower case to seach aggregation function name, which is defined in lower case.
	for (int i=0; i<5; i++)
	{
		int pos1 = cs_Select1.Find(AggreFunc[i]);
		if (pos1 >= 0)
		{
			cs_Select.Delete(pos1, AggreFunc[i].GetLength());
			cs_Select1 = cs_Select; 
			cs_Select.Insert(pos1, AggreFunc[i]); //Unify aggre function to lower case
			
			cs_Select1.Replace(")", "");   //change the filed of max(aa) to max_aa

			AggFuncId = i;
			break;
		}
	}
	if (cs_Create.Find("(")==-1)
		cs_Create += "(" + cs_Select1 +")";
	
	cs_Create.Replace(".", "_");
	CString org_Create = cs_Create;

	m_dataBase.m_Distinct = false;
	CString TmpAggName = "TmpAgg"+cs_Create.Right(cs_Create.GetLength()-cs_Create.Find("("));
	DoSql(TmpAggName, cs_Select1, cs_From, cs_Where);
	m_dataBase.m_Distinct = true;

	//UpdateAllViews(NULL);
	m_dataBase.m_pRelationList->GotoHead();  
	SlistIter<Relation> relIter( *(m_dataBase.m_pRelationList) );
	Relation* pR;
	Matrix<float>* p_matrix;

	while(pR =relIter()) 
	{
		String strName = pR->Name();
		if (strcmp(strName.GetText(),"TmpAgg")==0)
		{
			FILE* fp_out;
			if ((fp_out = fopen("TEMPAGG.txt","wt"))==NULL)
			{
				AfxMessageBox("Error creating file !");
				return;
			}

			if ((AggFuncId==1)||(AggFuncId==2))
			{
				int Aggpos=0;
				int pos=0;
				CString rtoken = cs_Select.Tokenize(",", pos);
				while (rtoken!="")
				{
					if (rtoken.Find(AggreFunc[AggFuncId])!=-1)
						break;
					rtoken = cs_Select.Tokenize(",", pos);
					Aggpos++;
				}

				if (!MaxMinOnStr(pR, Aggpos))
				{
					FILE* fp_out2;
					if ((fp_out2 = fopen("TEMPAGG2.txt","wt"))==NULL)
					{
						AfxMessageBox("Error creating file !");
						return;
					}
					CString AggHead = cs_Select;
					AggHead.Replace(".","");
					CString nonAggHead = cs_Select1;
					nonAggHead.Replace(".","");
					
					CString lines = "begin%temp%\n";
					lines += "TmpAgg2(" + AggHead + "):- TmpAgg(" +nonAggHead + ").\n";
					lines += "end%temp%\n";

					fwrite(lines, sizeof(char), lines.GetLength(), fp_out2);
					fclose(fp_out2);

					DoCalculate("TEMPAGG2.txt");

					m_dataBase.m_pRelationList->GotoHead();  
					SlistIter<Relation> relIter( *(m_dataBase.m_pRelationList) );
					while(pR =relIter()) 
					{
						String strName2 = pR->Name();
						if (strcmp(strName2.GetText(),"TmpAgg2")==0)
							break;
					}
				}
			}

			CString strOut("");
			
			DFIter<Matrix<float> >  matrixIter;
			matrixIter = DFIter<Matrix<float> >(*(pR->m_tablePtr));
			p_matrix =  matrixIter();
			CArray<CString> sortedList;
			while (p_matrix != NULL)
			{
				strOut = FormatMatrix(pR, p_matrix);
				InsertStr(&sortedList, strOut);
				p_matrix =  matrixIter();
			}
			strOut = "";
			
			//for (int i=0; i<sortedList.GetCount(); i++)
			//	strOut += sortedList[i]+"\n";
			//AfxMessageBox(strOut);

			DoAggFunc(&sortedList, cs_Select, cs_Group);

			strOut = "";
			CString head;
			head="begin%agg%\n\n";
			fwrite(head, sizeof(char), head.GetLength(), fp_out);
			
			cs_Create.Trim();
			if (cs_Having.Trim()!="")
			{
				cs_Create.Insert(cs_Create.Find("("),"_forHaving");
			}
			head = cs_Create.Right(cs_Create.GetLength()-cs_Create.Find('(')-1);
			//head = head.Left(head.GetLength()-1);
			for (int i=0; i<sortedList.GetCount(); i++)
			{
				CString tuple = cs_Create + ":- ";
				CString Value = sortedList[i];
				CString ss;
				CString rtoken;
				int varid=0;
				int pos=0;
				rtoken = head.Tokenize(", ()",pos);
				while (rtoken!="")
				{
					ss=Value.Mid(31*varid, 30).Trim();
					if (ss[0]=='S')
						ss = "=\""+ss.Right(29).Trim()+"\",";
					else
						ss = "=" + ss + ",";

					tuple += rtoken + ss;

					rtoken = head.Tokenize(", )",pos);
					varid++;
				}
				tuple.SetAt(tuple.GetLength()-1, '.');
				tuple += "\n";
				fwrite(tuple, sizeof(char), tuple.GetLength(), fp_out);
				//AfxMessageBox(tuple);
			}
			head="end%agg%\n";
			fwrite(head, sizeof(char), head.GetLength(), fp_out);

			fclose(fp_out);

			RemoveRelation("TmpAgg");
			RemoveRelation("TmpAgg2");

			DoCalculate("TEMPAGG.txt");
			if (cs_Having!="")
			{
				if ((fp_out = fopen("TEMPHAVE.txt","wt"))==NULL)
				{
					AfxMessageBox("Error creating file !");
					return;
				}

				CString newRelation = "begin %TEMPHAVE%\n";
				newRelation += org_Create + ":- "+ cs_Create +", "+ cs_Having+".\n";
				newRelation += "end %TEMPHAVE%\n";
				fwrite(newRelation, sizeof(char), newRelation.GetLength(), fp_out);
				fclose(fp_out);
				DoCalculate("TEMPHAVE.txt");
				RemoveRelation(cs_Create.Left(cs_Create.Find("(")));
			}
			
			UpdateAllViews(NULL);

			sortedList.RemoveAll();
			sortedList.FreeExtra();
			break;
		}
	}

}

Relation* CIdbDoc::FindRelation(CString RelName)
{
	m_dataBase.m_pRelationList->GotoHead();  
	SlistIter<Relation> relIter( *(m_dataBase.m_pRelationList) );
	Relation* pR;

	while(pR =relIter()) 
	{
		String strName = pR->Name();
		if (strcmp(strName.GetText(),RelName)==0)
			return pR;
	}
	return NULL;
}


void CIdbDoc::DoNestedSql(CString cs_Create, CString cs_Select1, CString cs_From1, CString cs_Where1, CString cs_Operator, CString cs_Select2, CString cs_From2, CString cs_Where2)
{
	str2ansi(&cs_Create);
	str2ansi(&cs_Select1);
	str2ansi(&cs_From1);
	str2ansi(&cs_Where1);
	str2ansi(&cs_Select2);
	str2ansi(&cs_From2);
	str2ansi(&cs_Where2);
	int opid=-1;
	CString wh1;
	CString wh2;
	BOOL addfld = false; //Add a field in the end of cs_Select1 if true
	int nestfld; //Position of field that is used for nesting. Used for "not in" and string value only.
	if (cs_Operator == "in")
	{
		opid = 1;
	}
	else if (cs_Operator == "not in")
	{
		opid = 2;
	}
	else if (cs_Operator == ">= all")
	{
		opid = 3;
		cs_Select2 = "max(" + cs_Select2 + ")";
		cs_Where1 = cs_Where1 + ">=";
	}
	else if (cs_Operator == "<= all")
	{
		opid = 4;
		cs_Select2 = "min(" + cs_Select2 + ")";
		cs_Where1 = cs_Where1 + "<=";
	}
	else if (cs_Operator == ">= some")
	{
		opid = 5;
		cs_Select2 = "min(" + cs_Select2 + ")";
		cs_Where1 = cs_Where1 + ">=";
	}
	else if (cs_Operator == "<= some")
	{
		opid = 6;
		cs_Select2 = "max(" + cs_Select2 + ")";
		cs_Where1 = cs_Where1 + "<=";
	}

	if (opid>2){
		DoSqlAggregation("TEMPSQL2", cs_Select2, cs_From2, cs_Where2, "", "");
	}
	else
	{
		int pos = cs_Where1.ReverseFind(',');
		if (pos==-1)
		{
			wh1 = "";
			wh2 = cs_Where1;
		}
		else
		{
			wh1 = cs_Where1.Left(pos);
			wh2 = cs_Where1.Right(cs_Where1.GetLength()-pos-1);
			wh2.Trim();
		}
		//If the selection fields do not contain the field for nested condition
		//Add the field to the selection here and remove it in the final query
		if (cs_Select1.Find(wh2)==-1)
		{
			cs_Select1 += ","+wh2;
			addfld = true;
		}
		CString tmps=cs_Select1.Left(cs_Select1.Find(wh2)); 
		nestfld = tmps.Replace(",", ";"); //Replace return the number of replaced instances of the character or substring 

		DoSql("TEMPSQL1", cs_Select1, cs_From1, wh1);
		DoSql("TEMPSQL2", cs_Select2, cs_From2, cs_Where2);
	}

	// Do nested
	Relation* pR = FindRelation("TEMPSQL2");

	CString strOut = "";
	Matrix<float>* p_matrix;
	DFIter<Matrix<float> >  matrixIter;
	matrixIter = DFIter<Matrix<float> >(*(pR->m_tablePtr));
	p_matrix =  matrixIter();
	
	FILE* fp_out;
	if ((fp_out = fopen("TEMPNEST.txt","wt"))==NULL)
	{
		AfxMessageBox("Error creating file !");
		return;
	}
	CString newRelation = "begin %TEMPNEST%\n";

	if (opid>2)
	{
		strOut = FormatMatrix(pR, p_matrix);
		strOut.Trim();
		if (strOut[0]=='S')
		{
			strOut.SetAt(0, '\"');
			strOut += "\"";
		}
		cs_Where1 += strOut + ".";
		newRelation += SQL2Datalog(cs_Create, cs_Select1, cs_From1, cs_Where1)+"\n";
	}
	else //deal with in and not in
	{
		//Set select
		Relation* pR1 = FindRelation("TEMPSQL1");
		POSITION pos = pR1->m_strAtriList.GetHeadPosition();
		cs_Select1 = "";
		while (pos != NULL)
			cs_Select1 += pR1->m_strAtriList.GetNext(pos)+",";
		cs_Select1.Delete(cs_Select1.GetLength()-1);
		
		if (addfld)
		{//recover to the original selection fields
			wh2 = cs_Select1.Right(cs_Select1.GetLength()-cs_Select1.ReverseFind(',')-1);
			cs_Select1 = cs_Select1.Left(cs_Select1.ReverseFind(','));
		}
		else
			wh2.Replace('.','_');

		//Set From
		cs_From1 = "TEMPSQL1";

		//Set Where
		CArray<float> lowerls;
		CArray<BOOL> lowereqls;
		CArray<float> upperls;
		CArray<BOOL> uppereqls;
		CArray<float> vResult;
		CArray<BOOL> vResultEq;
		CArray<CString> sResult;
		while (p_matrix != NULL)
		{
			char cOut[32];
			float upper=5000000; 
			float lower=-5000000;
			BOOL uppereq, lowereq;
			for(int i=0; i< p_matrix->Rows(); i++)
			{   
				POSITION pos1 = pR->m_strAtriList.GetHeadPosition();
				Vector<float> vector = (*p_matrix)[i];
				float value = (float)(vector[1]) / (float)(vector[2]);
				int opsign=(int)(vector[0]);

				if ((float)vector[2]<0) //negative numbers
				{
					switch (opsign)
					{
					case LESSTHAN: opsign = GREATTHAN; break;
					case LESSEQUAL: opsign = GREATEQUAL; break;
					case GREATTHAN: opsign = LESSTHAN; break;
					case GREATEQUAL: opsign = LESSEQUAL; break;
					}
				}
				switch (opsign)
				{
				case EQUAL :	//=
					upper = lower = value;
					uppereq = lowereq = true;
					break;
				case LESSTHAN :	//<
					if (upper > value) 
					{
						upper = value;
						uppereq = false;
					}
					break;
				case LESSEQUAL :	//<=
					if (upper > value) 
					{
						upper = value;
						uppereq = true;
					}
					break;
				case GREATTHAN :	//>
					if (lower < value) 
					{
						lower = value;
						lowereq = false;
					}
					break;
				case GREATEQUAL :	//>= 
					if (lower < value) 
					{
						lower = value;
						lowereq = true;
					}
					break;
				}
				//check if text
				if (vector[0]==STREQUAL)							
				{
					CString atomCs;
					atomCs.Format("%s", (*(*dataBase).m_pTextVec)[(int)vector[1]].GetText()); 
					sResult.Add(atomCs);
					break;
				}
			}
			if (lower<=upper)
			{
				if ((lower<upper)||((lowereq)&&(uppereq)))
				{
					lowerls.Add(lower);
					upperls.Add(upper);
					lowereqls.Add(lowereq);
					uppereqls.Add(uppereq);
				}
			}
			p_matrix = matrixIter();
		}

		int i=0; 
		while (i<lowerls.GetCount())
		{
			int addition=1;
			for (int j=i+1; j<lowerls.GetCount(); j++)
			{
				float maxlower = max(lowerls[i],lowerls[j]);
				float minupper = min(upperls[i],upperls[j]);
				if (maxlower<minupper)
				{
					if (lowerls[i]<lowerls[j])
					{
						lowerls.SetAt(j,lowerls[i]);
						lowereqls.SetAt(j,lowereqls[i]);
					}
					if (upperls[i]>upperls[j])
					{
						upperls.SetAt(j,upperls[i]);
						uppereqls.SetAt(j,uppereqls[i]);
					}
					lowerls.RemoveAt(i);
					lowereqls.RemoveAt(i);
					upperls.RemoveAt(i);
					uppereqls.RemoveAt(i);
					addition = 0; //Item i was removed and keep i value for next item
					break;
				}
			}		
			i = i + addition;
		}

		if (lowerls.GetCount()>0)
		{
			vResult.Add(lowerls[0]);
			vResultEq.Add(lowereqls[0]);
			vResult.Add(upperls[0]);
			vResultEq.Add(uppereqls[0]);
		}
		for (int j=1; j<lowerls.GetCount(); j++)
		{
			BOOL inserted = false;
			for(int k=0; k<vResult.GetCount(); k++)
			{
				if (upperls[j]<vResult[k])
				{
					vResult.InsertAt(k, upperls[j]);
					vResultEq.InsertAt(k, uppereqls[j]);
					vResult.InsertAt(k, lowerls[j]);
					vResultEq.InsertAt(k, lowereqls[j]);
					inserted = true;
					break;
				}
			}
			if (!inserted)
			{
				vResult.Add(lowerls[j]);
				vResultEq.Add(lowereqls[j]);
				vResult.Add(upperls[j]);
				vResultEq.Add(uppereqls[j]);
			}
		}

		CString f2str;
		if (opid==1) //in operator
		{
			if (cs_Select1.Find(wh2)>=0)
				newRelation += cs_Create + "(" + cs_Select1 + ") :- TEMPSQL1("+ cs_Select1+"), TEMPSQL2("+wh2+").\n";
			else
				newRelation += cs_Create + "(" + cs_Select1 + ") :- TEMPSQL1("+ cs_Select1+","+wh2+"), TEMPSQL2("+wh2+").\n";

			/*
			if (sResult.GetCount()>0)
			{
				for (int i=0; i<sResult.GetCount(); i++)
				{
					cs_Where1 = wh2+"="+"\""+sResult[i]+"\"\n";
					newRelation += SQL2Datalog(cs_Create, cs_Select1, cs_From1, cs_Where1)+"\n";
				}
			}
			else if (vResult.GetCount()>0)
			{
				for (int i=0; i<vResult.GetCount(); i=i+2)
				{
					cs_Where1 = "";
					if (vResult[i]>-5000000)
					{
						f2str.Format("%f", vResult[i]);
						if (vResultEq[i])
							cs_Where1 += wh2+">="+ f2str +",";
						else
							cs_Where1 += wh2+">"+ f2str +",";
					}
					if (vResult[i+1]<5000000)
					{
						f2str.Format("%f", vResult[i+1]);
						if (vResultEq[i+1])
							cs_Where1 += wh2+"<="+ f2str+",";
						else
							cs_Where1 += wh2+"<"+ f2str+",";
					}

					cs_Where1.SetAt(cs_Where1.GetLength()-1,'.');

					newRelation += SQL2Datalog(cs_Create, cs_Select1, cs_From1, cs_Where1)+"\n";
				}
			}
			else {
				AfxMessageBox(cs_Where1 +" ; "+ wh2+"<="+ f2str);
			}*/
		}
		else //not in operator
		{
			if (sResult.GetCount()>0)
			{
				newRelation = "begin %TEMPSQL3%\n";
				BOOL existing;
				matrixIter = DFIter<Matrix<float> >(*(pR1->m_tablePtr));
				p_matrix =  matrixIter();
				while (p_matrix != NULL)
				{
					existing = false;
					//Check if this matrix should output as result
					//Compare each matrix with all nested result set. Complexity: O(m*n)
					//This process can be improved if the matrix and nested set are sorted by the nested field
					for(int i=0; i< p_matrix->Rows(); i++)
					{   
						Vector<float> vector = (*p_matrix)[i];
						if (((float)vector[nestfld+2]==1)&&(vector[0]==5.5))
						{
							CString atomCs;
							atomCs.Format("%s", (*(*dataBase).m_pTextVec)[(int)vector[1]].GetText()); 
							for (int j=0; j<sResult.GetCount(); j++)
							{
								if (atomCs==sResult[j])
								{
									existing = true;
									break;
								}
							}
							break;
						}
					}
					if (!existing)
						GetMatrixInfo(pR1, p_matrix, newRelation, true);

					p_matrix =  matrixIter();
				}
				newRelation += "end %TEMPSQL3%\n";
				newRelation.Replace("TEMPSQL1", "TEMPSQL3");
				fwrite(newRelation, sizeof(char), newRelation.GetLength(), fp_out);
				fclose(fp_out);
				DoCalculate("TEMPNEST.txt");

				if ((fp_out = fopen("TEMPNEST.txt","wt"))==NULL)
				{
					AfxMessageBox("Error creating file !");
					return;
				}
				newRelation = "begin %TEMPNEST%\n";
				newRelation += SQL2Datalog(cs_Create, cs_Select1, "TEMPSQL3", "")+"\n";
				
			}
			else if (vResult.GetCount()>0)
			{
				if (vResult[0]>-5000000)
				{
					cs_Where1 = "";
					f2str.Format("%f", vResult[0]);
					if (vResultEq[0])
						cs_Where1 += wh2+"<"+ f2str;
					else
						cs_Where1 += wh2+"<="+ f2str;
					newRelation += SQL2Datalog(cs_Create, cs_Select1, cs_From1, cs_Where1)+"\n";
				}
				if (vResult[vResult.GetCount()-1]<5000000)
				{
					cs_Where1 = "";
					f2str.Format("%f", vResult[vResult.GetCount()-1]);
					if (vResultEq[vResult.GetCount()-1])
						cs_Where1 += wh2+">"+ f2str;
					else
						cs_Where1 += wh2+">="+ f2str;
					newRelation += SQL2Datalog(cs_Create, cs_Select1, cs_From1, cs_Where1)+"\n";
				}
				for (int i=1; i<vResult.GetCount()-1; i=i+2)
				{
					cs_Where1 = "";
					f2str.Format("%f", vResult[i]);
					if (vResultEq[i])
						cs_Where1 += wh2+">"+ f2str+",";
					else
						cs_Where1 += wh2+">="+ f2str+",";
					
					f2str.Format("%f", vResult[i+1]);
					if (vResultEq[i+1])
						cs_Where1 += wh2+"<"+ f2str+",";
					else
						cs_Where1 += wh2+"<="+ f2str+",";

					cs_Where1.Delete(cs_Where1.GetLength()-1);
					newRelation += SQL2Datalog(cs_Create, cs_Select1, cs_From1, cs_Where1)+"\n";
				}
				
			}
		}
	}

	newRelation += "end %TEMPNEST%\n";

	fwrite(newRelation, sizeof(char), newRelation.GetLength(), fp_out);
	fclose(fp_out);

	DoCalculate("TEMPNEST.txt");
	UpdateAllViews(NULL);
	RemoveRelation("TEMPSQL1");
	RemoveRelation("TEMPSQL2");
	RemoveRelation("TEMPSQL3");

	UpdateAllViews(NULL);

}

void CIdbDoc::RemoveRelation(CString RelationName)
{
	m_dataBase.m_pRelationList->GotoHead();  
	SlistIter<Relation> relIter( *(m_dataBase.m_pRelationList) );
	Relation* pR;
	
	while(pR =relIter()) 
	{
			String strName = pR->Name();
			if (RelationName==strName.GetText())
			{
				m_dataBase.m_pRelationList->Delete(*pR);
				m_dataBase.numRels -- ; 
				UpdateAllViews(NULL);
				break;
			}
	}
}

void CIdbDoc::saveImageInfo(CString fileName)
{
	POSITION pos = GetFirstViewPosition();
	while (pos != NULL)
	{
		CView* pView = GetNextView(pos);
		if (pView != NULL  &&  pView->IsKindOf(RUNTIME_CLASS(CGraphView)))
		{
			//((CGraphView*)pView)->saveImageInfo(fileName);
			ClearDrawObjList();
			((CGraphView*)pView)->m_selection.RemoveAll();
			UpdateAllViews(NULL);
			break;
		}
	}

}

/*********************************************************
 * Author:   Shasha Wu
 * Time:     Nov 2004
 * Input:    Matrix
 * Output:   Display the values of each fields only.
 *           No field name.
 *           Columns ordered by field order in the relation definition.
 *           All columns have fixed 30 characters width.
 *           String column start by character "S" as the sign of string field.
 ***********************************************************/
CString CIdbDoc::FormatMatrix(Relation* pR, Matrix<float>* p_matrix)
{
	if (pR==NULL)
		return "";
	
	//Shasha(July 03): Simplify the display. 
	p_matrix->Simplify(true);

	CString tuple = "";
	POSITION pos = pR->m_strAtriList.GetHeadPosition();
	//int i = pR->m_strAtriList.GetCount();
	while (pos != NULL)
	{
		tuple += pR->m_strAtriList.GetNext(pos);
		tuple += ",";
	}

	if (p_matrix != NULL)
	{
		char cOut[32];
		
		for(int i=0; i< p_matrix->Rows(); i++)
		{   
			POSITION pos1 = pR->m_strAtriList.GetHeadPosition();
			Vector<float> vector = (*p_matrix)[i];
			BOOL bAdd = FALSE;
			CString strAttr;
			CString atomCs="";
			for(int j=2; j< vector.Size(); j++)
			{
				if (vector[j] != 0)
					strAttr = pR->m_strAtriList.GetAt(pos1);
				pR->m_strAtriList.GetNext(pos1);
				if (vector[j] == 0)
					continue;
				if (vector[j] > 0  &&  bAdd)
					atomCs += "+";
				if (vector[j] == -1)
					atomCs += "-";
				else if (vector[j] != 1)
				{
					if (vector[j]-(int)(vector[j]) != 0)
						sprintf(cOut, "%.4f ", (float)(vector[j]));
					else
						sprintf(cOut, "%.f ", (float)(vector[j]));
					atomCs += cOut;
				}
				atomCs += strAttr;
				atomCs += " ";
				bAdd = TRUE;
				//AfxMessageBox("1:"+atomCs);
			}
			switch ((int)(vector[0]))
			{
			case 0 :	atomCs = ""; //atomCs += "= ";
				break;
			case 1 :	atomCs += "< ";
				break;
			case 2 :	atomCs += "<= ";
				break;
			case 3 :	atomCs += "> ";
				break;
			case 4 :	atomCs += ">= ";
				break;
			case 5 :	atomCs = ""; //atomCs += "= ";
				break;
			}
			//check if text
			if (vector[0]==5.5)							
				atomCs.Format("S%29s", (*(*dataBase).m_pTextVec)[(int)vector[1]].GetText()); 
			else {
				sprintf(cOut, "%30.4f", (float)(vector[1]));
				atomCs += cOut;
			}
			//AfxMessageBox(strAttr+"->"+atomCs);

			tuple.Replace(strAttr, atomCs);
		}
		return tuple;
	}
}

BOOL CIdbDoc::MaxMinOnStr(Relation* pR, int AggFldPos)
{
	Matrix<float>* p_matrix;

	if (pR==NULL)
		return false;

	DFIter<Matrix<float> >  matrixIter;
	matrixIter = DFIter<Matrix<float> >(*(pR->m_tablePtr));
	p_matrix =  matrixIter();
	while (p_matrix != NULL)
	{
		p_matrix->Simplify(true);
		if (p_matrix != NULL)
		{
			for(int i=0; i< p_matrix->Rows(); i++)
			{   
				Vector<float> vector = (*p_matrix)[i];
				//check if text
				if ((vector[2+AggFldPos]==1)&&(vector[0]==5.5))
					return true; 
			}
		}
		p_matrix =  matrixIter();
	}
	
	return false; 
}

void CIdbDoc::OnBnSqlRecursion()
{
	// TODO: Add your control notification handler code here
	Dlg_SQLRecursion DlgRecur;

    CString docpath=GetPathName();
	CString filename=GetTitle();

	int pos;
	pos = docpath.ReverseFind('\\');
	docpath = docpath.Left(pos+1);
	pos = filename.Find(".",0);
	if (pos>0) 
		filename = filename.Left(pos);
	filename = filename + "_RecuSql.txt";
	docpath = docpath + filename;

	DlgRecur.FileRead(docpath);

	if (DlgRecur.DoModal() == IDOK)
	{
		DlgRecur.FileSave(docpath);

		last_query_time=clock();    
		DoSqlRecur(&DlgRecur.m_ViewName_List,&DlgRecur.m_Select1_List,&DlgRecur.m_From1_List,&DlgRecur.m_Where1_List,&DlgRecur.m_Select2_List,&DlgRecur.m_From2_List,&DlgRecur.m_Where2_List);
		SetQueryTime();
		ShowResult(DlgRecur.m_ViewName);
	}
}

void CIdbDoc::DoSqlRecur(CArray<CString>* ViewName, CArray<CString>* Select1, CArray<CString>* From1, CArray<CString>* Where1, CArray<CString>* Select2, CArray<CString>* From2, CArray<CString>* Where2)
{

	CString cs_ViewName; 
	CString cs_Select1; 
	CString cs_From1; 
	CString cs_Where1;
	CString cs_Select2;
	CString cs_From2;
	CString cs_Where2;
	CString newRelation = "begin %TEMPRECUR%\n";
	for (int i=0; i<ViewName->GetCount(); i++)
	{
		cs_ViewName = ViewName->GetAt(i); 
		cs_Select1 = Select1->GetAt(i); 
		cs_From1 = From1->GetAt(i); 
		cs_Where1 = Where1->GetAt(i);
		cs_Select2 = Select2->GetAt(i);
		cs_From2 = From2->GetAt(i);
		cs_Where2 = Where2->GetAt(i);

		if (cs_Select1!="")
			newRelation += SQL2Datalog(cs_ViewName, cs_Select1, cs_From1, cs_Where1)+"\n";
		if (cs_Select2!="")
			newRelation += SQL2Datalog(cs_ViewName, cs_Select2, cs_From2, cs_Where2)+"\n";
	}
	newRelation += "end %TEMPRECUR%";
	//AfxMessageBox(newRelation);

	FILE* fp_out;
	if ((fp_out = fopen("TEMPRECUR.txt","wt"))==NULL)
	{
		AfxMessageBox("Error creating file !");
		return;
	}

	fwrite(newRelation, sizeof(char), newRelation.GetLength(), fp_out);

	fclose(fp_out);

	((CMainFrame*)(AfxGetApp()->GetMainWnd()))->ApproxDlg();
	DoCalculate("TEMPRECUR.txt");

	UpdateAllViews(NULL);

}

CString CIdbDoc::tabledisplay(CString m_strOut)
{
	// TODO: Add your control notification handler code here
	if (m_strOut.Find("===========")>0)
		return "";
	CString line;
	CString table = "";
	CString head;
	CString tuple;
	CString constraints = "";
	int pos1=0;
	line = m_strOut.Tokenize("\n",pos1);
	while (line!="")
	{
		line.Trim();
		if (line.Find(":-")>=0) 
		{
			if (table=="")
			{
				line.Delete(0,line.Find("(")+1);
				line.Delete(line.Find(":-"),2);
				line.Trim();
				CString field;
				int pos2=0;
				field = line.Tokenize(",)", pos2);
				while (field!="")
				{
					field.Trim();
					field.Format("%-18s", field);
					table += field;
					field = line.Tokenize(",)", pos2);
				}
				field.Format("%-10s", "CONSTRAINTS");
				table += field ;
				head = table;
				tuple = head;

				table += (char)(13);
				table += (char)(10);
				field = "";
				for (int i=0; i<table.GetLength()+20; i++)
					field += "=";
				table += field;
				table += (char)(13);
				table += (char)(10);
			}
		}
		else if ((line.Find(",")>=0)||(line.Find(".")>=0))
		{
			CString field;
			CString value;
			int pos2=0;
			field = line.Tokenize("=", pos2);
			field.Trim();
			value = line.Tokenize("=", pos2);
			value.Trim();
			BOOL TupleEnd = (line[line.GetLength()-1] == '.');
			value.Delete(value.GetLength()-1);

			CString idx = "";
			while ((field[0]=='-') || (field[0]=='.') || ((field[0]>='0')&&(field[0]<='9')))
			{
				idx += field[0];
				field.Delete(0);
			}
			if (idx=="-")
				idx = "-1";
			if (idx!="")
				value.Format("%-18.2f", atof(value)/atof(idx));
			else
				value.Format("%-18s", value);

			field.Format("%-18s", field);
			if (tuple.Replace(field, value)==0)
				constraints += line + "  ";
			if (TupleEnd)
			{
				if ((constraints.GetLength()>1)&&(constraints[constraints.GetLength()-2]==',')) //an extra space will be added at the end of each constraint
					constraints.SetAt(constraints.GetLength()-2, '.');
				tuple.Replace("CONSTRAINTS", constraints);
				
				table += tuple;
				table += (char)(13);
				table += (char)(10);
				
				tuple = head;
				constraints = "";
			}
		}
		line = m_strOut.Tokenize("\n",pos1);
	}
	return table;
	//UpdateData(false);
}

void CIdbDoc::ShowResult(CString RelationName)
{
	if (RelationName=="")
		return;
	if (RelationName.Find("(")>0)
		RelationName = RelationName.Left(RelationName.Find("("));

	m_dataBase.m_pRelationList->GotoHead();  
	SlistIter<Relation> relIter( *(m_dataBase.m_pRelationList) );
	Relation* pR;
	Matrix<float>* p_matrix;

	while(pR =relIter()) 
	{
		String strName = pR->Name();
		if (strcmp(strName.GetText(), RelationName)==0)
		{
			ShowRelationInfo(pR, NULL);

			break;
		}
	}
}

BOOL IsConstant(CString formula)
{
	formula.Trim();
	if ((formula.GetAt(0)=='"')&&(formula.GetAt(formula.GetLength()-1)=='"'))
		return true;
	if ((formula.GetAt(0)=='\'')&&(formula.GetAt(formula.GetLength()-1)=='\''))
		return true;
	for (int i=0; i<formula.GetLength(); i++)
	{
		char ch = formula.GetAt(i);
		if (((ch<'0')||(ch>'9'))&&(ch!='.'))
		{
			return false;
		}
	}
	return true;
}

void getsign(CString inputstr, CString atom, CString* sign, CString* nsign)
{
	*sign = "";
	for(int i=inputstr.Find(atom)-1; i>=0; i--)
	{
		if (inputstr.GetAt(i)=='-')
			*sign = "-";
		else if (inputstr.GetAt(i)=='+')
			*sign = "+";
		else if (inputstr.GetAt(i)!=' ')
			break;
	}
	if (*sign=="")
		*sign = "+";

	if (*sign=="+")
		*nsign="-";
	else if (*sign=="-")
		*nsign="+";

}

CString CIdbDoc::FormalizeTuple(CString tuple)
{
	CString resultTuple = "";
	tuple.Trim();
	if (tuple.GetAt(tuple.GetLength()-1) == '.')
		tuple.Delete(tuple.GetLength()-1);

	CString constraint;
	int curpos=0;
	constraint = tuple.Tokenize(",", curpos);
	while (constraint != "")
	{
		resultTuple += FormalizeCS(constraint) + ",";
		constraint = tuple.Tokenize(",", curpos);
	}
	resultTuple.Delete(resultTuple.GetLength()-1);
	return resultTuple;
}

CString CIdbDoc::FormalizeCS(CString constraint)
{
	CString Lstr, Rstr, Lout, Rout;

	int pos = 0;
	Lstr = constraint.Tokenize("><=",pos);
	Rstr = constraint.Tokenize("><=",pos);
	if (Rstr=="")
		return constraint;
	Lstr.Trim();
	Rstr.Trim();
	CString sign, nsign;
	pos=0;
	CString atom;
	
	atom = Lstr.Tokenize("+-*/",pos);
	getsign(Lstr, atom, &sign, &nsign);
	while (atom!="")
	{
		atom.Trim();
		if (IsConstant(atom))
			Rout += nsign + atom;
		else
			Lout += sign + atom;

		atom = Lstr.Tokenize("+-*/",pos);
		getsign(Lstr, atom, &sign, &nsign);
	}

	pos=0;
	atom = Rstr.Tokenize("+-*/",pos);
	getsign(Rstr, atom, &sign, &nsign);
	while (atom!="")
	{
		atom.Trim();
		if (IsConstant(atom))
			Rout += sign + atom;
		else
			Lout += nsign + atom;

		atom = Rstr.Tokenize("+-*/",pos);
		getsign(Rstr, atom, &sign, &nsign);
	}

	if (constraint.Find(">=")>0)
		sign = " >= ";
	else if (constraint.Find("<=")>0)
		sign = " <= ";
	else if (constraint.Find(">")>0)
		sign = " > ";
	else if (constraint.Find("<")>0)
		sign = " < ";
	else if (constraint.Find("=")>0)
		sign = " = ";
	
	if (Rout=="")
		Rout = "0";
	
	if (Rout.GetAt(0)=='+')
		Rout.Delete(0);

	if (Lout.GetAt(0)=='+')
		Lout.Delete(0);

	return Lout+sign+Rout;
}

CString CIdbDoc::SQL2Datalog(CString ViewName, CString cs_select, CString cs_from, CString cs_where)
{
	if ((ViewName.Find("(")==-1)&&(ViewName.Find(")")==-1))
	{
		CString fieldstr = cs_select;
		fieldstr.Replace(".", "_");
		ViewName = ViewName + "(" + fieldstr + ")";
	}
	// still has problem, generate an error
	if ((ViewName.Find("(")==-1)||(ViewName.Find(")")==-1))
	{
		AfxMessageBox("ERROR: Incomplete view name = "+ ViewName);
		return "ERROR(problem):-problem=\"View name incomplete\".";
	}
	cs_where = FormalizeTuple(cs_where);
	cs_from.Replace(" AS ", " as ");
	cs_from.Replace(" As ", " as ");
	
	CArray<CString> sellist;
	CArray<CString> fromlist;
	CArray<CString> fromAlias;
	CArray<CString> wherelist;

	CArray<CString> RelationNames;
	CArray<CString> RelationDefs;
	CArray<int> RelationDefPos;
	m_dataBase.m_pRelationList->GotoHead();  
	SlistIter<Relation> relIter( *(m_dataBase.m_pRelationList) );
	Relation* pR;
	Matrix<float>* p_matrix;
	int AttrPos=-1;

	while(pR =relIter()) 
	{
		String strName = pR->Name();
		RelationNames.Add(CString(strName.GetText()));
		RelationDefPos.Add(AttrPos+1);
	
		CString AttrName = "";
		POSITION pos = pR->m_strAtriList.GetHeadPosition();
		int i = pR->m_strAtriList.GetCount();
		while (pos != NULL)
		{
			AttrName = pR->m_strAtriList.GetNext(pos);
			AttrPos = RelationDefs.Add(AttrName);
		}
	}

	//FROM 1
	int pos=0;
	CString tokenstr = cs_from.Tokenize(",", pos);
	while (tokenstr != "")
	{
		tokenstr.Trim();
		int AsPos=tokenstr.Find(" as ");
		if (AsPos>0)
		{
			fromlist.Add(tokenstr.Left(AsPos).Trim());
			fromAlias.Add(tokenstr.Right(tokenstr.GetLength()-AsPos-3).Trim()+"_");
		}
		else
		{
			fromlist.Add(tokenstr);
			fromAlias.Add(tokenstr+"_");
		}
		tokenstr = cs_from.Tokenize(",", pos);
	}

	//Select 1
	pos=0;
	tokenstr = cs_select.Tokenize(",", pos);
	while (tokenstr != "")
	{
		tokenstr.Trim();
		if (tokenstr.Find(".")>0)
			tokenstr.Replace(".", "_");
		else
			tokenstr = fromAlias[0] + tokenstr;
		sellist.Add(tokenstr);
		tokenstr = cs_select.Tokenize(",", pos);
	}

	//WHERE 1
	pos=0;
	tokenstr = cs_where.Tokenize(",", pos);
	while (tokenstr != "")
	{
		tokenstr.Replace(" ", ""); // no space charactor
		if ((tokenstr.Find("=")>0)||(tokenstr.Find("<")>0)||(tokenstr.Find(">")>0))
		{
			//if "." is not for numeric value, it is the connection between table and field
			//then change it to be "_"
			//Support field with table prefix scuh as "1.456P.fld1 - 2.4P.fld2 > 1.2" => "1.456P_fld1 - 2.4P_fld2 > 1.2"
			//Support field without table prefix scuh as "1.456fld1 - 2.4fld2 > 1.2" => "1.456P_fld1 - 2.4P_fld2 > 1.2"
			//Support field with/without table prefix scuh as "1.456P.fld1 - 2.4fld2 > 1.2" => "1.456P_fld1 - 2.4P_fld2 > 1.2"
			//Support field with more than one tables prefix scuh as "1.456P1.fld1 - 2.4P2.fld2 > 1.2" => "1.456P1_fld1 - 2.4P2_fld2 > 1.2"
			CString fldstr;
			int posfld=0;
			CString outwhere = tokenstr;
			fldstr = tokenstr.Tokenize("+-*/><=! ", posfld);
			while (fldstr!="")
			{
				if (fldstr!=".")
				{
					//fldstr is the variable and its prefix number
					fldstr += "#"; // make sure following for loop ended in the if sentence
					for (int i=0; i<fldstr.GetLength(); i++)
					{
						if ((fldstr[i]!='.')&&((fldstr[i]<'0')||(fldstr[i]>'9')))
						{
							fldstr.Delete(0, i);
							break;
						}
					}
					fldstr.Delete(fldstr.GetLength()-1);
					//fldstr is only the variable

					if (fldstr.Find(".")>0)
					{  //field with table prefix such as P.field1
						int pointpos = fldstr.Find(".");
						outwhere.SetAt(posfld-1-fldstr.GetLength()+pointpos, '_');
					}
					else if ((fldstr!="")&&(fldstr.Find("\"")==-1))
					{ //field without table prefix such as field1
						outwhere.Insert(posfld-1-fldstr.GetLength(), fromAlias[0]);
						tokenstr = outwhere;
						posfld += fromAlias[0].GetLength();
					}
				}

				fldstr = tokenstr.Tokenize("+-*/><=! ", posfld);
			}
			tokenstr = outwhere;
			wherelist.Add(tokenstr);
		}
		tokenstr = cs_where.Tokenize(",", pos);
	}

	//Add new relation to list for recursion use
	RelationNames.Add(ViewName.Left(ViewName.Find("(")).Trim());
	RelationDefPos.Add(RelationDefs.GetCount());

	CString newRelation;
	CArray<CString> NewRelAttr;
	pos=0;
	CString Tmpstr=ViewName.Trim();
	Tmpstr.Delete(0,Tmpstr.Find("(")+1);
	tokenstr = Tmpstr.Tokenize(",)", pos);
	while (tokenstr != "")
	{
		tokenstr.Trim();
		NewRelAttr.Add(tokenstr);
		RelationDefs.Add(tokenstr);
		tokenstr = Tmpstr.Tokenize(",)", pos);
	}
	
	//One more empty relation for loop k
	RelationNames.Add("End");
	RelationDefPos.Add(RelationDefs.GetCount());

	//Add view name, select1 and from1
	newRelation = ViewName + " :- ";
	for (int i=0; i<fromlist.GetCount(); i++)
	{
		for(int j=0; j<RelationNames.GetCount(); j++)
		{
			if (fromlist[i] == RelationNames[j])
			{
				newRelation += RelationNames[j] + "(";
				for (int k=RelationDefPos[j]; k<RelationDefPos[j+1]; k++)
				{
					newRelation += fromAlias[i]+RelationDefs[k] +",";
				}
				newRelation.SetAt(newRelation.GetLength()-1, ')'); 
				break;
			}
		}
		newRelation += ", ";
	}

	//Add Where1
	for (int i=0; i<wherelist.GetCount(); i++)
	{
		newRelation += wherelist[i] +", ";
		//AfxMessageBox(wherelist[i]);
	}
	newRelation.SetAt(newRelation.GetLength()-2, '.');

	//Change original relation name to new relation's attributes
	for (int i=0; i<sellist.GetCount(); i++)
		newRelation.Replace(sellist[i], NewRelAttr[i]);

	//newRelation += "\n";

	sellist.RemoveAll();	sellist.FreeExtra();
	fromlist.RemoveAll();	fromlist.FreeExtra();
	fromAlias.RemoveAll();	fromAlias.FreeExtra();
	wherelist.RemoveAll();	wherelist.FreeExtra();
	RelationNames.RemoveAll();	RelationNames.FreeExtra();
	RelationDefs.RemoveAll();	RelationDefs.FreeExtra();
	RelationDefPos.RemoveAll();	RelationDefPos.FreeExtra();
	NewRelAttr.RemoveAll();	NewRelAttr.FreeExtra();

	return newRelation;

}