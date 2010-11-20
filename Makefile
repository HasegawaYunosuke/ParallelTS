vpath %.c src mpi
vpath %.h include
vpath %.o object

CPPFLAGS = -I include -g -pthread -lm
BASEFILE = main.c init.c check.c read_data.c file_manage.c error.c memory.c finalize.c math.c pthread.c init_path.c
MPIFILE = mpi.c
MPIFLAG = -DMPIMODE
DEBUGFLAG1 = -DDEBUG1
CC = gcc

all: ${BASEFILE}
	${CC} -c ${CPPFLAGS} $^
	mv *.o object/
	${CC} ${CPPFLAGS} $^ -o a.out

a: object/*.o
	${CC} ${CPPFLAGS} $^ -o a.out

mpi: ${BASEFILE} ${MPIFILE}
	${CC} ${CPPFLAGS} ${MPIFLAG} $^ -o b.out

debug: ${BASEFILE}
	${CC} ${CPPFLAGS} ${DEBUGFLAG1} $^ -o d.out

debugmpi: ${BASEFILE} ${MPIFILE}
	${CC} ${CPPFLAGS} ${MPIFLAG} ${DEBUGFLAG1} $^ -o dm.out

clean:
	rm *.o
