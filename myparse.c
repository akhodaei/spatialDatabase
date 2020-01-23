#include <stdio.h>

#include <stdlib.h>

#include <string.h>

#include <math.h>


#include "myparse.h"

/* Type and Variable Declaration */



#define SCALE_SIZE	 10000	/* to scale 'cost' from double type to int type */

#define CONST_COST	 0





int   **Cost;

int protolnum,distlnum, consCost;



/*	 Function Declaration */



double Anglediff(struct Line *l1, struct Line *l2);

double MidPntDist(struct Line *l1, struct Line *l2);

double LengthDiff(struct Line *l1, struct Line *l2);

double LengthSum(struct Line *l1, struct Line *l2);

/*double** simCal(int opt, struct pic_t *ptype, struct pic_t *dtype);*/

void CalCost(int opt, struct pic_t *ptPpic, struct pic_t *ptDpic);

int  CalNumPics(struct pic_t *ptPpic);

void CalPSegnum(struct pic_t *ptPpic);

void CalDSegNum(struct pic_t *ptDpic);

double CSA_S();



void Output();

double** simCal(int opt, struct pic_t *protopic, struct pic_t *distpic)

{

	struct pic_t *ptPpic, *ptDpic;

	int lnum, i, ppicnum, dpicnum, j = 0, k = 0;

	double **tot_cost;

	

	ptPpic = protopic;

	ptDpic = distpic;

	

	ppicnum = CalNumPics(protopic);

	tot_cost = malloc(sizeof(void*)*ppicnum);

	dpicnum = CalNumPics(distpic);

	for(i = 0; i < ppicnum; i++)

		tot_cost[i] = malloc(sizeof(double)*dpicnum);

	

	while (ptPpic!= NULL){

		CalPSegnum(ptPpic);

		lnum = protolnum;

		while (ptDpic != NULL){

			CalDSegNum(ptDpic);

			if (distlnum>lnum)

				lnum = distlnum;

			Cost = malloc(sizeof(void *)*lnum); 

			for(i=0; i<lnum;i++)

				Cost[i] = malloc(sizeof(long)*lnum);

			CalCost(opt, ptPpic, ptDpic);

			Output();

			

			tot_cost[j][k] =  (1) * CSA_S()/SCALE_SIZE;

			

			free(Cost);

			ptDpic = ptDpic->nextp;

			k++;

		}

		ptPpic = ptPpic->nextp;

		j++;

	} 

	

	return tot_cost;/* to be defined */

}


/*void main()

{

	int i, j, numDist = 2;

	double **tot_cost;

	int option = 1, LineNum = 10;

	char filename[20];

	struct pic_t Ppic[1], *Dpic, *dp;

	struct Line *pp, *nextp;

	

	FILE *DataFile;

	

	printf("\nPlease input the data file name: "); 

	scanf("%s", filename);

	DataFile = fopen(filename,"r+");

	if (DataFile == NULL){

		printf("\n file open error!!!");

		exit(1);

	}

	// read in the prototype pictuer from file 

	Ppic[0].nextp = NULL;

	pp = malloc(sizeof(struct Line));

	fscanf(DataFile, "%f %f %f %f",&pp->x1, &pp->y1,&pp->x2, &pp->y2);

	pp->nextl = NULL;

	Ppic->lseg = pp;

	nextp = pp; 

	for ( i=1; i<LineNum; i++){

		pp = malloc(sizeof(struct Line));

		fscanf(DataFile, "%f %f %f %f",&pp->x1, &pp->y1,&pp->x2, &pp->y2);

		pp->nextl = NULL;

		

		nextp->nextl = pp;

		pp->nextl = NULL;

		nextp = nextp->nextl;		

	}

	

	Dpic = malloc(sizeof(struct pic_t));

	dp = Dpic;

	dp->nextp = NULL;

	// read in the distortion pictuer from file 

	for(j = 0 ; j < numDist; j++)

	{

		pp = malloc(sizeof(struct Line));

		fscanf(DataFile, "%f %f %f %f",&pp->x1, &pp->y1,&pp->x2, &pp->y2);

		pp->nextl = NULL;

		dp->lseg = pp;

		nextp = pp; 

		for ( i=1; i<LineNum; i++){

			pp = malloc(sizeof(struct Line));

			fscanf(DataFile, "%f %f %f %f",&pp->x1, &pp->y1,&pp->x2, &pp->y2);

			pp->nextl = NULL;

		

			

			pp->nextl = NULL;

			nextp->nextl = pp;

			nextp = nextp->nextl;

		}

		if(j != numDist - 1)

		{

			dp->nextp = malloc(sizeof(struct pic_t));

			dp = dp->nextp;

			dp->nextp = NULL;

		}

		else

			dp->nextp = NULL;

	}



	fclose(DataFile);

	

	tot_cost = simCal(option, Ppic, Dpic);

	return;

}*/













