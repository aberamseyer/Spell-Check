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
  table = new string[size];
  std::fill_n(table, size, "0");
}

//HashTable::HashTable(const HashTable& orig)
//{
//  table = orig.table;
//}

HashTable::~HashTable()
{
  delete[] table;
  size = 11;
  load = 0;
}

//HashTable& HashTable::operator=(const HashTable& orig)
//{
//  table = orig.table;
//  size = orig.size;
//  load = orig.load;
// 
//  return *this;
//}

void HashTable::AddEntry(const string& anEntry)
{
  int location = hash(anEntry);
  int original = location;

  if(table[location] == "0")
    table[location] = anEntry;
  else {
    for(int i=1; table[location] != "0"; i++) {
      location = (original + i*i) % size; 
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
  int original = location;

  for(int i=0; table[location] != "0"; i++) { 
    if (table[location] == key)
      return true;
    location = (original + i*i) % size;
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
  string* temp = table;
  int tempNum = size;
  size = nextPrime(size*2);
  table = new string[size];
  std::fill_n(table, size, "0");
  load = 0;
  for(int i=0; i < tempNum; i++)
    if(temp[i] != "0")
      AddEntry(temp[i]); 
  delete[] temp;
  temp = NULL;
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
