#include<iostream.h>
#include<malloc.h>
#include<string.h>
#include<fstream.h>

struct node
{

float data1;
float data2;
struct node *link;

};


class list
{
 public:
  void append(node **q,float num1, float num2);
  void display(node *q);
//  void addatbeg(node **q,char num[]);
//  void addafter(node *q,int loc,char num[]);
//  void changeRelationAttr(node *q);
 // void deletenode(node **q,int num);

};
