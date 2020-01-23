// NewSocket.cpp : implementation file
//

#include "stdafx.h"
#include "idb.h"
#include "NewSocket.h"

#include "db.h"
#include "relation.h"
#include "slist.h"
#include <fstream.h>
#include "IdbDoc.h"
#include "OwnListBox.h"
#include "IdbView.h"
#include "MainFrm.h"
#include "graphview.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CNewSocket


CNewSocket::CNewSocket()
{

}

CNewSocket::~CNewSocket()
{
}


// Do not edit the following lines, which are needed by ClassWizard.
#if 0
BEGIN_MESSAGE_MAP(CNewSocket, CAsyncSocket)
	//{{AFX_MSG_MAP(CNewSocket)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()
#endif	// 0

/////////////////////////////////////////////////////////////////////////////
// CNewSocket member functions

void CNewSocket::OnReceive(int nErrorCode) 
{
	// TODO: Add your specialized code here and/or call the base class

	m_nLength=Receive(m_szBuffer,sizeof(m_szBuffer),0);

	CString cs_Cmd="";
	CString cs_User="";
	CString cs_Param1="";
	CString cs_Param2="";
	CString cs_Param3="";
	CString cs_Param4="";
	CString cs_Param5="";
	CString cs_Param6="";
	CString cs_Param7="";
	CString cs_Param8="";
	CString cs_Param9="";

	getParameters(m_szBuffer,cs_Cmd,cs_User,cs_Param1,cs_Param2,cs_Param3,
		cs_Param4,cs_Param5,cs_Param6,cs_Param7,cs_Param8,cs_Param9);
//////////////////// Open /////////////////////////////////
	strcpy(m_szBuffer,"1#");
	if (strcmp(LPCSTR(cs_Cmd),"Open")==0)
	{
		int j,k;
		CString filename;
		//strcpy(filename,SOURCE_DB_DIR);
		//strcat(filename,LPCSTR(cs_Param1));
		filename = SOURCE_DB_DIR + cs_Param1;

		AfxGetApp()->OpenDocumentFile(filename);
		
		cs_Param1.TrimLeft();
		cs_Param1.TrimRight();
		cs_User.TrimLeft();
		cs_User.TrimRight();
		
		bool findUser=false;

		for (j=0; j<MAX_USER; j++)
		{
			if (((CIdbApp*)AfxGetApp())->m_User[j].cs_UserName == cs_User)
			{
				findUser = true;
				break;
			}
			if (((CIdbApp*)AfxGetApp())->m_User[j].cs_UserName == "")
				break;
		}

		if (findUser)
		{
			for (k=0; k<MAX_FILE_OPEN; k++)
			{
				if (((CIdbApp*)AfxGetApp())->m_User[j].cs_DocName[k] == cs_Param1)
					break;
				if (((CIdbApp*)AfxGetApp())->m_User[j].cs_DocName[k] == "")
				{
					((CIdbApp*)AfxGetApp())->m_User[j].cs_DocName[k] = cs_Param1;
					((CIdbApp*)AfxGetApp())->m_User[j].p_Doc[k] = (CIdbDoc*)((CIdbApp*)AfxGetApp())->p_Doc;
					((CIdbApp*)AfxGetApp())->m_User[j].p_View[k] = (CIdbView*)((CIdbApp*)AfxGetApp())->p_View;
					((CIdbApp*)AfxGetApp())->m_User[j].p_Frame[k] = (CMDIChildWnd*)((CIdbApp*)AfxGetApp())->p_Frame;
					((CIdbApp*)AfxGetApp())->m_User[j].preSelIndex[k] = -1;
					break;
				}
			}
			strcpy(m_szBuffer,"0#");
		}
		else
		{
			((CIdbApp*)AfxGetApp())->m_User[j].cs_UserName = cs_User;
			((CIdbApp*)AfxGetApp())->m_User[j].cs_DocName[0] = cs_Param1;
			((CIdbApp*)AfxGetApp())->m_User[j].p_Doc[0] = (CIdbDoc*)((CIdbApp*)AfxGetApp())->p_Doc;
			((CIdbApp*)AfxGetApp())->m_User[j].p_View[0] = (CIdbView*)((CIdbApp*)AfxGetApp())->p_View;
			((CIdbApp*)AfxGetApp())->m_User[j].p_Frame[0] = (CMDIChildWnd*)((CIdbApp*)AfxGetApp())->p_Frame;
			((CIdbApp*)AfxGetApp())->m_User[j].preSelIndex[0] = -1;
		}
	
		//memset(m_szBuffer,0,sizeof(m_szBuffer));

	}

	//////////////////////////// Basic Sql /////////////////////////
	if (strcmp(LPCSTR(cs_Cmd),"SQLBasic")==0 ||
		strcmp(LPCSTR(cs_Cmd),"SQLAggregate")==0 ||
		strcmp(LPCSTR(cs_Cmd),"SQLSet")==0 ||
		strcmp(LPCSTR(cs_Cmd),"SQLNested")==0)
	{
		// look for the user
		int userIndex = getUserIndex(cs_User);

		if (userIndex==-1)
			goto next;

		//	look for the document used
		int docIndex = getDocIndex(userIndex,cs_Param1);

		if (docIndex==-1)
			goto next;
		
		CIdbDoc* pDoc = (CIdbDoc*)((CIdbApp*)AfxGetApp())->m_User[userIndex].p_Doc[docIndex];
		CIdbView* pView = (CIdbView*)((CIdbApp*)AfxGetApp())->m_User[userIndex].p_View[docIndex];
		CMDIChildWnd* pFrame = (CMDIChildWnd*)((CIdbApp*)AfxGetApp())->m_User[userIndex].p_Frame[docIndex];

		pFrame->ActivateFrame(-1);

		//	do calculate
		if (pDoc != NULL)
		{
			if (strcmp(LPCSTR(cs_Cmd),"SQLBasic")==0)
				pDoc->DoSql(cs_Param2,cs_Param3,cs_Param4,cs_Param5);

			if (strcmp(LPCSTR(cs_Cmd),"SQLSet")==0)
				pDoc->DoSqlsets(cs_Param2,cs_Param3,cs_Param4,cs_Param5,cs_Param6,cs_Param7,
				cs_Param8,cs_Param9);

			if (strcmp(LPCSTR(cs_Cmd),"SQLAggregate")==0)
				pDoc->DoSqlAggregation(cs_Param2,cs_Param3,cs_Param4,cs_Param5,cs_Param6,cs_Param7);

			if (strcmp(LPCSTR(cs_Cmd),"SQLNested")==0)
				pDoc->DoNestedSql(cs_Param2,cs_Param3,cs_Param4,cs_Param5,cs_Param6,cs_Param7,cs_Param8,cs_Param9);

			pDoc->UpdateAllViews(NULL);
			
			DB* dataBase =  &(pDoc->m_dataBase);
			SlistIter<Relation> relIter(*((*dataBase).m_pRelationList));
			Relation* pR;

			int i=0;
			pR = relIter();

			while (i < pView->m_listRecord.GetCount()-1)
			{	
				pR = relIter();
				i++;
			}

			FILE * fp_out;
			CString outPutFileName;
			outPutFileName = OUTPUT_DIR + cs_User + "_output.txt";

			if ((fp_out = fopen(outPutFileName,"wt"))==NULL)
			{
				AfxMessageBox("Error creating file !");
				return;
			}
	

			pDoc->SaveRelationInfo(pR, NULL, fp_out);
			fclose(fp_out);
			strcpy(m_szBuffer,outPutFileName);
			strcat(m_szBuffer,"#");
			//pView->callSelChange();

		}
		else
		{
			//memset(m_szBuffer,0,sizeof(m_szBuffer));
			AfxMessageBox("No Opened Doc !");
		}
	}
//////////////////////////// Close the User/////////////////////
	if (strcmp(LPCSTR(cs_Cmd),"Close")==0)
	{
		int userIndex = getUserIndex(cs_User);
		if (userIndex!=-1)
		{
			CIdbDoc* pDoc;
			CIdbView* pView;
			CMDIChildWnd* pFrame;
	
			for (int j=0; j<MAX_FILE_OPEN; j++)
			{
				if (((CIdbApp*)AfxGetApp())->m_User[userIndex].cs_DocName[j]!="")
				{
//					AfxGetApp()->GetMainWnd()->SendMessage(WM_COMMAND,ID_WINDOW_CLOSEALL);
					pDoc = (CIdbDoc*)((CIdbApp*)AfxGetApp())->m_User[userIndex].p_Doc[j];
					pView = (CIdbView*)((CIdbApp*)AfxGetApp())->m_User[userIndex].p_View[j];
					pFrame = (CMDIChildWnd*)((CIdbApp*)AfxGetApp())->m_User[userIndex].p_Frame[j];
					
					pDoc->DeleteContents();
//					pView->CloseWindow();
						
//					pView->DestroyWindow();

					pFrame->DestroyWindow();
				}
			}
			//Remove temp files
			CString outPutFileName;
			outPutFileName = OUTPUT_DIR + cs_User + "_output.txt";
			remove(outPutFileName);
			outPutFileName = OUTPUT_DIR + cs_User + "_output.jpg";
			remove(outPutFileName);
			

			for (int i=userIndex; i<MAX_USER-1;i++)
			{
				((CIdbApp*)AfxGetApp())->m_User[i].cs_UserName = ((CIdbApp*)AfxGetApp())->m_User[i+1].cs_UserName;
				for (j=0; j<MAX_FILE_OPEN; j++)
				{
					((CIdbApp*)AfxGetApp())->m_User[i].cs_DocName[j] = 
						((CIdbApp*)AfxGetApp())->m_User[i+1].cs_DocName[j];
					((CIdbApp*)AfxGetApp())->m_User[i].p_Doc[j] = 
						((CIdbApp*)AfxGetApp())->m_User[i+1].p_Doc[j];
					((CIdbApp*)AfxGetApp())->m_User[i].p_View[j] = 
						((CIdbApp*)AfxGetApp())->m_User[i+1].p_View[j];
					((CIdbApp*)AfxGetApp())->m_User[i].p_Frame[j] = 
						((CIdbApp*)AfxGetApp())->m_User[i+1].p_Frame[j];
					((CIdbApp*)AfxGetApp())->m_User[i].preSelIndex[j] = 
						((CIdbApp*)AfxGetApp())->m_User[i+1].preSelIndex[j];
				}
			}

			i=MAX_USER-1;
			((CIdbApp*)AfxGetApp())->m_User[i].cs_UserName = "";
			for (j=0; j<MAX_FILE_OPEN; j++)
			{
				((CIdbApp*)AfxGetApp())->m_User[i].cs_DocName[j] = "";
				((CIdbApp*)AfxGetApp())->m_User[i].p_Doc[j] = NULL;
				((CIdbApp*)AfxGetApp())->m_User[i].p_View[j] = NULL;
				((CIdbApp*)AfxGetApp())->m_User[i].p_Frame[j] = NULL;
				((CIdbApp*)AfxGetApp())->m_User[i].preSelIndex[j] = -1;
			}
		}
		strcpy(m_szBuffer,"0#");
	}
//////////////////////////// Datalog ///////////////////////////
	if (strcmp(LPCSTR(cs_Cmd),"Datalog")==0)
	{

		// look for the user
		int userIndex = getUserIndex(cs_User);
		if (userIndex == -1)
			goto next;

		//	look for the document used
		int docIndex = getDocIndex(userIndex,cs_Param1);
		if (docIndex == -1)
			goto next;
		
		CIdbDoc* pDoc = (CIdbDoc*)((CIdbApp*)AfxGetApp())->m_User[userIndex].p_Doc[docIndex];
		CIdbView* pView = (CIdbView*)((CIdbApp*)AfxGetApp())->m_User[userIndex].p_View[docIndex];
		CMDIChildWnd* pFrame = (CMDIChildWnd*)((CIdbApp*)AfxGetApp())->m_User[userIndex].p_Frame[docIndex];

//		pFrame->ActivateFrame(-1);
		//	do calculate
		if (pDoc != NULL)
		{
			FILE * fp;

			if ((fp = fopen(CMD_FILE_NAME,"wt"))==NULL)
			{
				AfxMessageBox("Error creating file !");
				return;
			}

			CString pdlg, prnm;
			int parea = cs_Param2.Find("area<",0);

			if ( parea > 0 ) {
				pdlg = cs_Param2;
				prnm = pdlg.Left(pdlg.Find("(", 0));
				pdlg.Delete(0, pdlg.Find("(", 0));
				pdlg.Delete(pdlg.Find("area<", 0), 5);
				pdlg.Delete(pdlg.Find(">", 0), 1);
				cs_Param2 = "temparea" + pdlg;
			}

			fwrite("begin%Cmd%",strlen("begin%Cmp%"),1,fp);
			fputc(0x0a,fp);
			fwrite(LPCSTR(cs_Param2),strlen(LPCSTR(cs_Param2)),1,fp);
			fputc(0x0a,fp);
			fwrite("end%Cmd%",strlen("end%Cmp%"),1,fp);
			
			fclose(fp);
			bool bCalc = pDoc->DoCalculate(CMD_FILE_NAME);
			pDoc->UpdateAllViews(NULL);

			Relation* pR;
			if ( parea > 0 ) {
				//pDoc->m_dataBase.AreaHandler3(prnm, "temparea", step, MinX, MaxX);
				pDoc->m_dataBase.AreaHandler3(prnm.GetBuffer(), "temparea", 2*dataBase->Mval, -dataBase->Mval, dataBase->Mval);
				pR = (Relation*)pDoc->m_dataBase.RetrieveRelation(prnm.GetBuffer());
				pDoc->RemoveRelation("temparea");
			}
			else {
				DB* dataBase =  &(pDoc->m_dataBase);
				SlistIter<Relation> relIter(*((*dataBase).m_pRelationList));

				int i=0;
				pR = relIter();

				while (i < pView->m_listRecord.GetCount()-1)
				{	
					pR = relIter();
					i++;
				}
			}

			FILE * fp_out;

			CString outPutFileName;
			outPutFileName = OUTPUT_DIR + cs_User + "_output.txt";

			if ((fp_out = fopen(outPutFileName,"wt"))==NULL)
			{
				AfxMessageBox("Error creating file !");
				return;
			}

			pDoc->SaveRelationInfo(pR, NULL, fp_out);
			fclose(fp_out);
			strcpy(m_szBuffer,outPutFileName);
			strcat(m_szBuffer,"#");
			//pView->callSelChange();

		}
		else
		{
			//memset(m_szBuffer,0,sizeof(m_szBuffer));
			AfxMessageBox("No Opened Doc !");
		}
	}

	//=========  Uses  ===== load file 2 =====================================
	if (strcmp(LPCSTR(cs_Cmd),"Uses")==0)
	{

		// look for the user
		int userIndex = getUserIndex(cs_User);
		if (userIndex == -1)
			goto next;

		//	look for the document used
		int docIndex = getDocIndex(userIndex,cs_Param1);
		if (docIndex == -1)
			goto next;
		
		CIdbDoc* pDoc = (CIdbDoc*)((CIdbApp*)AfxGetApp())->m_User[userIndex].p_Doc[docIndex];

		//	do calculate
		if (pDoc != NULL)
		{
			CFile file;
			CFileException fe;
			//AfxMessageBox(SOURCE_DB_DIR + cs_Param2);
			if (!file.Open(SOURCE_DB_DIR + cs_Param2, CFile::modeRead, &fe))
			{
				//strcpy(m_szBuffer,"1");
				file.Close();
			}
			else {
				file.Close();
				bool bCalc = pDoc->DoCalculate(SOURCE_DB_DIR + cs_Param2);
				pDoc->UpdateAllViews(NULL);
				
				if (bCalc)
					strcpy(m_szBuffer,"0#");

			}
			//pView->callSelChange();
		}
		else
		{
			//memset(m_szBuffer,0,sizeof(m_szBuffer));
			AfxMessageBox("No Opened Doc !");
		}
	}
	
	//Clear
	if (cs_Cmd=="Clear")
	{
		// look for the user
		int userIndex = getUserIndex(cs_User);
		if (userIndex == -1)
			goto next;

		//	look for the document used
		int docIndex = getDocIndex(userIndex,cs_Param1);
		if (docIndex == -1)
			goto next;
		
		CIdbDoc* pDoc = (CIdbDoc*)((CIdbApp*)AfxGetApp())->m_User[userIndex].p_Doc[docIndex];
		CIdbView* pView = (CIdbView*)((CIdbApp*)AfxGetApp())->m_User[userIndex].p_View[docIndex];
		//CMDIChildWnd* pFrame = (CMDIChildWnd*)((CIdbApp*)AfxGetApp())->m_User[userIndex].p_Frame[docIndex];

		//	set selection
		if (pDoc != NULL)
		{
			int preSelIndex = getPreSelIndex(cs_User,cs_Param1);
			pView->m_listRecord.SelItemRange(false,0,pView->m_listRecord.GetCount()-1);
			//pDoc->m_bResetDrawObj = TRUE;
			//pDoc->ClearDrawObjList();
			pDoc->saveImageInfo(""); //Clear relation
			//pDoc->UpdateAllViews(NULL);	
			strcpy(m_szBuffer,"0#");
		}
		else
		{
			//memset(m_szBuffer,0,sizeof(m_szBuffer));
			AfxMessageBox("No Opened Doc !");
		}
	}

	//Include Relations
	if (strcmp(LPCSTR(cs_Cmd),"Include")==0)
	{

		// look for the user
		int userIndex = getUserIndex(cs_User);
		if (userIndex == -1)
			goto next;

		//	look for the document used
		int docIndex = getDocIndex(userIndex,cs_Param1);
		if (docIndex == -1)
			goto next;
		
		CIdbDoc* pDoc = (CIdbDoc*)((CIdbApp*)AfxGetApp())->m_User[userIndex].p_Doc[docIndex];
		CIdbView* pView = (CIdbView*)((CIdbApp*)AfxGetApp())->m_User[userIndex].p_View[docIndex];
		//CMDIChildWnd* pFrame = (CMDIChildWnd*)((CIdbApp*)AfxGetApp())->m_User[userIndex].p_Frame[docIndex];

		//	set selection
		if (pDoc != NULL)
		{
			int preSelIndex = getPreSelIndex(cs_User,cs_Param1);

			//AfxMessageBox(cs_Param2);

	
			DB* dataBase = &(pDoc->m_dataBase);
			if (!(*dataBase).numRels) 
				return; 
			else
			{
				int IncludeIdx = 0;
				SlistIter<Relation> relationListIter(*(*dataBase).m_pRelationList);
				//const Relation* p_r1;
				Relation* p_r; 
				while(p_r = (Relation*)relationListIter())
				{
					CString strOut("");
					String strName = p_r->Name();
					strOut = strName.GetText();
					//AfxMessageBox(strOut);
					if (cs_Param2==strOut)
					{
						BOOL flag = true;
						//unsigned long 
						COLORREF color_set = atol(cs_Param3);
						switch (color_set)
						{
						case 1: p_r->m_colorStart=RGB(255,0,0); break;
						case 2: p_r->m_colorStart=RGB(0,255,0); break;
						case 3: p_r->m_colorStart=RGB(0,0,255); break;
						default : p_r->m_colorStart = color_set;
						}	
						p_r->m_colorEnd = p_r->m_colorStart;
						p_r->m_color = p_r->m_colorStart;

						pView->m_listRecord.SetSel(IncludeIdx,flag);
						//pView->callSelChange();
						((CIdbApp*)AfxGetApp())->m_User[userIndex].preSelIndex[docIndex] = IncludeIdx; //pView->m_listRecord.GetCount()-1;
						break;
					}
					IncludeIdx++;
				}
			}
			strcpy(m_szBuffer,"0#");
		}
		else
		{
			//memset(m_szBuffer,0,sizeof(m_szBuffer));
			AfxMessageBox("No Opened Doc !");
		}
	}

	//Remove Relations
	if (strcmp(LPCSTR(cs_Cmd),"Remove")==0)
	{
		// look for the user
		int userIndex = getUserIndex(cs_User);
		if (userIndex == -1)
			goto next;

		//	look for the document used
		int docIndex = getDocIndex(userIndex,cs_Param1);
		if (docIndex == -1)
			goto next;
		
		CIdbDoc* pDoc = (CIdbDoc*)((CIdbApp*)AfxGetApp())->m_User[userIndex].p_Doc[docIndex];

		if (pDoc != NULL)
		{
			pDoc->RemoveRelation(cs_Param2);
			strcpy(m_szBuffer,"0#");
		}
		else
		{
			//memset(m_szBuffer,0,sizeof(m_szBuffer));
			AfxMessageBox("No Opened Doc !");
		}
	}
	//Calculate Area
	if (strcmp(LPCSTR(cs_Cmd),"Area")==0)
	{
		// look for the user
		int userIndex = getUserIndex(cs_User);
		if (userIndex == -1)
			goto next;

		//	look for the document used
		int docIndex = getDocIndex(userIndex,cs_Param1);
		if (docIndex == -1)
			goto next;
		
		CIdbDoc* pDoc = (CIdbDoc*)((CIdbApp*)AfxGetApp())->m_User[userIndex].p_Doc[docIndex];

		if (pDoc != NULL)
		{
			//pDoc->m_dataBase.AreaHandler3(out_rel, in_rel, step, MinX, MaxX);
			String outname, inname;
			outname= cs_Param3;
			inname = cs_Param2;
			float step = atof(cs_Param4);
			float MinX = atof(cs_Param5);
			float MaxX = atof(cs_Param6);

			pDoc->m_dataBase.AreaHandler3(outname, inname, step, MinX, MaxX);
			Relation* pR = (Relation*)pDoc->m_dataBase.RetrieveRelation(outname);

			FILE * fp_out;
			CString outPutFileName;
			outPutFileName = OUTPUT_DIR + cs_User + "_output.txt";

			if ((fp_out = fopen(outPutFileName,"wt"))==NULL)
			{
				AfxMessageBox("Error creating file !");
				return;
			}
			pDoc->SaveRelationInfo(pR, NULL, fp_out);
			fclose(fp_out);
			strcpy(m_szBuffer,outPutFileName);
			strcat(m_szBuffer,"#");
		}
		else
		{
			//memset(m_szBuffer,0,sizeof(m_szBuffer));
			AfxMessageBox("No Opened Doc !");
		}
	}


	//Do ColorRelation
	if (strcmp(LPCSTR(cs_Cmd),"ColorRelation")==0)
	{

		// look for the user
		int userIndex = getUserIndex(cs_User);
		if (userIndex == -1)
			goto next;

		//	look for the document used
		int docIndex = getDocIndex(userIndex,cs_Param1);
		if (docIndex == -1)
			goto next;
		
		CIdbDoc* pDoc = (CIdbDoc*)((CIdbApp*)AfxGetApp())->m_User[userIndex].p_Doc[docIndex];
		CIdbView* pView = (CIdbView*)((CIdbApp*)AfxGetApp())->m_User[userIndex].p_View[docIndex];
		//CMDIChildWnd* pFrame = (CMDIChildWnd*)((CIdbApp*)AfxGetApp())->m_User[userIndex].p_Frame[docIndex];

		//	set selection
		if (pDoc != NULL)
		{

			int preSelIndex = getPreSelIndex(cs_User,cs_Param1);

			//AfxMessageBox(cs_Param2);
	
			DB* dataBase = &(pDoc->m_dataBase);
			if (!(*dataBase).numRels) 
				return; 
			else
			{
				int IncludeIdx = 0;
				SlistIter<Relation> relationListIter(*(*dataBase).m_pRelationList);
				//const Relation* p_r1;
				Relation* p_r; 
				while(p_r = (Relation*)relationListIter())
				{
					CString strOut("");
					String strName = p_r->Name();
					strOut = strName.GetText();
					//AfxMessageBox(strOut);
					if (cs_Param2==strOut)
					{
						pView->m_listRecord.SetSel(IncludeIdx,true);
						pView->callSelChange();
						//((CIdbApp*)AfxGetApp())->m_User[userIndex].preSelIndex[docIndex] = IncludeIdx; //pView->m_listRecord.GetCount()-1;
						break;
					}
					IncludeIdx++;
				}
			}

			pView->callColorRelation();

			cs_Param2 = "Color_" + cs_Param2;
			int IncludeIdx = 0;
			SlistIter<Relation> relationListIter(*(*dataBase).m_pRelationList);
			//const Relation* p_r1;
			Relation* p_r; 
			while(p_r = (Relation*)relationListIter())
			{
				CString strOut("");
				String strName = p_r->Name();
				strOut = strName.GetText();
				if (cs_Param2==strOut)
				{
					pView->m_listRecord.SetSel(IncludeIdx,true);
					pView->callSelChange();
					//((CIdbApp*)AfxGetApp())->m_User[userIndex].preSelIndex[docIndex] = IncludeIdx; //pView->m_listRecord.GetCount()-1;
					break;
				}
				IncludeIdx++;
			}

			strcpy(m_szBuffer,"0#");
		}
		else
		{
			//memset(m_szBuffer,0,sizeof(m_szBuffer));
			AfxMessageBox("No Opened Doc !");
		}
	}

	if (strcmp(LPCSTR(cs_Cmd),"Zoom")==0)
	{

		// look for the user
		int userIndex = getUserIndex(cs_User);
		if (userIndex == -1)
			goto next;

		//	look for the document used
		int docIndex = getDocIndex(userIndex,cs_Param1);
		if (docIndex == -1)
			goto next;
		
		CIdbDoc* pDoc = (CIdbDoc*)((CIdbApp*)AfxGetApp())->m_User[userIndex].p_Doc[docIndex];

		if (pDoc != NULL)
		{

			POSITION pos = pDoc->GetFirstViewPosition();
			while (pos != NULL)
			{
				CView* pV = pDoc->GetNextView(pos);
				if (pV != NULL  &&  pV->IsKindOf(RUNTIME_CLASS(CGraphView)))
				{
					int x = atoi(cs_Param2);
					int y = atoi(cs_Param3);
					int w = atoi(cs_Param4);
					int h = atoi(cs_Param5);
					((CGraphView*)pV)->ZoomRectZoom(CRect(x-w/2, y-h/2, x+w/2, y+h/2));
					pDoc->UpdateAllViews(NULL);
					break;
				}
			}

			strcpy(m_szBuffer,"0#");
		}
		else
		{
			//memset(m_szBuffer,0,sizeof(m_szBuffer));
			AfxMessageBox("No Opened Doc !");
		}
	}

	//Get animation images
	if (strcmp(LPCSTR(cs_Cmd),"GetAnimation")==0)
	{

		// look for the user
		int userIndex = getUserIndex(cs_User);
		if (userIndex == -1)
			goto next;

		//	look for the document used
		int docIndex = getDocIndex(userIndex,cs_Param1);
		if (docIndex == -1)
			goto next;
		
		CIdbDoc* pDoc = (CIdbDoc*)((CIdbApp*)AfxGetApp())->m_User[userIndex].p_Doc[docIndex];
		CIdbView* pView = (CIdbView*)((CIdbApp*)AfxGetApp())->m_User[userIndex].p_View[docIndex];
		CMDIChildWnd* pFrame = (CMDIChildWnd*)((CIdbApp*)AfxGetApp())->m_User[userIndex].p_Frame[docIndex];

		if (pDoc != NULL)
		{

			CString outPutFileName;
			char buffer[10];
			//(int)((CIdbApp*)AfxGetApp())->m_animationOUT = 1;

			int start_T = atoi(cs_Param2);
			int end_T = atoi(cs_Param3);
			int step = atoi(cs_Param4);
			if (start_T==-1)
				start_T = pDoc->m_nDBTimeS;
			if (end_T==-1)
				end_T = pDoc->m_nDBTimeE;

			if (step==0)
				return;

			int filect = 0;
			for (int i=start_T; i <= end_T; i+=step)
			{
				_itoa( filect, buffer, 10 );
				filect++;
				outPutFileName = OUTPUT_DIR + cs_User + "_aniout" + buffer + ".jpg";
				strcpy((char*)(((CIdbApp*)AfxGetApp())->m_graphFileName),LPCSTR(outPutFileName));

				pDoc->DoShowAnimation(i);
				((CMainFrame*)(AfxGetApp()->GetMainWnd()))->ShowAnimation(i, pDoc->m_nDBTimeE);

			}
			//(int)((CIdbApp*)AfxGetApp())->m_animationOUT = 0;
			//pView->callSelChange();
			//pDoc->saveImageInfo((char*)(outPutFileName));

			//((CIdbApp*)AfxGetApp())->m_User[userIndex].preSelIndex[docIndex] = pView->m_listRecord.GetCount()-1;
			strcpy(m_szBuffer,outPutFileName);
			strcat(m_szBuffer,"#");

			strcpy(m_szBuffer,"0#");
		}
		else
		{
			//memset(m_szBuffer,0,sizeof(m_szBuffer));
			AfxMessageBox("No Opened Doc !");
		}
	}

	//Generate image
	if (strcmp(LPCSTR(cs_Cmd),"GetImage")==0)
	{

		// look for the user
		int userIndex = getUserIndex(cs_User);
		if (userIndex == -1)
			goto next;

		//	look for the document used
		int docIndex = getDocIndex(userIndex,cs_Param1);
		if (docIndex == -1)
			goto next;
		
		CIdbDoc* pDoc = (CIdbDoc*)((CIdbApp*)AfxGetApp())->m_User[userIndex].p_Doc[docIndex];
		CIdbView* pView = (CIdbView*)((CIdbApp*)AfxGetApp())->m_User[userIndex].p_View[docIndex];
		CMDIChildWnd* pFrame = (CMDIChildWnd*)((CIdbApp*)AfxGetApp())->m_User[userIndex].p_Frame[docIndex];

		if (pDoc != NULL)
		{

			//char outPutFileName[256];
			//strcpy(outPutFileName,SOURCE_DB_DIR);
			//strcat(outPutFileName,LPCSTR(cs_User));
			//strcat(outPutFileName,"_output.bmp");
			CString outPutFileName;
			outPutFileName = OUTPUT_DIR + cs_User + "_output.jpg";

			strcpy((char*)(((CIdbApp*)AfxGetApp())->m_graphFileName),OUTPUT_DIR);
			strcat((char*)(((CIdbApp*)AfxGetApp())->m_graphFileName),LPCSTR(cs_User));
			strcat((char*)(((CIdbApp*)AfxGetApp())->m_graphFileName),"_output.jpg");

			//(int)(((CIdbApp*)AfxGetApp())->m_animationOUT)=0;
			pView->callSelChange();

			//pDoc->saveImageInfo((char*)(outPutFileName));

			//((CIdbApp*)AfxGetApp())->m_User[userIndex].preSelIndex[docIndex] = pView->m_listRecord.GetCount()-1;
			strcpy(m_szBuffer,outPutFileName);
			strcat(m_szBuffer,"#");

		}
		else
		{
			//memset(m_szBuffer,0,sizeof(m_szBuffer));
			AfxMessageBox("No Opened Doc !");
		}
	}

next:	// continue	

//	memset(m_szBuffer,0,sizeof(m_szBuffer));
	
	AsyncSelect(FD_WRITE);
	
	CAsyncSocket::OnReceive(nErrorCode);
}

