all: listtest treetest

clean:
	rm listtest treetest

listtest: linkedlist.h linkedlist.c listtest.c
	gcc -Wall -ansi -pedantic -o listtest linkedlist.c listtest.c

debuglisttest: linkedlist.h linkedlist.c listtest.c
	gcc -Wall -ansi -pedantic -g3 -o listtest linkedlist.c listtest.c

treetest: binarytree.h binarytree.c treetest.c
	gcc -Wall -ansi -pedantic -o treetest binarytree.c treetest.c

debugtreetest: binarytree.h binarytree.c treetest.c
	gcc -Wall -ansi -pedantic -g3 -o treetest binarytree.c treetest.c
