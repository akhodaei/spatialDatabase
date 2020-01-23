/***************************************************
 * Name:     hulstruct.h
 * Author:   Huge Wang
 * Time:     July 31, 1997
 * Descript: define of class Point and class AnalysisNode
 *
 ***************************************************/

#ifndef HULSTRUCT_H
#define HULSTRUCT_H

#include <iostream.h>
//#include "string.h"
#include "slist.h"
//#include "vector.h"

#include "GlobalVar.h"
//#define FLOAT_MIN_BOUND  0.00002

class ParaPoint		// parametric point x=at+b
{
public:
	ParaPoint() 
	{	
		m_fXa = 0; 
		m_fXb = 0; 
		m_fYa = 0; 
		m_fYb = 0; 
		m_fX = 0; 
		m_fY = 0; 
		m_bShow = TRUE;
	}

	ParaPoint(float fXa, float fXb, float fYa, float fYb)
	{  
		m_fXa = fXa; 
		m_fX = m_fXb = fXb; 
		m_fYa = fYa; 
		m_fY = m_fYb = fYb;
		m_bShow = TRUE;
	}

	ParaPoint(const ParaPoint& p)
	{	
		m_fXa = p.m_fXa; 
		m_fX = m_fXb = p.m_fXb; 
		m_fYa = p.m_fYa; 
		m_fY = m_fYb = p.m_fYb; 
		m_bShow = TRUE;
	}

	float Triangle_Area(ParaPoint B, ParaPoint C);

	ParaPoint& operator = (const ParaPoint& a)
	{
		if (this != &a) 
		{
			this->m_fXa = a.m_fXa;
			this->m_fX = this->m_fXb = a.m_fXb;
			this->m_fYa = a.m_fYa;
			this->m_fY = this->m_fYb = a.m_fYb;
		}
		return *this ; 
	}

	bool operator == (const ParaPoint& a) const
	{ 
		double t1 = fabs(m_fXa - a.m_fXa);
		double t2 = fabs(m_fXb -a.m_fXb);
		//??
		double t3 = fabs(m_fYa - a.m_fYa);
		double t4 = fabs(m_fYb - a.m_fYb);
		return ((t1 < FLOAT_ZERO) && (t2 < FLOAT_ZERO)
			&& (t3 < FLOAT_ZERO)  && (t4 < FLOAT_ZERO) 
			? true : false);
	
	
/*		return ((m_fXa == a.m_fXa) && (m_fXb == a.m_fXb)
			&& (m_fYa == a.m_fYa)  && (m_fYb == a.m_fYb) 
			? true : false); */
	}

	bool operator != (const ParaPoint& a) const 
	{ return (*this == a) ? false : true ; }
	
public:
	float m_fXa;
	float m_fXb;
	float m_fYa; 
	float m_fYb;
	float m_fX;
	float m_fY;
	BOOL  m_bShow;

	friend ostream& operator << (ostream& os, const ParaPoint& a) 
	{ 
		os << a.m_fX <<" "<< a.m_fX; 
		return os ;
	}
};

class Point
{
 public :
   // Arg Constructors
   Point()
      {  m_x = 0;
         m_y = 0;
      } 
    Point(float i, float j) 
      { m_x = i ; m_y = j; }
    Point(const Point& p)
      { m_x = p.m_x; m_y=p.m_y; }
 
    // Point Destructor
   ~Point() {  };
   
   // Point Operators 
   Point& operator = (const Point& a) 
   { if (this != &a) 
     {  this->m_x = a.m_x;
        this->m_y = a.m_y;
     }
     return *this ; 
   }

   bool operator == (const Point& a) const 
      { 
        return ((m_x == a.m_x)&&(m_y == a.m_y)) ? true :false;
      }

   bool operator != (const Point& a) const 
      { return (*this == a) ? false : true ; }
   float Getx(){ return m_x;}; 
   float Gety(){ return m_y;};
 public :
      float m_x;
      float m_y; 
   float Triangle_Area(Point B, Point C);
   friend ostream& operator << (ostream& os, const Point& a) 
   { 
     os << a.m_x <<" "<<a.m_y; 
     return os ;
   }
};


class AnalysisNode
{
 public :
   // AnalysisNode Constructors
   AnalysisNode()
      {  
		 m_X = ParaPoint();
         m_line1 = 0;
         m_line2 = 0;
         m_flag  = true;  
      }
   AnalysisNode(ParaPoint p, int i, int j)
   {
         m_X = ParaPoint(p);
         m_line1=i;
         m_line2=j;
         m_flag = true;
    }
   // AnalysisNode Destructor
   ~AnalysisNode() { /*delete &m_X;*/  }
   bool operator == (const AnalysisNode& a) const 
      { 
        return ((m_X != a.m_X) ? false :
           ( (m_line1!=a.m_line1) ? false:
                          ( (m_line2!=a.m_line2)?false : true)));}
   bool operator != (const  AnalysisNode& a) const 
      { return (*this == a) ? false : true ; }
private:
       ParaPoint m_X;
       int m_line1;
       int m_line2;
       bool m_flag;
   friend ostream& operator << (ostream& os, const AnalysisNode& a) 
   { 
     os /*<<a.m_X*/ <<" "<<a.m_line1<<" "<<a.m_line2<<" "<< (int)a.m_flag<<endl; 
     return os ;
   }
   friend class DB;
}; 
bool Parallel(Vector<float> v1, Vector<float> v2);
ParaPoint Intersection(Vector<float> v1, Vector<float> v2);
Vector<float>* GetVectorFromPoints(Point p0, Point p1, Point p2);
bool CoLine(Point p0, Point p1, Point p3);
bool Complement(Vector<float>* vec1, Vector<float>* vec2);
#endif



