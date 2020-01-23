/*********************************************************
 * Name:     db.c
 * Author:   
 * Time:     April 6, 1997
 * Function:  implement member function of class DB
 *            including  the interface with
 *            parser, after parser of input, a Relation 
 *            list will be built up, it stores all relations
 *            in the (*dataBase), using matrices. 
 ***********************************************************/
#include "stdafx.h"
//#include <values.h>
#include "string.h"
#include <stdlib.h>
#include <fstream.h>
#include <stdio.h>
#include<string.h>
#include "slist.h"
#include "vector.h"
#include "db.h"

#include "lp_solve.h"
#include "MainFrm.h"

extern DB (*dataBase);

//extern "C" void write_LP(lprec *lp, FILE *output); 

/*************************************************************
 * name:     DB::ArgHandler(const char* a)
 * Time:     May 22, 1997
 * Descript: Add the arguments of the predicate to  m_ArgList. 
 *           The arguments that are not present in the m_pArgVector
 *           are added to that list.
 * ************************************************************/
void DB::ArgHandler(const char* a) 
{
		if(m_ArgList.Size()==0 && STDB==TRUE)		//new line /*
		{
			m_ArgList.AppendHere(*new Arg("i"));
			InstallVariable(String("i"));
			m_ArgList.AppendHere(*new Arg("x1"));
			InstallVariable(String("x1"));
			m_ArgList.AppendHere(*new Arg("y1"));
			InstallVariable(String("y1"));
			m_ArgList.AppendHere(*new Arg("x2"));
			InstallVariable(String("x2"));
			m_ArgList.AppendHere(*new Arg("y2"));
			InstallVariable(String("y2"));
			m_ArgList.AppendHere(*new Arg("t"));
			InstallVariable(String("t"));
			m_ArgList.AppendHere(*new Arg("p"));
			InstallVariable(String("p"));
			m_ArgList.AppendHere(*new Arg("s"));
			InstallVariable(String("s"));
		}
	    String a1 = String(a);		//new line */
		m_ArgList.GotoTail();		//new line
        m_ArgList.AppendHere(*new Arg(a1));
        int position = m_pArgVector->Search(a1);
        if( position == -1) 
            InstallVariable(String(a1));
}  

void DB::ArgHandler(float f ) 
{
	Arg* a1 = new Arg(f);
	char buffer[20];

	_itoa( m_iConstNumber++, buffer, 10 );
 
	a1->strPtr = new String(String("Const_")+ String(buffer));
	m_ArgList.GotoTail();		//new line 6/23
	m_ArgList.AppendHere(*a1);
	//int position = m_pArgVector->Search(a1);
	//if( position == -1) 
            InstallVariable(*(a1->strPtr));
}  

/***************************************************
 * name:     DB::PredHandler(const char* predName)
 * Time:     April 6, 1997
 * Descript: when this is called, the m_ArgList has
 *           already been set up. 
 *           m_pRelNameVec: hold relation names appear in this clause
 *           m_pArgVector: hold all argument strings appear in this clause
 *           this function build up the equality matrix defined in 
 *           Dr. Peter Revesz's book "Constraint DB, chapter 4" 
 * ***************************************************/
void DB::PredHandler(const char* predName)
{
	if(m_ArgList.Size()==0 && STDB==TRUE)		//new line /*
		{
			m_ArgList.AppendHere(*new Arg("i"));
			InstallVariable(String("i"));
			m_ArgList.AppendHere(*new Arg("x1"));
			InstallVariable(String("x1"));
			m_ArgList.AppendHere(*new Arg("y1"));
			InstallVariable(String("y1"));
			m_ArgList.AppendHere(*new Arg("x2"));
			InstallVariable(String("x2"));
			m_ArgList.AppendHere(*new Arg("y2"));
			InstallVariable(String("y2"));
			m_ArgList.AppendHere(*new Arg("t"));
			InstallVariable(String("t"));
			m_ArgList.AppendHere(*new Arg("p"));
			InstallVariable(String("p"));
			m_ArgList.AppendHere(*new Arg("s"));
			InstallVariable(String("s"));
		}
   Vector<int>* p_EqualVec = new Vector<int>(m_pArgVector->Size());
   *p_EqualVec = 0;

   int size = m_pRelNameVec->Size();
   m_pRelNameVec->Resize(size+1);
   (*m_pRelNameVec)[size]= predName;

   SlistIter<Arg> argListIter(m_ArgList);
   Arg* argPtr;
   int i = 0;

   while(argPtr = argListIter())
   {
	int position = m_pArgVector->Search(*(argPtr->strPtr) );
        if( position != -1) 
		{
            (*p_EqualVec)[position] = i + 1;

			if( argPtr->cFlag == 1)
			{  // const argument
				(*m_pVecLine)[0]= EQUAL;
				(*m_pVecLine)[1]= argPtr->floatVal;
				(*m_pVecLine)[ position+2] = 1;
				AddVectorToMatrix(m_pMatrix, m_pVecLine);
				*m_pVecLine = 0; 
			}       
        }
        else {
			 ASSERT(FALSE);
              cout<< "Bug in program, m_pArgVector not set propaerly\n";
              exit(0);
        }
                 
        i++;
   } 
   int rows = m_pEqualMatrix->Rows();
   if(rows==0){
               m_sName=predName;
               m_pVecLine->Resize(p_EqualVec->Size()+2); 
               (*m_pVecLine) = 0;
   }

   m_pEqualMatrix->Resize(rows+1, p_EqualVec->Size());
   (*m_pEqualMatrix)[rows]= *p_EqualVec;
   m_ArgList.DeepDestroy();
   delete p_EqualVec;  
}

/***************************************************
 * name:     DB::NegPredHandler(const char* predName)
 * Time:     May  15, 1997
 * Descript: Takes care of the case we have a negation of .
 *           a Predicate. 
 * Input :  Predicate  name
 *             
 * ***************************************************/
void DB::NegPredHandler(const char* predname )
{
char * newpredname= new char[strlen(predname)+3];
       newpredname[0]='!';
       newpredname[1]='\0';
       strcat(newpredname,predname);
       PredHandler(newpredname);
}

/***************************************************
 * name:     DB::ItemHandler(float, .. const char* a)
 * Time:     April 6, 1997
 * Descript: This group of functions are used to copy the 
 *           coefficient of an inequality expression:
 *           such as:   x+4.6y-z <=8,  to the m_VecLine vector
 *****************************************************/
//  deal with all cases of Item
void DB::ItemHandler(float c, const char* a)
{
    String a1 = String(a);  
	
	if(p_state==2 && STDB==TRUE)			//new line /*
	{
		if(m_ArgList.Size()==0)
		{
			m_pArgVector->Resize(0);
			m_pMatrix->Resize(0,0);
			m_pEqualMatrix->Resize(0,0);
			ArgHandler(a);
		}
	}									//new line */

    int i = m_pArgVector->Search(a1);
    if(i==-1) {

            InstallVariable(String(a1));
            int cols = m_pVecLine->Size();
            (*m_pVecLine)[cols-1]= c; 

    }
    else
       (*m_pVecLine)[i+2]= c;
}



/***************************************************
 * name:     DB::ExpressionHandler(...)
 * Time:     April 6, 1997
 * Descript: it is used to copy the relation symbol
 *           "=" ---- use value 5 to deputy it
 *           "<" ---- value 1
 *           "<=" --- value 2
 *           and right value of  an inequality expression:
 *           such as:   ...  <= 8,  to the m_VecLine vector
 *****************************************************/
void DB::ExpressionHandler(const char* relOp, float rvalue)
{
   switch(relOp[0]) {
       case '=':  
           (*m_pVecLine)[0]= 5;
           (*m_pVecLine)[1]= rvalue;
           break;
       case '<' :
	   switch(relOp[1]) {
	       case '\0' :
                  (*m_pVecLine)[0]= 1;
                  (*m_pVecLine)[1]= rvalue;
                  break;
	       case '='  :
                  (*m_pVecLine)[0]= 2;
                  (*m_pVecLine)[1]= rvalue;
                  break;
	       default:
                  break;
            }
            break;
       case '>' :
	   if( relOp[1]=='\0' ) {
	       
                  (*m_pVecLine)[0]= 1;
                  for(int i=2; i< m_pVecLine->Size();i++)
                      (*m_pVecLine)[i] = - (*m_pVecLine)[i];
		  (*m_pVecLine)[1]= -rvalue;
           } 
           else if( relOp[1]=='=')
           {
	       
                  (*m_pVecLine)[0]= 2;
                  for(int i=2; i< m_pVecLine->Size();i++)
                      (*m_pVecLine)[i] = - (*m_pVecLine)[i];
		  (*m_pVecLine)[1]= -rvalue;
           }       
	       
                              
            break;
 
       default:
            break;
    }
           
   if(STDB==TRUE) 
		AddVectorToMatrix2(m_pMatrix, m_pVecLine);//DRK made it 2 new line
   else
		AddVectorToMatrix(m_pMatrix, m_pVecLine);
   *m_pVecLine = 0; 
}


void DB::ExpressionHandler(const char* relOp, const char* rvalue)	//new function
{
	int ret;
	String pStr=String(rvalue);
	int size = m_pTextVec->Size();
   switch(relOp[0]) {
       case '=':  
            (*m_pVecLine)[0]= 5.5;
		    ret=m_pTextVec->Search(pStr);
			if(ret==(-1))
			{
				m_pTextVec->Resize(size+1);
				(*m_pTextVec)[size]= pStr;
				//(*m_pTextVec)[size]+= "\0";
				(*m_pVecLine)[1]=(float)size;
			}
			else
				(*m_pVecLine)[1]=(float)ret;
           //(*m_pVecLine)[1]= rvalue;
           break;
       case '<' :
	   switch(relOp[1]) {
	       case '\0' :
                  (*m_pVecLine)[0]= 1;
                  //(*m_pVecLine)[1]= rvalue;
                  break;
	       case '='  :
                  (*m_pVecLine)[0]= 2;
                  //(*m_pVecLine)[1]= rvalue;
                  break;
	       default:
                  break;
            }
            break;
       case '>' :
	   if( relOp[1]=='\0' ) {
	       
                  (*m_pVecLine)[0]= 1;
                  for(int i=2; i< m_pVecLine->Size();i++)
                      (*m_pVecLine)[i] = - (*m_pVecLine)[i];
		  //(*m_pVecLine)[1]= -rvalue;
           } 
           else if( relOp[1]=='=')
           {
	       
                  (*m_pVecLine)[0]= 2;
                  for(int i=2; i< m_pVecLine->Size();i++)
                      (*m_pVecLine)[i] = - (*m_pVecLine)[i];
		  //(*m_pVecLine)[1]= -rvalue;
           }       
	       
                              
            break;
 
       default:
            break;
    }
           
   AddVectorToMatrix(m_pMatrix, m_pVecLine);
   *m_pVecLine = 0; 
   //m_pMatrix->Trace();
}



/*******************************************************
 * name:     DB::AggregateHandler(char* aggtype)
 * Time:     April 20, 1997
 * Descript: Called after parsing of  "max" in the input:
 *           R(x,max(x+y)):- Q(x,y), 3x+y <= 0.
 *           
 ********************************************************/

void DB::AggregateHandler(char* aggtype)
{
char temp[20];
Vector<int>* agg_vector= new Vector<int>(3); 

  
  if (!strcmp(aggtype,"max")) { (*agg_vector)[0]=1; strcpy(temp,"max");}
  if (!strcmp(aggtype,"min")) { (*agg_vector)[0]=2; strcpy(temp,"min");}
  if (!strcmp(aggtype,"MAX")) { (*agg_vector)[0]=3; strcpy(temp,"MAX");}
  if (!strcmp(aggtype,"MIN")) { (*agg_vector)[0]=4; strcpy(temp,"MIN");}
  if (!strcmp(aggtype,"sum_max")) { (*agg_vector)[0]=5; strcpy(temp,"sum_max");}
 if (!strcmp(aggtype,"sum_min")) { (*agg_vector)[0]=6; strcpy(temp,"sum_min");}
  String* newvar= new String(temp);
  *newvar=newvar->Unique();

  /* new aggregate variable name has to added to arglist and argvector.
     Position 1 of agg_vector stores the position of where the new 
     aggregate operator is present. */  
   m_ArgList.GotoTail();		//new line 6/23
   m_ArgList.AppendHere(*new Arg(*newvar));
   int size = m_pArgVector->Size();
   InstallVariable(*newvar);
   (*agg_vector)[1]=size;
   (*agg_vector)[2]=-1;
  int rows= m_pAggMatrix->Rows();
    if (rows>0)
      {
		 ASSERT(FALSE);
       cout<<"More then one aggregate operator not allowed"<<endl;
       exit(0);
      }
    m_pAggMatrix->Resize(rows+1, agg_vector->Size());
   (*m_pAggMatrix)[rows] = *agg_vector;
}
///////////////////////////////////////////
void DB::ObjectiveHandler()
{
   *m_pAggObjectVec = *m_pVecLine;
   *m_pVecLine=0;
}