/* Function Implementation */



double AngleDiff(struct Line *l1, struct Line *l2)

/* Angle range 0 - 90 degree */

{

	double pi = 22/7;

	double angle1, angle2, Angle;

	

	if (l1->x1 == l1->x2)

		angle1 = pi/2;

	else 

		angle1 = atan((l1->y1 - l1->y2)/(l1->x1 - l1->x2));

	

	if (l2->x1 == l2->x2)

		angle2 = pi/2;

	else 

		angle2 = atan((l2->y1 - l2->y2)/(l2->x1 - l2->x2));

	

	/*Angle = fabs(angle1 - angle2)*180/pi;*/
	Angle = fabs(angle1 - angle2);
	Angle = Angle > pi/2 ? Angle - pi/2 : Angle;

	

	return Angle;

}



double MidPntDist(struct Line *l1, struct Line *l2)

{

	double m1_x, m1_y, m2_x, m2_y, MDist;

	

	m1_x = (l1->x1+l1->x2)/2;

	

	m1_y = (l1->y1+l1->y2)/2;

	

	m2_x = (l2->x1+l2->x2)/2;

	

	m2_y = (l2->y1+l2->y2)/2;

	

	MDist = sqrt(pow((m1_x - m2_x),2) + pow((m1_y - m2_y),2));

	

	return MDist;

}



double LengthDiff(struct Line *l1, struct Line *l2)

{

	double len1, len2, LenDiff;

	

	len1 = sqrt(pow((l1->x1 - l1->x2),2) + pow((l1->y1 - l1->y2),2));

	

	len2 = sqrt(pow((l2->x1 - l2->x2),2) + pow((l2->y1 - l2->y2),2));

	

	LenDiff = fabs(len1 - len2);

	

	return LenDiff;

}





double LengthSum(struct Line *l1, struct Line *l2)

{

	double len1, len2, LenSum;

	

	len1 = sqrt(pow((l1->x1 - l1->x2),2) + pow((l1->y1 - l1->y2),2));

	

	len2 = sqrt(pow((l2->x1 - l2->x2),2) + pow((l2->y1 - l2->y2),2));

	

	LenSum = len1 + len2;

	

	return LenSum;

}



int CalNumPics(struct pic_t *ptPpic)

{

	struct pic_t *pl;

	

	protolnum = 0;

	if (ptPpic != NULL){

		pl = ptPpic->nextp;

		while(pl != NULL){

			protolnum ++;

			pl = pl->nextp;

		}

	}

	return protolnum + 1;

}



void CalPSegnum(struct pic_t *ptPpic)

{

	struct Line *pl;

	

	protolnum = 0;

	if (ptPpic != NULL){

		pl = ptPpic->lseg;

		while(pl != NULL){

			protolnum ++;

			pl = pl->nextl;

		}

	}

}



void CalDSegNum(struct pic_t *ptDpic)

{

	struct Line *pl;



	distlnum = 0;

	if (ptDpic != NULL){

		pl = ptDpic->lseg;

		while(pl != NULL){

			distlnum ++;

			pl = pl->nextl;

		}

	}

	

}



void  CalCost(int opt, struct pic_t *ptPpic, struct pic_t *ptDpic)

