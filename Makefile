vpath %.c src
vpath %.h include
vpath %.o object

CPPFLAGS = -I include
BASEFILE = main.c init.c check.c read_data.c
MPIFILE = mpi.c
CC = gcc

%.o: ${BASEFILE}
	${CC} -c ${CPPFLAGS} $^
	mv *.o object/

a.out: object/*.o
	${CC} ${CPPFLAGS} $^ -o a.out
