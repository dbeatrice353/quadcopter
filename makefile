
CC = gcc
FLAGS = -ggdb

main.exe: main.c quadcopter.o interfaces.o dev_htc.o quadcopter.h interfaces.h
	$(CC) $(FLAGS) main.c quadcopter.o interfaces.o dev_htc.o -o main.exe

quadcopter.o: quadcopter.c quadcopter.h
	$(CC) $(FLAGS) -c quadcopter.c -o quadcopter.o

interfaces.o: interfaces.c interfaces.h
	$(CC) $(FLAGS) -c interfaces.c -o interfaces.o

dev_htc.o: dev_htc.c dev_htc.h
	$(CC) $(FLAGS) -c dev_htc.c -o dev_htc.o

clean:
	rm -rf ./*.o
