#Usman Zahid
#uzahid

MKFILE    = Makefile
DEPSFILE  = ${MKFILE}.deps
NOINCLUDE = clean spotless
NEEDINCL  = ${filter ${NOINCLUDE}, ${MAKECMDGOALS}}

GCC       = gcc -g -O0 -Wall -Wextra -std=gnu99
MKDEPS    = gcc -MM
GRIND     = valgrind --leak-check=full

CSOURCE   = numsort.c inssort.c
CSOURCE2  = linesort.c inssort.c
CHEADER   = inssort.h
OBJECTS   = ${CSOURCE:.c=.o}
OBJECTS2  = ${CSOURCE2:.c=.o}
EXECBIN   = numsort
EXECBIN2  = linesort
SOURCES   = ${CHEADER} ${CSOURCE} linesort.c ${MKFILE}

OUTPUT    = output*.lis

all : ${EXECBIN} ${EXECBIN2}

${EXECBIN} : ${OBJECTS}
	${GCC} -o $@ ${OBJECTS}

${EXECBIN2} : ${OBJECTS2}
	${GCC} -o $@ ${OBJECTS2}

%.o : %.c
	- checksource ${SOURCES}
	${GCC} -c $<

git:
	- git commit -a

gitp:
	- git push

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

check : ${SOURCES}
	checksource ${SOURCES}

submit:
	submit cmps012b-wm.s14 lab8 ${SOURCES} README

${DEPSFILE} :
	@ touch ${DEPSFILE}
	${MAKE} --no-print-directory deps


again :
	gmake spotless deps all

ifeq "${NEEDINCL}" ""
include ${DEPSFILE}
endif
