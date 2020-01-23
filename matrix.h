/***************************************************
 * Name:     matrix.h
 * Author:   copy from disco system
 * Time:     April 6, 1997
 * Descript: define of class Matrix
 *
 ***************************************************/

#ifndef MATRIX_H
#define MATRIX_H

#include "GlobalVar.h"
//#define EQUAL       5
//#define LESSEQUAL   2
//#define LESSTHAN	1
//#define GREATEQUAL  4
//#define GREATTHAN   3
//#define STREQUAL   5.5
//#define FLOAT_ZERO 0.0005

#include "vector.h"
#include "afxtempl.h"

#include "db.h"       //RUICHEN
extern DB* dataBase;  //RUICHEN

class CSCDrawObj;
class ParaPoint;
class Slist;
template <class T>
class Matrix
{
protected :
	int numRows ;
	int numCols ;


public:
	Vector<T>** matPtr ;   // first * is a vector to a vector* 
	Slist<ParaPoint>* m_pList;   
	COLORREF m_color;		// for output color
	CSCDrawObj*	m_pDrawObj;		//

	friend ostream& operator << (ostream&, Matrix<T>&) ;

	int	m_nTimeS;	// start time t		02.04.98
	int	m_nTimeE;	// end time t
	int m_nCurrent;	// current time t

	int m_Period;			//for the period DRK
	int m_PeriodStart;		//for the extended periodic model

	void RecalcPoints(int nTime);	// recalculate para-points
	BOOL DoCheckPointsSatisfiable();	// check points satisfiable
	void RegeneratePoints(int nTime);	// if the no. of points changed, re gen
	int find_next(int current, CArray<double> *final_x, CArray<int>* temp_e1, CArray<int>* temp_e2, CArray<int> *final_e1, CArray<int> *final_e2);
	CString FindPolygonPoints(bool SimplficationOnly, CArray<double> *cx, CArray<double> *cy, CArray<double> *ct, CArray<double> *order_x, CArray<double> *order_y);

	void Trace();
	void TraceNoEqual();
	void Simplify(boolean create_equality);

	Matrix() 
	{	matPtr = (Vector<T>**) 0 ; 
		numRows = numCols = 0 ; 
		m_color=RGB(0,0,0); //RUICHEN
		m_pList=NULL;
		m_nTimeS = -1;
		m_nTimeE = -1;
		m_nCurrent = -1;
		m_Period = -1;
	}
	Matrix(const Matrix<T>&) ;
	Matrix(const int&, const int&) ;
	~Matrix() ;

	Vector<T>& operator[] (const int& i)
    { 
		if ((i < 0) || (i >= numRows))
		{ 
			ASSERT(FALSE);
			cout << "Matrix : illegal index " << i << " for matrix of size " 
				<< numRows << "x" << numCols << endl ; 
			exit(0) ; 
		}
		return *(matPtr[i]) ;
	}

	const Vector<T>& operator[] (const int& i) const
    { 
		if ((i < 0) || (i >= numRows))
		{ 
			ASSERT(FALSE);
			cout << "Matrix : illegal index " << i << " for matrix of size " 
				<< numRows << "x" << numCols << endl ; 
			exit(0) ; 
		}
		return *(matPtr[i]) ;
	}

	void EqlToInEql();
	Matrix<T>& operator = (const Matrix<T>&) ;
	Matrix<T>& operator = (const T&) ;
//   Matrix<T>& operator = (T&) ;
	bool operator == (const Matrix<T>&) const ;
	bool operator != (const Matrix<T>& m) const { return
                                            (*this == m) ? false : true ; }
	void Transpose();

	void Del(Slist<int> *l, int); 
	void DelVector(CArray<int> *l, int cols);
	void Resize(const int&, const int&) ;
	int Rows() const { return numRows ; }
	int Cols() const { return numCols ; }
	bool Copy(const Matrix<T>&m) ;
//	void Transpose() ;

} ;


template <class T>
Matrix<T>::Matrix(const Matrix<T>& m)
 {
   numRows = m.numRows ;
   numCols = m.numCols ;
   if((*dataBase).GIS) 
   {
	   m_color=m.m_color; //RUICHEN
   }
   matPtr = new Vector<T>* [numRows] ;
   for (int i = 0 ; i < numRows ; i++)
		matPtr[i] = new Vector<T>(*(m.matPtr[i])) ;
   m_pList = NULL;
	
	m_Period=m.m_Period;//changed for period
	m_PeriodStart=m.m_PeriodStart;//for the extended periodic model

	/*m_nTimeS = -1;//changed for period
	m_nTimeE = -1;*/
    m_nTimeS = m.m_nTimeS;
	m_nTimeE = m.m_nTimeE;
	m_nCurrent = -1;
 }

/*==============================================================================
==============================================================================*/

template <class T>
Matrix<T>::Matrix(const int &r, const int &c)
 {
  numRows = r ;
  numCols = c ;
  m_color=RGB(0,0,0); //RUICHEN
  matPtr = new Vector<T>* [numRows] ;
  for (int i = 0 ; i < numRows ; i++)
   matPtr[i] = new Vector<T>(numCols) ;
  m_pList = NULL;

	m_nTimeS = -1;
	m_nTimeE = -1;
	m_nCurrent = -1;
 }

/*==============================================================================
==============================================================================*/

