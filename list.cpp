#include "list.h"

/*
int main()
{
  node *p;
  p=NULL;

  list l;

  l.append(&p,1);
  l.append(&p,2);
  l.append(&p,3);
  l.display(p);
  l.addatbeg(&p,0);
  l.display(p);
  l.addafter(p,2,10);
  l.display(p);
  l.deletenode(&p,2);
  l.display(p);

}
*/

void list::append(node **q, float num1 , float num2)
{
  node *temp;
  temp=*q;
  if(*q==NULL)
  {
    *q=(node *)malloc(sizeof(struct node));
    temp=*q;
  }
  else
  {
    while(temp->link!=NULL)
     temp=temp->link;
    temp->link=(node *)malloc(sizeof(struct node));
    temp=temp->link;
  }
  temp->data1 = num1;
  temp->data2 = num2;
  temp->link=NULL;
}

void list::display(node *q)
{
//	fstream output;
//	output.open("output.txt",ios::out);
 while(q!=NULL)
  {
//    output << q->data << endl;
    q=q->link;
  }
//  output<<endl;
}
/*
void list::changeRelationAttr(node *q)
{
//	fstream output;
//	output.open("output.txt",ios::app);
//	output << "Syed" << endl;
	while(q!=NULL)
	{
		if(!strcmp(q->data,":-"))
			break;
		q=q->link;
	}

	q=q->link;

	while(q!=NULL)
	{
		char store[100];
		int k = 0;
		char temp1[100];
		strcpy(temp1,q->data);
//		output << temp1 << endl;
		q=q->link;
		char temp2[100];
		strcpy(temp2,q->data);

		for(int i=0;i<strlen(temp2);i++)
		{
			if(temp2[i]==' ')
				continue;
			if(temp2[i]=='(')
			{
				store[k++] = temp2[i];
				for(int j=0;j<strlen(temp1);j++)
					store[k++] = temp1[j];
				continue;
			}
			if(temp2[i]==',')
			{
				store[k++] = temp2[i];
				for(int j=0;j<strlen(temp1);j++)
					store[k++] = temp1[j];
				continue;
			}
			store[k++]= temp2[i];
		}
		store[k]='\0';
		strcpy(q->data,store);
//		output << q->data << endl;
		q=q->link;
		q=q->link;
	}
}


void list::addatbeg(node **q,char num[])
{
 node *temp;
 temp=(node *)malloc(sizeof(struct node));
 strcpy(temp->data,num);
 temp->link = *q;
 *q=temp;
}

void list::addafter(node *q,int loc, char num[])
{
node *temp;
int i;
for(i=0;i<loc-1;i++)
{
 q=q->link;
if(q==NULL)
 {
  cout << "there are less than " << loc << "elements" << endl;
  return;
 }
}
temp=(node *)malloc(sizeof(struct node));
strcpy(temp->data,num);
temp->link=q->link;
q->link=temp;
}
*/
/*
void list::deletenode(node **q,int num)
{
 node *old,*temp;
 temp=*q;
 while(temp!=NULL)
 {
  if(temp->data==num)
  {  
   if(temp==*q)
    {
     *q=temp->link;
      free(temp);
      return;
}
else
 {
 old->link=temp->link;
free(temp);
return;
}
}
else
{
 old=temp;
temp=temp->link;
}
}
cout << "element not found"<< endl;
}
*/
