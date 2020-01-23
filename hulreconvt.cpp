/*********************************************
* File:   hulreconvt.c
* Date:   August 11, 97
* Author: Huge Wang
*
***********************************************/
#include "stdafx.h"
//#include <values.h>
#include <string.h>
#include <stdlib.h>
#include <fstream.h>
#include <stdio.h>
#include "db.h"
#include "slist.h"
#include "hulstruct.h"
extern DB (*dataBase);  
/*************************************************************
 * name:     DB::HulReConvt(Relation* prel)
 * Time:     Aug 11, 1997
 * Descript: input relation has the format:
 *           Obj(i,x1,y1,x2,y2,x3,y3):- i=2, x1=2,y1=3, x2=2,y2=7,
 *                                           x3=6,y3=3. 
 *           Use the three extreme points (2,3),(2,7),(6,3),
 *           Build up a new relation(linear constraints discription)  
 *           Obj_l(i,x,y):- i=2, x>=2,y>=3,x+y<=9. 
 *************************************************************/
Relation* DB::HulReConvt(Relation* prel)
{
//   cout<<*prel<<endl;
   const Matrix<float>* p_matrix;
   const String t = String("_l");
   Relation* t_pr = new Relation(prel->Name()+t);
   t_pr->m_Arity = 3;
   t_pr->m_Satisfiable=prel->m_Satisfiable;
   Matrix<float>* p_m;   

   Vector<float> vec1;
   Vector<float> vec2; 
   cout << endl;
   cout << "=======================\n";
   cout << "Relation \" " << prel->m_sName<<"\"" ;
   if(prel->m_Satisfiable==1)  {
         cout << " is Universally Satisfiable" << endl;
         return NULL;
   }
   if(prel->m_Satisfiable==-1)  {
         cout  << " is Unsatisfiable. " << endl;
         return NULL;
   }
   DFIter<Matrix<float> >  matrixIter(*(prel->m_tablePtr));
   cout  << " : Arity = "<< prel->Arity() << endl;

   /*now change the relation to new format*/
  // int cols = prel->Arity()+1; 

   vec1 = Vector<float>(5);
   Point p[3];
   while(p_matrix =  matrixIter()) { 
      p_m = new Matrix<float>();

      vec1=0;
      vec1[0] = 5; 
      vec1[1] = (*p_matrix)[0][1]; 
      vec1[2] = 1;
      AddVectorToMatrix(p_m,&vec1);

      for(int i=0; i<=2; i++)
      {   
            p[i].m_x=(*p_matrix)[2*i+1][1];
			p[i].m_y=(*p_matrix)[2*i+2][1];
      }
      if( (p[0]==p[1])&&(p[1]==p[2])){ // 3 points is same
           vec1=0;
           vec1[0]=5;
           vec1[1]=p[0].m_x;
           vec1[3]=1;
           AddVectorToMatrix(p_m,&vec1);
           vec1=0;
           vec1[0]=5;
           vec1[1]= p[0].m_y;
           vec1[4]=1;
           AddVectorToMatrix(p_m,&vec1);
      }
      else
      { 
         if( p[0]==p[1]) { 
          Point temp = p[1];
          p[1] = p[2];
          p[2] = temp;
         } 
           cout<<p[0]<<p[1]<<p[2]<< endl; 
          if(!CoLine(p[0],p[1],p[2])){ 
           vec1 = *GetVectorFromPoints(p[0],p[1],p[2]);
           AddVectorToMatrix(p_m,&vec1);
           vec1 = *GetVectorFromPoints(p[1],p[2],p[0]);
           AddVectorToMatrix(p_m,&vec1); 
           vec1 = *GetVectorFromPoints(p[2],p[0],p[1]);
           AddVectorToMatrix(p_m,&vec1);  
         }
         else {  // 3 points coline 
           vec1 = *GetVectorFromPoints(p[0],p[1],p[2]);
           vec1[0] = 5;
           AddVectorToMatrix(p_m,&vec1);           
           if(p[0].m_x != p[1].m_x){
	     float min = (p[0].m_x < p[1].m_x)? p[0].m_x : p[1].m_x;
	     min = (min < p[2].m_x)? min : p[2].m_x;
	     float max = (p[0].m_x < p[1].m_x)? p[1].m_x : p[0].m_x;
	     max = (max < p[2].m_x)? p[2].m_x : max;
             vec1 = 0;
             vec1[0]=2; // ">="
             vec1[1] = -min;
             vec1[3] = -1;
             AddVectorToMatrix(p_m,&vec1);
             vec1 = 0;
             vec1[0]=2; // "<="
             vec1[1] = max;
             vec1[3] = 1;
             AddVectorToMatrix(p_m,&vec1);
           }
           else{ // x1 == x2
	     float min = (p[0].m_y < p[1].m_y)? p[0].m_y : p[1].m_y;
	     min = (min < p[2].m_y)? min : p[2].m_y;
	     float max = (p[0].m_y < p[1].m_y)? p[1].m_y : p[0].m_y;
	     max = (max < p[2].m_y)? p[2].m_y : max;
             vec1 = 0;
             vec1[0]=2; // ">="
             vec1[1] = -min;
             vec1[4] = -1;
             AddVectorToMatrix(p_m,&vec1);
             vec1 = 0;
             vec1[0]=2; // "<="
             vec1[1] = max;
             vec1[4] = 1;
             AddVectorToMatrix(p_m,&vec1);
          }                  
       }
     }
     t_pr->AddMatrix(*p_m);
   }/* end of while*/
   return   t_pr; 
}

