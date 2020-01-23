/*********************************************
* add after July 31
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
extern bool ImportLineFlag;//for the Import Line DRK


float DB::RelationArea(Relation* prel)
{
   const Matrix<float>* p_matrix;
   DFIter<Matrix<float> >  matrixIter1(*(prel->m_tablePtr));
   float tot_area=0;
   while(p_matrix =  matrixIter1()) {
       tot_area += HulArea(HulConvt((Matrix<float>*)p_matrix));
   }
   float intersect_area = IntersectArea(prel);
   return tot_area-intersect_area;
}

float DB::IntersectArea(Relation* prel)
{ 

   Vector <Matrix<float>* >* p_vecmat= new Vector<Matrix<float>*>();
   const Matrix<float>* p_matrix;
   Matrix<float>* p_mergedmatrix;
   DFIter<Matrix<float> >  matrixIter1(*(prel->m_tablePtr));
   float tot_area=0;
   int size=0;
   while(p_matrix =  matrixIter1()) {
      p_vecmat->Resize(size+1);
      (*p_vecmat)[size]=(Matrix<float>*)p_matrix;
      size++;
   }

   for(int i=0;i<size;i++)
      for (int j=i+1;j<size;j++)
	{
          p_mergedmatrix=prel->MergeMatrix((*p_vecmat)[i],(*p_vecmat)[j]);
          tot_area += HulArea(HulConvt(p_mergedmatrix));
	}

  return tot_area;
}
   


float DB::HulArea(Slist<ParaPoint>* PointList)
{  
//   cout<<*PointList<<endl;
   float area=0;
   if(PointList==NULL) return 0;

   if (PointList->Size()<=2) return 0;

   const ParaPoint* p_point;
   SlistIter<ParaPoint> pointIter(*PointList);
   ParaPoint* p_cordA, *p_cordB, *p_cordC;
   p_cordA=(ParaPoint*) pointIter();
   p_cordC=(ParaPoint*)pointIter();
   while(p_point = pointIter()){
          p_cordB= p_cordC;
          p_cordC=(ParaPoint*)p_point;
          area+=p_cordA->Triangle_Area(*p_cordB,*p_cordC);
      }    

   return area;
}

BOOL ValidLine(Vector<float> vec)
{
//vec.Trace();
	if (fabs(vec[2]) <= FLOAT_ZERO  &&  fabs(vec[3]) < FLOAT_ZERO)
		return FALSE;
	return TRUE;
}



Slist<ParaPoint>* DB::HulConvt(Matrix<float>* p_matrix)
{ 
/*	#ifdef _DEBUG
		CMemoryState oldMemState, newMemState, diffMemState;
		oldMemState.Checkpoint();
	#endif
*/
if(STDB==TRUE)
{
	bool satisflag;

	if(p_matrix == NULL)
		return NULL;

   //p_matrix->Trace();
   //Relation* r = new Relation();
   Matrix<float>* p_m;
   Vector<float> vec1, vec2; 
   //Slist<AnalysisNode>* NodeList= new Slist<AnalysisNode>;
   Slist<ParaPoint>* PointList= new Slist<ParaPoint>;//checkmem
	// Declare the variables needed
   //DRK added
   vec1=(*p_matrix)[1];
   vec2=(*p_matrix)[2];
   ParaPoint *ppt1=new ParaPoint((-1)*vec1[7],vec1[1],(-1)*vec2[7],vec2[1]);
   vec1=(*p_matrix)[3];
   vec2=(*p_matrix)[4];
   ParaPoint *ppt2=new ParaPoint((-1)*vec1[7],vec1[1],(-1)*vec2[7],vec2[1]);
   
    PointList->GotoTail();
	PointList->AppendHere(*(new ParaPoint(*ppt1)));
	PointList->GotoTail();
	PointList->AppendHere(*(new ParaPoint(*ppt2)));
	delete ppt1;
	delete ppt2;
    return PointList;
	}

	else
	{
	bool satisflag;

	if(p_matrix == NULL)
	{
		return NULL;
	}
   //p_matrix->Trace();
   Vector<float> vec1, vec2; 
   Slist<ParaPoint>* PointList= new Slist<ParaPoint>;//checkmem
	// Declare the variables needed
	
   if(ImportLineFlag==TRUE)
   {
		vec1=(*p_matrix)[0];
		vec2=(*p_matrix)[1];
		ParaPoint *pnt1=new ParaPoint(0.0,vec1[1],0.0,vec2[1]);
		PointList->AppendHere(*(new ParaPoint(*pnt1)));
		vec1=(*p_matrix)[2];
		vec2=(*p_matrix)[3];
		ParaPoint *pnt2=new ParaPoint(0.0,vec1[1],0.0,vec2[1]);
		PointList->AppendHere(*(new ParaPoint(*pnt2)));
		delete pnt1;
		delete pnt2;
		return PointList;
   }

   /*now calculate the intersection of every two lines*/
   Matrix<float>* p_m;
   Relation* r = new Relation();
   Slist<AnalysisNode>* NodeList= new Slist<AnalysisNode>;

      for(int i=0; i< p_matrix->Rows()-1; i++)
      {   
          vec1 = (*p_matrix)[i];
          for(int j=i+1;j<p_matrix->Rows();j++){
             vec2= (*p_matrix)[j];
            if(ValidLine(vec1)  &&	ValidLine(vec2)  &&
				!Parallel(vec1,vec2))
               {
				ParaPoint p = Intersection(vec1,vec2);
                p_m = new Matrix<float>();
                vec2[0] = 5;
                vec2[1] = p.m_fXb;
                vec2[2] = 1;
                vec2[3] = 0;
				int nTemp = 4;
				if (vec2.Size() > 4)
				{
					vec2[4] = -p.m_fXa;
					nTemp = 5;
				}
				for (; nTemp<vec2.Size(); nTemp++)
					vec2[nTemp] = 0;
				AddVectorToMatrix(p_m,&vec2);
				vec2[0] = 5;
				vec2[1] = p.m_fYb;
				vec2[2] = 0;
				vec2[3] = 1;  
				nTemp = 4;
				if (vec2.Size() > 4)
				{
					vec2[4] = -p.m_fYa;
					nTemp = 5;
				}
				for (; nTemp<vec2.Size(); nTemp++)
					vec2[nTemp] = 0;
				AddVectorToMatrix(p_m,&vec2);
                for(int k = 0; k< p_matrix->Rows(); k++)
				{
					if( k !=i && k!= j)
					{
						vec2 = (*p_matrix)[k];
                        AddVectorToMatrix(p_m,&vec2);
                    }
				} 
//p_m ->Trace();
                 
				  if (p_m->Cols() <=SIMPLEX_SIZE)
						satisflag=r->MatrixSatisfiable(p_m);
				  else
						satisflag=dataBase->SimplexMatrixSatisfiable(p_m);
                 if(satisflag)
                  {
                      NodeList->AppendHere(
                              *new AnalysisNode(p,i,j));//checkmem major
                  } 
                  delete p_m;
               }

          }
      }//end for 
      //how many different nodes we have ?
       int num_of_nodes = 0;
       ParaPoint p;
       const AnalysisNode* p_aNode;
       SlistIter<AnalysisNode> nodeIter(*NodeList);

//      cout << *NodeList << endl;

      p_aNode = nodeIter();
      if(p_aNode){ 
            p = (*p_aNode).m_X;
            PointList->AppendHere(*(new ParaPoint(p_aNode->m_X)));     
            num_of_nodes++;
      } 

      while(p_aNode = nodeIter() ){
		  if(p != (*p_aNode).m_X){
                 PointList->AppendHere(*(new ParaPoint(p_aNode->m_X)));     
                 num_of_nodes++;  
		  }
      }
      // have only two points
      if(num_of_nodes<=2){
//         NodeList->DeepDestroy();
//          cout<<*PointList<<endl; 
          delete r;
		  delete NodeList;
          return PointList;
      }  

      // have more than 3 points
      PointList->Reset(); 
      // check which line is not convex hull edge 
	  //p_matrix->Trace();
      for(i=0;i< p_matrix->Rows(); i++){
        num_of_nodes = 0;
        nodeIter.Reset();
        while(p_aNode = nodeIter()){
			if(((i==(*p_aNode).m_line1)||(i==(*p_aNode).m_line2))
            && ((*p_aNode).m_flag == true))
            if(num_of_nodes==0)  
            {    p = (*p_aNode).m_X;
                 num_of_nodes++;
            }
            else{ 
               if( p != (*p_aNode).m_X)
                 num_of_nodes++;
			}
		}
		if(num_of_nodes<2){
           nodeIter.Reset();
           while(p_aNode = nodeIter()){
             if((i==(*p_aNode).m_line1)||(i==(*p_aNode).m_line2))
                    NodeList->Delete(*p_aNode);
           }
        }
     }//end for

      // now triangulate the convex hull points
      nodeIter.Reset(); 
      int line; 

      //have more than two points
      while(p_aNode = nodeIter()){
//        cout<<*p_aNode<<endl;
		if( (*p_aNode).m_flag==true)
		{
			line = min(p_aNode->m_line1, p_aNode->m_line2);
            break;
        }
      }
      while(p_aNode){
           PointList->AppendHere(*(new ParaPoint(p_aNode->m_X)));//checkmem
           NodeList->Delete(*p_aNode);        
           nodeIter.Reset();
           while(p_aNode=nodeIter()){
               if((p_aNode->m_flag==true)&&
                   (p_aNode->m_line1==line ||p_aNode->m_line2==line))
			   {
                    if(p_aNode->m_line1==line)
                        line=p_aNode->m_line2;
                    else line=p_aNode->m_line1;
                    break;
               }
           }
      } 

//   cout<<*PointList<<endl;
//  NodeList->DeepDestroy();
    delete r;
	delete NodeList;

    return PointList;
	
	}
};

