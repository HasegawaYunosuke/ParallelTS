vpath %.c src mpi
vpath %.h include
vpath %.o object

CPPFLAGS = -I include -g -pthread
BASEFILE = main.c init.c check.c read_data.c file_manage.c error.c memory.c finalize.c math.c pthread.c init_path.c timer.c search.c tabu.c result.c debug.c
MPIFILE = mpi.c
MPIFLAG = -DMPIMODE
DEBUGFLAG1 = -DDEBUG1
CC = gcc
CCC = mpicc

all: ${BASEFILE}
	${CC} -c ${CPPFLAGS} $^
	mv *.o object/
	${CC} ${CPPFLAGS} -lm $^ -o a.out

a: object/*.o
	${CC} ${CPPFLAGS} -lm $^ -o a.out

mpi: ${MPIFILE} ${BASEFILE}
	${CCC} -c ${CPPFLAGS} ${MPIFLAG} $^
	mv *.o object/
	${CCC} ${CPPFLAGS} ${MPIFLAG} -lm $^ -o b.out

debug: ${BASEFILE}
	${CC} ${CPPFLAGS} ${DEBUGFLAG1} -lm $^ -o d.out

debugmpi: ${BASEFILE} ${MPIFILE}
	${CCC} ${CPPFLAGS} ${MPIFLAG} ${DEBUGFLAG1} -lm $^ -o dm.out

clean:
	rm *.o
