all:
	g++ -std=c++11 Dictionary.cpp Dictionary.h spell-check-avl.cpp -o avl
hash:
	g++ -std=c++11 HashTable.cpp HashTable.h spell-check-hash.cpp -o hash
clean:
	rm hash
	rm avl