template <class T>
Matrix<T>::~Matrix()
{
	for (int i = 0 ; i < numRows ; i++)
		delete matPtr[i];
	if (numRows != 0)
		delete [] matPtr;

	if (m_pList != NULL)
	{
		m_pList->DeepDestroy();
		delete m_pList;
	}
 }

/*==============================================================================
==============================================================================*/
template <class T>
void Matrix<T>::EqlToInEql () 
{
    Vector<float>* p_vec=new Vector<float>();
     int rows = this->Rows();
     for(int i=0; i< rows;i++){
          *p_vec = (*this)[i];
          if( (*p_vec)[0]== 5){
              (*p_vec)[0]=2;
              (*this)[i][0]= 2;
              for(int j=1;j< p_vec->Size(); j++)
                   (*p_vec)[j]= -(*p_vec)[j];
              (*dataBase).AddVectorToMatrix2(this, p_vec); 
          }
     }     
	 delete p_vec; //KPP
}

template <class T>
Matrix<T>& Matrix<T>::operator = (const Matrix<T>& m)
{
	if (this == &m)
		return *this ;

	for (int i = 0 ; i < numRows ; i++)
		delete matPtr[i] ;
	if (numRows > 0)
		delete [] matPtr ;

	numRows = m.numRows ;
	numCols = m.numCols ;
	if((*dataBase).GIS) m_color=m.m_color; //RUICHEN
	matPtr = new Vector<T>* [numRows] ;

	for (i = 0 ; i < numRows ; i++)
		matPtr[i] = new Vector<T>(*(m.matPtr[i])) ;
  
	return *this ;
 }

/*==============================================================================
==============================================================================*/

template <class T>
Matrix<T>& Matrix<T>::operator = (const T& c)
{
	for (int i = 0 ; i < numRows ; i++)
		*(matPtr[i]) = c ;

	return (*this) ;
}

/*==============================================================================
==============================================================================*/

template <class T>
bool Matrix<T>::operator == (const Matrix<T>& m) const
 {
  bool equal = false; 
  if ((numRows == m.numRows) && (numCols == m.numCols))
  {
    for (int i = 0 ; i < numRows ; i++)
    {
       for(int j = 0; j < numRows; j++)
       {
	  if (*(matPtr[i]) == *(m.matPtr[j]))
           {
             equal=true;
             break;
	   }
       }
       if(equal == false) 
           return false;
       else 
           equal = false;   
    }             
    return true ;
  }
  return false ;
 }


/*==============================================================================
==============================================================================*/
template <class T>
void Matrix<T>::DelVector(CArray<int> *l, int cols) 
{
	int j=0;
	Matrix<float>* tmpmat=new Matrix<float>();
	tmpmat->Resize(numRows - l->GetCount(), numCols);

	int k=0;
	for (int i=0; i<numRows; i++)
	{
		if (j<l->GetCount() && l->GetAt(j)==i)
			j++;
		else {
			tmpmat->matPtr[k] = new Vector<T>(*(matPtr[i]));
			k++;
		}
	}
	//delete matPtr;
	for (int i = 0 ; i < numRows ; i++)
		delete matPtr[i] ;
	if (numRows > 0)
		delete [] matPtr ;

	numRows = tmpmat->numRows ;
	numCols = tmpmat->numCols ;
	if((*dataBase).GIS) m_color=tmpmat->m_color; //RUICHEN
	matPtr = new Vector<T>* [numRows] ;

	for (i = 0 ; i < numRows ; i++)
		matPtr[i] = new Vector<T>(*(tmpmat->matPtr[i])) ;

	delete tmpmat;

}

template <class T>
void Matrix<T>::Del(Slist<int> *l, int cols) 
{
	int cnt = 0;
	int *j;
	l->GotoHead();
	SlistIter<int> lstitr(*l);
	while(j=lstitr()) {
		*j-=cnt;
		if (*j+1 < numRows) {
			for (int i=*j; i<numRows-1; i++) {
				Vector<float> *dvecPtr = matPtr[i];
				Vector<float> *mvecPtr = matPtr[i+1];
				dvecPtr->Copy(*mvecPtr);
				
			}
			int rows = numRows-1;
			Resize(rows, numCols);
		}
		else {
			int rows = numRows-1;
			Resize(rows, numCols);
		}
		cnt++;
	}

}
/*==============================================================================
==============================================================================*/

template <class T>
void Matrix<T>::Resize(const int &rows, const int &cols)
{
	if (rows==0  &&  numRows!=0)//KPP
	{
		for (int i = 0 ; i < numRows ; i++)
			delete matPtr[i];
		delete [] matPtr;
		matPtr=NULL;//KPP
		numRows=0; return;
	}

	else if  (numRows==rows && numCols==cols)
		return ;

	else if (numRows==0)
	{   
		if(matPtr!=NULL) 
			delete [] matPtr;//KPP
		if(NULL==(matPtr = new Vector<T>* [numRows = rows])) 
		{
			ASSERT(FALSE);
			cout << "Memory allocation error" << endl;
			exit(0);
		}    
       
		for (int i = 0 ; i < rows ; i++)
		{
			if(NULL==(matPtr[i] = new Vector<T>(cols)))
			{
				 ASSERT(FALSE);
               cout << "Memory allocation error" << endl;
               exit(0);
			}
		}
 
		numCols = cols;
		return;
	}

	else //numRows != 0
	{
	Vector<T>** oldMatPtr = matPtr ;
	int old = numRows ;

	numCols = cols ;
    if(NULL==(matPtr = new Vector<T>* [numRows = rows])) //checkmem
	{
		 ASSERT(FALSE);
        cout << "Vector memory allocation error" << endl;
        exit(0);
    }
    for (int i = 0 ; i < numRows ; i++)
    {
		if (i < old)
		{
			matPtr[i] = oldMatPtr[i];
			matPtr[i]->Resize(cols);
		}
		else
		{
			if(NULL==(matPtr[i] = new Vector<T>(cols)))//checkmem
			{ 
				 ASSERT(FALSE);
				cout << "Vector memory allocation error" << endl;
				exit(0);
			}
		}
    }
//KPP
	for (int j= numRows; j<old; j++)
		delete oldMatPtr[j];
	delete [] oldMatPtr;
	}
}