void CNewSocket::OnSend(int nErrorCode) 
{
	// TODO: Add your specialized code here and/or call the base class
	m_nLength = 256;
	Send(m_szBuffer,m_nLength,0);

	memset(m_szBuffer,0,sizeof(m_szBuffer));

	AsyncSelect(FD_READ);

	CAsyncSocket::OnSend(nErrorCode);
}

int CNewSocket::getUserIndex(CString cs_User)
{
	bool findUser=false;

	for (int j=0; j<MAX_USER; j++)
	{
		if (((CIdbApp*)AfxGetApp())->m_User[j].cs_UserName == cs_User)
		{
			findUser = true;
			break;
		}
		if (((CIdbApp*)AfxGetApp())->m_User[j].cs_UserName == "")
			break;
	}

	if (findUser)
		return j;
	else
		return -1;
}

int CNewSocket::getDocIndex(int userIndex, CString cs_Doc)
{
	bool findDocument=false;

	for (int k=0; k<MAX_FILE_OPEN; k++)
	{
		if (((CIdbApp*)AfxGetApp())->m_User[userIndex].cs_DocName[k] == cs_Doc)
		{
			findDocument = true;
			break;
		}
		if (((CIdbApp*)AfxGetApp())->m_User[userIndex].cs_DocName[k] == "")
			break;
	}

	if (findDocument)
		return k;
	else
		return -1;
}

