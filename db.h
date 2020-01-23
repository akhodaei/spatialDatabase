/***************************************************
 * Name:     db.h
 * Author:   Yonghui Wang
 * Time:     April 6, 1997
 * Descript: define of class DB
 *
 ***************************************************/
#ifndef DB_H
#define DB_H

#include "slist.h"
#include "arg.h"
#include "matrix.h"
#include "vector.h"
#include "relation.h"
#include "string.h"
#include "lpkit.h"
//#include "lp_solve.h"
#include <time.h>
#include "hulstruct.h"


typedef struct s_t
{
	String *opnd1;
	String *opnd2;
	String *result;
	String *optr;
	struct s_t *next;
	Slist<Arg> *arg_list;	//for the renaming operation
	String *p_list;			//for the projection operation
	Matrix<float>* s_matrix;	//for the selection operation
} evalnList;

class  DB{

public:
	int BuffHandler(String strSRelName, String strDRelName, float d);
 
DB() {
      numRels = 0 ;	
      m_pVecLine = new Vector<float>;  
      m_pArgVector=new Vector<String>;  
      m_pMatrix  = new Matrix<float> ; 
      m_pRelationList= new Slist<Relation> ;  
      m_pRelNameVec = new Vector<String>;
      m_pEqualMatrix= new Matrix<int>; 
      m_pAggMatrix= new Matrix<int>; 
      m_pAggObjectVec = new Vector<float>;
      m_pAggGrpValues = new Vector<float>;
	  m_EndFlag = true;
	  m_execution_time=0;
	  m_iConstNumber = 0;	
	  m_pTextVec = new Vector<String>;//DRK
	  DoHull=TRUE;//DRK
	  STDB=FALSE;//DRK
	  relCtr=0;
	  m_pEvalnList=NULL;
	  DBRecursive=FALSE;//DRK
	  p_state=0;
	  selMatVec = new Vector<Matrix<float> >;

	  GIS=FALSE;	//RUICHEN
	  Approx = false;	//SRA TJP
	  ApproxBound = 0.0; //SRA TJP
	  m_Distinct = true; //Shasha
	  //iterationCT=0;
   } ; 
  
~DB() {
	//CString tt;
	//tt.Format("%d", iterationCT);
	//AfxMessageBox(tt);
      delete m_pVecLine;  
      delete m_pArgVector;   
      delete m_pMatrix; 
      delete m_pRelationList;  
      delete m_pRelNameVec;
      delete m_pEqualMatrix; 
      delete m_pAggMatrix; 
      delete m_pAggObjectVec;
      delete m_pAggGrpValues;
	  delete m_pTextVec;
	  delete selMatVec;
   } ;    

   //static clock_t last_db_time;
   // after a clause such as:  R(...):- 3x+4y-z <= 9, 2x-y < 8. 
   //was analysized, call  ClauseHandler()
   void LowerApproxHandler(Relation* &ptempRel);
   void UpperApproxHandler(Relation* &ptempRel);
   void ClauseHandler();
   void STDBClauseHandler();	//for STDB clause handling DRK
   void OnlyHeadPredicateHandler();
   
   void Display(const char*, ostream&) ;
   void Display_points(const char* relName,ostream& os );


   //predicate, now only deal with situation that 
   // there is no predicate in the body.
   void PredHandler(const char* predName);
   void NegPredHandler(const char* predname );    
   void ArgHandler(const char* a);
	void ArgHandler(float f );    
	void Convt_t(const char*){};
   void Convt_l(const char*);
   float HulArea(Slist<ParaPoint>* PointList);
//   Relation* HulPreConvt(Relation* prel);
   Relation* HulReConvt(Relation* prel);

   Slist<ParaPoint>* HulConvt(Matrix<float>* p_matrix);


   // Expression Handler, when it is called, the coefficient on
   // the left of an expression has already been copied into m_pVecLine
   void ExpressionHandler(const char* relOp, float rvalue);
	
   void ExpressionHandler(const char* relOp, const char* rvalue);
	//for the new text MLPQ by DRK

  // Sets up the aggregate matrix so that simplex method could be 
  // invoved later to solve for aggregate operators
   void AggregateHandler(char* aggtype);
   void ObjectiveHandler();
   void ObjectiveHandler(char* groupname);

   // item handler, fill in the m_pVecLine
   void ItemHandler(float c, const char* a); 
 