void DB::ObjectiveHandler(char* groupname)
{   
   String a = String(groupname);	 
   int position = m_pArgVector->Search(a);
   if( position == -1) 
     {
        int size = m_pArgVector->Size();
        InstallVariable(String(a));
        (*m_pAggMatrix)[0][2]=size;
     }
   else
      (*m_pAggMatrix)[0][2]=position;
   ObjectiveHandler();    
}

/*******************************************************
 *
 * Name:	DB::ApproximationHandler
 * Time:	April 23, 2003
 * Desc:	This mathod checks the bounds and resets
 *			them according to DB::ApproxValue
 *
 *
 *******************************************************/

void print_matrix2(Matrix<float>* m, char* name){
	ofstream os;
	os.open(name,ios::app);
	Matrix<float>* p_matrix = m;
      Vector<float> vector;

      os << endl;
      for(int i=0; i< p_matrix->Rows(); i++)
      {   
          os << endl;
          vector = (*p_matrix)[i];
		  // printout coefficents of the variables
          for(int j=2; j< vector.Size(); j++)
              os <<vector[j] << " ";
		  // printout the predicate
          if(vector[0]==0) os << "= ";
          else if(vector[0]==1) os << "< ";
          else if(vector[0]==2) os << "<= ";
          else if(vector[0]==3) os << "> ";
          else if(vector[0]==4) os << ">= ";
          else if(vector[0]==5) os  <<"= ";
          else os << vector[0];
		  //printout the bound
          os << vector[1];                
      }
      os << endl;
      os.close();
}

/**********************************************************
 * name:		DB::LowerApproxHandler()
 * Time:		June, 6 2003
 * Description:	Called to handle recursive queries with lower bound approximation
 *				uses DB::ApproxBound
 *				This function will not be called unless the query is recursive
 *				called if DB::Approx == true
 * Authors:		Scot Anderson and Tim Perrin
 */
void DB::LowerApproxHandler(Relation* &ptempRel) 
{
	int i=0, j=0;
	int rowsize=0, colsize=0;
	int matsize=0;
	float ftmp;
	bool changed; //,matrix_sat;
	float pred=0.0;
	Matrix<float> *smatPtr;//, *tmpmatPtr;
	Vector<float> *svecPtr;
	DFIter<Matrix<float> >  tempRel_matrixIter(*(ptempRel->m_tablePtr));
	while ((smatPtr=tempRel_matrixIter())!=0 )
	{
		changed=false;
		matsize++;
		rowsize=smatPtr->Rows();
		colsize=smatPtr->Cols();
		for (j=0; j<rowsize; j++) {
			svecPtr = smatPtr->matPtr[j];
			ftmp = svecPtr->vecPtr[1];
			pred = svecPtr->vecPtr[0];
			if ((pred == 2 || pred == 1) && (ftmp > ApproxBound)) {
				svecPtr->vecPtr[1] = ApproxBound;
				changed = true;
			}
		}
		if (changed==true && !ptempRel->MatrixSatisfiable(smatPtr)) {
			//We made a change and this tuple is no longer satisfiable - so we'll remove it
			ptempRel->m_tablePtr->Delete((*smatPtr));
		}
	}
}	

/**********************************************************
 * name:		DB::ApproxHandler()
 * Time:		June, 6 2003
 * Description:	Called to handle recursive queries with upper bound approximation
 *				uses DB::ApproxBound
 *				This function will not be called unless the query is recursive
 *				called if DB::Approx == true
 * Authors:		Scot Anderson 
 */
void DB::UpperApproxHandler(Relation* &ptempRel) 
{
	int i=0, j=0;
	int rowsize=0, colsize=0;
	int matsize=0;
	float ftmp;
	bool changed; //,matrix_sat;
	float pred=0.0;
	Matrix<float> *smatPtr;//, *tmpmatPtr;
	Vector<float> *svecPtr;
	DFIter<Matrix<float> >  tempRel_matrixIter(*(ptempRel->m_tablePtr));
	while ((smatPtr=tempRel_matrixIter())!=0 )
	{
		changed=false;
		matsize++;
		rowsize=smatPtr->Rows();
		colsize=smatPtr->Cols();
		/*
		Slist<int> *dellist = new Slist<int>();
		for (j=0; j<rowsize; j++) {
			svecPtr = smatPtr->matPtr[j];
			ftmp = svecPtr->vecPtr[1];
			pred = svecPtr->vecPtr[0];
			if ((pred == 2 || pred == 1) && (ftmp > ApproxBound)) {
				int *k = new int(j);
				dellist->AppendHere(*k); //Shasha: memory of k does not release
			}
		}
		int test = dellist->Size();
		if (test > 0) {
			smatPtr->Del(dellist, colsize);
		}
		dellist->~Slist<int>();
		*/
		CArray<int> dellist;
		for (j=0; j<rowsize; j++) {
			svecPtr = smatPtr->matPtr[j];
			ftmp = svecPtr->vecPtr[1];
			pred = svecPtr->vecPtr[0];
			if ((pred == 2 || pred == 1) && (ftmp > ApproxBound)) {
				dellist.Add(j);
			}
		}
		int test = dellist.GetCount();
		if (test > 0) {
			smatPtr->DelVector(&dellist, colsize);
		}
		dellist.RemoveAll();
		dellist.FreeExtra();

	}
}
	


/*******************************************************
 * name:     DB::ClauseHandler()
 * Time:     April 20, 1997
 * Descript: Called after parsing of such input:
 *           R(x,y):- Q(x,y), 3x+y <= 0.
 *           Now, m_pMatrix, m_sName already exist in the 
 *           in the DB object
 ********************************************************/
void DB::ClauseHandler()
{    
//m_pMatrix->Trace(); Commented out by Scot Anderson 6/22/2006
//m_pMatrix is what represents a clause shown above.
	
	Relation* p_r;
    Relation* p_r1;
    Relation* ptempRel;
	int rounds=0; //REMOVE THIS DEBUG CODE
doagain:
	rounds++; //REMOVE THIS DEBUG CODE
	//SA: The clause will be put into a new relation called ptempRel
	ptempRel=new Relation(); 
    String relname;

//m_pMatrix->Trace();
	//SA: If we are not given an empty matrix representing this clause, 
	//    then we add this clause to the ptmpRel (which is currently empty).
	//    So far: make empty relation, add parsed clause to it
    if(m_pMatrix->Rows()!=0) // m_pMatrix is part of DB
	{ 
		ptempRel= ptempRel->CombineMatrix(m_pMatrix); // only pointers are used no new objects
		// this seems to cleanup after itself. 06/23/06
		//delete m_pMatrix;	//commented by DRK
		//m_pMatrix = NULL;	//commented by DRK
	}
	//ptempRel->Trace();


    int vec_size = m_pRelNameVec->Size();
    for(int i = 1; i< vec_size; i++)
    {  
		relname=(*m_pRelNameVec)[i];
		//This is a negated relation we want p_r to be the negation when we are done with this if.
		if (relname[0]=='!')
		{  
			relname=relname.Substring(1);
			//SA: if we haven't seen this before we get null or 0. In a recursive 
			//program it is possible that we have not defined this yet, and we must 
			//allow for that possibility. p_r points to this relation as the one 
			//being used in a clause, and sets it to unsatisfiable.
			p_r=(Relation*)RetrieveRelation(relname); // returns a pointer to an existing relation
            if(p_r==0 )
			{ 
				p_r=new Relation();
				p_r->m_Satisfiable=-1;
				if(ptempRel)  // wm 06/23/06 to be sure that the old Relation is deleted
					delete ptempRel;
				ptempRel=new Relation(); //SA: Possible memory leak
				ptempRel->m_Satisfiable=-1;
				//ASSERT(FALSE);
				//cout << "Relation: " << relname << " used before being  declared" <<endl;
                //exit(0);
            }
			//SA: We found this in our list of known relations
            else
			{
				//This copies the old relation with equalities changed to inequalities i.e. x=1 --> x<=1 AND x>=1 
				//this representation allows certain operations to go smoothly.
				p_r1=p_r->InequalRelation();  
				                              //SA: THERE IS STILL something in p_r
				p_r=p_r1->NegationRelation(); //    should p_r be deleted? Maybe not 
				                              //    because p_r1 may be the temporary relation
					// check to see if we need to delete this p_r!!!!
				if (p_r1 == 0)				  //SA: This will never be thrown, null pointer access in previous line! 
					throw "DB::ClauseHandler Line 508";
				delete p_r1;					// test to see if null, we should not delete null
			}
		}
		//SA:whew this is not a negated relation we will place a copy in p_r
		else
        {   
			//SA: of course if its unknown, we just create a new one
			p_r=(Relation*)RetrieveRelation(relname);
			if( p_r==0 )
            { 
				//commented out and added this by DRK
				p_r=new Relation();
				p_r->m_Satisfiable=-1;
				if(ptempRel) {
					delete ptempRel; //SA: Fixed Memory Leak
				}
				ptempRel=new Relation(); 
				ptempRel->m_Satisfiable=-1;
				//AfxMessageBox("Relation used before been declared"); 
				//ASSERT(FALSE);

				//cout << "Relation: " << relname << " used before being  declared" <<endl;
                //exit(0);
            }
		}
		if (p_r == NULL) 
			throw "DB::ClauseHandler Line 529 p_r = 0";
		//SA: This performs an alignment that reorders the relation variables according to the ordering found 
		//    in &((*m_pEqualMatrix)[i]). 
		//    Allignment needs to be done in a more equitable manner! See p 177 ICDB (Revesz2001)
		p_r = p_r->AllignRelation( &((*m_pEqualMatrix)[i]) ); 
		ptempRel = ptempRel->CombineRelation(p_r);
		delete p_r;  // are we deleting null?
		             //SA: This apprears to be properly deleting p_r the relation (assuming delete calls the destructor properly)
	} //end of for loop through vectors in matrix
    ptempRel=DoAggregation(ptempRel); //SA: Assumed ok for now - or at least sane call structure
    ptempRel->m_sName = m_sName;      //SA: We waited until now to set the name?

	//SA: In the head of the clause we check to see if we have a 0 in the jth position indicating that 
	//the variable in this place is eliminated (or not used) in the resulting relation
    int cols=m_pEqualMatrix->Cols();
    for(int  j=cols-1;j>=0; j--)
	{

		if( (*m_pEqualMatrix)[0][j]==0) 
		{
			ptempRel = VarElimination(ptempRel, j);
			//ptempRel->Trace();
		}
    }
	//SA: not sure what this is doing other than setting the allignVec value 
	//    but I'm not sure why
    Vector<int>* allignVec = new Vector<int>(); 
    for(j=0;j<cols; j++)
	{
		if( (*m_pEqualMatrix)[0][j]!=0)
		{
			int size = allignVec->Size();
			allignVec->Resize(size+1);
			(*allignVec)[size]=(*m_pEqualMatrix)[0][j];   
		}
	}
    p_r1 = ptempRel->AllignRelation(allignVec);
	delete ptempRel;
	ptempRel=p_r1;
	//SA: adding the names of the vars etc. to ptempRel
    for(j=0;j<cols; j++)
	{
		if( (*m_pEqualMatrix)[0][j]!=0)
		{
			CString s  = CString((*m_pArgVector)[j].GetText());
			(ptempRel->m_strAtriList).AddTail( s);
		}
	}
   
	//SA: So you are adding a relation? Update the db object
	//    NOTE: p_r is reset here! Has p_r been deleted or properly disposed of? if not :memory leak!!!
	if(0==(p_r=(Relation*)RetrieveRelation(ptempRel->m_sName)) ) 
	{ // a new relation
		numRels++;
		m_pRelationList->GotoTail();		//new line 6/23
        m_pRelationList->AppendHere(*ptempRel);
		//ptempRel->Trace();//DRK
    }
    else // relation exists before this appear and is now assigned to p_r
	{
        
		//inserted by DRK - check if recursive clause or not
		bool p_recursive = FALSE;
		p_recursive = CheckRecursiveClause();
		if (p_recursive==TRUE)				
		{
//Begin: inserted by Scot to check for approximation safe queries
			if (Approx == true) {
				if (ApproxType == 0) {
					LowerApproxHandler(ptempRel);
				}
				if (ApproxType == 1) {
					UpperApproxHandler(ptempRel);
				}
			}
//End: inserted by Scot to check for approximation safe queries continue old code 
			Relation *newC=new Relation();
			bool newfacts=FALSE;
			//SA: Just glanced at. This checks to see if |newC|>0, where newC = ptempRel - p_r
			//SA: This contains an error that can be seen when doing a simple diff query: e.g. with upper, l=2 we get x-y>=3 and x-y>=4 both
			//TODO fix check_containment see above note.
			newfacts=check_containment(newC,p_r,ptempRel);
			if (newfacts==TRUE)
			{			
				p_r->UnionRelation(newC);
				delete newC;
				//ptempRel=NULL;
				delete ptempRel;
				ptempRel=NULL;
				goto doagain;
			}
			else
			{
				delete newC;
				//ptempRel=NULL;
				delete ptempRel;
				ptempRel=NULL;
			}

		}
		else						
		// end of insertion by DRK
		//original code from here onwards
		{
			p_r->UnionRelation( ptempRel);
			delete ptempRel;
		}
	}

	//SA: This appears to be reseting this object to its default values. The question is who 
	//    will delete this object and when?
	m_ArgList.DeepDestroy();
    m_pVecLine->Resize(0);
	if(m_pMatrix!= NULL)
		delete m_pMatrix;
    m_pMatrix = new Matrix<float>(); //SA: why would we just recreate something here?
    m_pArgVector->Resize(0);
    m_pRelNameVec->Resize(0);
//	cout << *ptempRel << endl;
    //HulConvt(ptempRel);
    m_sName = String(); 
    ptempRel=NULL;
    delete m_pEqualMatrix; 
	m_pEqualMatrix= new Matrix<int>();
	delete allignVec;
	return;
}
/*********************************************************
 *
 *********************************************************/ 
