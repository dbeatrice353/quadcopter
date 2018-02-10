
CC = gcc

main.exe: main.c quadcopter.o quadcopter.h
	$(CC) main.c quadcopter.o -o main.exe

quadcopter.o: quadcopter.c quadcopter.h
	$(CC) -c quadcopter.c -o quadcopter.o
