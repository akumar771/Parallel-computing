COMPILER = gcc
CFLAGS = -Wall -pedantic

EXES = example01 example02  example03 example04 example05 example06

all: ${EXES}


example01:  example01.c 
	${COMPILER} ${CFLAGS}  example01.c -o example01
example02:  example02.c 
	${COMPILER} ${CFLAGS}  example02.c -o example02
example03:  example03.c
	${COMPILER} ${CFLAGS}  example03.c -o example03
example04:  example04.c
	${COMPILER} ${CFLAGS}  example04.c -o example04
example05:  example05.c
	${COMPILER} ${CFLAGS}  example05.c -o example05
example06:  example06.c
	${COMPILER} ${CFLAGS}  example06.c -o example06
clean: 
	rm -f *~ *.o ${EXES}
