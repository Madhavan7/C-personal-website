all: libTrie.o test_libTrie

clean:
	rm -f libTrie.o test_libTrie

libTrie.o: libTrie.c libTrie.h
	gcc -g -c libTrie.c

test_libTrie: test_libTrie.c libTrie.o
	gcc -g -o test_libTrie test_libTrie.c libTrie.o