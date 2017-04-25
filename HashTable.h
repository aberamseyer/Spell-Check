// file to implement a binary search tree of Entry objects

#ifndef DICTIONARY_H
#define DICTIONARY_H

#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Dictionary
{
 private:
   vector<string> table;
   int size;
   int load;
   const double MAX_LOAD = 0.5;

 public:

  HashTable();
  // Creates an empty hash table

  HashTable(const HashTable& orig);
  // Copy constructor

  virtual ~HashTable();
  // Destructor

  HashTable& operator=(const HashTable& orig);
  // assignment operator

  void AddEntry(string anEntry);
  // Preconditions: anEntry has a key not already in the hash table 
  // Postconditions: anEntry has been added to the hash table 

  bool FindEntry(string key);
  // Postconditions: if key is found in the hash table, returns true; 
  //   otherwise returns false

  void PrintSorted(ostream& outStream);
  // Postconditions: has printed contents of the hash table in order

 private:

  void HashTable(const HashTable& orig);
  // copies the contents of orig to this dictionary

  void deleteTable();
  // properly frees all memory occupied by this hash table 

};

#endif