void DB::Convt_l(const char* relName)
{ 
  const Relation* relPtr ;
  Relation* r;
  Relation* p_r;  
  if (!(relPtr = RetrieveRelation(relName))) 
      cout << "\"" << relName << "\":" << " No such relation in data base\n" ;
  else{
      r = HulReConvt((Relation*)relPtr);
      r = r->MergeTriangle();
     if(0==(p_r=(Relation*)RetrieveRelation(r->m_sName)) ) { // a new relation
               m_pRelationList->AppendHere(*r);
     }
     else // relation exit before this appear
          p_r->UnionRelation(r);
  }
}
/*************************************************************
 * name:     Relation* Relation::MergeTriangle()
 * Author:   Huge Wang
 * Time:     Aug 19, 1997
 * Descript: input relation has the format:
 * Pt_l(i,x,y):- i=4,-9x<= -9,10.5y<= 115.5,9x-10.5y<= -12.
 * Pt_l(i,x,y):- i=4,9x<= 103.5,-10.5y<= -21,-9x+10.5y<= 12.
 * Pt_l(i,x,y):- i=5,-3x<= -9,-x+y<= 5,4x-y<= 7.
 * Pt_l(i,x,y):- i=5,3x+3y<= 39,x-4y<= -17,-4x+y<= -7.
 * Pt_l(i,x,y):- i=5,-x+4y<= 17,x-y<= 1,-3y<= -15.
 * 
 *  For all constraints with i=5, every 3 constraints represent a traingle.
 *  three triangles can be merged as a polygon, it represents the whole
 *  area of the three triangles.
 *  For example:  
 *     1. we add all the constraints with the same i=5 together.
 *     2. we find ( 4x-y<= 7 and -4x+y<= -7)  can be deleted.
 *           also ( x-4y<= -17,-x+4y<= 17 ) can be deleted.
 *  At last, we get 
 *  Pt_l(i,x,y):- i=5,-3x<= -9,-x+y<= 5, 3x+3y<= 39,x-y<= 1,-3y<= -15.
 *    this is a pantegon, represents the same area as three triangles.
 *  Output:  a new relation with triangls been merged 
 *************************************************************/
