#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include "HashTable.h"

void addLetter(std::string& inputString);
void testTwo();
void testThree();

bool readFromTestFile(std::string& testFileName);
bool buildDictionary(std::string& dictFileName);

HashTable dict; // declare data structure
std::vector<std::string> testData;  // input data to check for misspellings
std::vector<std::string> foundWords;
std::ofstream outfile("another.txt");
int num = 0;

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
    for (int index = 0; index < testData.size(); index++) // Add to the line in main with comment "do test cases"
	  {
		    addLetter(testData.at(index));
	  }
    std::cout << "Finished with first test." << std::endl;
    num = 0;
    testTwo();
    std::cout << "Second test finished"<< std::endl;
    num = 0;
    testThree();
    std::cout << "Third test finished" << std::endl;
    num = 0;
  }
  else
    std::cout << "Couldn't open file for reading\n";

  outfile << "Fixed words" << std::endl << std::endl;
  int count = 0;
  for (std::string a : foundWords) {
    outfile << a << std::endl;
    count++;
  }

  std::cout << "Total fixed is: " << count << std::endl;

  return 0;
}

void addLetter(std::string& inputString)
{
  int asciiValue; // 'a' has ascii value 97, 'z' has ascii value of 122.
  bool found = false;
  char asciiCharacter;
  std::string characterToInsert;
  std::string testString = inputString;
  for (int j = 0; j < testString.size(); j++) {
    if (testString[j] == ' ') {
      testString.erase(j, 1);
    }
  }
  for (int index = 0; index < inputString.size(); index++)
  {
    for (asciiValue = 97; asciiValue < 123; asciiValue++)
    {
      asciiCharacter = static_cast<char>(asciiValue);
      characterToInsert = string(1, asciiCharacter);
      testString = testString.insert(index, characterToInsert);
      found = dict.FindEntry(testString);
      if (found)
      {
        // std::cout << testString << std::endl;
        if (std::find(foundWords.begin(), foundWords.end(), testString) == foundWords.end()) {
        foundWords.push_back(testString);
      }
      }
      testString = inputString;
    }
  }
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
        if (std::find(foundWords.begin(), foundWords.end(), a) == foundWords.end()) {
        foundWords.push_back(a);
      }
      }

      a = toTest;
    }
  }
}

void testThree() {
  // Test 3
  for (std::string toTest : testData) {
    for (int i = 0; i < toTest.size(); i++) {
      std::string a = toTest;
      std::swap(a[i], a[i+1]);
      for (int j = 0; j < a.size(); j++) {
        if (a[j] == ' ') {
          a.erase(j, 1);
        }
      }
      if (dict.FindEntry(a)) {
        if (std::find(foundWords.begin(), foundWords.end(), a) == foundWords.end()) {
          foundWords.push_back(a);
        }
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
    }
    dictFile.close();
    dict.PrintSorted(cout);
    return true;
  }
  else
    return false;
}