//DEL void CNewSocket::getCommand(CString & cs_Input, CString &cs_Cmd)
//DEL {
//DEL 	cs_Input.TrimLeft();
//DEL 	cs_Input.TrimRight();
//DEL 
//DEL 	cs_Cmd="";
//DEL 	
//DEL 	int i = 0;
//DEL 	
//DEL 	while(cs_Input.GetAt(i)!=' ' && i< cs_Input.GetLength())
//DEL 	{
//DEL 		cs_Cmd += cs_Input.GetAt(i);
//DEL 		i++;
//DEL 	}
//DEL 
//DEL 	cs_Input = cs_Input.Right(cs_Input.GetLength()-i);
//DEL }

//DEL void CNewSocket::getUser(CString & cs_Input, CString &cs_User)
//DEL {
//DEL 	cs_Input.TrimLeft();
//DEL 	cs_Input.TrimRight();
//DEL 
//DEL 	cs_User="";
//DEL 	
//DEL 	int i = 0;
//DEL 	
//DEL 	while(cs_Input.GetAt(i)!=' ' && i< cs_Input.GetLength())
//DEL 	{
//DEL 		cs_Cmd += cs_Input.GetAt(i);
//DEL 		i++;
//DEL 	}
//DEL 
//DEL }

void CNewSocket::getParameters(char *str_Input, CString &cs_Cmd, CString &cs_User, CString &cs_Param1, CString &cs_Param2, CString &cs_Param3, CString &cs_Param4, CString &cs_Param5, CString &cs_Param6, CString &cs_Param7, CString &cs_Param8, CString &cs_Param9)
{
	CString cs_Input = str_Input;
	cs_Input.TrimLeft();
	cs_Input.TrimRight();

	int index = cs_Input.Find('$');
	cs_Input = cs_Input.Left(index);

	if (cs_Input.GetAt(cs_Input.GetLength()-1)==0x0a || cs_Input.GetAt(cs_Input.GetLength()-1)==0x0d)
		cs_Input = cs_Input.Left(cs_Input.GetLength()-1);

	cs_Input.TrimRight();

	cs_Cmd="";
	cs_User="";
	cs_Param1="";
	cs_Param2="";
	cs_Param3="";
	cs_Param4="";
	cs_Param5="";
	cs_Param6="";
	cs_Param7="";
	cs_Param8="";
	cs_Param9="";


	int i = 0;
	
	while(cs_Input.GetAt(i)!=' ' && i< cs_Input.GetLength())
	{
		cs_Cmd += cs_Input.GetAt(i);
		i++;
	}

	// skip the space
	while(cs_Input.GetAt(i)==' ' && i< cs_Input.GetLength())
		i++;

	// get the user name
	while(cs_Input.GetAt(i)!=' ' && i< cs_Input.GetLength())
	{
		cs_User += cs_Input.GetAt(i);
		i++;
	}
	// skip the space
	while(cs_Input.GetAt(i)==' ' && i< cs_Input.GetLength())
		i++;

	// get parameters
	if (strcmp(LPCSTR(cs_Cmd),"Open")==0)
	{
		// get the param1 - document name
		while(cs_Input.GetAt(i)!=' ' && i< cs_Input.GetLength())
		{
			cs_Param1 += cs_Input.GetAt(i);
			i++;
		}
	}

	if (strcmp(LPCSTR(cs_Cmd),"Datalog")==0)
	{
		// get the param1 - document name
		while(cs_Input.GetAt(i)!=' ' && i< cs_Input.GetLength())
		{
			cs_Param1 += cs_Input.GetAt(i);
			i++;
		}
		// skip the space
		while(cs_Input.GetAt(i)==' ' && i< cs_Input.GetLength())
			i++;
		// get the param2 - datalog expression
		while(i< cs_Input.GetLength())
		{
			cs_Param2 += cs_Input.GetAt(i);
			i++;
		}
	}

//wss
	if ((strcmp(LPCSTR(cs_Cmd),"GetImage")==0) || 
		(strcmp(LPCSTR(cs_Cmd),"Clear")==0)) 
	{
		// get the param1 - document name
		while(cs_Input.GetAt(i)!=' ' && i< cs_Input.GetLength())
		{
			cs_Param1 += cs_Input.GetAt(i);
			i++;
		}
	}

	if (strcmp(LPCSTR(cs_Cmd),"Include")==0)
	{
		// get the param1 - document name
		while(cs_Input.GetAt(i)!=' ' && i< cs_Input.GetLength())
		{
			cs_Param1 += cs_Input.GetAt(i);
			i++;
		}
		// skip the space
		while(cs_Input.GetAt(i)==' ' && i< cs_Input.GetLength())
			i++;
		// get the param2 - relation name
		while(cs_Input.GetAt(i)!=' ' && i< cs_Input.GetLength())
		{
			cs_Param2 += cs_Input.GetAt(i);
			i++;
		}
		while(cs_Input.GetAt(i)==' ' && i< cs_Input.GetLength())
			i++;
		// get the param3 - 0-unsel; 1-sel
		while(i< cs_Input.GetLength())
		{
			cs_Param3 += cs_Input.GetAt(i);
			i++;
		}
	}

	if (strcmp(LPCSTR(cs_Cmd),"ColorRelation")==0 || 
		strcmp(LPCSTR(cs_Cmd),"Remove")==0 ||
		strcmp(LPCSTR(cs_Cmd),"Uses")==0 )
	{
		// get the param1 - document name
		while(cs_Input.GetAt(i)!=' ' && i< cs_Input.GetLength())
		{
			cs_Param1 += cs_Input.GetAt(i);
			i++;
		}
		// skip the space
		while(cs_Input.GetAt(i)==' ' && i< cs_Input.GetLength())
			i++;

		// get the param2 - relation name / file2 name
		while(i< cs_Input.GetLength())
		{
			cs_Param2 += cs_Input.GetAt(i);
			i++;
		}
	}

	if (strcmp(LPCSTR(cs_Cmd),"Zoom")==0)
	{
		// get the param1 - document name
		while(cs_Input.GetAt(i)!=' ' && i< cs_Input.GetLength())
		{
			cs_Param1 += cs_Input.GetAt(i);
			i++;
		}
		// skip the space
		while(cs_Input.GetAt(i)==' ' && i< cs_Input.GetLength())
			i++;
		// get the param2 - x
		while(cs_Input.GetAt(i)!=' ' && i< cs_Input.GetLength())
		{
			cs_Param2 += cs_Input.GetAt(i);
			i++;
		}
		while(cs_Input.GetAt(i)==' ' && i< cs_Input.GetLength())
			i++;
		// get the param3 - y
		while(cs_Input.GetAt(i)!=' ' && i< cs_Input.GetLength())
		{
			cs_Param3 += cs_Input.GetAt(i);
			i++;
		}
		while(cs_Input.GetAt(i)==' ' && i< cs_Input.GetLength())
			i++;
		// get the param4 - w
		while(cs_Input.GetAt(i)!=' ' && i< cs_Input.GetLength())
		{
			cs_Param4 += cs_Input.GetAt(i);
			i++;
		}
		while(cs_Input.GetAt(i)==' ' && i< cs_Input.GetLength())
			i++;
		// get the param5 - h
		while(i< cs_Input.GetLength())
		{
			cs_Param5 += cs_Input.GetAt(i);
			i++;
		}
	}
	if (strcmp(LPCSTR(cs_Cmd),"GetAnimation")==0)
	{
		// get the param1 - document name
		while(cs_Input.GetAt(i)!=' ' && i< cs_Input.GetLength())
		{
			cs_Param1 += cs_Input.GetAt(i);
			i++;
		}
		// skip the space
		while(cs_Input.GetAt(i)==' ' && i< cs_Input.GetLength())
			i++;
		// get the param2 - Start_T
		while(cs_Input.GetAt(i)!=' ' && i< cs_Input.GetLength())
		{
			cs_Param2 += cs_Input.GetAt(i);
			i++;
		}
		while(cs_Input.GetAt(i)==' ' && i< cs_Input.GetLength())
			i++;
		// get the param3 - End_T
		while(cs_Input.GetAt(i)!=' ' && i< cs_Input.GetLength())
		{
			cs_Param3 += cs_Input.GetAt(i);
			i++;
		}
		while(cs_Input.GetAt(i)==' ' && i< cs_Input.GetLength())
			i++;
		// get the param4 - step
		while(i< cs_Input.GetLength())
		{
			cs_Param4 += cs_Input.GetAt(i);
			i++;
		}
	}
	if (strcmp(LPCSTR(cs_Cmd),"Area")==0)
	{
		// get the param1 - document name
		while(cs_Input.GetAt(i)!=' ' && i< cs_Input.GetLength())
		{
			cs_Param1 += cs_Input.GetAt(i);
			i++;
		}
		// skip the space
		while(cs_Input.GetAt(i)==' ' && i< cs_Input.GetLength())
			i++;
		// get the input relation
		while(cs_Input.GetAt(i)!=' ' && i< cs_Input.GetLength())
		{
			cs_Param2 += cs_Input.GetAt(i);
			i++;
		}
		while(cs_Input.GetAt(i)==' ' && i< cs_Input.GetLength())
			i++;
		// get the output relation
		while(cs_Input.GetAt(i)!=' ' && i< cs_Input.GetLength())
		{
			cs_Param3 += cs_Input.GetAt(i);
			i++;
		}
		while(cs_Input.GetAt(i)==' ' && i< cs_Input.GetLength())
			i++;
		// get the param4 - Step
		while(cs_Input.GetAt(i)!=' ' && i< cs_Input.GetLength())
		{
			cs_Param4 += cs_Input.GetAt(i);
			i++;
		}
		while(cs_Input.GetAt(i)==' ' && i< cs_Input.GetLength())
			i++;
		// get the param5 - MinX
		while(cs_Input.GetAt(i)!=' ' && i< cs_Input.GetLength())
		{
			cs_Param5 += cs_Input.GetAt(i);
			i++;
		}
		while(cs_Input.GetAt(i)==' ' && i< cs_Input.GetLength())
			i++;
		// get the param6 - MaxX
		while(i< cs_Input.GetLength())
		{
			cs_Param6 += cs_Input.GetAt(i);
			i++;
		}
	}
//wss

	if (cs_Cmd.GetAt(0)=='S' && cs_Cmd.GetAt(1)=='Q' && cs_Cmd.GetAt(2)=='L')
	{
		// get the param1 - document name
		while(cs_Input.GetAt(i)!=' ' && i< cs_Input.GetLength())
		{
			cs_Param1 += cs_Input.GetAt(i);
			i++;
		}
		// skip the space
		while(cs_Input.GetAt(i)==' ' && i< cs_Input.GetLength())
			i++;
		// get the other parameters
		while(i< cs_Input.GetLength() && cs_Input.GetAt(i)!='#')
		{
			cs_Param2 += cs_Input.GetAt(i);
			i++;
		}

		i++;
		if (i>=cs_Input.GetLength())
			return;

		while(i< cs_Input.GetLength() && cs_Input.GetAt(i)!='#')
		{
			cs_Param3 += cs_Input.GetAt(i);
			i++;
		}

		i++;
		if (i>=cs_Input.GetLength())
			return;

		while(i< cs_Input.GetLength() && cs_Input.GetAt(i)!='#')
		{
			cs_Param4 += cs_Input.GetAt(i);
			i++;
		}

		i++;
		if (i>=cs_Input.GetLength())
			return;

		while(i< cs_Input.GetLength() && cs_Input.GetAt(i)!='#')
		{
			cs_Param5 += cs_Input.GetAt(i);
			i++;
		}

		i++;
		if (i>=cs_Input.GetLength())
			return;

		while(i< cs_Input.GetLength() && cs_Input.GetAt(i)!='#')
		{
			cs_Param6 += cs_Input.GetAt(i);
			i++;
		}

		i++;
		if (i>=cs_Input.GetLength())
			return;

		while(i< cs_Input.GetLength() && cs_Input.GetAt(i)!='#')
		{
			cs_Param7 += cs_Input.GetAt(i);
			i++;
		}

		i++;
		if (i>=cs_Input.GetLength())
			return;

		while(i< cs_Input.GetLength() && cs_Input.GetAt(i)!='#')
		{
			cs_Param8 += cs_Input.GetAt(i);
			i++;
		}

		i++;
		if (i>=cs_Input.GetLength())
			return;

		while(i< cs_Input.GetLength() && cs_Input.GetAt(i)!='#')
		{
			cs_Param9 += cs_Input.GetAt(i);
			i++;
		}

	}
}

int CNewSocket::getPreSelIndex(CString cs_User, CString cs_Doc)
{
	int userIndex = getUserIndex(cs_User);
	if (userIndex == -1)
		return -1;
	int docIndex = getDocIndex(userIndex,cs_Doc);
	if (docIndex == -1)
		return -1;

	return 	((CIdbApp*)AfxGetApp())->m_User[userIndex].preSelIndex[docIndex];
}

