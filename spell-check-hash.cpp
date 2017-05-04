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
std::vector<std::string> original;
std::vector<std::string> change;

int main() {

  // name files for building and outputting
  std::string dictFileName = "bigdict.txt";
  std::string testFileName;
  std::cout << "Enter a file to spell check: ";
  cin >> testFileName;

  std::cout << std::endl;

  // read words from input file provided
  if (readFromTestFile(testFileName) && buildDictionary(dictFileName)) {
    std::cout << std::endl;
    for (int index = 0; index < testData.size(); index++) // Add to the line in main with comment "do test cases"
	  {
		    addLetter(testData.at(index));
	  }
    testTwo();
    testThree();
  }
  else
    std::cout << "Couldn't open file for reading\n";

  /** OUTPUT GOES HERE */
  std::cout << "Fixed words" << std::endl << "___________\n\n";
  std::cout.width(25); std::cout << std::left << "Misspelled Word";
  std::cout.width(25); std::cout << std::left << "Corrected Word";
  std::cout.width(15); std::cout << std::left << "Changed Letter\n";
  std::cout << "|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||\n";
  int count = 0;
  for (std::string a : foundWords) {
    std::cout.width(25); std::cout << std::left << original[count];
    std::cout.width(25); std::cout << std::left << a;
    std::cout.width(8); std::cout << std::left << change[count] << std::endl;
    count++;
  }

  std::cout << "\nTotal fixed is: " << count << std::endl;

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
        if (std::find(foundWords.begin(), foundWords.end(), testString) == foundWords.end()) {
          foundWords.push_back(testString);
          original.push_back(inputString);
          std::string toChange = "added: " + characterToInsert;
          change.push_back(toChange);
        }
      }
      testString = inputString;
    }
  }
}

void testTwo() {
  // Test 2
  std::string characterToInsert;
  for (std::string toTest : testData) {
    for (int i = 0; i < toTest.size(); i++) {
      string a = toTest;
      characterToInsert = string(1, a[i]);
      char c = a[i];
      a.erase(i, 1);
      for (int j = 0; j < a.size(); j++) {
        if (a[j] == ' ') {
          a.erase(j, 1);
        }
      }
      if (dict.FindEntry(a)) {
        if (std::find(foundWords.begin(), foundWords.end(), a) == foundWords.end()) {
          foundWords.push_back(a);
          original.push_back(toTest);
          std::string toChange = "removed: " + characterToInsert;
          change.push_back(toChange);
        }
      }

      a = toTest;
    }
  }
}

void testThree() {
  // Test 3
  std::string leftChar;
  std::string rightChar;
  for (std::string toTest : testData) {
    for (int i = 0; i < toTest.size(); i++) {
      std::string a = toTest;
      leftChar = a[i];
      rightChar = a[i+1];
      std::swap(a[i], a[i+1]);
      for (int j = 0; j < a.size(); j++) {
        if (a[j] == ' ') {
          a.erase(j, 1);
        }
      }
      if (dict.FindEntry(a)) {
        if (std::find(foundWords.begin(), foundWords.end(), a) == foundWords.end()) {
          foundWords.push_back(a);
          original.push_back(toTest);
          std::string toChange = "swapped: " + leftChar + " and " + rightChar;
          change.push_back(toChange);
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
