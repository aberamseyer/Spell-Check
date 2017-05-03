
CC = g++ 
FLAGS = -std=c++11 

all:
	${CC} ${FLAGS} Dictionary.cpp Dictionary.h spell-check-avl.cpp -o avl
hash:
	${CC} ${FLAGS} HashTable.cpp HashTable.h spell-check-hash.cpp -o hash
clean:
	rm -f hash
	rm -f avl
debug:
	${CC} ${FLAGS} -g HashTable.cpp HashTable.h spell-check-hash.cpp -o hash 
	gdb ./hash bigdict.txt testone.txt
