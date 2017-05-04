#include <iostream>
#include <cstring>
#include <iterator>
#include <sstream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include "HashTable.h"

void addLetter(std::string& inputString, int lineNumber);
void testTwo(int lineNumber);
void testThree(int lineNumber);

bool buildDictionary(std::string& dictFileName);

HashTable dict; // declare data structure
std::vector<std::string> testData;  // input data to check for misspellings
std::vector<std::string> foundWords;
std::vector<std::string> original;
std::vector<std::string> change;
int changeCount = 0;

int main() {

  // name files for building and outputting
  int count = 0;
  std::string dictFileName = "bigdict.txt";
  std::string testFileName;
  std::cout << "Enter a file to spell check: ";
  cin >> testFileName;

  std::cout << std::endl;

  int lineNumber = 1;
  // read words from input file provided
  if (buildDictionary(dictFileName)) {
    std::cout << std::endl;

    /** OUTPUT GOES HERE */
    std::cout << "Fixed words" << std::endl << "___________\n\n";
    std::cout.width(25); std::cout << std::left << "Misspelled Word";
    std::cout.width(25); std::cout << std::left << "Corrected Word";
    std::cout.width(15); std::cout << std::left << "Changed Letter\n";
    std::cout << "|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||\n";

    std::ifstream testFile(testFileName);
    if(testFile.is_open()) {
      std::string line;
      while(getline(testFile, line)) {
        transform(line.begin(), line.end(), line.begin(), ::tolower); // change to lower case

	char chars[] = "<>?:\\\"{}|+_)(*&^%$#@!~`1234567890-=[]\';/.,";
        for(unsigned int i = 0; i < strlen(chars); i++)
          line.erase(remove(line.begin(), line.end(), chars[i]), line.end());
        istringstream iss;
        iss.str(line);
        copy(istream_iterator<string>(iss), istream_iterator<string>(), back_inserter(testData));


        for (int index = 0; index < testData.size(); index++) // Add to the line in main with comment "do test cases"
	      {
		      addLetter(testData.at(index), lineNumber);
	      }
        testTwo(lineNumber);
        testThree(lineNumber);
        count = 0;
        for (std::string a : foundWords) {
          std::cout.width(25); std::cout << std::left << original[count];
          std::cout.width(25); std::cout << std::left << a;
          std::cout.width(8); std::cout << std::left << change[count] << std::endl;
          count++;
        }

        std::cout << "\n";
        testData.clear();
        foundWords.clear();
        original.clear();
        change.clear();
        lineNumber++;
      }
    testFile.close();
  }
  else
    std::cout << "Couldn't open file for reading\n";
}
  std::cout << "\nTotal fixed is: " << changeCount << std::endl;

  return 0;
}

void addLetter(std::string& inputString, int lineNumber)
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
      if (found && testString != "")
      {
          foundWords.push_back(testString);
          changeCount++;
          original.push_back(inputString);
          std::string toChange = "added: " + characterToInsert + " at line " + to_string(lineNumber);
          change.push_back(toChange);
      }
      testString = inputString;
    }
  }
}

void testTwo(int lineNumber) {
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
      if (dict.FindEntry(a) && a != "") {
          foundWords.push_back(a);
          changeCount++;
          original.push_back(toTest);
          std::string toChange = "removed: " + characterToInsert + " at line " + to_string(lineNumber);
          change.push_back(toChange);
      }

      a = toTest;
    }
  }
}

void testThree(int lineNumber) {
  // Test 3
  std::string leftChar;
  std::string rightChar;
  for (std::string toTest : testData) {
    for (int i = 0; i < toTest.size(); i++) {
      std::string a = toTest;
      leftChar = a[i];
      rightChar = a[i+1];
      if (leftChar != rightChar) {
      std::swap(a[i], a[i+1]);
      for (int j = 0; j < a.size(); j++) {
        if (a[j] == ' ') {
          a.erase(j, 1);
        }
      }
      if (dict.FindEntry(a) && a != "") {
          foundWords.push_back(a);
          changeCount++;
          original.push_back(toTest);
          std::string toChange = "swapped: " + leftChar + " and " + rightChar + " at line " + to_string(lineNumber);
          change.push_back(toChange);
      }

      a = toTest;
    }
      }
    }
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
    // dict.PrintSorted(cout);
    return true;
  }
  else
    return false;
}
