#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "Dictionary.h"

bool readFromTestFile(std::string& testFileName);
bool buildDictionary(std::string& dictFileName);

Dictionary dict; // declare data structure
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
bool readFromTestFile(std::string& testFileName) {
  std::ifstream testFile(testFileName);
  if(testFile.is_open()) {
    std::string line;
    while(getline(testFile, line)) {
      testData.push_back(line); // insert into testing data structure
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
  int count = 0;
  if(dictFile.is_open()) {
    std::string line;
    while(getline(dictFile, line)) {
      // insert into dictionary data structure
      if(!dict.FindEntry(line)) {
        count++;
        dict.AddEntry(line);
      }
    }
    dictFile.close();
    cout << "Total load: " << count << endl;
    return true;
  }
  else
    return false;
}