/*==============================================================================
==============================================================================*/

template <class Type>
void Matrix<Type>::Transpose()
 {
  register int i, j ;

   if (numRows != numCols)
    return ;
   for (i = 0 ; i < numRows - 1 ; i++)
    for (j = i ; j < numCols ; j++)
     Swap(matPtr[i]->vecPtr[j], matPtr[j]->vecPtr[i]) ;
 }
/********************************************************
 *   redirection of output symbol: "<<"
 ********************************************************/
template <class Type>
ostream& operator << (ostream& os, Matrix<Type>& m) 
{
      Matrix<Type>* p_matrix = &m;
      Vector<Type> vector;

      os << endl;
      for(int i=0; i< p_matrix->Rows(); i++)
      {   
          os << endl;
          vector = (*p_matrix)[i];
          for(int j=2; j< vector.Size(); j++)
              os << setw(5)<<vector[j] << " ";
          if(vector[0]==0) os << "= ";
          else if(vector[0]==1) os << "< ";
          else if(vector[0]==2) os << "<= ";
          else if(vector[0]==3) os << "> ";
          else if(vector[0]==4) os << ">= ";
          else if(vector[0]==5) os  <<"= ";
          else os << vector[0];
          os << vector[1];                
      }
      os << endl;
      return os;
}


template <class Type>
void Matrix<Type>::Trace()
{
      Matrix<Type>* p_matrix = this;
      Vector<Type> vector;

	  for(int i=0; i< p_matrix->Rows(); i++)
      {   
		  char cOut[32];
		  CString str("");

          vector = (*p_matrix)[i];
          for(int j=2; j< vector.Size(); j++)
		  {
			  sprintf(cOut, "%f", (float)(vector[j]));
			  str += cOut;
			  str += "  ";
		  }
          
		  if(vector[0]==0)
			  str += "= ";
          else if(vector[0]==1)
			  str += "< ";
          else if(vector[0]==2)
			  str += "<= ";
          else if(vector[0]==3)
			  str += "> ";
          else if(vector[0]==4)
			  str += ">= ";
          else if(vector[0]==5)
			  str += "= ";
          else
		  {
			  sprintf(cOut, "%f", (float)(vector[0]));
			  str += cOut;
		  }
		  str += "  ";
		  sprintf(cOut, "%f", (float)(vector[1]));
		  str += cOut;
		  str += (char)(0x0D);
		  str += (char)(0x0A);
	
		  TRACE0(str);
      }

	  TRACE0("\n");

}

template <class Type>
void Matrix<Type>::TraceNoEqual()
{
      Matrix<Type>* p_matrix = this;
      Vector<Type> vector;

	  for(int i=0; i< p_matrix->Rows(); i++)
      {   
		  char cOut[32];
		  CString str("");

          vector = (*p_matrix)[i];
          for(int j=0; j< vector.Size(); j++)
		  {
			  sprintf(cOut, "%f", (float)(vector[j]));
			  str += cOut;
			  str += "  ";
		  }
		  str += (char)(0x0D);
		  str += (char)(0x0A);
	
		  TRACE0(str);
      }

	  TRACE0("\n");
}

/*******************************************************
 * Name:	 Matrix<Type>::Simplify(boolean create_equality)
 * Author:   Shasha
 * Time:	 07/2003
 * Descrpn:	 Simplify the matrix
 *			 Remove redundent vectors based on lower and upper bound.
 *			 Remove redundent inequality if it has equality. 
 *			 Execute only if the matrix is satisfiable.
 *           Set create_equality as true if the caller want to 
 *           combine <= and >= into =. Otherwise set it as false.
 *******************************************************/