Relation* Relation::MergeTriangle()
{
	Matrix<float>* p_matrix;
  
	Relation* t_pr = new Relation(this->Name());
	t_pr->m_Arity = 3;
	t_pr->m_Satisfiable=this->m_Satisfiable;
	Matrix<float>* p_m;
	Matrix<float>* p_m2;    

	Vector<float> vec1;   //= new Vector<float>();
	Vector<float> vec2; 
	int label = -1;
	DFIter<Matrix<float> >  matrixIter(*(this->m_tablePtr));

	while(p_matrix =  matrixIter()) 
	{
     //cout << *p_matrix<<endl;
		if(label != (*p_matrix)[0][1])
		{ 
			if( -1 !=label) 
				t_pr->AddMatrix(*p_m);
			p_m = new Matrix<float>(*p_matrix);
			label = (int)(*p_matrix)[0][1];
			for(int i=1; i< p_m->Rows(); i++)
			{
				if( 5== (*p_m)[i][0])
				{  // "="
					t_pr->AddMatrix(*p_m);
					label = -1;
					break;
				}
			}
			// if(label==-1) continue;
			// label = (*p_matrix)[0][1];
		}
		else
		{ 
			for(int i=1; i< p_matrix->Rows(); i++)
			{
				if( 5== (*p_m)[i][0])
				{  // "="
					t_pr->AddMatrix(*p_matrix);	// may be errors.
					break;
				}
			}
			if(i< p_matrix->Rows()) 
				continue; 
			for( i = 1; i< p_matrix->Rows();i++)
			{
				vec1 = (*p_matrix)[i];
				int rows = p_m->Rows();
				for( int j = 1; j < p_m->Rows(); j++)
				{
					if(  Complement( &vec1, &((*p_m)[j])) ) 
					{
						p_m2 = new Matrix<float>();
						for(int k = 0; k < p_m->Rows();k++)
						if(k!=j)
							(*dataBase).AddVectorToMatrix(p_m2,&((*p_m)[k]));
						delete p_m;
						p_m = p_m2;
						break;
					}
				}
				if( j < rows) 
					continue;
				else 
					(*dataBase).AddVectorToMatrix(p_m, &vec1);
			}    
		}
	}
	//cout << *p_m << endl;
	t_pr->AddMatrix(*p_m);
	delete this; 
	return t_pr; 
}

bool Complement(Vector<float>* vec1, Vector<float>* vec2)
{
    for(int i = 1; i< vec1->Size(); i++)
    {
        if( ( (*vec1)[i]+(*vec2)[i]) == 0) continue;
        else return false;
    }
    return true;  
} 

Vector<float>* GetVectorFromPoints(Point p0, Point p1, Point p2)
{
        Matrix<float>* p_test = new Matrix<float>();
        Vector<float> vec2 = Vector<float>(4);  
        Vector<float>* p_vec1 = new Vector<float>(5);
        Relation* r = new Relation(); 
        vec2=0;
        vec2[0]= 2; /* 1 <,  2 <=, 3 >, 4 >=, 5 =*/
        vec2[2]= p1.m_y - p0.m_y;
        vec2[3]= p0.m_x- p1.m_x;
        vec2[1]= p0.m_x*(p1.m_y - p0.m_y)- p0.m_y*(p1.m_x - p0.m_x);
        (*dataBase).AddVectorToMatrix(p_test,&vec2);  
        vec2 = 0;
        vec2[0] = 5;
        vec2[1] = p2.m_x;
        vec2[2] = 1;
        (*dataBase).AddVectorToMatrix(p_test,&vec2); 
        vec2 = 0;
		vec2[0] = 5;
        vec2[1] = p2.m_y;
        vec2[3] = 1;
        (*dataBase).AddVectorToMatrix(p_test,&vec2); 
        (*p_vec1) = 0;
        (*p_vec1)[1] = (*p_test)[0][1];
        (*p_vec1)[2] = 0;
        (*p_vec1)[3] = (*p_test)[0][2];
        (*p_vec1)[4] = (*p_test)[0][3];
        (*p_vec1)[0] = 2;
        if(!(r->MatrixSatisfiable(p_test)))
             for(int i = 1; i<=4; i++)
               (*p_vec1)[i]= -(*p_vec1)[i];         
         
        delete r;
        delete p_test;
        return p_vec1;         
}