void DB::OnlyHeadPredicateHandler()
{
	Relation* p_r;
//    Relation* p_r1;
    Relation* ptempRel=new Relation(); 
    String relname;

//m_pMatrix->Trace();
	int cols=m_pEqualMatrix->Cols();

    if(m_pMatrix->Rows()!=0) 
	{ 
		ptempRel= ptempRel->CombineMatrix(m_pMatrix);
		delete m_pMatrix;
		m_pMatrix = NULL;
	}
    ptempRel->m_sName = m_sName;  

	for(int j=0;j<cols; j++)
	{
//		if( (*m_pEqualMatrix)[0][j]!=0)
//		{
			CString s  = CString((*m_pArgVector)[j].GetText());
			(ptempRel->m_strAtriList).AddTail( s);
//		}
	}
    
    if(0==(p_r=(Relation*)RetrieveRelation(ptempRel->m_sName)) ) 
	{ // a new relation
		numRels++;
		m_pRelationList->GotoTail();		//new line 6/23
        m_pRelationList->AppendHere(*ptempRel);
    }
    else // relation exit before this appear
	{
        p_r->UnionRelation( ptempRel);
		delete ptempRel;
	}
    m_ArgList.DeepDestroy();
    m_pVecLine->Resize(0);
	if(m_pMatrix!= NULL)
		delete m_pMatrix;
    m_pMatrix = new Matrix<float>();
    m_pArgVector->Resize(0);
    m_pRelNameVec->Resize(0);
//	cout << *ptempRel << endl;
    //HulConvt(ptempRel);
    m_sName = String(); 
    ptempRel=NULL;
    delete m_pEqualMatrix; 
	m_pEqualMatrix= new Matrix<int>();
//	delete allignVec;
}
 
int DB::InsertRelation(const Relation& r)
{
      Relation* hPtr = new Relation(r) ;
	  m_pRelationList->GotoTail();		//new line 6/23
      m_pRelationList->AppendHere(*hPtr); 
      numRels++ ; 
      return numRels; 
}

const Relation* DB::RetrieveRelation(const String& s)
{ 
	 ASSERT( this != NULL );
	 m_pRelationList->GotoHead();  //Huge
     SlistIter<Relation> relIter(*m_pRelationList);
     const Relation* p_relation;
     while(p_relation =relIter()) {
         if(s== p_relation->Name())
               return p_relation;
     }
     return (Relation*)0;
} 

const Relation* DB::DeleteRelation(const String& s)
{ 
   const Relation* p_r = RetrieveRelation(s);  
   return m_pRelationList->Delete(*p_r);
}
 
void DB::Display(const char* relName, ostream& os)
 { 
  const Relation* relPtr ;
  if (!(relPtr = RetrieveRelation(relName))) 
      os << "\"" << relName << "\":" << " No such relation in data base\n" ;
  else
   os << *relPtr ;  
  
 }

/*********************************************************************
 * name:     DB::VarElimination(Relation* r, int j)
 * Time:     April 8, 1997
 * Descript: Please refer to "discript3" file
 * Input:    Relation* r, the relation to be done variabe 
 *                          elimibnation
 *           int j: the column number of variable,
 *                  the j+2 column of matrix will be eliminated.
 *                  first col is Op code, second col is right value.
 * Output:   a new relation with the variable has been eliminated       
 *            
 *****************************************************/
Relation* DB::VarElimination(Relation* r, int j)
{

    Relation* tr = new Relation(m_sName);
    tr->m_Arity = r->m_Arity-1;
	tr->m_Satisfiable = r->SatisFlag();
    if( tr->m_Satisfiable == -1 || tr->m_Satisfiable == 1 )
	{
		delete r;
		return tr;
	}

    Matrix<float>* m_tmpMatrix = new Matrix<float>(); 
	Vector<float>* m_tmpVecLine= new Vector<float>();

	int vec_size = (*r).Arity();

   const Matrix<float>* p_matrix;
   int iNewSize = vec_size -1+2;
   m_tmpVecLine->Resize(iNewSize);
   *m_tmpVecLine = 0; 

   j=j+2; 
   DFIter<Matrix<float> >  matrixIter(*(r->m_tablePtr));
   int sign1, sign2;
   while(p_matrix =  matrixIter()) {
      // eql
//      cout << *p_matrix << endl;
      ((Matrix<float>*)p_matrix)->EqlToInEql();
//      cout << *p_matrix << endl;
      // eql

      for(int i=0; i< p_matrix->Rows(); i++)
      {
		  if( (*p_matrix)[i][j]!=0) {
            for(int i2=i+1; i2< p_matrix->Rows(); i2++) {
               if( (*p_matrix)[i2][j]!=0 ) {
				   sign1=(*p_matrix)[i][j]>0?1:-1;
                   sign2=(*p_matrix)[i2][j]>0?1:-1;
                   if( 0==(sign1+sign2) ) {
                      int k=1;
                      for(int col=1;col< p_matrix->Cols(); col++)
					  {
                         if(col!=j)  
                           (*m_tmpVecLine)[k++]=(float)((double)((*p_matrix)[i][col]*sign2*(*p_matrix)[i2][j])
                                               +(double)((*p_matrix)[i2][col]*sign1*(*p_matrix)[i][j]));
                      }
                      int symbol= (int)( (*p_matrix)[i][0]+(*p_matrix)[i2][0])/2;
                      (*m_tmpVecLine)[0]=  (float)symbol;
//					  m_tmpVecLine->Trace();
					  for( k=2; k < iNewSize; k++)
					  {
						  if( (*m_tmpVecLine)[k] != 0) 
							  break;
					  }
					  if( k != iNewSize) 
							AddVectorToMatrix2(m_tmpMatrix, m_tmpVecLine);
                      *m_tmpVecLine = 0; //SA: If we are pointing to m_tmpVecLine in m_tmpMatrix this is ok, otherwise: memory leak
                   }
                }
            }
		  }
		  else {  
             int k=0;
			 for(int col=0;col< p_matrix->Cols(); col++) {
                 if(col!=j)  
                     (*m_tmpVecLine)[k++] = (*p_matrix)[i][col];
             }
             AddVectorToMatrix2(m_tmpMatrix, m_tmpVecLine);
			 *m_tmpVecLine = 0; //SA: If we are pointing to m_tmpVecLine in m_tmpMatrix this is ok, otherwise: memory leak
		  }
      }   
      if(m_tmpMatrix->Rows()!=0) {
		  tr->AddMatrix(*m_tmpMatrix); // object is deleted or used
 		  m_tmpMatrix = new Matrix<float>();
      }
      else {
          tr->m_Satisfiable = 1;
          break; /* jump out of while loop */ 
      }
   } /* end of while */
   
   r->m_sName=String();
    /*because r->m_sName  and tr->m_sName refer to the same String, so we cut
      off the relation between r->m_sName and tr->m_sName */ 
    
   delete r; //KPP

   Relation* tr2 = tr->CopyRelationWithEqual(); 
   delete m_tmpMatrix;  //KPP
   delete m_tmpVecLine; //KPP 
   delete tr;
   return tr2;
}
/*********************************************************************
 * bool AddVectorToMatrix(Matrix<float>* p_matrix,Vector<float>* p_vec)
 * Time:     May 15, 1997
 * Descript: judge if the vector was already included in the matrix,
 *           if not, append the vector to the last line of the matrix
             also combine a<=b, a>=b to a=b. 
 * Input:  p_matrix   a pointer to a float matrix
 *         p_vec      a pointer to a float vector
 * Output: true:  if the vector has been added to the matrix
 *         false:  if the vector has not been added to the matrix  

 IMPORTANT(Shasha): A new vector will be created to store the content of input vector 
 *****************************************************/
bool DB::AddVectorToMatrix(Matrix<float>* p_matrix, Vector<float>* p_vec)
{
   int rows = p_matrix->Rows();
   if( *p_vec == 0) return false;
   for(int i=0; i < rows; i++){
	   if (STDB==TRUE && (*p_vec)[2]==0  &&  (*p_vec)[3]==0 && (*p_vec)[4]==0							//new line
							&&  (*p_vec)[5]==0  &&  (*p_vec)[6]==0 && (*p_vec)[7]!=0)	
			break;																		//new line
       if( (*p_matrix)[i] == *p_vec)  
            return false;
	   /*
	   if( (*p_matrix)[i] <= *p_vec )  
			return false;  
	   else if ( *p_vec <= (*p_matrix)[i] )  
	   {
		   (*p_matrix)[i] = *p_vec ;
		   return true;
	   }*/

	   if( ((*p_matrix)[i]).Equal(*p_vec) && Approx!=true){ //added && Approx != true for approximation
			 (*p_matrix)[i][0]=5;
			  return false;  
	   }   
   }
   p_matrix->Resize(rows+1, p_vec->Size());
   (*p_matrix)[rows] = *p_vec;
   return true;  
}
/*********************************************************************
 * bool AddVectorToMatrix2(Matrix<float>* p_matrix,Vector<float>* p_vec)
 * Time:     May 15, 1997
 * Descript: judge if the vector was already included in the matrix,
 *           if not, append the vector to the last line of the matrix 
 * Input:  p_matrix   a pointer to a float matrix
 *         p_vec      a pointer to a float vector
 * Output: true:  if the vector has been added to the matrix
 *         false:  if the vector has not been added to the matrix   

 IMPORTANT(Shasha): A new vector will be created to store the content of input vector 
*****************************************************/
bool DB::AddVectorToMatrix2(Matrix<float>* p_matrix, Vector<float>* p_vec)
{
   int rows = p_matrix->Rows();
   if( *p_vec == 0) return false;
   for(int i=0; i < rows; i++){
       if( (*p_matrix)[i] == *p_vec)  
            return false;
	   /*
       if( (*p_matrix)[i] <= *p_vec)  
            return false; 
	   else if ( *p_vec <= (*p_matrix)[i] )  
	   {
		   (*p_matrix)[i] = *p_vec ;
		   return true;
	   }*/
   }
   p_matrix->Resize(rows+1, p_vec->Size());
   (*p_matrix)[rows] = *p_vec;
   return true;  
}


// IMPORTANT(Shasha): A new vector will be created to store the content of input vector 
bool DB::AddDVectorToDMatrix2(Matrix<double>* p_matrix, Vector<double>* p_vec)
{
   int rows = p_matrix->Rows();
   if( *p_vec == 0) return false;
   for(int i=0; i < rows; i++){
       if( (*p_matrix)[i] == *p_vec)  
            return false;
       /*
	   if( (*p_matrix)[i] <= *p_vec)  
            return false;
	   else if ( *p_vec <= (*p_matrix)[i] )  
	   {
		   (*p_matrix)[i] = *p_vec ;
		   return true;
	   }*/
   }
   p_matrix->Resize(rows+1, p_vec->Size());
   (*p_matrix)[rows] = *p_vec;
   return true;  
}




ostream& operator << (ostream& os, const DB& d)
{
  if (!d.numRels) os << "\nEmpty (*dataBase)\n" ; 
  else
  {
       SlistIter<Relation> relationListIter(*d.m_pRelationList);
       //const Relation* p_r1;
       Relation* p_r; 
       while(p_r = (Relation*)relationListIter()){
          
          os<< "Relation \"" << p_r->Name()<<"\":Arity "
             << p_r->Arity() <<", ";
          if(p_r->SatisFlag()==0)
                os <<p_r->NumberOfMatrixes()<<" row(es)\n";
          else if(p_r->SatisFlag()==1)
                os <<"Univeral Satisfiable\n";
          else  os <<"Can not be satisfied\n";
       }
  };  
  return os ;
};



/*********************************************************************
 * void  InstallVariable(String newvar)
 * Time:     May 24, 1997
 * Descript: When a new variable is encounterd, it has to be added
 *           to m_pArgVector. m_pEqualMatrix, m_pMatrix and  m_pVecline
 *           has to be resized and the new column added to them has to
 *           be set to zero.
 *            
 * Input:    String which has new variable encountered.
 *         
 * Output:   void. Matrices are chaged as in description.
 **********************************************************************/

