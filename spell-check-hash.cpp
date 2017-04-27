#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include "HashTable.h"

void testTwo();
void testThree();

bool readFromTestFile(std::string& testFileName);
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
    testTwo();
    testThree();
  }
  else
    std::cout << "Couldn't open file for reading\n";

  //dict.PrintSorted(std::cout);

  std::cout << "Fixed words" << std::endl << std::endl;
  for (std::string a : foundWords) {
    std::cout << a << std::endl;
  }

  return 0;
}

void testTwo() {
  // Test 2
  for (std::string toTest : testData) {
    for (int i = 0; i < toTest.size(); i++) {
      string a = toTest;
      a.erase(i, 1);
      for (int j = 0; j < a.size(); j++) {
        if (a[j] == ' ') {
          a.erase(j, 1);
        }
      }
      if (dict.FindEntry(a)) {
        foundWords.push_back(a);
      }

      a = toTest;

      // else {
      //   testThree(a);
      // }
    }
  }
}

void testThree() {
  // Test 3
  for (std::string toTest : testData) {
    for (int i = 0; i < (toTest.size() - 1); i++) {
      std::string a = toTest;
      std::swap(a[i], a[i+1]);
      for (int j = 0; j < a.size(); j++) {
        if (a[j] == ' ') {
          a.erase(j, 1);
        }
      }
      if (dict.FindEntry(a)) {
        foundWords.push_back(a);
      }

      a = toTest;
    }
  }
}

/*
 * Reads all the text from the specified input file name
 * returns true if successful
 */
bool readFromTestFile(std::string& testFileName) {
  std::ifstream testFile(testFileName);
  if(testFile.is_open()) {
    std::string line;
    while(getline(testFile, line)) {
      transform(line.begin(), line.end(), line.begin(), ::tolower);
      testData.push_back(line);
    }
    testFile.close();
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
      if(!dict.FindEntry(line))
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
