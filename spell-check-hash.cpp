#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include "HashTable.h"

bool readFromTestFile(std::string& dictFileName);
bool buildDictionary(std::string& dictFileName);

HashTable dict; // declare data structure
std::vector<std::string> testData;  // input data to check for misspellings
std::vector<std::string> foundWords;

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
    // Test 1


    // Test 2
    /* For each string in test data */
    for (std::string toTest : testData) {
      for (int i = 0; i < toTest.size(); i++) {
        string a = toTest;
        a.erase(i, 1);
        if (dict.FindEntry(a)) {
          foundWords.push_back(a);
        }
      }
    }


    // Test 3
    for (std::string toTest : testData) {
      for (int i = 0; i < (toTest.size() - 1); i++) {
        string a = toTest;
        swap(a[i], a[i+1]);
        if (dict.FindEntry(a)) {
          foundWords.push_back(a);
        }
      }
    }
  }
  else
    std::cout << "Couldn't open file for reading\n";

  //dict.PrintSorted(std::cout);

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
      testData.push_back(line);
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
      transform(line.begin(), line.end(), line.begin(), ::tolower);
      dict.AddEntry(line);
      //dict.PrintSorted(cout);
      //cout << "=====================================" << endl;
    }
    dictFile.close();
    dict.PrintSorted(cout);
    return true;
  }
  else
    return false;
}