void  DB::InstallVariable(String newvar)
{

    /* Add variable to ArgVector*/
    int size = m_pArgVector->Size();
    m_pArgVector->Resize(size+1);
    (*m_pArgVector)[size] = newvar;

    /* Take care of  EqualMatrix*/
    int old_cols=m_pEqualMatrix->Cols();
    int old_rows=m_pEqualMatrix->Rows();
    m_pEqualMatrix->Resize(old_rows, size+1);
    for(int row=0; row < old_rows; row++) 
        (*m_pEqualMatrix)[row][size]=0;
 
    /* Take care of  m_pMatrix*/
    old_cols=m_pMatrix->Cols();
    old_rows=m_pMatrix->Rows();
    m_pMatrix->Resize(old_rows, size+3);
    for(row=0; row < old_rows; row++) 
        (*m_pMatrix)[row][size+2]=0;

    /* Increase size of m_pVecline and store the coefficient of new
        variable */
    m_pVecLine->Resize(size+3);
    (*m_pVecLine)[size+2]=0;  
}
  

Relation* DB::DoAggregation(Relation* rel)
{
  if (m_pAggMatrix->Rows()>0)
    {
      if( (*m_pAggMatrix)[0][2]==-1)
         rel=ComputeAggregate(rel);
      else
         rel=Compute_GroupBy_Relation(rel);
    }
  return rel;
}

/*********************************************************************
 * void  ComputeAggregates(Relation* rel)
 * Time:     June 3, 1997
 * Descript: Take care of aggregate operators
 *            
 * Input:    Relation on which the aggregate operation has to be done
 *         
 * Output:   The relation is modified to take care of the aggregate 
 *           operation result.
 **********************************************************************/

Relation*  DB::ComputeAggregate(Relation *rel)
{

        rel=ComputeRelation(rel);
       //cout << *rel << endl;
       switch( (*m_pAggMatrix)[0][0] ) {
         case  1: /* max */
            break;
         case  2: /* min */
            break;
         case  3: /* MAX */
            rel = rel->GetMAX();
            break;
         case  4: /* MIN */
	    rel = rel->GetMIN();
            break;
         case  5: /* sum_max */
            rel = rel->GetSum_max_min();
            break;
         case  6: /* sum_min */
	   rel = rel->GetSum_max_min();
            break;
         default:
            break;
       }

//     cout<<*rel<<endl;
/* Reinitialize Aggregate Matrix*/
    delete m_pAggMatrix; 
    m_pAggMatrix= new Matrix<int>; 
    return rel;
}

Relation*  DB::ComputeRelation(Relation *rel)
{   
   lprec* lp='\0';

    char **argv='\0';

   const Matrix<float>* p_mat;
   Relation* prel=new Relation();
   prel->m_Arity = rel->m_Arity;
  
   DFIter<Matrix<float> >  matrixIter1(*(rel->m_tablePtr));

   while(p_mat =  matrixIter1()) {
        fwrite_matrix_for_lp("temp.lp",p_mat);
        FILE* file;
        if(!(file=fopen("temp.lp","r") )) {
		 ASSERT(FALSE);
          cerr << "Can't open file:" << "temp_out" << endl;
          exit(1);
        };
        lp = lp_main(lp,1,argv,file);  
        prel= create_simplex_relation(prel,lp);
		fclose(file); //KPPagg
   }
    delete rel; //KPPagg
//	delete_lp(lp);//KPPagg  // huge wang
    return prel;
}
   
void DB::fwrite_matrix_for_lp(char* filename,const Matrix<float>* p_matrix)
{
      Vector<float> vector;
      ofstream output(filename);
      if(!output){
		 ASSERT(FALSE);
         cerr << "Can't open file:" << filename << endl;
         exit(1);
      };

   /* Write objective fuction to file */
    
     switch( (*m_pAggMatrix)[0][0] ) {
         case  1: /* max */
         case  3: /* MAX */ 
         case  5: /* sum_max*/
              output << "max:";
              break;
         case  2: /* min */
         case  4: /* MIN */
         case  6: /* sum_min */
              output << "min:";
              break; 
         default:
            break;
       }
   int obj_cols=m_pAggObjectVec->Size();
   for(int cols=2; cols < obj_cols; cols++)
    { 
        if ((*m_pAggObjectVec)[cols]>0)
	      output << "+"<<(*m_pAggObjectVec)[cols]<<(*m_pArgVector)[cols-2];
        else if ((*m_pAggObjectVec)[cols]<0)
               output <<(*m_pAggObjectVec)[cols]<<(*m_pArgVector)[cols-2];
    }
         
      output<<";\n";
      for(int i=0; i< p_matrix->Rows(); i++)
      {   
          vector = (*p_matrix)[i];
          for(int j=2; j< vector.Size(); j++)
	    { 
              if (vector[j]>0)
	         output << "+"<<vector[j]<<(*m_pArgVector)[j-2];
              else if (vector[j]<0)
                  output <<vector[j]<<(*m_pArgVector)[j-2];
            }
          if(vector[0]==0) output << "= ";
          else if(vector[0]==1) output << "< ";
          else if(vector[0]==2) output << "<= ";
          else if(vector[0]==3) output << "> ";
          else if(vector[0]==4) output << ">= ";
          else if(vector[0]==5) output <<"= ";
          else if(vector[0]==5.5) output <<"= "; //shasha(11/2004): add to support string value
          else output << vector[0];
          output << vector[1]<<";\n";                
      }
	output.close();//KPPagg
}


Relation*  DB::create_simplex_relation(Relation* prel, lprec *lp)
{
  int i;
  Matrix<float> *new_matrix= new Matrix<float> ();



  /* print normal variables */
  for(i = 1; i <= lp->columns; i++)
    if(lp->names_used)
      { 
        char* temp=(char*)lp->col_name[i];
        //cout << *temp << endl;
		String temp1 = String(temp);
        int pos= m_pArgVector->Search(temp1);
        if (pos==-1)
          {
			 ASSERT(FALSE);
            cout<<"something screwed up with aggregate operation"<<endl;
            exit(0);
          }
        Vector<float> *new_vector=new Vector<float>(prel->Arity()+2);
        *new_vector=0;
        (*new_vector)[0]=5;
        (*new_vector)[1]=(float)lp->best_solution[lp->rows+i];
       
        (*new_vector)[pos+2]=1;
        AddVectorToMatrix(new_matrix,new_vector);
		delete new_vector; //KPP

      };

   Vector<float> *new_vector=new Vector<float>(prel->Arity()+2);
   *new_vector=0;
   (*new_vector)[0]=5;
   (*new_vector)[1]=(float)lp->best_solution[0];
   (*new_vector)[(*m_pAggMatrix)[0][1]+2]=1;
   AddVectorToMatrix(new_matrix,new_vector);
   prel->AddMatrix(*new_matrix);
   delete new_vector;  //KPP
   return prel;
 
} 

void  DB::Check_GroupBy_Format(Relation* prel)
{  
   bool col_err, row_err;
   int gp_cols= (*m_pAggMatrix)[0][2]+2;

   Matrix<float>* t_pm;
   Vector<float>* p_vec=new Vector<float>();
   const Matrix<float>* p_matrix1;
   DFIter<Matrix<float> >  matrixIter1(*(prel->m_tablePtr));

     
   while(p_matrix1 =  matrixIter1()) 
   {
     row_err=true;
     t_pm = new Matrix<float>(*p_matrix1);
     for(int i=0; i< t_pm->Rows();i++)
     {
       if  ((*t_pm)[i][gp_cols]!=0 && (*t_pm)[i][0]==5) //Variable on which group by is being done
       { 
             row_err=false;
             col_err=false;
             for (int j=2;j<t_pm->Cols();j++)
                if(j!=gp_cols &&(*t_pm)[i][j]!=0)
                {
                    col_err=true;
		    break;
		}
         if (col_err) 
             break;
         else 
            Add_Agg_Value((*t_pm)[i][1]/ (*t_pm)[i][gp_cols]);
       }
      
     }
     if (col_err ||row_err)    
       {
		 ASSERT(FALSE);
          cout<<" Group by not in proper format"<<endl;
          exit(0);
       }
   }
   
}

void DB::Add_Agg_Value(float agg_value)
{

      int i= m_pAggGrpValues->Search(agg_value);
      if(i==-1)
	{
	  int size=  m_pAggGrpValues->Size();
          m_pAggGrpValues->Resize(size+1);
          (*m_pAggGrpValues)[size]=agg_value;
	}
}
   



Relation* DB::Compute_GroupBy_Relation(Relation *prel)
{   
    Relation* pnewrel= new Relation();
    pnewrel=pnewrel->SetSatisfiable();
    pnewrel->m_Arity = prel->m_Arity;
    Check_GroupBy_Format(prel);
    for(int i=0;i< m_pAggGrpValues->Size();i++)
    {   
       Relation* ptemprel= new Relation();
       ptemprel= AddVectorFunction(prel,(*m_pAggGrpValues)[i]);

  //     cout<<*ptemprel<<endl;
       ptemprel= ComputeRelation(ptemprel);
       switch( (*m_pAggMatrix)[0][0] ) {
         case  1: /* max */
         case  3: /* MAX */
            ptemprel = ptemprel->GetMAX();
            break; 
         case  2: /* min */
         case  4: /* MIN */
	    ptemprel = ptemprel->GetMIN();
            break;
         case  5: /* sum_max */
            ptemprel = ptemprel->Get_Grp_Sum_max_min((*m_pAggGrpValues)[i] );
            break;
         case  6: /* sum_min */
	   ptemprel = ptemprel->Get_Grp_Sum_max_min((*m_pAggGrpValues)[i]);
            break;
         default:
            break;
       } 
   //    cout<<*pnewrel<<endl;
   //    cout<<*ptemprel<<endl;

       pnewrel->UnionRelation(ptemprel);
    } 
/* Reinitialize Aggregate Matrix*/
    delete m_pAggMatrix; 
    m_pAggMatrix= new Matrix<int>; 
 //   cout<<*pnewrel<<endl;
	delete prel; //KPPagg
   return pnewrel;

}

Relation* DB::AddVectorFunction(Relation* prel,float agg_value)
{
int cols;
   if(prel->SatisFlag()==1 ||prel->SatisFlag()==-1)
     {
		 ASSERT(FALSE);
        cout<<"Relation is either universally satisfiable or unsatisfiable\n";
        cout<<"Aggregate operation not possible\n";
        exit(0);
     }
   Relation* t_pr = new Relation();
   
   Matrix<float>* t_pm;
   Vector<float>* p_vec=new Vector<float>(prel->Arity()+2);
   const Matrix<float>* p_matrix1;
   *p_vec=0;
   (*p_vec)[0]=5;
   (*p_vec)[1]=agg_value;
   (*p_vec)[(*m_pAggMatrix)[0][2]+2]=1;

   DFIter<Matrix<float> >  matrixIter1(*(prel->m_tablePtr));
   t_pr->m_Arity = prel->m_Arity;   
   while(p_matrix1 =  matrixIter1()) {
        cols=p_matrix1->Cols();
        Vector<float>* tmpvec=new Vector<float>(*p_vec);

        t_pm = new Matrix<float>();
        t_pm->Resize(t_pm->Rows()+1,cols);
        (*t_pm)[0] = *tmpvec;  
        delete tmpvec;
        for(int i=0; i< p_matrix1->Rows();i++){
            t_pm->Resize(t_pm->Rows()+1,cols);
            (*t_pm)[t_pm->Rows()-1] =  (*p_matrix1)[i]; 
		}
        t_pr->AddMatrix(*t_pm);
        
   }
   
   return t_pr; 
};  

