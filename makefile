
CC = g++ 
FLAGS = -std=c++11

all:
	${CC} ${FLAGS} Dictionary.cpp Dictionary.h spell-check-avl.cpp -o avl
hash:
	${CC} ${FLAGS} HashTable.cpp HashTable.h spell-check-hash.cpp -o hash
clean:
	rm hash
	rm avl
debug:
	${CC} ${FLAGS} -g HashTable.cpp HashTable.h spell-check-hash.cpp -o hash 
	gdb ./hash dict.txt inputForTesting.txt