template <class Type>
void Matrix<Type>::Simplify(boolean create_equality)
{

//Start of 2-D convex simplification ======================================================
/*
//The simplification program was originated by L. D. Miller in May 2005. 
//It works fine for relations do represent 2-D shapes. 
//But it has problems for the relations that do not represent 2-D shapes and 
//will cause the mlpq system to quit without warning. 
//I bookmark the codes here before the problem is fixed.
//Shasha Wu, 1/22/2006

	if (Cols()<=5 && Cols()>=4)
	{
		CArray<double> cx;
		CArray<double> cy;
		CArray<double> ct;
		CArray<int> vecid;

		for(int i=0; i< Rows(); i++)
		{
			if ((*matPtr[i])[0]==5.5 ) //Strings
				continue;

			if (Cols()==4) //(x,y)
			{
				if ((*matPtr[i])[0]<=2)  //< or <=
				{
					cx.Add((*matPtr[i])[2]);
					cy.Add((*matPtr[i])[3]);
					ct.Add((*matPtr[i])[1]);
					vecid.Add(i);
				}
				else //> or >= or =
				{
					cx.Add(-(*matPtr[i])[2]);
					cy.Add(-(*matPtr[i])[3]);
					ct.Add(-(*matPtr[i])[1]);
					vecid.Add(i);
				}
			}
			else if (Cols()==5) //(i,x,y) 
			{
				if ((*matPtr[i])[2]==0)
				{
					if ((*matPtr[i])[0]<=2)  //< or <=
					{
						cx.Add((*matPtr[i])[3]);
						cy.Add((*matPtr[i])[4]);
						ct.Add((*matPtr[i])[1]);
						vecid.Add(i);
					}
					else //> or >= or =
					{
						cx.Add(-(*matPtr[i])[3]);
						cy.Add(-(*matPtr[i])[4]);
						ct.Add(-(*matPtr[i])[1]);
						vecid.Add(i);
					}
				}
			}
		}

		CString removevec=FindPolygonPoints(true, &cx, &cy, &ct, NULL, NULL);
		CString token, tmp, vec4del;
		int *redundent; //0--nonredundent; 1--redundent
		redundent = new int[Rows()];

		for(int n=0; n< Rows(); n++)
			redundent[n]=0;
		
		//vec4del="";
		int pos=0;
		token = removevec.Tokenize(",",pos);
		while (token!="")
		{
			int id=atoi(token);
			redundent[vecid[id]]=1;
			//tmp.Format("%d,", vecid[id]);
			//vec4del += tmp;
			token = removevec.Tokenize(",",pos);
		}

		int j=0;
		for (int i = 0 ; i < numRows ; i++)
		{
			if (redundent[i]==0)	
			{
				if (i!=j){
					for(int k=0; k< numCols; k++)		//Can't use "=" to assign vector's value here. Will generate error in deleting.
						(*matPtr[j])[k] = (*matPtr[i])[k];
				}
				j++;
			}
		}

		delete []redundent;
		for (i = j ; i < numRows ; i++) 
			delete matPtr[i] ;

		numRows = j;

		cx.RemoveAll();
		cx.FreeExtra();
		cy.RemoveAll();
		cy.FreeExtra();
		ct.RemoveAll();
		ct.FreeExtra();
		return;
	}
*/ 
//End of 2-D convex simplification ======================================================

      Matrix<Type>* p_matrix = this;
      Vector<Type> vector1, vector2;

	  int *redundent; //0--nonredundent; 1--redundent
	  redundent = new int[p_matrix->Rows()];
	  int i;

	  for(int n=0; n< p_matrix->Rows(); n++){
		  redundent[n]=0;}

	  if (create_equality){
	  for(i=0; i< p_matrix->Rows(); i++)
	  {   
	      vector1 = (*p_matrix)[i];
		  int k;
		  for(k=2; k< vector1.Size(); k++)
		  {
			  if (vector1[k]!=0) break; 
		  }
		  if (k<vector1.Size() )
		  {
			  double firstv = vector1[k];
			  if (firstv==1 || firstv==-1) continue;
			  if (firstv<0) {
				  firstv=-firstv;
				  (*matPtr[i])[k]=-1;
			  }
			  else
				  (*matPtr[i])[k]=1;
			  
			  (*matPtr[i])[1]=((*matPtr[i])[1]/firstv);
			  for (int j=k+1; j<vector1.Size(); j++)
			  {
				  if ((*matPtr[i])[j]!=0)
					  (*matPtr[i])[j] = (*matPtr[i])[j]/firstv;
			  }
		  }
	  }
	  }


	  for(i=1; i< p_matrix->Rows(); i++)
	  {   
		  if (redundent[i]==1) continue;

	      vector1 = (*p_matrix)[i];
		  for (int j=0; j< i; j++)
		  {
			  if (redundent[j]==1) continue;

			  vector2 = (*p_matrix)[j];
			  boolean same=true;
			  boolean complement=true;
			  for(int k=2; k< vector1.Size(); k++)
			  {
				  if (!same && !complement) break;
				  if (vector2[k]!=vector1[k]) {same=false; }
				  if (vector2[k]!=-vector1[k]) {complement=false; }
			  }
			  if (same)
			  {
				  float op_i=vector1[0];
				  float op_j=vector2[0]; 
				  float cnst_i=vector1[1];
				  float cnst_j=vector2[1];

				  if (((op_i==1)||(op_i==2))&&((op_j==1)||(op_j==2))) // < or <=
				  {
					  if (cnst_i==cnst_j){			//both have same constant 
						  if (op_i==1)				// vector i has '<', remove it
							  redundent[i]=1;
						  else redundent[j]=1;		//otherwise i is '<=', remove j
					  }
					  else if (cnst_i<cnst_j)  // for < or <=, remove bigger one
						  redundent[j]=1;
					  else redundent[i]=1;
				  }
				  else if (((op_i==3)||(op_i==4))&&((op_j==3)||(op_j==4))) // > or >=
				  {
					  if (cnst_i==cnst_j)			//both have same constant 
						  if (op_i==3)				// vector i has '<', remove it
							  redundent[i]=1;
						  else redundent[j]=1;		//otherwise i is '<=', remove j
					  else	if (cnst_i<cnst_j)		// for < or <=, remove smaller one
							  redundent[i]=1;
					  else redundent[j]=1;
				  }
				  else if (op_i!=op_j)
					  continue;
			  }
			  else if (complement && create_equality) // merge x<=5, -x<=-5 to x=5
			  {
				  float op_i=vector1[0];
				  float op_j=vector2[0]; 
				  float cnst_i=vector1[1];
				  float cnst_j=vector2[1];
				  if (op_i==2 && op_j==2 && cnst_i==-cnst_j)
				  {
					for(int k=2; k< vector1.Size(); k++)
					{
						if (vector1[k]!=0) 
						{ 
							if (vector1[k]<0){
								(*this)[j][0]= 5;
								redundent[i]=1;
							}
							else {
								(*this)[i][0]= 5;
								redundent[j]=1;
							}
							break;
						}
					}
				  }
			  }
		  }

	  }
	  // remove all inequality constraints if there is an equality for the same formula
		for(i=0; i< p_matrix->Rows(); i++)
		{   
			if (redundent[i]==1) continue;
			vector1 = (*p_matrix)[i];
			if (vector1[0]==EQUAL) 
			{  
				for (int j=0; j< p_matrix->Rows(); j++)
				{
					if ((redundent[j]==1)||(i==j)) continue;
				  
					vector2 = (*p_matrix)[j];
					boolean same=true;
					boolean complement=true;
					for(int k=2; k< vector1.Size(); k++)
					{
						if (!same && !complement) break;
						if (vector2[k]!=vector1[k]) {same=false; }
						if (vector2[k]!=-vector1[k]) {complement=false; }
					}
					if (same || complement) redundent[j]=1; 
				}
			}
		}


	int j=0;
	for (i = 0 ; i < numRows ; i++)
	{
		if (redundent[i]==0)	
		{
			if (i!=j){
				for(int k=0; k< numCols; k++)		//Can't use "=" to assign vector's value here. Will generate error in deleting.
					(*matPtr[j])[k] = (*matPtr[i])[k];
			}
			j++;
		}
	}

	delete []redundent;
	for (i = j ; i < numRows ; i++) 
		delete matPtr[i] ;

	numRows = j;
}

