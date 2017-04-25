#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "HashTable.h"

bool readFromTestFile(std::string& dictFileName);
bool buildDictionary(std::string& dictFileName);

HashTable dict; // declare data structure
std::vector<std::string> testData;  // input data to check for misspellings

int main(int argc, char* argv[]) {

  // grab command line argument for filenames
  std::string execName = argv[0];
  std::string dictFileName;
  std::string testFileName;

  if (argc == 3) {
    dictFileName = argv[1];
    testFileName = argv[2];
  }
  else
    std::cout << "Syntax error, input and output file names required\n";

  // read words from input file provided
  if (readFromTestFile(testFileName) && buildDictionary(dictFileName)) {
    // do test cases
  }
  else
    std::cout << "Couldn't open file for reading\n";

  dict.PrintSorted(std::cout);

  return 0;
}

/*
 * Reads all the text from the specified input file name
 * returns true if successful
 */
bool readFromTestFile(std::string& dictFileName) {
  std::ifstream dictFile(dictFileName);
  if(dictFile.is_open()) {
    std::string line;
    while(getline(dictFile, line)) {
      dict.AddEntry(line); // insert into testing data structure
    }
    dictFile.close();
    return true;
  }
  else
    return false;
}

/*
 * Reads all the text from the specified input dictionary
 * returns true if successful
 */
bool buildDictionary(std::string& dictFileName) {
  std::ifstream dictFile(dictFileName);
  if(dictFile.is_open()) {
    std::string line;
    while(getline(dictFile, line)) {
      // insert into dictionary data structure
    }
    dictFile.close();
    return true;
  }
  else
    return false;
}
