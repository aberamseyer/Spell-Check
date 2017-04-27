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
  table = orig.table;
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
  int location = hash(anEntry);

  if(table[location] == "")
    table[location] = anEntry;
  else {
    for(int i=0; table[location] != ""; i++) {
      //if(table[location] == anEntry) return; // don't insert a duplicate
      location = (location + i*i) % size; 
    }
    table[location] = anEntry;
  }
  load++;
  
  if((double) load/size >= MAX_LOAD)
    reHash();
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
  int location = hash(key);

  for(int i=0; table[location] != ""; i++) { 
    if (table[location] == key)
      return true;
    location = (location + i*i) % size;
  }
  return false;
}

void HashTable::PrintSorted(ostream& outstream)
{
  int i = 0;
  outstream << endl;
  //for(string item : table) {
  //  outstream << i << ": " << item << endl;
  //  i++;
  //}
  outstream << "load: " << load << ", size: " << size << ", ratio: " << ((double) load/size) << endl;
}

void HashTable::reHash() 
{
  vector<string> temp = table;
  size = nextPrime(size*2);
  table.clear();
  table.resize(size);
  load = 0;
  for(string word : temp)
    if(word != "")
      AddEntry(word); 
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
    if (isPrime) 
      return i;
  }
}