template <class T>
bool Matrix<T>::Copy(const Matrix<T>& m)
{
	if (this == &m)
		return true ;

	if (numCols != m.Cols())
		return false;
	
	this->Resize(m.Rows(), m.Cols());

	if((*dataBase).GIS) m_color=m.m_color; //RUICHEN
	//matPtr = new Vector<T>* [numRows] ;

	for (int i = 0 ; i < numRows ; i++)
	for (int j = 0 ; j < numCols ; j++)
		matPtr[i][j] = (*(m.matPtr[i]))[j] ;
  
	return true ;
}

//current is the point to start
//return the next point from current point
template <class T>
int Matrix<T>::find_next(int current, CArray<double> *final_x, CArray<int>* temp_e1, CArray<int>* temp_e2, CArray<int> *final_e1, CArray<int> *final_e2)
{
    int temp=-1;
	int flag = 0;

	for (int i=0; i<final_x->GetCount(); i++)
	{
		if (temp_e1->GetAt(i) == final_e1->GetAt(current))
		{
			if (i == current)
				continue;
			else
			{
				temp = i;
				flag = 1;
				break;
			}
		}
		else
		{
			if (temp_e2->GetAt(i) == final_e1->GetAt(current))
			{
				if (i == current)
					continue;
				else
				{
					temp = i;
					flag = 1;
					break;
				}
			}
			else
				continue;
		}
	}

	if (flag == 0)
	{
		for (int i=0; i<final_x->GetCount(); i++)
		{
			if (temp_e1->GetAt(i) == final_e2->GetAt(current))
			{
                if (i == current)
					continue;
				else
				{
					temp = i;
					flag = 1;
					break;
				}
			}
			else
			{
				if (temp_e2->GetAt(i) == final_e2->GetAt(current))
				{
					if (i == current)
						continue;
					else
					{
						temp = i;
						flag = 1;
						break;
					}
				}
				else
					continue;
			}
		}
	}

	return temp;
}

