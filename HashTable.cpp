// Implementation file for the hash table
#include "HashTable.h"

int max(int x, int y)
{
  return (x > y) ? x : y;
}

HashTable::HashTable()
{
  size = 11;
  load = 0;
}

HashTable::HashTable(const HashTable& orig)
{
  this->copyTable(orig);
}

HashTable::~HashTable()
{
  table.clear();
  size = 11;
  load = 0;
  vector<string>().swap(table);
}

HashTable& HashTable::operator=(const HashTable& orig)
{
  table = orig.table;
  size = orig.size;
  load = orig.load;
 
  return *this;
}

void HashTable::AddEntry(const string& anEntry)
{
  if(table[hash(anEntry)] == "")
    table[hash(anEntry)] = anEntry;
  else {
    int i = 0;
    for(; table[hash(anEntry) + i*i] != ""; i++); 
    table[hash(anEntry) + i*i] = anEntry;
  }
  load++;
}

int HashTable::hash(const string& key)
{
  int hashVal = 0;

  for(int i=0; i<key.length(); i++) 
    hashVal = 37 * hashVal + key[i];

  hashVal %= size;
  if(hashVal < 0)
    hashVal += size;

  return hashVal;
}

bool HashTable::FindEntry(const string& key) 
{
  for(int i=0; table[hash(key) + i*i] != ""; i++) {
    if (table[hash(key) + i*i] == key)
      return true;
  }
  return false;
}

void HashTable::reHash() 
{
  vector<string> temp = table;
  size = nextPrime(size*2);
  table.clear();
  table.resize(size);
  load = 0;
  for(string word : temp)
    if(word != "") AddEntry(word); 
}
 

int HashTable::nextPrime(int start) 
{
  for(int i=start+1; true; i++) {
    bool isPrime = true;
    for(int j=2; j < i/2; j++) {
      if (i % j == 0) {
	isPrime = false;
	break;
      }
    }
    if (isPrime) return i;
  }
}
