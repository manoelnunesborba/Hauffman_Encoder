CC = gcc
CFLAGS  = -g
TARGET = hcode

all: main.o huffman_tree.o frequency.o huffman_enc.o
	$(CC) $(CFLAGS) -o $(TARGET) main.o huffman_tree.o frequency.o huffman_enc.o
main.o: src/main.c
	$(CC) $(CFLAGS) -c src/main.c
frequency.o: src/frequency/frequency.c src/frequency/frequency.h
	$(CC) $(CFLAGS) -c src/frequency/frequency.c src/frequency/frequency.h
huffman_tree.o: src/huffman_tree/huffman_tree.c src/huffman_tree/huffman_tree.h
	$(CC) $(CFLAGS) -c src/huffman_tree/huffman_tree.c src/huffman_tree/huffman_tree.h 
huffman_enc.o: src/huffman_enc/huffman_enc.c src/huffman_enc/huffman_enc.h
	$(CC) $(CFLAGS) -c src/huffman_enc/huffman_enc.c src/huffman_enc/huffman_enc.h 
clean:
	@rm *.o src/*/*.gch *.huffman *.txt *.bin *.huff* $(TARGET) 2>/dev/null || true
test-slow:
	./test.sh -s -t 40 && ./test.sh -s -i ./samples/E.coli -t 70 && ./test.sh -s -t 20 -i ./samples/world192.txt
test-fast:
	./test.sh -f -i ./samples/miserable-short.txt