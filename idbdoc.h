// idbDoc.h : interface of the CIdbDoc class
//
/////////////////////////////////////////////////////////////////////////////
#include "afxtempl.h"

#if !defined(AFX_IDBDOC_H__2BC8E99C_3B7D_11D1_BDA8_00A0C96C8797__INCLUDED_)
#define AFX_IDBDOC_H__2BC8E99C_3B7D_11D1_BDA8_00A0C96C8797__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

//#include "db.h"

class CSCDrawObj;
class DB;
class CIdbDoc : public CDocument
{
protected: // create from serialization only
	CIdbDoc();
	DECLARE_DYNCREATE(CIdbDoc)

// Attributes
public:
	DB			m_dataBase; 
	CPtrList	m_listRelation;		// list of relations for draw queue
	CPtrList	m_objects;		// DrawObj list
	BOOL		m_bResetDrawObj;	// When selected relations list changed, set TRUE

	CPtrList    m_ranges;            //RUICHEN different ranges displayed by different colors 

	int	m_nDBTimeS;		// start time of the database
	int	m_nDBTimeE;		// end time of the database
	int	m_nDBCurrent;	// current time of the database
	bool m_bSameRelationColor; //  Same relation display with same color or not?
	int m_legendS;
	int m_legendE;
	int m_legend;
	
	CString		m_strColorFileName;
	BOOL		m_bColorRead;

	CString     m_strRangeFileName;  //RUICHEN

// for DAO
	CDaoRecordset* m_pRecordset;
	CDaoDatabase m_daoDB;
	CStringArray m_arrayFieldName;
	CWordArray m_arrayFieldSize;
	int m_nFields;
 	int m_nRowCount;
 	CString m_strDatabase;
	CString m_strConnect;
	CString m_strQuery;
	BOOL m_bConnected;
	enum {UNK, MDB, ISAM, ODBC} m_nDatabaseType;

	clock_t m_wrap_time;
	clock_t m_query_time;

	BOOL m_bAddRelation;	// after file import (add new relation), 
							// set to TRUE to update relationListView
//    int m_CurRelation; 
// Operations
public:
		CIdbDoc(int i);
	BOOL DoCalculate(LPCTSTR lpszPathName);
	BOOL DoCalculateGroup(LPCTSTR lpszPathName);
	void OnShapeAnimation(int StartTime, int EndTime, int nStep);
	void OnViewShapePlay(int StartTime, int EndTime);
	void OnRegCalT(CString ChangeRel,int startTime, int endTime);
	void SetMatrixTime(DB* pDB);			
	void ShowRelationInfo(Relation* pR, Matrix<float>* p_matrix);
	CString ShowRelation(Relation* pR, Matrix<float>* p_matrix);
	CString ShowEquationInfo(Relation* pR, Matrix<float>* p_matrix);
	void GetMatrixInfo(Relation* pR, Matrix<float>* p_matrix, CString& strOut, BOOL bSave=false);  //RUICHEN modify
	void GetEquationInfo(Relation* pR, Matrix<float>* p_matrix, CString& strOut, BOOL bSave=false);  //syed modify
	void ChangeEquationInfo(Relation* pR, Matrix<float>* p_matrix, CString& strOut , CString& tempstrOut , BOOL bSave=false);  //Syed modify
	void GetAttryInfo(Relation* pR, Matrix<float>* p_matrix, CString& strOut, BOOL bSave=false);  //Syed modify
	Matrix<float>* GetMatrixFromIDPoints(float id, Point p0, Point p1, Point p2);

// Recalc time
	void DoReCalculate(int nTime);
	void DoShowAnimation(int nTime);
	void DoShowShapeAnimation(int nTime);
	void DoReCalculateShape(int nTime);

// draw obj
	void ClearDrawObjList();
	void AddDrawObj(CSCDrawObj* pObj);

// DAO operation
public:
	void SaveRelationInfo(Relation* pR, Matrix<float>* p_matrix, FILE * fp);
	void GetQuery();
	void PutQuery();
	void GetFieldSpecs();
	bool OpenRecordset(CString fileName);
	void OpenRecordset();
	void OnRequery();
	void OnSql();
	void OnSqlAggregation();
	void OnSqlsets();
	void NestedSql();
	void OnBnSqlRecursion();


private:
	void SetWrapTime();
	bool DaoOpenMdb();
	void DaoOpenOdbc();
	void DaoOpenIsam();
	void CreateRelation(ifstream& iStream, CString& fileName);
	void CreateRelationFromAccessTable(CString& fileName);
	void CreatePointRelation(ifstream& iStream, CString& fileName);	
	void CreateLineRelations(ifstream& iStream, CString& fileName);	
	//added by DRK for the Import Line
	Relation* GetOtherColumns(Relation* pR);
	Relation* PointsAddToRelation(Relation*   p_r, 
								Slist<Point>* pPList, float& id);
	Relation* ImportAccessTable(Relation* pR);
	void CreateElevationRelation(ifstream& iStream, CString& fileName);   //LEIZHANG

