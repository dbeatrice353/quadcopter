
CC = gcc

main.exe: main.c quadcopter.o interfaces.o quadcopter.h interfaces.h
	$(CC) main.c quadcopter.o interfaces.o -o main.exe

quadcopter.o: quadcopter.c quadcopter.h
	$(CC) -c quadcopter.c -o quadcopter.o

interfaces.o: interfaces.c interfaces.h
	$(CC) -c interfaces.c -o interfaces.o