int DB::AreaHandler3(String output_name, String relname,float step,float lower, float upper)
{
 Relation* p_r;

 //RUI CHEN change
 //String* tempstr=new String(output_name); //new String("_Area");

 if((p_r=(Relation*)RetrieveRelation(relname))==0 )
   { // a new relation
      cout<<"No Relation with name \"" <<relname<<"\" exists in the (*dataBase)"<<endl;
 
      return(0);
  }
  int Arity_init = p_r->Arity(); 
  Relation* t_pr = new Relation();
  t_pr->m_Arity = 2;
  const Matrix<float>* p_matrix;
  DFIter<Matrix<float> >  matrixIter(*(p_r->m_tablePtr));
  while(p_matrix =  matrixIter()) {
		    Vector<float> vec1 = Vector<float>(4);
		    Matrix<float>* p_m = new Matrix<float>();
			for(int i=0; i< p_matrix->Rows(); i++)
			{   
				if (Arity_init>2 && (*p_matrix)[i][2]!=0) continue;
				vec1[0]=(*p_matrix)[i][0];
				vec1[1]=(*p_matrix)[i][1];
				if (Arity_init>2){
					vec1[2]=(*p_matrix)[i][3];
					vec1[3]=(*p_matrix)[i][4];
				}
				else {
					vec1[2]=(*p_matrix)[i][2];
					vec1[3]=(*p_matrix)[i][3];
				}
				(*dataBase).AddVectorToMatrix(p_m,&vec1);
			}
			t_pr->AddMatrix(*p_m);
			//m.m_pList = (*dataBase).HulConvt(p_m);
   }
   t_pr->m_Arity=2;
   if( (t_pr->m_tablePtr)->Size() !=0)
               t_pr->m_Satisfiable = 0; //Satisfiable
			   

  Relation* p_arearel = new Relation();
  Vector<float>* p_vec=new Vector<float>(4);
  Vector<float>* area_vec=new Vector<float>(5);
  *area_vec = 0;
   for(float i=lower;i<upper;i+=step)
   {  Matrix<float>* t_pm = new Matrix<float>();
      
      Relation* temp_pr=new Relation(*t_pr);
      *p_vec=0;
      (*p_vec)[0]=(*area_vec)[0]=2;
      (*p_vec)[1]=(*area_vec)[1]=-i;
      (*p_vec)[2]=(*area_vec)[2]=-1;
      (*p_vec)[3]=(*area_vec)[3]=0;
	  (*area_vec)[4]=0;

      temp_pr = temp_pr->AddVectorToRelation(this,p_vec);
      (*dataBase).AddVectorToMatrix(t_pm, area_vec);

      *p_vec=0;
      (*p_vec)[0]=(*area_vec)[0]=2;
      if(i+step<upper)
         (*p_vec)[1]=(*area_vec)[1]=i+step;
      else
         (*p_vec)[1]=(*area_vec)[1]=upper;
      
      (*p_vec)[2]=(*area_vec)[2]=1;
      (*p_vec)[3]=(*area_vec)[3]=0;
      (*area_vec)[4]=0;
      temp_pr = temp_pr->AddVectorToRelation(this,p_vec);
      (*dataBase).AddVectorToMatrix(t_pm, area_vec);

       *area_vec=0;
      (*area_vec)[0]=5;
      (*area_vec)[1]= RelationArea(temp_pr);
      (*area_vec)[4]=1;
      (*dataBase).AddVectorToMatrix(t_pm, area_vec);

      p_arearel->AddMatrix(*t_pm);
	  delete temp_pr;
   }
//   relname+=*tempstr;
   p_arearel->m_sName = output_name; //relname;  
   p_arearel->m_Arity = 3;   
	//p_arearel->m_strAtriList.AddTail(CString("i"));
	p_arearel->m_strAtriList.AddTail(CString("x"));
	p_arearel->m_strAtriList.AddTail(CString("y"));
	p_arearel->m_strAtriList.AddTail(CString("Area"));
   numRels++;
	m_pRelationList->GotoTail(); // alal added
   m_pRelationList->AppendHere(*p_arearel);
   return(1); 

}

int DB::AreaHandler(String relname,float step,float lower, float upper)
{
 Relation* p_r;
 String* tempstr=new String("_Area");

 if((p_r=(Relation*)RetrieveRelation(relname))==0 )
   { // a new relation
      cout<<"No Relation with name \"" <<relname<<"\" exists in the (*dataBase)"<<endl;
 
      return(0);
  }
  int Arity_init = p_r->Arity(); 
  Relation* t_pr = new Relation();
  t_pr->m_Arity = 2;
  const Matrix<float>* p_matrix;
  DFIter<Matrix<float> >  matrixIter(*(p_r->m_tablePtr));
  while(p_matrix =  matrixIter()) {
		    Vector<float> vec1 = Vector<float>(4);
		    Matrix<float>* p_m = new Matrix<float>();
			for(int i=0; i< p_matrix->Rows(); i++)
			{   
				if (Arity_init>2 && (*p_matrix)[i][2]!=0) continue;
				vec1[0]=(*p_matrix)[i][0];
				vec1[1]=(*p_matrix)[i][1];
				if (Arity_init>2){
					vec1[2]=(*p_matrix)[i][3];
					vec1[3]=(*p_matrix)[i][4];
				}
				else {
					vec1[2]=(*p_matrix)[i][2];
					vec1[3]=(*p_matrix)[i][3];
				}
				(*dataBase).AddVectorToMatrix(p_m,&vec1);
			}
			t_pr->AddMatrix(*p_m);
			//m.m_pList = (*dataBase).HulConvt(p_m);
   }
   t_pr->m_Arity=2;
   if( (t_pr->m_tablePtr)->Size() !=0)
               t_pr->m_Satisfiable = 0; //Satisfiable
			   

  Relation* p_arearel = new Relation();
  Vector<float>* p_vec=new Vector<float>(4);
  Vector<float>* area_vec=new Vector<float>(5);
  *area_vec = 0;
   for(float i=lower;i<upper;i+=step)
   {  Matrix<float>* t_pm = new Matrix<float>();
      
      Relation* temp_pr=new Relation(*t_pr);
      *p_vec=0;
      (*p_vec)[0]=(*area_vec)[0]=2;
      (*p_vec)[1]=(*area_vec)[1]=-i;
      (*p_vec)[2]=(*area_vec)[2]=-1;
      (*p_vec)[3]=(*area_vec)[3]=0;
	  (*area_vec)[4]=0;

      temp_pr = temp_pr->AddVectorToRelation(this,p_vec);
      (*dataBase).AddVectorToMatrix(t_pm, area_vec);

      *p_vec=0;
      (*p_vec)[0]=(*area_vec)[0]=2;
      if(i+step<upper)
         (*p_vec)[1]=(*area_vec)[1]=i+step;
      else
         (*p_vec)[1]=(*area_vec)[1]=upper;
      
      (*p_vec)[2]=(*area_vec)[2]=1;
      (*p_vec)[3]=(*area_vec)[3]=0;
      (*area_vec)[4]=0;
      temp_pr = temp_pr->AddVectorToRelation(this,p_vec);
      (*dataBase).AddVectorToMatrix(t_pm, area_vec);

       *area_vec=0;
      (*area_vec)[0]=5;
      (*area_vec)[1]= RelationArea(temp_pr);
      (*area_vec)[4]=1;
      (*dataBase).AddVectorToMatrix(t_pm, area_vec);

      p_arearel->AddMatrix(*t_pm);
	  delete temp_pr;
   }
   relname+=*tempstr;
   p_arearel->m_sName = relname;  
   p_arearel->m_Arity = 3;   
	//p_arearel->m_strAtriList.AddTail(CString("i"));
	p_arearel->m_strAtriList.AddTail(CString("x"));
	p_arearel->m_strAtriList.AddTail(CString("y"));
	p_arearel->m_strAtriList.AddTail(CString("Area"));
   numRels++;
	m_pRelationList->GotoTail(); //alal added
   m_pRelationList->AppendHere(*p_arearel);
   return(1); 

}


int DB::AreaHandler2(String relname,float step1,float lower1, float upper1,float step2,float lower2, float upper2)
{
 Relation* p_r;
 String* tempstr=new String("_Area");
 if((p_r=(Relation*)RetrieveRelation(relname))==0 )
   { // a new relation
      cout<<"No Relation with name \""<<relname<<"\" exists in the (*dataBase)"<<endl;
 
      return(0);
  }

  Relation* t_pr = new Relation(*p_r);
  Relation* p_arearel = new Relation();
  Vector<float>* p_vec=new Vector<float>(p_r->Arity()+2);
  Vector<float>* area_vec=new Vector<float>(p_r->Arity()+3);
 



   for(float i=lower1;i<upper1;i+=step1)
   {  Matrix<float>* t_pm = new Matrix<float>();
      t_pr=new Relation(*p_r);
      *p_vec=0;
      (*p_vec)[0]=(*area_vec)[0]=2;
      (*p_vec)[1]=(*area_vec)[1]=-i;
      (*p_vec)[2]=(*area_vec)[2]=-1;
      (*p_vec)[3]=(*area_vec)[3]=0;
      t_pr = t_pr->AddVectorToRelation(this,p_vec);
       (*area_vec)[4]=0;
      (*dataBase).AddVectorToMatrix(t_pm, area_vec);

      *p_vec=0;
      (*p_vec)[0]=(*area_vec)[0]=2;
      if(i+step1<upper1)
         (*p_vec)[1]=(*area_vec)[1]=i+step1;
      else
         (*p_vec)[1]=(*area_vec)[1]=upper1;
      (*p_vec)[2]=(*area_vec)[2]=1;
      (*p_vec)[3]=(*area_vec)[3]=0;
      (*area_vec)[4]=0;
      t_pr = t_pr->AddVectorToRelation(this,p_vec);
      (*dataBase).AddVectorToMatrix(t_pm, area_vec);
      for(float j=lower2;j<upper2;j+=step2)
	{ Relation* temp_rel=new Relation(*t_pr);
          Matrix<float>* temp_pm=new Matrix<float>(*t_pm);
          *p_vec=0;
          (*p_vec)[0]=(*area_vec)[0]=2;
	  (*p_vec)[1]=(*area_vec)[1]=-j;
	  (*p_vec)[2]=(*area_vec)[2]=0;
	  (*p_vec)[3]=(*area_vec)[3]=-1;
	   temp_rel =  temp_rel->AddVectorToRelation(this,p_vec);
//	  cout<<*temp_rel<<endl;
	  (*area_vec)[4]=0;
	  (*dataBase).AddVectorToMatrix(temp_pm, area_vec);

	  *p_vec=0;
	  (*p_vec)[0]=(*area_vec)[0]=2;
	  if(j+step1<upper2)
	    (*p_vec)[1]=(*area_vec)[1]=j+step2;
	  else
	    (*p_vec)[1]=(*area_vec)[1]=upper2;
	  (*p_vec)[2]=(*area_vec)[2]=0;
	  (*p_vec)[3]=(*area_vec)[3]=1;
	  (*area_vec)[4]=0;
	  temp_rel = temp_rel->AddVectorToRelation(this,p_vec);
	  (*dataBase).AddVectorToMatrix(temp_pm, area_vec);
	  
          *area_vec=0;
          (*area_vec)[0]=5;
          (*area_vec)[1]= RelationArea(temp_rel);
          (*area_vec)[4]=1;
          (*dataBase).AddVectorToMatrix(temp_pm, area_vec);

          p_arearel->AddMatrix(*temp_pm);
	}
   }
   relname+=*tempstr;
   p_arearel->m_sName = relname;  
   p_arearel->m_Arity = t_pr->m_Arity+1;   
   numRels++;
	m_pRelationList->GotoTail(); //alal added
   m_pRelationList->AppendHere(*p_arearel);
   return(1); 

}



void DB::Cpu_time()
{
	char strtime[100];
//  static clock_t last_time = 0;
  clock_t new_db_time;

extern clock_t last_db_time;
  new_db_time = clock();
 
  sprintf(strtime, "CPU Time for computation: %gs \n", (new_db_time - last_db_time) / (
				double) CLOCKS_PER_SEC);
  m_execution_time = (new_db_time - last_db_time); // (double) CLOCKS_PER_SEC;
  //	((CMainFrame*)(AfxGetApp()->GetMainWnd()))->ShowTime(strtime);
  last_db_time = new_db_time;
}                               

void fwritestr(CString str, FILE* fp)
{
	if (str!="")
		fwrite(str, sizeof(char), str.GetLength(), fp);
}

/**************************************************************
 * name:     DB::SimplexMatrixSatisfiable(Matrix* p_Matrix)
 * Time:     Feb 12, 1998
 * Descript: judge whether a matrix is satisfiable or not using
 *           Simplex method.
 * Input:    Matrix* p_Matrix
 * Output:   true, if p_Matrix is satisfiable
 *           false, otherwise
 *****************************************************/
