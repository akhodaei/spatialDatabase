#ifndef _NRUTILS_H
#define _NRUTILS_H

void nrerror(char error_text[]);
int *ivector(long nl, long nh);
float **convert_matrix(float *a,long nrl,long nrh,long ncl,long nch);
void free_ivector(int *v,long nl,long nh);
void free_convert_matrix(float **b,long nrl,long nrh,long ncl,long nch);
float f_convert(char []);
void itoc(int, char []);


#endif

