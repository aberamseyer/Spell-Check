// file to implement a binary search tree of Entry objects

#ifndef DICTIONARY_H
#define DICTIONARY_H

#include <iostream>
#include <string>
#include <vector>

using namespace std;

class HashTable 
{
 private:
   vector<string> table = vector<string>(11);
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

 private:

  void copyTable(const HashTable& orig);
  // copies the contents of orig to this hash table 

  int hash(const string& key);
  // evaluates a hash for a string

  void reHash();
  // rehashes the table to the next prime number that is at least twice the original

  void nextPrime(int start);
  // gets the next prime number that comes after the number provided

};

#endif