bool DB::SimplexMatrixSatisfiable(Matrix<float>* p_matrix)
{
    lprec* lp1='\0';
    char **argv='\0';
    Vector<float> vector;

    ofstream output("satis.lp");
    if(!output){
         cerr << "Can't open file: satis.lp for satisfiability checking" << endl;
         exit(1);
    };
    
    output << "min:+1new_variable;\n";

    for(int i=0; i< p_matrix->Rows(); i++)
    {   
          vector = (*p_matrix)[i];
          if(vector[0]==0||vector[0]==3||vector[0]==4||(int)vector[0]==5)
          {
               output << "-1new_variable";
               for(int j=2; j< vector.Size(); j++)
	       { 

                  if (vector[j]>0)
	             output << "-"<<vector[j]<<(*m_pArgVector)[j-2];
                  else if (vector[j]<0)
                     output <<"+"<<fabs(vector[j])<<(*m_pArgVector)[j-2];
               }
               if(vector[1]>0) output<<"<= -"<< vector[1]<<";\n"; 
               else output<<"<= +"<< fabs(vector[1])<<";\n";
          }


          if(vector[0]==0||vector[0]==1||vector[0]==2||(int)vector[0]==5)
          {
               output << "-1new_variable";
               for(int j=2; j< vector.Size(); j++)
	       { 

                  if (vector[j]>0)
	             output << "+"<<vector[j]<<(*m_pArgVector)[j-2];
                  else if (vector[j]<0)
                     output <<vector[j]<<(*m_pArgVector)[j-2];

               }
               if(vector[1]>0) output<<"<= +"<< vector[1]<<";\n"; 
               else output<<"<= "<< vector[1]<<";\n";
          }
    }

    output << "new_variable >= 0;\n"; 
    output.close(); 

    FILE* file;
    if(!(file=fopen("satis.lp","r") )) {
          cerr << "Can't open file:" << "satis1.lp" << endl;
          exit(1);
    };
    lp1 = lp_main(lp1,1,argv,file);  
    if (fabs(lp1->best_solution[0])<=0.000001)
	{       
		delete_lp(lp1);
		p_matrix->Simplify(false);
        return true;
	}
    else
	{      
		delete_lp(lp1);
        return false;
	}
}
/*
bool DB::SimplexMatrixSatisfiable(Matrix<float>* p_matrix)
{
  
    lprec* lp1='\0';
    char **argv='\0';
    Vector<float> vector;
	CString tmp;

    FILE* output;
	if(!(output=fopen("satis.lp","wt") )) {
         AfxMessageBox( "Can't open file: satis.lp for satisfiability checking");
         exit(1);
    };
    
	fwritestr("min:+1new_variable;\n", output);

    for(int i=0; i< p_matrix->Rows(); i++)
    {   
          vector = (*p_matrix)[i];
          if(vector[0]==0||vector[0]==3||vector[0]==4||(int)vector[0]==5)
          {
			  fwritestr("-1new_variable", output);
			  for(int j=2; j< vector.Size(); j++)
			  { 
				   tmp = "";
                  if (vector[j]>0)
					  tmp.Format( "-%.6f%s", vector[j], (*m_pArgVector)[j-2].GetText());
                  else if (vector[j]<0)
					  tmp.Format("+%.6f%s",fabs(vector[j]),(*m_pArgVector)[j-2].GetText());
				fwritestr(tmp, output);
			  }
			  if(vector[1]>0) 
				   tmp.Format("<= -%.6f;\n", vector[1]); 
			  else 
				   tmp.Format("<= +%.6f;\n", fabs(vector[1]));
			  fwritestr(tmp, output);
          }


          if(vector[0]==0||vector[0]==1||vector[0]==2||(int)vector[0]==5)
          {
			   fwritestr("-1new_variable", output);
               for(int j=2; j< vector.Size(); j++)
			   { 
				   tmp = "";
                  if (vector[j]>0)
					  tmp.Format("+%.6f%s", vector[j],(*m_pArgVector)[j-2].GetText());
                  else if (vector[j]<0)
					  tmp.Format("%.6f%s",vector[j],(*m_pArgVector)[j-2].GetText());
				  fwritestr(tmp, output);
               }
		   
			   if(vector[1]>0) 
				   tmp.Format("<= +%.6f;\n", vector[1]); 
			   else 
				   tmp.Format("<= %.6f;\n", vector[1]);
			   fwritestr(tmp, output);
          }
    }

	fwritestr("new_variable >= 0;\n", output);
    fclose(output); 

    FILE* file;
    if(!(file=fopen("satis.lp","r") )) {
          AfxMessageBox("Can't open file: satis1.lp");
          exit(1);
    };
    lp1 = lp_main(lp1,1,argv,file);  
    if (fabs(lp1->best_solution[0])<=0.000001)
	{       
		delete_lp(lp1);
		p_matrix->Simplify(false);
        return true;
	}
    else
	{      
		delete_lp(lp1);
        return false;
	}
}
*/
int DB::BuffHandler(String strSRelName, String strDRelName, float d)
{
	Relation* pR;
	if((pR=(Relation*)RetrieveRelation(strSRelName))==0 )
	{ // a new relation
      TRACE0("No Such Relation ");
      return(0);
	}

	//Relation* t_pr = new Relation(*p_r);
	//Vector<float>* area_vec=new Vector<float>(p_r->Arity()+3);
 
//	CIdbDoc* pDoc = GetDocument();
//	ASSERT(pDoc != NULL);
	Relation* p_buffrel = new Relation(strDRelName);

	switch (pR->SatisFlag())
	{
	case 1  :	//strOut = "Universally Satisfiable";
				//pDC->TextOut(0, nY+=nYStep, strOut);
				break;
	case -1 :	//strOut = "Unsatisfiable";
				//pDC->TextOut(0, nY+=nYStep, strOut);
				break;
	default :

		Vector<float>* p_vec=new Vector<float>(pR->Arity()+2);

		Matrix<float>* p_matrix;
		DFIter<Matrix<float> >  matrixIter(*(pR->m_tablePtr));
		while(p_matrix =  matrixIter()) 
		{

			Slist<ParaPoint>* pointList = p_matrix->m_pList;
			if (pointList != NULL)
			{
				//LPPOINT pPoints = (LPPOINT) new POINT[pointList->len];

				Snode<ParaPoint>* nPtr = pointList->headPtr ;
				float y0 = 	nPtr->itemPtr ->m_fY;
				float x0 =	nPtr->itemPtr ->m_fX;

				if (pointList->len == 1)
				{
					//pDC->SetPixel(pPoints[0], pR->m_color);
					//CSCDrawPoly
					Matrix<float>* t_pm = new Matrix<float>();
					  //t_pr=new Relation(*p_r);
					*p_vec=0;
					/*x -x0 + 0.414214 y- 0.414214 y0 - 1 d <= 0,
					x -x0 + 2.41421 y - 2.41421 y0 - 2.41421 d <= 0,
					x -x0 -2.41421 y + 2.41421 y0 + 2.41421 d >= 0,
					x -x0 -0.414214 y +0.414214 y0 + 1 d >= 0,
					x -x0 + 0.414214 y - 0.414214 y0 + 1 d >= 0,
					x -x0 + 2.41421 y - 2.41421 y0 + 2.41421 d >= 0,
					x -x0 -2.41421 y + 2.41421 y0 - 2.41421 d <= 0,
					x -x0 -0.414214 y + 0.414214 y0 - 1 d <= 0.*/
					
					/* Removed by Shasha July'03
					(*p_vec)[0] = EQUAL;
					(*p_vec)[1] = (*p_matrix)[0][1];  // Set id value; (No necessary)
					(*p_vec)[2]= 1;
					(*dataBase).AddVectorToMatrix(t_pm, p_vec);
					*/

					//x -x0 + 0.414214 y- 0.414214 y0 - 1 d <= 0
					int x_pos=3;
					if ((*p_vec).vecSize==4) 
						x_pos=2;

					*p_vec=0;
					(*p_vec)[0]= LESSEQUAL;
					(*p_vec)[1]= (float)(x0 + 0.414214 * y0 + d);
					(*p_vec)[x_pos]= 1;
					(*p_vec)[x_pos+1]= (float)0.414214 ;
					(*dataBase).AddVectorToMatrix(t_pm, p_vec);
						
					//x -x0 + 2.41421 y - 2.41421 y0 - 2.41421 d <= 0,
					*p_vec=0;
					(*p_vec)[0]= LESSEQUAL;
					(*p_vec)[1]= (float)(x0 + 2.41421 * y0 + 2.41421 * d);
					(*p_vec)[x_pos]= 1;
					(*p_vec)[x_pos+1]= (float)2.41421 ;
					(*dataBase).AddVectorToMatrix(t_pm, p_vec);

					//x -x0 -2.41421 y + 2.41421 y0 + 2.41421 d >= 0,
					*p_vec=0;
					(*p_vec)[0]= LESSEQUAL;
					(*p_vec)[1]= (float)(-x0 + 2.41421 * y0 + 2.41421 * d);
					(*p_vec)[x_pos]= -1;
					(*p_vec)[x_pos+1]= (float)2.41421 ;
					(*dataBase).AddVectorToMatrix(t_pm, p_vec);
				
					//x -x0 -0.414214 y +0.414214 y0 + 1 d >= 0,
					*p_vec=0;
					(*p_vec)[0]= LESSEQUAL;
					(*p_vec)[1]= (float)(-x0 + 0.414214 * y0 + d);
					(*p_vec)[x_pos]= -1;
					(*p_vec)[x_pos+1]= (float)0.414214 ;
					(*dataBase).AddVectorToMatrix(t_pm, p_vec);
					
					// x -x0 + 0.414214 y - 0.414214 y0 + 1 d >= 0,
					*p_vec=0;
					(*p_vec)[0]= LESSEQUAL;
					(*p_vec)[1]= (float)(-x0 - 0.414214 * y0 + d);
					(*p_vec)[x_pos]= -1;
					(*p_vec)[x_pos+1]= (float)-0.414214 ;
					(*dataBase).AddVectorToMatrix(t_pm, p_vec);
					
					//x -x0 + 2.41421 y - 2.41421 y0 + 2.41421 d >= 0,
					*p_vec=0;
					(*p_vec)[0]= LESSEQUAL;
					(*p_vec)[1]= (float)(-x0 - 2.41421 * y0 + 2.41421 * d);
					(*p_vec)[x_pos]= -1;
					(*p_vec)[x_pos+1]=(float) -2.41421 ;
					(*dataBase).AddVectorToMatrix(t_pm, p_vec);
					
					//x -x0 -2.41421 y + 2.41421 y0 - 2.41421 d <= 0,
					*p_vec=0;
					(*p_vec)[0]= LESSEQUAL;
					(*p_vec)[1]= (float)(x0 - 2.41421 * y0 + 2.41421 * d);
					(*p_vec)[x_pos]= 1;
					(*p_vec)[x_pos+1]=(float) -2.41421 ;
					(*dataBase).AddVectorToMatrix(t_pm, p_vec);
				
					//x -x0 -0.414214 y + 0.414214 y0 - 1 d <= 0.*/
					*p_vec=0;
					(*p_vec)[0]= LESSEQUAL;
					(*p_vec)[1]= (float)(x0 - 0.414214 * y0 + d);
					(*p_vec)[x_pos]= 1;
					(*p_vec)[x_pos+1]= (float)-0.414214 ;

					(*dataBase).AddVectorToMatrix(t_pm, p_vec);
					
					t_pm->m_nTimeS = -1;  
					t_pm->m_nTimeE = -1;					
					p_buffrel->AddMatrix(*t_pm);
				}
				else
				{   //pointList->len > 1
					// assume the first row of p_matrix is  id = xxx
					Matrix<float>*  pM= new Matrix<float>(*p_matrix);

					//Vector<float>* p_vec=new Vector<float>();
					 int rows = pM->Rows();
					 for(int i=1; i< rows;i++){
						  *p_vec = (*pM)[i];
						  if( (*p_vec)[0]== EQUAL){
							  (*p_vec)[0]=LESSEQUAL;
							  (*pM)[i][0]= LESSEQUAL;
							  for(int j=1;j< p_vec->Size(); j++)
								   (*p_vec)[j]= -(*p_vec)[j];
							  (*dataBase).AddVectorToMatrix2(pM, p_vec); 
						  }
					 }     
					 //delete p_vec; //KPP
					
					Matrix<float>* t_pm = new Matrix<float>();
					  //t_pr=new Relation(*p_r);
					*p_vec=0;
					*p_vec = (*pM)[0];
					(*dataBase).AddVectorToMatrix(t_pm, p_vec);

					for( i = 1; i < pM->Rows(); i ++)
					{
						*p_vec = (*pM)[i];
						(*p_vec)[1] += d;
						(*dataBase).AddVectorToMatrix(t_pm, p_vec);
					}
					t_pm->m_nTimeS = -1;  
					t_pm->m_nTimeE = -1;					
					p_buffrel->AddMatrix(*t_pm);
					delete pM;
				}
			}
		} // while
		delete p_vec;
		
	} // switch

	POSITION pos = pR->m_strAtriList.GetHeadPosition();
	while (pos != NULL)
	{
		   p_buffrel->m_strAtriList.AddTail(CString(pR->m_strAtriList.GetNext(pos)));
	}
	
//   p_buffrel->m_strAtriList.AddTail(CString("y"));
   p_buffrel->m_Arity = pR->m_Arity;   
   numRels++;
   m_pRelationList->GotoTail(); //alal added
   m_pRelationList->AppendHere(*p_buffrel);

  return(1); 
}

