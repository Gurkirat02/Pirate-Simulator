EXE = main
SOBJ = main.o deque.o run.o fight.o scenario.o 
CC = gcc -pthread

all:	$(EXE)

main:	$(SOBJ)
	$(CC) -o main $(SOBJ)

main.o:	main.c defs.h
	$(CC) -c main.c

deque.o:	deque.c defs.h
	$(CC) -c deque.c

run.o:	run.c defs.h
	$(CC) -c run.c

fight.o:	fight.c defs.h
	$(CC) -c fight.c

scenario.o:	scenario.c defs.h
	$(CC) -c scenario.c

clean:
	rm -f $(EXE) $(SOBJ)
