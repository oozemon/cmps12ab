# usman zahid
# uzahid

GCC      = gcc -g -O0 -Wall -Wextra -std=gnu99

CSOURCES = l9stat.c
SOURCES  = ${CSOURCES} Makefile README
EXECBINS = l9stat
SUBMIT   = submit cmps012b-wm.s14 lab9 ${SOURCES}

all : ${EXECBINS}

% : %.c
	- checksource $<
	${GCC} $< -o $@

clean :
	- rm core

spotless : clean
	- rm ${EXECBINS}

git:
	- git commit -a

submit : ${SOURCES} 
	 ${SUBMIT}

again : ${SOURCES}
	gmake --no-print-directory spotless ci all lis
