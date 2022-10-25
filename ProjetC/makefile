CC = gcc
CFLAGS  = -g
TARGET = huffman

all: main.o word.o
	$(CC) $(CFLAGS) -o $(TARGET) main.o word.o
main.o: main.c
	$(CC) $(CFLAGS) -c main.c
word.o: ./Word/word.c ./Word/word.h
	$(CC) $(CFLAGS) -c ./Word/word.c ./Word/word.h
clean:
	rm *.o ./Tree/*.gch ./Word/*.gch $(TARGET)