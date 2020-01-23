#include <stdlib.h>
#include <stddef.h>
#include <string.h>
#include <stdio.h>
#include "nrutil.h"
#define NR_END 1 


/* Numerical recipes standard error handler */
void nrerror(char error_text[])
{
	
	fprintf(stderr,"Numerical Recipes run-time error...\n");
	fprintf(stderr,"%s\n",error_text);
	fprintf(stderr,"...now exiting to system...\n");
	exit(1);
}

/* allocate an int vector with subscript range v[nl...nh] */
int *ivector(long nl,long nh)
{
	int *v;

        v=(int *)malloc((size_t)((nh-nl+1+NR_END)*sizeof(int)));
	if (!v) nrerror("allocation failure in ivector()");
	return v-nl+NR_END;
}

/* allocate a float matrix m[nrl..nrh][ncl..nch] that points to the
   matrix declared in the standard C mananer as a[nrow][ncol], where
   nrow=nrh-nrl+1 and ncol=nch-ncl+1. The routine should be called
   with the address &a[0][0] as the first argument */ 
float **convert_matrix(float *a,long nrl,long nrh,long ncl,long nch)
{
	long i,j,nrow,ncol;
	float **m;

	nrow=nrh-nrl+1;
	ncol=nch-ncl+1;
        /* allocate pointers to pointers to rows */
      	m = (float **) malloc((size_t) ((nrow+NR_END)*sizeof(float*)));
	if (!m) nrerror("allocation failure in convert_matrix()");
        m += NR_END;
	m -= nrl;

	/*set pointers to rows */
     	m[nrl]=a-ncl;

	for(i=0,j=nrl+1;i<=nrow;i++,j++) m[j]=m[j-1]+ncol;
        /*return pointer to array of pointers to rows */
	return m;
}


/* free an int vector allocated with ivector() */
void free_ivector(int *v,long nl,long nh)
{
       	free((char*) (v+nl-NR_END));
}

/* free a matrix allcoated by convert_matrix */
void free_convert_matrix(float **b,long nrl,long nrh,long ncl,long nch)
{
       	free((char*) (b+nrl-NR_END));
}

float f_convert(char s[])
{
int k,sign,digit,period;
float amount,point;
k = 0;
sign=1;
	while(s[k])
		if (s[k++]=='-') sign=-1;
	k= period=0;
	amount=(float)0;
	point=1;
	while(s[k]){
		if (s[k]=='.') period=1;
		if (s[k]>='0'&& s[k]<='9')
		{
			digit=s[k]-'0';
			amount*=10;
			amount+=digit;
			if(period==1) point*=(float) .1;
		}
		k++;
	}
	amount *=point;
	amount *=sign;
	return (amount);
}

void itoc(int n,char s1[])
{
int c;

   s1[0]=n%10+'0';
   n=n/10;
   if (n>0){
      s1[1]=n%10+'0';
      c=s1[0];
      s1[0]=s1[1];
      s1[1]=c;
   }
}