bool Parallel(Vector<float> v1, Vector<float> v2)
{
    if((v1)[2]==0 && (v2)[2]==0) return true;
    if((v1)[3]==0 && (v2)[3]==0) return true;
    if( ((v1)[2]!=0 && (v2)[2]!=0) && 
        (((v1)[3]/(v1)[2])== ((v2)[3]/(v2)[2])) )
         return true;
    else 
       return false; 
}

ParaPoint Intersection(Vector<float> v1, Vector<float> v2)
{
// x = fXa*t + fXb
// y = fYa*t + fYb

	float fXa;
	float fYa;
	if (v1.Size()>4)
	{
		fXa =( v1[3]* v2[4]-v1[4]* v2[3])
           / ( v1[2]* v2[3]- v1[3]*v2[2]);
		fYa =( v1[4]* v2[2]-v1[2]* v2[4])
           / ( v1[2]* v2[3]- v1[3]*v2[2]);
	}
	else
		fXa = fYa = 0.0;
	float fXb =( v1[1]* v2[3]-v1[3]* v2[1])
           / ( v1[2]* v2[3]- v1[3]*v2[2]);
	float fYb =( v1[2]* v2[1]-v1[1]* v2[2])
           / ( v1[2]* v2[3]- v1[3]*v2[2]);

	return ParaPoint(fXa, fXb, fYa, fYb); 
}

