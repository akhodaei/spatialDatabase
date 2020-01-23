CFLAGS = -lm -g 
CC=CC 
FLEX_FLAGS = -8 -I -L -H/usr/home/disco/flex/flexskel.h -S/usr/home/disco/flex/flexskel.cc
YACC_FLAGS = -l -d
FLEX = /usr/home/disco/flex/flex++
BISON =  /usr/dist/pkgs/bison++-1.21-8/bin/bison++ --debug -v
CSOURCES=lpkit.c solve.c debug.c read.c readmps.c lp_solve.c demo.c hash.c lp.c
COBJ=$(CSOURCES:.c=.o)
.SUFFIXES : .cpp .cc .y .l $(SUFFIXES)

.cc.o :
	$(CC) $(CFLAGS) -c $*.cc
.cpp.o:
	$(CC) $(CFLAGS) -c $*.cpp
.l.o  :
	$(CC) $(CFLAGS) -c $*.cc
.y.o  :
	$(CC) $(CFLAGS) -c $*.cc

##.y.cc :
##	$(BISON) $(YACC_FLAGS) -o$*.cc -h$*.h  $*.y

##.l.cc :
#	$(FLEX)  $(FLEX_FLAGS) -h$*.h -o$*.cc $*.l
##.y.h :
#	$(BISON) $(YACC_FLAGS) -o$*.cc -h$*.h  $*.y
##.l.h :
#	$(FLEX) $(FLEX_FLAGS) -h$*.h -o$*.cc $*.l

.h.c:
	touch $*.c
.h.cpp:
	touch $*.cpp
obj= scanner.o parser.o  string.o engine.o db.o slist.o \
     vector.o matrix.o dlist.o relation.o arg.o  debug.o \
     hash.o  lpkit.o read.o solve.o lp.o lp_solve.o readmps.o\
     hulconvt.o hulreconvt.o 
      
lcs:  $(obj) stack.cpp
	$(CC) $(obj) $(CFLAGS) lcs.cpp  -o lcs -ll

debug.o : debug.c debug.h
	cc -c -g debug.c

hash.o : hash.c hash.h
	cc -c -g hash.c

lpkit.o : lpkit.c lpkit.h
	cc -c -g lpkit.c

read.o : read.c read.h
	cc -c -g read.c

solve.o : solve.c
	cc -c -g solve.c


lp.o : lp.c
	cc -c -g lp.c

lp_solve.o : lp_solve.c
	cc -c -g lp_solve.c

readmps.o : readmps.c
	cc -c -g readmps.c
parser.o : parser.cc parser.h

scanner.o : scanner.cc scanner.h parser.h

relation.o: simplexlcs.cpp  string.o dlist.o slist.o matrix.o vector.o arg.o
	$(CC) -c -g relation.cpp
db.o : relation.o matrix.o slist.o dlist.o vector.o arg.o
	$(CC) -c -g db.cpp
matrix.o : matrix.cpp matrix.h 
	$(CC) -c -g matrix.cpp
vector.o : vector.cpp vector.h
	$(CC) -c -g vector.cpp

string.o : string.cpp string.h 
	$(CC) -c -g string.cpp 

slist.o : slist.cpp slist.h
	$(CC) -c -g slist.cpp 
arg.o   : arg.cpp arg.h
	$(CC) -c -g arg.cpp
dlist.o : dlist.h dlist.cpp
	$(CC) -c -g dlist.cpp
hulconvt.o:	hulstruct.h hulconvt.cpp	
	$(CC) -c -g hulconvt.cpp
hulreconvt.o:	hulstruct.h hulreconvt.cpp
	$(CC) -c -g hulreconvt.cpp
engine.o:	engine.h engine.cpp
	$(CC) -c -g engine.cpp
##parser.cc : parser.y scanner.l

#scanner.cc : scanner.l parser.y parser.cc

#parser.h : parser.y

#scanner.h : scanner.l




ptclean:
	ptclean

clean:
	rm -rf *.o parser.o scanner.o core lcs

fresh:
	rm -rf *.o parser.o scanner.o\
     core lcs ptrepository










