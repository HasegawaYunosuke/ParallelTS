CC = gcc
BASEFILE = main.c check.c init.c read_data.c

nompi:	$(BASEFILE)
	$(CC) $(BASEFILE)
	rm *.o