bool CoLine(Point p0, Point p1, Point p2)
{
        Matrix<float>* p_test = new Matrix<float>();
        Vector<float> vec2 = Vector<float>(4);  
        Relation* r = new Relation(); 
        vec2=0;
        vec2[0]= 5; /* 1 <,  2 <=, 3 >, 4 >=, 5 =*/
        vec2[2]= p1.m_y - p0.m_y;
        vec2[3]= p0.m_x- p1.m_x;
        vec2[1]= p0.m_x*(p1.m_y - p0.m_y)- p0.m_y*(p1.m_x - p0.m_x);
        (*dataBase).AddVectorToMatrix(p_test,&vec2);  
        vec2 = 0;
        vec2[0] = 5;
        vec2[1] = p2.m_x;
        vec2[2] = 1;
        (*dataBase).AddVectorToMatrix(p_test,&vec2); 
        vec2 = 0;
	vec2[0] = 5;
        vec2[1] = p2.m_y;
        vec2[3] = 1;
        (*dataBase).AddVectorToMatrix(p_test,&vec2);
        if(r->MatrixSatisfiable(p_test))
	{
            delete r;
            delete p_test;
            return true;
        }    
        else{
            delete r;
            delete p_test;     
            return false;
        }
}

Matrix<float>* DB::GetMatrixFromIDPoints(float id, Point p0, Point p1, Point p2)
{

   Matrix<float>* p_m;   

   Vector<float> vec1;
   Vector<float> vec2; 


   vec1 = Vector<float>(5);
   Point p[3];

   p_m = new Matrix<float>();

   vec1=0;
   vec1[0] = 5; 
   vec1[1] = id; 
   vec1[2] = 1;
   AddVectorToMatrix(p_m,&vec1);


      if( (p0==p1)&&(p1==p2)){ // 3 points is same
           vec1=0;
           vec1[0]=5;
           vec1[1]=p0.m_x;
           vec1[3]=1;
           AddVectorToMatrix(p_m,&vec1);
           vec1=0;
           vec1[0]=5;
           vec1[1]= p0.m_y;
           vec1[4]=1;
           AddVectorToMatrix(p_m,&vec1);
	  }
      else
	  { 
         if( p0==p1) { 
          Point temp = p1;
          p1 = p2;
          p2 = temp;
         } 
          // cout<<p[0]<<p[1]<<p[2]<< endl; 
          if(!CoLine(p0,p1,p2)){ 
           vec1 = *GetVectorFromPoints(p0,p1,p2);
           AddVectorToMatrix(p_m,&vec1);
           vec1 = *GetVectorFromPoints(p1,p2,p0);
           AddVectorToMatrix(p_m,&vec1); 
           vec1 = *GetVectorFromPoints(p2,p0,p1);
           AddVectorToMatrix(p_m,&vec1);  
         }
         else {  // 3 points coline 
           vec1 = *GetVectorFromPoints(p0,p1,p2);
           vec1[0] = 5;
           AddVectorToMatrix(p_m,&vec1);           
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
				 AddVectorToMatrix(p_m,&vec1);
				 vec1 = 0;
				 vec1[0]=2; // "<="
				 vec1[1] = max;
				 vec1[3] = 1;
				 AddVectorToMatrix(p_m,&vec1);
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
				AddVectorToMatrix(p_m,&vec1);
				 vec1 = 0;
				 vec1[0]=2; // "<="
				 vec1[1] = max;
				 vec1[4] = 1;
				 AddVectorToMatrix(p_m,&vec1);
			}                  
		}
	  }
    
	p_m->m_nTimeS = -1;  
	p_m->m_nTimeE = -1;					
   return   p_m; 
}
