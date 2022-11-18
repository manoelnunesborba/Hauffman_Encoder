CC = gcc
CFLAGS  = -g
TARGET = hcode

all: main.o huffman.o word.o hufenc.o
	$(CC) $(CFLAGS) -o $(TARGET) main.o huffman.o word.o hufenc.o
main.o: main.c
	$(CC) $(CFLAGS) -c main.c
word.o: ./Word/word.c ./Word/word.h
	$(CC) $(CFLAGS) -c ./Word/word.c ./Word/word.h
huffman.o: ./Tree/huffman.c ./Tree/huffman.h
	$(CC) $(CFLAGS) -c ./Tree/huffman.c ./Tree/huffman.h 
hufenc.o: ./Hufenc/hufenc.c ./Hufenc/hufenc.c
	$(CC) $(CFLAGS) -c ./Hufenc/hufenc.c ./Hufenc/hufenc.c 
clean:
	@rm *.o ./Tree/*.gch ./Word/*.gch ./Hufenc/*.gch $(TARGET) 2>/dev/null || true
test-slow:
	./test.sh -s
test-fast:
	./test.sh -f -i ./samples/miserable-short.txt