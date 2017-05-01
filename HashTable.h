// file to implement a binary search tree of Entry objects

#ifndef DICTIONARY_H
#define DICTIONARY_H

#include <iostream>
#include <string>
//#include <vector>
#include <algorithm>
#include <fstream>

using namespace std;

class HashTable 
{
 private:
   string* table;
   int size;
   int load;
   const double MAX_LOAD = 0.5;

 public:

  HashTable();
  // Creates an empty hash table

//  HashTable(const HashTable& orig);
  // Copy constructor

  virtual ~HashTable();
  // Destructor

//  HashTable& operator=(const HashTable& orig);
  // assignment operator

  void AddEntry(const string& anEntry);
  // Preconditions: anEntry has a key not already in the hash table 
  // Postconditions: anEntry has been added to the hash table 

  bool FindEntry(const string& key);
  // Postconditions: if key is found in the hash table, returns true; 
  //   otherwise returns false

  void PrintSorted(ostream& outstream);
  // prints the hash table contents to the specified output stream.
  // The table will NOT be in order because it is hashed

  void output();
 private:

  void copyTable(const HashTable& orig);
  // copies the contents of orig to this hash table 

  int hash(const string& key);
  // evaluates a hash for a string

  void reHash();
  // rehashes the table to the next prime number that is at least twice the original

  int nextPrime(int start);
  // gets the next prime number that comes after the number provided

};

#endif