{

	double LSim, angle;

	double WLength, WMidPnt, WSlope;

	int i, j, p, d;

	struct Line *LineSet1, *LineSet2;

	

	i=0,j=0, consCost = CONST_COST;

	

	switch (opt){

	case 3:

		WSlope = 1;

		WLength = 1;

		WMidPnt = 1;

		LineSet1 = ptPpic->lseg;

		LineSet2 = ptDpic->lseg;

		while (LineSet1 != NULL ){

			j = 0;

			while(LineSet2 != NULL){

				LSim = WSlope * AngleDiff(LineSet1, LineSet2) 

					+ WLength * LengthDiff(LineSet1,LineSet2) 

					+ WMidPnt * MidPntDist(LineSet1,LineSet2);

				Cost[i][j++] = (int) (-LSim*SCALE_SIZE);

				LineSet2 = LineSet2->nextl;

			}

			LineSet2 = ptDpic->lseg;

			LineSet1 = LineSet1->nextl;

			i++;

		}

		

		break;

	case 2: 

		WSlope = 8;

		WLength = 5;

		WMidPnt = 1;

		LineSet1 = ptPpic->lseg;

		LineSet2 = ptDpic->lseg;

		while (LineSet1 != NULL ){

			j = 0;

			while(LineSet2 != NULL){

				angle = AngleDiff(LineSet1,LineSet2);

				if (angle > 1)

					LSim = WSlope * log(angle)/log(2)

					+ WLength * pow(LengthDiff(LineSet1,LineSet2), 2) 

					+ WMidPnt * MidPntDist(LineSet1,LineSet2);

				else	  /* WSlope * log(angle)/log(2) = 0   */

					LSim = WLength * pow(LengthDiff(LineSet1,LineSet2), 2) 

					+ WMidPnt * MidPntDist(LineSet1,LineSet2);

				Cost[i][j++] = (int) (-LSim*SCALE_SIZE);

				LineSet2 = LineSet2->nextl;

			}

			LineSet2 = ptDpic->lseg;

			LineSet1 = LineSet1->nextl;

			i++;

		}

		

		break;

		

	case 1: 

		WSlope = 1;

		WLength = 1;

		WMidPnt = 1;

		LineSet1 = ptPpic->lseg;

		LineSet2 = ptDpic->lseg;

		while (LineSet1 != NULL ){

			j = 0;		

			while(LineSet2 != NULL){

				LSim = WSlope * LengthSum(LineSet1,LineSet2)*sin(AngleDiff(LineSet1,LineSet2)) 

					+ WLength * LengthDiff(LineSet1,LineSet2) 

					+ WMidPnt * MidPntDist(LineSet1,LineSet2);

				Cost[i][j++] = (int) ((-1) * LSim * SCALE_SIZE);

				LineSet2 = LineSet2->nextl;

			}

			LineSet2 = ptDpic->lseg;					

			LineSet1 = LineSet1->nextl;

			i++;

		}

		

		break;

		

	default:

		printf("\n Unknown Distance formula number.\n");	

		exit(0);

	}

	/* for each unpaired line segment, assign a constant distance */

	if (i>j){

		for (p = 1; p < i; p++)

			for (d = j; d < i; d++)

				Cost[p][d] = CONST_COST;

	}

	if (i<j){

		for (p = i; p < j; p++)

			for (d = 0; d < j; d++)

				Cost[p][d] = CONST_COST;

	}

	return;

}







void Output()

{

	int i, j;

	int LineNum;

	

	FILE *fp;

	fp = fopen("cost.dat", "w+");

	

	LineNum = protolnum>distlnum ? protolnum : distlnum ;

	fprintf(fp,"p asn %d %d\n", LineNum*2, LineNum*LineNum);

	for(i=1; i<=LineNum; i++)

		fprintf(fp,"n %d\n",i);

	for(j=LineNum+1; j<=2*LineNum; j++)

		for(i=1; i<=LineNum; i++)

			fprintf(fp,"a  %d  %d %d\n", i, j, Cost[i-1][j-LineNum-1]);

		

		fclose(fp);

		return;

}











