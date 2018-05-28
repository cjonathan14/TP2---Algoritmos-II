CC = gcc
CFLAGS = -Wall -ansi -pedantic

all: rand_binary.exe

rand_binary.exe: main.c
	$(CC) $(CFLAGS) -o rand_binary.exe main.c

clean:
	$(RM) -vf *.o *.exe *.t *.out *.err