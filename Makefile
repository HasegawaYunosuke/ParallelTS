vpath %.c src mpi
vpath %.h include
vpath %.o object

CPPFLAGS = -I include
BASEFILE = main.c init.c check.c read_data.c
MPIFILE = mpi.c
MPIFLAG = -DMPIMODE
DEBUGFLAG1 = -DDEBUG1
CC = gcc

%.o: ${BASEFILE}
	${CC} -c ${CPPFLAGS} $^
	mv *.o object/

a: object/*.o
	${CC} ${CPPFLAGS} $^ -o a.out

mpi: ${BASEFILE} ${MPIFILE}
	${CC} ${CPPFLAGS} ${MPIFLAG} $^ -o b.out

debug: ${BASEFILE}
	${CC} ${CPPFLAGS} ${DEBUGFLAG1} $^ -o d.out

debugmpi: ${BASEFILE} ${MPIFILE}
	${CC} ${CPPFLAGS} ${MPIFLAG} ${DEBUGFLAG1} $^ -o dm.out