//cx: array of coefficients of x of all the equations
//cy: array of coefficients of y of all the equations
//ct: array of constants of all the equations
//Return a list of points representing the polygon
//CArray<float> order_x; // array of x coordinates of vertices of the polygon in clockwise order
//CArray<float> order_y; // array of y coordinates of vertices of the polygon in clockwise order
template <class T>
CString Matrix<T>::FindPolygonPoints(bool SimplficationOnly, CArray<double> *cx, CArray<double> *cy, CArray<double> *ct, CArray<double> *order_x, CArray<double> *order_y)
{
	CString rmedges=",";
	CArray<double> final_x; // array of x coordinates of vertices of the polygon
	CArray<double> final_y; // array of y coordinates of vertices of the polygon
    CArray<int> final_e1; // equation number of the intersecting lines - 1
    CArray<int> final_e2; // equation number of the intersecting lines - 2
    CArray<int> temp_e1; // equation number of the intersecting lines - 1
    CArray<int> temp_e2; // equation number of the intersecting lines - 2
	
	//	Find all the possible intersection points
	int i;
	for (i=0; i<(cx->GetCount())-1; i++)
	{
		for (int j=i+1; j<cx->GetCount(); j++)
		{
			double point_x, point_y;
			double temp = cx->GetAt(i)*cy->GetAt(j) - cx->GetAt(j)*cy->GetAt(i);

			//check if the two lines are parallel to each other
			if (temp != 0)
			{
				//point_x = (trans_ct[i] - trans_ct[j])/(trans_cx[i] - trans_cx[j]);
				//point_y = trans_ct[i] - trans_cx[i] * point_x;
				point_x = (ct->GetAt(i)*cy->GetAt(j) - ct->GetAt(j)*cy->GetAt(i))/temp;

				if (cy->GetAt(i)!=0)
					point_y = (ct->GetAt(i) - point_x*cx->GetAt(i))/cy->GetAt(i);
				else
					point_y = (ct->GetAt(j) - point_x*cx->GetAt(j))/cy->GetAt(j);

			}
			else
				continue;

			final_x.Add(point_x);
			final_y.Add(point_y);

			final_e1.Add(i);
			final_e2.Add(j);

			temp_e1.Add(i);
			temp_e2.Add(j);
		}
	}

//	Remove the points that lie outside the polygon
	i=0; 
	while(i<final_x.GetCount())
	{
		int outside_point=0;
		
		for (int j=0; j<cx->GetCount(); j++)
		{
			double lhs_value;

			lhs_value = final_x[i] * cx->GetAt(j) + final_y[i] * cy->GetAt(j);

			if (lhs_value - ct->GetAt(j) > FLOAT_ZERO)
			{
				outside_point = 1;
				break;
			}
		}
		
		if (outside_point == 1)
		{ //point is located outside of the polygon
			final_x.RemoveAt(i);
			final_y.RemoveAt(i);
			final_e1.RemoveAt(i);
			final_e2.RemoveAt(i);
			temp_e1.RemoveAt(i);
			temp_e2.RemoveAt(i);
		}
		else i++;
	}

	for (i=0; i<cx->GetCount(); i++)
	{
		int p1, p2;
		p1=p2=-1;
		for (int j=0; j<final_e1.GetCount(); j++)
		{
			if (final_e1[j]==i || final_e2[j]==i )
			{
				if (p1==-1) //make p1 < p2
					p1 = j;
				else {
					p2 = j;
					break;
				}
			}
		}
		if (p1==-1 || p2==-1)
			continue;

		else if (fabs(final_x[p1] - final_x[p2]) < FLOAT_ZERO && fabs(final_y[p1]-final_y[p2]) < FLOAT_ZERO)
		{ //the edge has one unique intersect point: remove the points generated by the edge 
			// p2 always greater than p1 (See previous codes)
			final_x.RemoveAt(p2);
			final_y.RemoveAt(p2);
			final_e1.RemoveAt(p2);
			final_e2.RemoveAt(p2);
			temp_e1.RemoveAt(p2);
			temp_e2.RemoveAt(p2);

			final_x.RemoveAt(p1);
			final_y.RemoveAt(p1);
			final_e1.RemoveAt(p1);
			final_e2.RemoveAt(p1);
			temp_e1.RemoveAt(p1);
			temp_e2.RemoveAt(p1);
		}
	}

	if (SimplficationOnly)
	{
		for (i=0; i<cx->GetCount(); i++)
		{
			int used=0;
			CString tmpstr;
			for (int j=0; j<final_e1.GetCount(); j++)
			{
				if (final_e1[j]==i || final_e2[j]==i )
				{
					used=1;
					break;
				}
			}
			if (used==0)
			{
				tmpstr.Format(",%d,", i);
				rmedges += tmpstr;
			}
		}
		//quit here, no need to order the vertices.
		goto free_mem;
	}

	//Less than 3 intersection points
	if (final_x.GetCount()<4)
	{
		for ( i=0; i<final_x.GetCount(); i++)
		{
			order_x->Add(final_x[i]);
			order_y->Add(final_y[i]);
		}
		goto free_mem ;
	}

//	Find the first vertex; i.e., the vertex the smallest x coordinate

	int smallest = 0;
	int num_pts = final_x.GetCount();

	for (int i=1; i<num_pts; i++)
	{
		if (final_x[i] == final_x[smallest])
		{
			if (final_y[i] < final_y[smallest])
				smallest = i;
			//continue;
		}
		else
		{
            if (final_x[i] < final_x[smallest])
				smallest = i;
			else
				continue;
		}
	}

//	Enter the first point into the array

    order_x->Add(final_x[smallest]);
    order_y->Add(final_y[smallest]);
	temp_e1.SetAt(smallest, -1);
	temp_e2.SetAt(smallest, -1);


//	Find the second point

	int tmp1, tmp2, current;
	tmp1 = find_next(smallest, &final_x, &temp_e1, &temp_e2, &final_e1, &final_e2);
	for (int i=0; i<num_pts; i++)
	{
		if (final_e2[i] == final_e2[smallest])
		{
			if (i == smallest)
				continue;
			else
			{
				tmp2 = i;
				break;
			}
		}
		else
		{
			if (final_e1[i] == final_e2[smallest])
			{
				if (i == smallest)
					continue;
				else
				{
					tmp2 = i;
					break;
				}
			}
			else
				continue;
		}
	}

	if (final_y[tmp1] == final_y[tmp2])
	{
		if (final_x[tmp1] > final_x[tmp2])
			current = tmp1;
		else
			current = tmp2;
	}
	else
	{
		if (final_y[tmp1] > final_y[tmp2])
			current = tmp1;
		else
			current = tmp2;
	}

	order_x->Add(final_x[current]);
	order_y->Add(final_y[current]);
	temp_e1.SetAt(current, -1);
	temp_e2.SetAt(current, -1);

	for (int i=2; i<final_x.GetCount(); i++)
	{
		current = find_next(current, &final_x, &temp_e1, &temp_e2, &final_e1, &final_e2);
		if (current==-1)
			break;

		order_x->Add(final_x[current]);
		order_y->Add(final_y[current]);
		temp_e1.SetAt(current, -1);
		temp_e2.SetAt(current, -1);

	}

free_mem:
	final_x.RemoveAll();
	final_x.FreeExtra();
	final_y.RemoveAll();
	final_y.FreeExtra();
	final_e1.RemoveAll();
	final_e1.FreeExtra();
	final_e2.RemoveAll();
	final_e2.FreeExtra();
	temp_e1.RemoveAll();
	temp_e1.FreeExtra();
	temp_e2.RemoveAll();
	temp_e2.FreeExtra();
	//AfxMessageBox(rmedges);
	return rmedges;

}

