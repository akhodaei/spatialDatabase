//#include<stdio.h>

struct Line{

	float x1;

	float y1;

	float x2;

	float y2;

	struct Line *nextl;

};



struct pic_t{

	struct Line *lseg;

	struct pic_t *nextp;

};

//double** simCal(int opt, struct pic_t *protopic, struct pic_t *distpic);