void DB::STDBClauseHandler()	//for STDB clause handling DRK
{
	Relation *rel1,*rel2;
	if(relCtr==0)
	{
		ClauseHandler();
		return;
	}
	evalnList *ptr=m_pEvalnList;
	while(ptr!=NULL)
	{
		SetMatrixTime();
		rel1=(Relation*)RetrieveRelation(*(ptr->opnd1));
		rel2=(Relation*)RetrieveRelation(*(ptr->opnd2));
		if(*(ptr->optr)=="+")
		{
			int timeS=32000,timeE=0;
			Relation* ptempRel =  new Relation(*(ptr->result));  
			ptempRel->m_Satisfiable = -1;
			ptempRel->m_nTimeS=timeS;//DRK
			ptempRel->m_nTimeE=timeE;//DRK
			if(rel1->NumberOfMatrixes()!=0)
				ptempRel->UnionRelation(rel1);
			ptempRel->m_nTimeS=min(ptempRel->m_nTimeS,rel1->m_nTimeS);//DRK
			ptempRel->m_nTimeE=max(ptempRel->m_nTimeE,rel1->m_nTimeE);//DRK
			if(rel2->NumberOfMatrixes()!=0)
				ptempRel->UnionRelation(rel2);
			ptempRel->m_nTimeS=min(ptempRel->m_nTimeS,rel2->m_nTimeS);//DRK
			ptempRel->m_nTimeE=max(ptempRel->m_nTimeE,rel2->m_nTimeE);//DRK
			POSITION pos = (rel1->m_strAtriList).GetHeadPosition();
			while(pos != NULL)
			{
				CString s = (rel1->m_strAtriList).GetNext(pos);
				ptempRel->m_strAtriList.AddTail(s);
			}
			numRels++;
			m_pRelationList->GotoTail();		//new line 6/23
			m_pRelationList->AppendHere(*ptempRel);
			//delete ptempRel;
			ptempRel=NULL;
		}
		if(*(ptr->optr)=="*")
		{
			rel1 = rel1->RelationIntersect(rel2);
			rel1->m_Arity=rel2->m_Arity;
			rel1->m_sName=*(ptr->result);

			if(rel1->NumberOfMatrixes()==0)
				rel1->m_Satisfiable = -1;
			POSITION pos = (rel2->m_strAtriList).GetHeadPosition();
			while(pos != NULL)
			{
				CString s = (rel2->m_strAtriList).GetNext(pos);
				rel1->m_strAtriList.AddTail(s);
			}

			numRels++;
			m_pRelationList->GotoTail();		//new line 6/23
			m_pRelationList->AppendHere(*rel1);
		}
		if(*(ptr->optr)=="-")					//does not work due to MVal problem
		{
			rel1 = rel1->RelationComplement(rel1);
			rel2 = rel2->RelationIntersect(rel1);
			
			rel2->m_sName=*(ptr->result);

			if(rel2->NumberOfMatrixes()==0)
				rel2->m_Satisfiable = -1;

			numRels++;
			m_pRelationList->GotoTail();		//new line 6/23
			m_pRelationList->AppendHere(*rel2);
		}
		if(*(ptr->optr)=="r")
		{
			Relation *ptempRel=new Relation(*rel1);
			ptempRel->m_sName=*(ptr->result);
			POSITION pos = (rel1->m_strAtriList).GetHeadPosition();
			while(pos != NULL)
			{
				CString s = (rel1->m_strAtriList).GetNext(pos);
				ptempRel->m_strAtriList.AddTail(s);
			}
			Arg *tmp;
			int listct=0;CString s;
			SlistIter<Arg> arg_iter(*(ptr->arg_list));
			pos = (ptempRel->m_strAtriList).GetHeadPosition();
			while(tmp=arg_iter())
			{
				if(listct<8)
				{
					(ptempRel->m_strAtriList).GetNext(pos);
					listct++;
					continue;
				}
				else
				{
					s = (ptempRel->m_strAtriList).GetAt(pos);
					(ptempRel->m_strAtriList).SetAt(pos,(const char *)(tmp->strPtr->GetText()));
					(ptempRel->m_strAtriList).GetNext(pos);
				}
			}	
			numRels++;
			m_pRelationList->GotoTail();		//new line 6/23
			m_pRelationList->AppendHere(*ptempRel);
		}
		if(*(ptr->optr)=="p")
		{
			Relation *ptempRel=new Relation(*rel1);
			CString s,s2;
			int ctr=0;
			CStringList p_list,p_list2;
			int timeS,timeE;
			timeS=rel1->m_nTimeS;
			timeE=rel1->m_nTimeE;
			int listct=0,p_arity=0;
			if(strcmp(ptr->p_list->GetText(),"")==0)
			{
				p_list2.AddTail(&(rel1->m_strAtriList));
				POSITION pos = p_list2.GetHeadPosition();
				while(pos!=NULL)
				{
					if(listct<8)
					{
						s=p_list2.GetAt(pos);
						p_list2.GetNext(pos);
						p_list.AddTail(s);
						p_arity++;
						listct++;
						continue;
					}
					else
					{						
						ptempRel=VarElimination(ptempRel,listct-ctr);
						ctr++;
						listct++;
						p_list2.GetNext(pos);
					}
				}	
			}
			else
			{
				p_list2.AddTail(&(rel1->m_strAtriList));
				POSITION pos = p_list2.GetHeadPosition();
				while(pos!=NULL)
				{
					if(listct<8)
					{
						s=p_list2.GetAt(pos);
						p_list2.GetNext(pos);
						p_list.AddTail(s);
						p_arity++;
						listct++;
						continue;
					}
					else
					{						
						s=p_list2.GetAt(pos);
						s2=s+",";
						if(strstr(ptr->p_list->GetText(),s2)==NULL)						
						{
							ptempRel=VarElimination(ptempRel,listct-ctr);
							ctr++;
						}
						else
						{
							p_arity++;
							p_list.AddTail(s);
						}
						listct++;
						p_list2.GetNext(pos);
					}
				}
			}

			numRels++;
			ptempRel->m_sName=*(ptr->result);
			ptempRel->m_Arity=p_arity;
			ptempRel->m_strAtriList.AddTail(&p_list);
			ptempRel->m_nTimeS=timeS;
			ptempRel->m_nTimeE=timeE;
			m_pRelationList->GotoTail();		//new line 6/23
			m_pRelationList->AppendHere(*ptempRel);
		}
		if(*(ptr->optr)=="s")
		{
			Vector<CString> *indvec = new Vector<CString>(rel1->m_Arity);
			Relation *ptempRel=new Relation;
			ptempRel->m_sName=*(ptr->result);
			POSITION pos = (rel1->m_strAtriList).GetHeadPosition();
			int mctr=0;
			while(pos != NULL)
			{
				CString s = (rel1->m_strAtriList).GetNext(pos);
				ptempRel->m_strAtriList.AddTail(s);
				(*indvec)[mctr]=*new CString(s);
				mctr++;
			}
			Matrix<float> *mod_matx = new Matrix<float>(0,indvec->Size()+2);
			String *m_pstr=new String(*(ptr->p_list));
			int length=0,ind=0;
			for(int i=0;i<ptr->p_list->Length();i++)
			{
				if((*(ptr->p_list))[i]==',')
				{
					CString *s1=new CString((const char *)m_pstr->GetText());
					CString s2=(*s1).Mid(ind,length);
					int k=indvec->Search(s2);
					length=0;
					ind=i+1;	
					mod_matx->Resize(mod_matx->Rows()+1,mod_matx->Cols());
					(*mod_matx)[mod_matx->Rows()-1]=0;
					//bug fix 11/16
					float mval;
					int mx=(*ptr->s_matrix).Cols();
					for(int mctr=2;mctr<mx;mctr++)
					{
						if((*ptr->s_matrix)[mod_matx->Rows()-1][mctr]!=0)
						{
							mval=(*ptr->s_matrix)[mod_matx->Rows()-1][mctr];
							break;
						}
					}
					//char strx[100];
					//sprintf(strx,"value of mval = %f",mval);
					//AfxMessageBox(strx);
					// end of bug fix
					(*mod_matx)[mod_matx->Rows()-1][k+2]=mval;
					(*mod_matx)[mod_matx->Rows()-1][0]=(*ptr->s_matrix)[mod_matx->Rows()-1][0];
					(*mod_matx)[mod_matx->Rows()-1][1]=(*ptr->s_matrix)[mod_matx->Rows()-1][1];
				}
				else
					length++;
			}
			DoHull=FALSE;
			ptr->s_matrix->Trace();
			mod_matx->Trace();
			ptempRel= ptempRel->CombineMatrix(mod_matx);
			DoHull=TRUE;
			ptempRel=ptempRel->CombineRelation(rel1);
			pos = (rel1->m_strAtriList).GetHeadPosition();
			while(pos != NULL)
			{
				CString s = (rel1->m_strAtriList).GetNext(pos);
				ptempRel->m_strAtriList.AddTail(s);
			}
			ptempRel=ptempRel->DoSelectOpn(mod_matx->Rows());
			numRels++;
			ptempRel->m_sName=*(ptr->result);
			ptempRel->m_Arity=rel1->m_Arity;
			m_pRelationList->GotoTail();		//new line 6/23
			m_pRelationList->AppendHere(*ptempRel);
		}
		ptr=ptr->next;
	}
	char lastres[20];
	sprintf(lastres,"%d",relCtr-1);
	rel1=(Relation*)RetrieveRelation(String(lastres));
	rel1->m_sName=(*m_pRelNameVec)[0];
	for(int i=0;i<=relCtr-2;i++)
	{
		sprintf(lastres,"%d",i);
		numRels--;
		DeleteRelation(String(lastres));
	}
	relCtr=0;
	m_pEvalnList=NULL;
	m_ArgList.DeepDestroy();
    m_pVecLine->Resize(0);
	if(m_pMatrix!= NULL)
		delete m_pMatrix;
    m_pMatrix = new Matrix<float>();
    m_pArgVector->Resize(0);
    m_pRelNameVec->Resize(0);
    m_sName = String(); 
    delete m_pEqualMatrix; 
	m_pEqualMatrix= new Matrix<int>();
	return;
}

void DB::AddEvalRow(const char *op1,const char *op2,const char *res,const char *opr)
{
	if(m_pEvalnList==NULL)
	{
		m_pEvalnList=new evalnList;
		m_pEvalnList->next=NULL;
		m_pEvalnList->opnd1=new String(op1);
		m_pEvalnList->opnd2=new String(op2);
		m_pEvalnList->result=new String(res);
		m_pEvalnList->optr=new String(opr);
		if(strcmp(opr,"r")==0)
			(*m_pEvalnList).arg_list=new Slist<Arg>(m_ArgList);
		if(strcmp(opr,"p")==0)
			(*m_pEvalnList).p_list=new String(op2);
		if(strcmp(opr,"s")==0)
		{
			(*m_pEvalnList).p_list=new String(op2);
			(*m_pEvalnList).s_matrix=new Matrix<float>((*selMatVec)[selMatVec->Size()-1]);
			selMatVec->Resize(selMatVec->Size()-1);
		}
	}
	else
	{
		evalnList *neweval=new evalnList;
		neweval->opnd1=new String(op1);
		neweval->opnd2=new String(op2);
		neweval->result=new String(res);
		neweval->optr=new String(opr);
		neweval->next=NULL;
		if(strcmp(opr,"r")==0)
			(*neweval).arg_list=new Slist<Arg>(m_ArgList);
		if(strcmp(opr,"p")==0)
			(*neweval).p_list=new String(op2);
		if(strcmp(opr,"s")==0)
		{
			(*neweval).p_list=new String(op2);
			(*neweval).s_matrix=new Matrix<float>((*selMatVec)[selMatVec->Size()-1]);
			selMatVec->Resize(selMatVec->Size()-1);
		}
		evalnList *tmp=m_pEvalnList;
		while(tmp->next!=NULL)
			tmp=tmp->next;
		tmp->next=neweval;
		tmp=NULL;
	}
}

