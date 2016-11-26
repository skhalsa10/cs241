all: huffencode huffdecode

clean:
	rm huffencode huffdecode

huffencode: huffman.h queueAndTree.h queueAndTree.c huffman.c huffencode.c
	gcc -Wall -ansi -pedantic -o huffencode huffman.c huffencode.c queueAndTree.h queueAndTree.c

huffdecode: huffman.h queueAndTree.h queueAndTree.c huffman.c huffdecode.c
	gcc -Wall -ansi -pedantic -o huffdecode huffman.c huffdecode.c queueAndTree.h queueAndTree.c

testhuffencode: huffman.h queueAndTree.h queueAndTree.c huffman.c huffencode.c
	gcc -Wall -ansi -pedantic -g3 -o huffencode huffman.c huffencode.c queueAndTree.h queueAndTree.c

