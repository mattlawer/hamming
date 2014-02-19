# Hamming makefile

CC = gcc
CC_OPTIONS = -g -Wall

all : hamming clean

hamming : hamming.o
	$(CC) $(CC_OPTIONS) hamming.o -o hamming

hamming.o : hamming.c
	$(CC) $(CC_OPTIONS) -c hamming.c

clean :
	rm *.o