//Recalculate the intersection points
template <class T>
void Matrix<T>::RegeneratePoints(int nTime)
{
	//begin: Shasha====================================================
	if(dataBase->STDB==TRUE){
		RecalcPoints(nTime);
	}
	else {
		if (m_pList)
			m_pList->DeepDestroy();
		else
			m_pList = new Slist<ParaPoint>;
		//delete m_pList;
		//m_pList = new Slist<ParaPoint>;

		CArray<double> cx;
		CArray<double> cy;
		CArray<double> ct;
		CArray<double> order_x;
		CArray<double> order_y;
		//Vector<float> vec1;

		for(int i=0; i< Rows(); i++)
		{
			//(matPtr[i]);
			if ((*matPtr[i])[0]<=2)  //< or <=
			{
				if(Cols() > 5) //(i,x,y,t)
				{
					if ((*matPtr[i])[3]==0 && (*matPtr[i])[4]==0)
						continue;
					cx.Add((*matPtr[i])[3]);
					cy.Add((*matPtr[i])[4]);
					ct.Add((*matPtr[i])[1]-nTime*(*matPtr[i])[5]);
				}
				else if (Cols() == 5) //(i,x,y)
				{
					if ((*matPtr[i])[3]==0 && (*matPtr[i])[4]==0)
						continue;
					cx.Add((*matPtr[i])[3]);
					cy.Add((*matPtr[i])[4]);
					ct.Add((*matPtr[i])[1]);
				}
				else if (Cols() == 4) //(x,y)
				{
					if ((*matPtr[i])[2]==0 && (*matPtr[i])[3]==0)
						continue;
					cx.Add((*matPtr[i])[2]);
					cy.Add((*matPtr[i])[3]);
					ct.Add((*matPtr[i])[1]);
				}
			}
			else            //> or >= or =
			{
				if(Cols() > 5) //(i,x,y,t)
				{
					if ((*matPtr[i])[3]==0 && (*matPtr[i])[4]==0)
						continue;
					cx.Add(-(*matPtr[i])[3]);
					cy.Add(-(*matPtr[i])[4]);
					ct.Add(-(*matPtr[i])[1]+nTime*(*matPtr[i])[5]);
				}
				else if(Cols() == 5) //(i,x,y)
				{
					if ((*matPtr[i])[3]==0 && (*matPtr[i])[4]==0)
						continue;
					cx.Add(-(*matPtr[i])[3]);
					cy.Add(-(*matPtr[i])[4]);
					ct.Add(-(*matPtr[i])[1]);
				}
				else if(Cols() == 4) //(x,y)
				{
					if ((*matPtr[i])[2]==0 && (*matPtr[i])[3]==0)
						continue;
					cx.Add(-(*matPtr[i])[2]);
					cy.Add(-(*matPtr[i])[3]);
					ct.Add(-(*matPtr[i])[1]);
				}
			}
		}
		/*
		cx.Add(1);
		cy.Add(0);
		ct.Add(30);
		cx.Add(-1);
		cy.Add(0);
		ct.Add(30);
		cx.Add(0);
		cy.Add(1);
		ct.Add(30);
		cx.Add(0);
		cy.Add(-1);
		ct.Add(30);
		*/

		FindPolygonPoints(false, &cx, &cy, &ct, &order_x, &order_y);
		ParaPoint p;
		for(int i=0; i < order_x.GetCount(); i++)
		{
				// x = fXa*t + fXb
				// y = fYa*t + fYb
			p.m_fXa = p.m_fYa = 0;
				p.m_fX = p.m_fXb = order_x[i];
				p.m_fY = p.m_fYb = order_y[i];
				p.m_bShow = TRUE;
				m_pList->AppendHere(*(new ParaPoint(p)));
		}
		cx.RemoveAll();
		cx.FreeExtra();
		cy.RemoveAll();
		cy.FreeExtra();
		ct.RemoveAll();
		ct.FreeExtra();
		order_x.RemoveAll();
		order_x.FreeExtra();
		order_y.RemoveAll();
		order_y.FreeExtra();
		//return ;

		//End: Shasha====================================================
	}
/*
    if(Cols() >= 5)
	{	
		int cols = Cols()-1; 
		Vector<float> vec1(cols);
		Matrix<float>* p_m = new Matrix<float>();
		//this->Trace();
		for(int i=0; i< Rows()-1; i++)
		{
			if (fabs((*this)[i+1][2]) < FLOAT_ZERO  &&  fabs((*this)[i+1][3]) < FLOAT_ZERO
				&&  fabs((*this)[i+1][4]) < FLOAT_ZERO  &&  fabs((*this)[i+1][5]) > FLOAT_ZERO) //t
			{
				vec1 = 0.0;
				//(*this)[i+1].Trace();
				if (((*this)[i+1][5] < 0  &&  
					((int)((*this)[i+1][0]) == 3  ||  (int)((*this)[i+1][0]) == 4))	// t >=
					|| ((*this)[i+1][5] > 0  &&  
					((int)((*this)[i+1][0]) == 1  ||  (int)((*this)[i+1][0]) == 2)))	// t <=
				{
					vec1[1] = (*this)[i+1][1] - (*this)[i+1][5]*nTime;
				}
				else
					vec1[1] = (*this)[i+1][1];
			}
			else
			{
				vec1[1] = (*this)[i+1][1] - (*this)[i+1][5]*nTime;		// val const
				vec1[2] = (*this)[i+1][3];		// x
				vec1[3] = (*this)[i+1][4];		// y
			}
			vec1[0] = (*this)[i+1][0];		// op
			for (int nTemp=4; nTemp<cols; nTemp++)
				vec1[nTemp] = (*this)[i+1][nTemp+1];
			
			dataBase->AddVectorToMatrix(p_m,&vec1);
		}
		//p_m->Trace();
		m_pList = dataBase->HulConvt(p_m);
		
		Snode<ParaPoint>* nPtr = m_pList->headPtr;
		i = 0;
		while(i++ < m_pList->len)
		{
			ParaPoint* p = (ParaPoint*)(nPtr->itemPtr);
			
			p->m_fX = p->m_fXb;
			p->m_fY = p->m_fYb;
			p->m_fXb -= p->m_fXa * nTime;
			p->m_fYb -= p->m_fYa * nTime;
			p->m_bShow = TRUE;
			
			nPtr = nPtr->nextPtr;
		}
		
		delete p_m;
	}
*/
}