   int   InsertRelation(const Relation& r); 
   const Relation* RetrieveRelation(const String& s); 
   const Relation* DeleteRelation(const String& s); 
   Relation* VarElimination(Relation* r, int j);
   bool AddVectorToMatrix(Matrix<float>* p_matrix, Vector<float>* p_vec);
   bool AddVectorToMatrix2(Matrix<float>* p_matrix, Vector<float>* p_vec);
   bool AddDVectorToDMatrix2(Matrix<double>* p_matrix, Vector<double>* p_vec);
   Relation*  ComputeAggregate(Relation *rel);
   void fwrite_matrix_for_lp(char* filename,const Matrix<float>* p_matrix);
   Relation* ComputeRelation(Relation* rel);
   Relation* create_simplex_relation(Relation* prel, lprec *lp);
   Relation* Compute_GroupBy_Relation(Relation *prel);
   Relation* AddVectorFunction(Relation* prel,float agg_value);
   Relation* DoAggregation(Relation* rel);
   void Add_Agg_Value(float agg_value);
   void  Check_GroupBy_Format(Relation* prel);
   int AreaHandler(String relname,float step,float lower, float upper);
   int AreaHandler3(String output_name, String relname,float step,float lower, float upper);
   float RelationArea(Relation* prel);
   int AreaHandler2(String relname,float step1,float lower1, float upper1,float step2,float lower2, float upper2);
   float IntersectArea(Relation* prel);
   Matrix<float>* GetMatrixFromIDPoints(float id, Point p0, Point p1, Point p2);
   void Cpu_time();
   bool SimplexMatrixSatisfiable(Matrix<float>* p_matrix);
   
   bool CheckRecursiveClause();		//added by DRK
   Relation * linear_partition(Matrix<float> *c1,Matrix<float> *c2);			//added by DRK
   bool check_containment(Relation *p_oldC, Relation *p_r, Relation *ptempRel);	//added by DRK
   bool polyhedron_containment(Relation *p_oldC, Matrix<float> *p_rmat, Matrix<float> *ptempRelmat); //added by DRK
   bool check_disjoint(Matrix<float> *c1,Matrix<float> *c2);					//added by DRK

//private:	
   clock_t m_execution_time; 
   int numRels;
   friend ostream& operator << (ostream&, const DB&);
   friend class Relation;
   Slist<Arg> m_ArgList ;       //relation's arg list
   Vector<String>* m_pArgVector; // list of all variables in a clause

 /*hold all relation names in a clause. 1'st is the left side predicate*/
   Vector<String>* m_pRelNameVec; 


   /* the equality matrix which is used for joins Ref: Dr.Revesz Book chap 4. */
   Matrix<int>* m_pEqualMatrix;  

   /* Coefficient's  of an expression*/
   Vector<float>* m_pVecLine;

   /* Stores aggregate op type, position in relation and the variable it operates on*/
   Matrix<int>* m_pAggMatrix;
   /* Store the Ojective function as a vector of float*/
   Vector<float>*  m_pAggObjectVec;
 
 /* Store the possible values of the Group by clause */
   Vector<float>*   m_pAggGrpValues;

   bool DoHull;		//added by DRK for selection
   bool STDB;		//flag which indicates whether STDB or CDB
   bool GIS;	     //RUICHEN  //flag which indicates whether color bands or not
   bool DBRecursive;//flag which indicates whether recursive query or not
   int relCtr;		//counter for temporary relations used during STDB clause evaluation
   evalnList * m_pEvalnList;//data structure which is used to evaluate algebra expressions
   int p_state;		//state variable used by the scanner and parser DRK
   
   void AddEvalRow(const char *,const char *,const char *,const char *);//add row to EvalnList
   void SetMatrixTime();	//for setting the time values prior to STDB expression evaluation DRK

   Vector<String>* m_pTextVec;	//for the various text constants
   Vector<Matrix<float> > *selMatVec;	// for the nested select operator of STDB
   double Mval;		//this determines the realm of the complement

   bool Approx;
   float ApproxBound;
   int ApproxType;
   String m_sName;                //Relation name
   Matrix<float>* m_pMatrix; 
   Slist<Relation>* m_pRelationList;
   bool m_EndFlag;
   int m_iConstNumber;			// the number of constant
   void  InstallVariable(String newvar);
   bool m_Distinct; //Shasha: distinct result
	
   int iterationCT;
} ; 

#endif