float ParaPoint::Triangle_Area(ParaPoint B, ParaPoint C)
{
     ParaPoint A=*this;
     float area= (float)fabs((float)(0.5*(A.m_fX*(B.m_fY-C.m_fY)+ 
                     B.m_fX*(C.m_fY-A.m_fY)+
                     C.m_fX*(A.m_fY-B.m_fY))));
     return area;
}

float Point::Triangle_Area(Point B, Point C)
{
 /*    ParaPoint A=*this;
     float area= (float)fabs((float)(0.5*(A.m_fX*(B.m_fY-C.m_fY)+ 
                     B.m_fX*(C.m_fY-A.m_fY)+
                     C.m_fX*(A.m_fY-B.m_fY))));
     return area;
*/
	return 0;
}


void DB::Display_points(const char* relName,ostream& os )
{
  const Relation* relPtr ;
  //Relation* r;
  //Relation* p_r;  
  if (!(relPtr = RetrieveRelation(relName))) {
      cout << "\"" << relName << "\":" << " No such relation in data base\n" ;
      return;
  }
  else{
     
   const Matrix<float>* p_matrix;
  
   Matrix<float>* p_m;   
   Vector<float> vec1; 

//   os << "Relation \" " << relPtr->m_sName<< endl;
   if(relPtr->m_Satisfiable==1)  {
         cout << " is Universally Satisfiable" << endl;
         return;
   }
   if(relPtr->m_Satisfiable==-1)  {
         cout  << " is Unsatisfiable. " << endl;
         return;
   }
   DFIter<Matrix<float> >  matrixIter(*(relPtr->m_tablePtr));
   //cout  << " : Arity = "<< prel->Arity() << endl;
   os << (relPtr->m_tablePtr)->Size()<<endl;
   /*now change the relation to new format*/
   int cols = (((Relation*)relPtr)->Arity())+1; 
   vec1 = Vector<float>(cols);
   while(p_matrix =  matrixIter()) { 
      p_m = new Matrix<float>();
      for(int i=0; i< p_matrix->Rows()-1; i++)
      {   
            vec1[0]=(*p_matrix)[i+1][0];
	    vec1[1]=(*p_matrix)[i+1][1];
            vec1[2]=(*p_matrix)[i+1][3];
	    vec1[3]=(*p_matrix)[i+1][4];
            AddVectorToMatrix(p_m,&vec1);
      }

      //error cout<< *p_m<<endl;
	  Slist<ParaPoint>* pointList = HulConvt(p_m);
      os << pointList->Size()<<endl;
      os <<  *pointList << endl; 
      delete p_m;
//      p_m =  new Matrix<float>(); 
      
   }/* end of while*/
   return; 
  }
}