void DB::SetMatrixTime()
{
	if (!numRels) 
		return; 
	else
	{
		BOOL bSet = FALSE;
		SlistIter<Relation> relationListIter(*m_pRelationList);
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
					if (p_matrix->Cols() <= 5)
					{	
						p_matrix->m_nTimeS = -1;
						p_matrix->m_nTimeE = -1;
						continue;
					}
	
					BOOL bMinT = FALSE;
					BOOL bMaxT = FALSE;
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
					if (!bMinT)
						p_matrix->m_nTimeS = 0;
					if (!bMaxT)
						p_matrix->m_nTimeE = p_matrix->m_nTimeS;
					p_matrix->m_nCurrent = /*p_matrix->m_nTimeS*/ - 1;

					/*if (!bSet)
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
					}*/

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

/* new algorithm from here onwards DRK */
// return ((!p_rmat && ptempRelmat)!=0)
bool DB::polyhedron_containment(Relation *p_oldC, Matrix<float> *p_rmat, Matrix<float> *ptempRelmat)
{

			Snode<Matrix<float> >* nptr;				//for traversing chkmatlist

			if (*ptempRelmat == *p_rmat)	
				return FALSE;               //if no new facts,then return 

			Matrix<float>* p_r_matrix=new Matrix<float>(*p_rmat);
			Matrix<float>* tempRelmatrix=new Matrix<float>(*ptempRelmat);

			int m_i=0;
			int index=tempRelmatrix->Rows();
			int index2=p_r_matrix->Rows();
			
			Slist<Matrix<float> >* chkmatlist=new Slist<Matrix<float> >;
			for(m_i=0;m_i<index2;m_i++)
			{
				bool satisfiable=FALSE;

				//negate the constraint before adding it
				//Question: how to handle equality constraints???
				//Answer: the negation of '=' is the union of '<' and '>'
				Vector<float>* curr_row=new Vector<float>((*p_r_matrix)[m_i]);

				if ((*curr_row)[0]!=5)  //negation of inequality vector
				{
					if ((*curr_row)[0]==1)
						(*curr_row)[0]=2;
					else					//Question: ?
					if ((*curr_row)[0]==2)
						(*curr_row)[0]=1;

					for (int m_j=1; m_j<p_r_matrix->Cols(); m_j++)
						(*curr_row)[m_j] = - (*curr_row)[m_j];

					chkmatlist->AppendHere(*new Matrix<float> (*tempRelmatrix));
					nptr=chkmatlist->curPtr; //headPtr;
					AddVectorToMatrix2(nptr->itemPtr,curr_row);
				}
				else if ((*curr_row)[0]==5) //negation of equality vector
				{
					Vector<float>* dubs=new Vector<float>(*curr_row);
					//(*dubs)=(*curr_row);
					(*dubs)[0]=1;
					chkmatlist->AppendHere(*new Matrix<float> (*tempRelmatrix));
					nptr=chkmatlist->curPtr; //headPtr;
					AddVectorToMatrix2(nptr->itemPtr,dubs);
					delete dubs;

					dubs=new Vector<float>(*curr_row);
					//(*dubs)=(*curr_row);
					(*dubs)[0]=1;
					for (int t_i=1;t_i<p_r_matrix->Cols();t_i++)
						(*dubs)[t_i] = - (*dubs)[t_i];
					chkmatlist->AppendHere(*new Matrix<float> (*tempRelmatrix));
					nptr=chkmatlist->curPtr; //headPtr;
					AddVectorToMatrix2(nptr->itemPtr,dubs);
					delete dubs;
				}

				delete curr_row;

				Relation *dummyRel=new Relation();
				nptr=chkmatlist->headPtr;
				while(nptr!=NULL)
				{
					dummyRel->AddMatrix(*new Matrix<float>(*(nptr->itemPtr)));
					nptr=nptr->nextPtr;
				}
				satisfiable=(bool)dummyRel->NumberOfMatrixes();
				delete dummyRel;
				chkmatlist->DeepDestroy();
				if (satisfiable==TRUE)
				{
					//p_oldC->AddMatrix(*tempRelmatrix);
					delete chkmatlist;
					// possibly delete p_r_matrix and tempRelmatrix Here
					delete p_r_matrix; // wm 06/25/06 created but not used or deleted
					delete tempRelmatrix;  // wm 06/25/06 created but not used or deleted
					return TRUE;
				}
			}
			chkmatlist->DeepDestroy();
			delete chkmatlist;
			// possibly delete p_r_matrix and tempRelmatrix Here
			delete p_r_matrix; // wm 06/25/06 created but not used or deleted
			delete tempRelmatrix;  // wm 06/25/06 created but not used or deleted

			return FALSE;//((bool)p_oldC->NumberOfMatrixes());	
}

bool DB::check_containment(Relation *p_oldC, Relation *p_r, Relation *ptempRel)
{
	_heapmin();
			
	//=============== p_newC = ptempRel - p_r ================================
			Relation *p_newC=new Relation();
			(*p_newC)=(*p_oldC); //SA: memory leak? - no just a copy I think
			
			Snode<Matrix<float> >* nptr;				//for traversing chkmatlist

			DFIter<Matrix<float> >  tempRel_matrixIter(*(ptempRel->m_tablePtr));//latest facts
			DFIter<Matrix<float> >  p_r_matrixIter(*(p_r->m_tablePtr));			//previous facts	
			Matrix<float>* p_r_matrix;
			Matrix<float>* tempRel_matrix;
			bool chkflag=FALSE;
			//SA: IF WE COULD INDEX THE FACTS: this would be a much more efficient process!!!
			//SA: while there is another matrix (fact) from the new facts iterator...
			while(tempRel_matrix=tempRel_matrixIter())	//disregard all the repeated facts
			{
				bool disreg=FALSE;
				//SA: while there is another matrix (fact) from the old facts iterator...
				while(p_r_matrix=p_r_matrixIter())
				{
					if (*tempRel_matrix == *p_r_matrix)	
					{
						disreg=TRUE;						//old fact, so disregard
						break;
					}
				}

				if (disreg==FALSE)
				{
					//p_newC->CombineMatrix(tempRel_matrix);
					p_newC->AddMatrix(*new Matrix<float>(*tempRel_matrix));
					chkflag=TRUE;
				}

				p_r_matrixIter.Reset();
			}
			if (chkflag==FALSE)			//if no new facts,then return
			{
				delete p_newC;
				return FALSE;
			}
	//=============== p_newC = ptempRel - p_r ================================

			Matrix<float>* tmpmat=new Matrix<float>();
			Relation *retrel=new Relation();
			Matrix<float>* newC_matrix;
			DFIter<Matrix<float> >  newC_matrixIter(*(p_newC->m_tablePtr));
			while(newC_matrix=newC_matrixIter())
			{
				p_r_matrixIter.Reset();
				Slist<Matrix<float> >*  Ctmp=new Slist<Matrix<float> >;
				Ctmp->AppendHere(*new Matrix<float>(*newC_matrix));

				while(p_r_matrix=p_r_matrixIter())
				{
					nptr=Ctmp->headPtr;
					//Ctmp=Ctmp->GotoHead();
					while(nptr!=NULL)
					{
						tmpmat->Copy(*(nptr->itemPtr));
						bool cont=FALSE;
						//p_r_matrix->Trace();	//Shasha: remove to improve speed
						//tmpmat->Trace();		//Shasha: remove to improve speed
						cont=polyhedron_containment(NULL,p_r_matrix,tmpmat);

						Snode<Matrix<float> >* tmpptr=nptr->nextPtr;

						//cont=PerformIteration(tmpnew,tmprel2,tmprel1);
						if (cont==FALSE)
						{
							Ctmp->Delete(*(nptr->itemPtr));
							//Ctmp->Delete();
						}
						nptr=tmpptr;
					}
					if (Ctmp->Size()==0){
						Ctmp->DeepDestroy();
						delete Ctmp;
						Ctmp = NULL;
						//continue; //
						goto end;//return FALSE;
						}
					else
					{
						Slist<Matrix<float> >*  Ctmp2=new Slist<Matrix<float> >;
						nptr=Ctmp->headPtr;
						
						while (nptr!=NULL)
						{ 
							//Relation *retrel=new Relation();
							retrel->EmptyMatrix();
							if (check_disjoint(p_r_matrix,nptr->itemPtr)==FALSE)
								retrel=linear_partition(p_r_matrix,nptr->itemPtr);
							else
								retrel->AddMatrix(*new Matrix<float>(*(nptr->itemPtr)));
							Matrix<float>* ret_matrix;
							DFIter<Matrix<float> >  ret_matrixIter(*(retrel->m_tablePtr));
							while (ret_matrix=ret_matrixIter())
							{
								Ctmp2->AppendHere(*new Matrix<float>(*ret_matrix));
								//Ctmp2->AppendHere(*ret_matrix);
							}
							//delete retrel;
							//retrel = NULL;
							nptr=nptr->nextPtr;
						}
						
						Ctmp->DeepDestroy();
						delete Ctmp;
						Ctmp = NULL;
						Ctmp=new Slist<Matrix<float> >(*Ctmp2);
						
						Ctmp2->DeepDestroy();
						delete Ctmp2;
						Ctmp2 = NULL;
					}
				}
				
				Ctmp->DeepDestroy();
				delete Ctmp;
				Ctmp = NULL;
				p_oldC->AddMatrix(*new Matrix<float>(*newC_matrix));
end:			int xx=0;
			}
			//(*p_oldC) = (*p_newC);
			delete retrel;
			retrel = NULL;
			delete tmpmat;
			tmpmat = NULL;
			delete p_newC;
			p_newC = NULL;
			return((bool)p_oldC->NumberOfMatrixes());
}


bool DB::check_disjoint(Matrix<float> *c1,Matrix<float> *c2)
{
	Matrix<float> *m1=new Matrix<float>(*c1);
	Matrix<float> *m2=new Matrix<float>(*c2);
	Relation *dummy=new Relation;

	for (int i=0;i<m2->Rows();i++)
		AddVectorToMatrix2(m1,&(*m2)[i]);
	//m1->Trace(); //Shasha: remove to improve speed
	dummy->AddMatrix(*m1);
	//if(dummy->NumberOfMatrixes()==1)
	int nm = dummy->NumberOfMatrixes();
	delete m2;
	delete dummy;
	if(nm ==1)
		return FALSE;
	else
		return TRUE;
}


Relation * DB::linear_partition(Matrix<float> *c1,Matrix<float> *c2)
{
	//Relation *retRel=new Relation();
	//Matrix<float> *pmatx=new Matrix<float>(*c2);
	int index;
	Snode<Matrix<float> >* nptr;
	int m1=c1->Rows();
	//Vector<float> *tmp=new Vector<float>;
	Relation *dummyRel=new Relation();
	for (index=m1-1;index>=0;index--)
	{
					Matrix<float>* chk_matrix=new Matrix<float>;
					Slist<Matrix<float> >* chkmatlist=new Slist<Matrix<float> >;
					chkmatlist->AppendHere(*new Matrix<float>(*c2));
		for (int m_i=index-1;m_i>=0;m_i--)
		{
			//(*tmp)=(*c1[j-1]);
			//AddVectorToMatrix2(pmatx,tmp);
			nptr=chkmatlist->headPtr;
			while (nptr!=NULL)
			{
				AddVectorToMatrix2(nptr->itemPtr,&((*c1)[m_i]));
				nptr=nptr->nextPtr;
			}
		}
					Vector<float>* curr_row=new Vector<float>();
					(*curr_row)=((*c1)[index]);
					if ((*curr_row)[0]!=5)
					{
						if ((*curr_row)[0]==1)
							(*curr_row)[0]=2;
						if ((*curr_row)[0]==2)
							(*curr_row)[0]=1;
						for (int m_j=1;m_j<c1->Cols();m_j++)
							(*curr_row)[m_j]=0 - (*curr_row)[m_j];
						nptr=chkmatlist->headPtr;
						while(nptr!=NULL)
						{
							AddVectorToMatrix2(nptr->itemPtr,curr_row);
							nptr=nptr->nextPtr;
						}
					}
					else if ((*curr_row)[0]==5)
					{
						nptr=chkmatlist->headPtr;
						while (nptr!=NULL)
						{
							Vector<float>* dubs=new Vector<float>();
							(*dubs)=(*curr_row);
							(*dubs)[0]=1;
							Matrix<float>* t_mat=new Matrix<float>(*(nptr->itemPtr));
							AddVectorToMatrix2(nptr->itemPtr,dubs);
							Vector<float>* dubs2=new Vector<float>(*dubs);
							for (int t_i=1;t_i<t_mat->Cols();t_i++)
								(*dubs2)[t_i]=0 - (*dubs2)[t_i];
							AddVectorToMatrix2(t_mat,dubs2);
							chkmatlist->AppendHere(*new Matrix<float>(*t_mat));
							nptr=nptr->nextPtr;
							nptr=nptr->nextPtr;
							delete dubs;
							delete dubs2;
							delete t_mat;
						}
					}
					delete curr_row;
					nptr=chkmatlist->headPtr;
					//int prevno=dummyRel->NumberOfMatrixes();
					while(nptr!=NULL)
					{
						dummyRel->AddMatrix(*new Matrix<float>(*(nptr->itemPtr)));
						nptr=nptr->nextPtr;
					}
					//satisfiable=(bool)(dummyRel->NumberOfMatrixes() - prevno);
					//delete dummyRel;
					delete chk_matrix;
				//	nptr=chkmatlist->headPtr;
				//	while(nptr!=NULL)
				//	{
				//		(nptr->itemPtr)=NULL;
				//		nptr=nptr->nextPtr;
				//	}
					chkmatlist->DeepDestroy();
					delete chkmatlist;
	}
	return dummyRel;
}


/*******************************************************
 * Name:	 DB::CheckRecursiveClause()
 * Time:	
 * Descrpn:	 Checks if the current clause is one that
 *			 requires recursive evaluation or not
 *			 It makes use of RelNameVec.
 *			 It returns true if Clause is recursive and
 *			 false otherwise.
 *******************************************************/
bool DB::CheckRecursiveClause()
{
	/* check using RelNameVec, if the name of the head predicate is repeated
	   in the body. if so, this means that the clause is recursive */
	int m_size = m_pRelNameVec->Size();
	String this_name=(*m_pRelNameVec)[0];
	for(int m_i = 1; m_i < m_size; m_i++)
		if (this_name==(*m_pRelNameVec)[m_i])	//head predicate is repeated => recursive
			return(TRUE);
	return(FALSE);								//head predicate is not repeated
}


