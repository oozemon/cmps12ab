MKFILE    = Makefile
DEPSFILE  = ${MKFILE}.deps
NOINCLUDE = ci clean spotless
NEEDINCL  = ${filter ${NOINCLUDE}, ${MAKECMDGOALS}}

GCC       = gcc -g -O0 -Wall -Wextra -std=gnu99
MKDEPS    = gcc -MM
GRIND     = valgrind --leak-check=full

CSOURCE   = main.c queue.c
CHEADER   =        queue.h
OBJECTS   = ${CSOURCE:.c=.o}
EXECBIN   = catqueue
SOURCES   = ${CHEADER} ${CSOURCE} ${MKFILE}
LISTSRC   = ${SOURCES} ${DEPSFILE}
LISTING   = Listing.catqueue.ps
OUTPUT    = output*.lis

all : ${EXECBIN}

${EXECBIN} : ${OBJECTS}
	${GCC} -o $@ ${OBJECTS}

%.o : %.c
	${GCC} -c $<

git:
	- git commit -a

gitp:
	- git push

lis : ${SOURCES} test
	mkpspdf ${LISTING} ${LISTSRC} ${OUTPUT}

clean :
	- rm ${OBJECTS} ${DEPSFILE} core ${OUTPUT}

spotless : clean
	- rm ${EXECBIN}

test : ${EXECBIN}
	- runprogram.perl -x output1.lis -0test1.data ${EXECBIN}
	- runprogram.perl -x output2.lis ${EXECBIN} test*.data
	- ${GRIND} ${EXECBIN} <test1.data >output3.lis 2>&1

deps : ${CSOURCE} ${CHEADER}
	@ echo "# ${DEPSFILE} created `date`" >${DEPSFILE}
	${MKDEPS} ${CSOURCE} | sort | uniq >>${DEPSFILE}

submit:
	submit cmps012b-wm.s14 lab7 Makefile main.c queue.c queue.h

${DEPSFILE} :
	@ touch ${DEPSFILE}
	${MAKE} --no-print-directory deps


again :
	gmake spotless deps ci all lis

ifeq "${NEEDINCL}" ""
include ${DEPSFILE}
endif

