using namespace std;

#include "test.h"
#include <algorithm>
#include <cctype>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

string normalizeText(string &input) {
  string result = "";

  // Ad 2
  // Preallocation optimization
  result.reserve(input.size());

  bool inWhitespace = false;

  for (char c : input) {
    if (c < 32 || c > 126)
      continue;

    if (isspace(static_cast<unsigned char>(c))) {
      if (!inWhitespace) {
        result += ' ';
        inWhitespace = true;
      }
    } else {
      if (ispunct(static_cast<unsigned char>(c)) && c != ',') {
        result += ',';
      } else {
        result += static_cast<char>(tolower(static_cast<unsigned char>(c)));
      }
      inWhitespace = false;
    }
  }

  string prevWord = "", word = "", tempResult = "";

  // Ad 2
  // Preallocation optimization
  prevWord.reserve(result.size());
  word.reserve(result.size());
  tempResult.reserve(result.size());

  for (size_t i = 0; i < result.size(); ++i) {
    if (result[i] == ' ') {
      if (!word.empty() && word != prevWord) {
        tempResult += word + ' ';
        prevWord = word;
      }
      word.clear();
    } else {
      word += result[i];
    }
  }
  if (!word.empty() && word != prevWord) {
    tempResult += word + ' ';
  }
  result = tempResult;

  return result;
}

int main(int argc, char *argv[]) {
  string input;
  getline(cin, input, '\0');

  double result = test(normalizeText, input, true);
  string timeFile = (argc > 1) ? argv[1] : "benchmark_time.txt";

  ofstream outFile(timeFile, ios::app);
  if (outFile.is_open()) {
    outFile << result << '\t';
    outFile.close();
  } else {
    cerr << "Unable to open file for writing time." << endl;
  }

  return 0;
}