template <class T>
BOOL Matrix<T>::DoCheckPointsSatisfiable()
{
	BOOL bReturn = TRUE;
	
	if (m_pList != NULL)
	{
		Snode<ParaPoint>* nPtr = m_pList->headPtr ;
		int i = 0;
		while(i++ < m_pList->len)
		{
			ParaPoint* p = (ParaPoint*)(nPtr->itemPtr);
			p->m_bShow = TRUE;
			
			// check p->m_fX, p->m_fY
			for(int i=0; i<Rows(); i++)
			{
				Vector<float> vector = (*this)[i];
				
				if (fabs((float)(vector[3])) > FLOAT_ZERO  ||  fabs((float)(vector[4])) > FLOAT_ZERO)
				{
					float fLeft = vector[3] * p->m_fX 
						+ vector[4] * p->m_fY 
						+ vector[5] * m_nCurrent;
					switch ((int)(vector[0]))
					{
					case 0 :	// "= ";
					case 5 :	
						if (fabs(fLeft - vector[1]) < FLOAT_ZERO)
							p->m_bShow = FALSE;
						break;
					case 1 :	// "< ";
						//						if (fLeft >= vector[1])
						//							p->m_bShow = FALSE;
						//						break;
					case 2 :	// "<= ";
						if (fLeft > vector[1])
							p->m_bShow = FALSE;
						break;
					case 3 :	// "> ";
						//						if (fLeft <= vector[1])
						//							p->m_bShow = FALSE;
						//						break;
					case 4 :	// ">= ";
						if (fLeft < vector[1])
							p->m_bShow = FALSE;
						break;
					}
					if (!p->m_bShow)
					{
						bReturn = FALSE;
						break;
					}
				}
			}
			
			nPtr = nPtr->nextPtr;
		}
	}
	
	return bReturn;
}


template <class T>
void Matrix<T>::RecalcPoints(int nTime)
{
/*	if (nTime < m_nTimeS)
nTime = m_nTimeS;
else
if (nTime > m_nTimeE)
nTime = m_nTimeE;
	*/

	if (nTime == m_nCurrent)
		return;
	
	if (nTime < m_nTimeS  ||  nTime > m_nTimeE)
	{
		m_nCurrent = -1;	// invalid
		return;
	}
	
	// recalc
	
	if (m_pList != NULL)
	{
		Snode<ParaPoint>* nPtr = m_pList->headPtr ;
		for(int i=0; i < m_pList->len; i++)
		{
			ParaPoint* p = (ParaPoint*)(nPtr->itemPtr);
			p->m_fX = p->m_fXa * nTime + p->m_fXb;
			p->m_fY = p->m_fYa * nTime + p->m_fYb;
			nPtr = nPtr->nextPtr;
		}
	}
	
	m_nCurrent = nTime;
	/*
	if (!DoCheckPointsSatisfiable())
	{
	AfxGetApp()->BeginWaitCursor();
	RegeneratePoints(nTime);
	AfxGetApp()->EndWaitCursor();
	}
	*/
}

/*==============================================================================
==============================================================================*/

#endif
