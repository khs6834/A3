CC = g++
CFLAGS = -Wall -std=c++11 -fsanitize=address -fsanitize=undefined

TrieTest: Trie.o TrieTest.o Makefile
	$(CC) $(CFLAGS) Trie.o TrieTest.o -o TrieTest

Trie.o: Trie.h Trie.cpp
	$(CC) $(CFLAGS) -c Trie.cpp

TrieTest.o: TrieTest.cpp
	$(CC) $(CFLAGS) -c TrieTest.cpp

clean:
	rm *.o

Test:
	./TrieTest "words.txt" "queries.txt"