	BOOL SaveIDBFile(CFile& file);
	BOOL ReadWriteColorFile(int mode, LPCTSTR lpszPathName);	// 1: read, 2: write
	BOOL DoReadWriteColorFile(int mode, CFile& file);	// 1: read, 2: write
	BOOL bHasFromToAttribute();

	BOOL ReadWriteRangeFile(int mode, LPCTSTR lpszPathName);   //RUICHEN // 1: read; 2: write
	BOOL DoReadWriteRangeFile(int mode, CFile& file);   //RUICHEN // 1: read, 2: write

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CIdbDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void OnCloseDocument();
	virtual void Serialize(CArchive& ar);
	virtual BOOL OnOpenDocument(LPCTSTR lpszPathName);
	virtual BOOL OnSaveDocument(LPCTSTR lpszPathName);
//		afx_msg void OnSql();
//	afx_msg void OnSqlAggregation();
//	afx_msg void OnSqlsets();
//	afx_msg void NestedSql();
	//}}AFX_VIRTUAL

// Implementation
public:
	void saveImageInfo(CString fileName);
	void RemoveRelation(CString RelationName);
	BOOL str2ansi(CString *input);
	void DoNestedSql(CString cs_Create,CString cs_Select1,CString cs_From1,CString cs_Where1, CString cs_Operator, CString cs_Select2, CString cs_From2, CString cs_Where2);
	void DoSqlAggregation(CString cs_Create,CString cs_Select, CString cs_From, CString cs_Where, CString cs_Group, CString cs_Having);
	void DoSqlsets(CString cs_View, CString cs_Select1, CString cs_From1, CString cs_Where1, CString cs_Operation, CString cs_Select2, CString cs_From2, CString cs_Where2);
	void DoSql(CString cs_Create, CString cs_Select, CString  cs_From, CString cs_Where);
	void DoSqlRecur(CArray<CString>* ViewName, CArray<CString>* Select1, CArray<CString>* From1, CArray<CString>* Where1, CArray<CString>* Select2, CArray<CString>* From2, CArray<CString>* Where2);
	CString SQL2Datalog(CString ViewName, CString select, CString from, CString where);
	Relation* FindRelation(CString RelName);
	void SetQueryTime();
	virtual ~CIdbDoc();
	CString FormatMatrix(Relation* pR, Matrix<float>* p_matrix);
	CString tabledisplay(CString m_strOut);
	void ShowResult(CString RelationName);
	CString FormalizeCS(CString constraint);
	CString FormalizeTuple(CString tuple);
	BOOL MaxMinOnStr(Relation* pR, int AggFldPos);
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:

	//{{AFX_MSG(CIdbDoc)
	afx_msg void OnEditInsrelation();
	afx_msg void OnViewTime();
	afx_msg void OnViewGoend();
	afx_msg void OnViewGohead();
	afx_msg void OnViewNextstep();
	afx_msg void OnViewPlay();
	afx_msg void OnViewPlayback();
	afx_msg void OnViewPriorstep();
	afx_msg void OnViewExecutiontime();
	afx_msg void OnViewSamerelationcolor();
	afx_msg void OnUpdateViewSamerelationcolor(CCmdUI* pCmdUI);
	afx_msg void OnUpdateViewTime(CCmdUI* pCmdUI);
	afx_msg void OnUpdateViewPriorstep(CCmdUI* pCmdUI);
	afx_msg void OnUpdateViewGoend(CCmdUI* pCmdUI);
	afx_msg void OnUpdateViewGohead(CCmdUI* pCmdUI);
	afx_msg void OnUpdateViewNextstep(CCmdUI* pCmdUI);
	afx_msg void OnUpdateViewPlay(CCmdUI* pCmdUI);
	afx_msg void OnUpdateViewPlayback(CCmdUI* pCmdUI);
	afx_msg void OnButtonMin();
	afx_msg void OnButtonMax();
	afx_msg void OnViewIgnore();
	afx_msg void OnUpdateViewIgnore(CCmdUI* pCmdUI);
	afx_msg void OnFileImport();
	afx_msg void OnImportMdb();
	afx_msg void OnFileImportfilePoint();
	afx_msg void OnFileExport();
	afx_msg void OnButtonSimQuery();
	afx_msg void OnImportLine();
	afx_msg void OnFileImportfileElevation();
	afx_msg void OnUpdateButtonMax(CCmdUI* pCmdUI);
	afx_msg void OnUpdateButtonMin(CCmdUI* pCmdUI);
	afx_msg void OnAggresql();
	afx_msg void OnSqlDialogBox();
	afx_msg void OnShapeAnim();
	afx_msg void OnViewShapeNext();
	afx_msg void OnViewShapeprior();
	afx_msg void OnViewShapegohead();
	afx_msg void OnViewShapegoend();
	afx_msg void OnViewPlayshapeback();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CDlgTime dialog

class CDlgTime : public CDialog
{
// Construction
public:
	CDlgTime(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgTime)
	enum { IDD = IDD_DLG_TIME };
	CString	m_strTimeRange;
	int		m_nNoOfStep;
	int		m_nSpeed;
	int		m_nTimeStart;
	int		m_nStep;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgTime)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgTime)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_IDBDOC_H__2BC8E99C_3B7D_11D1_BDA8_00A0C96C8797__INCLUDED_)

