using namespace std;

#include "test.h"
#include <algorithm>
#include <cctype>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

string normalizeText(string &input) {

  // Ad 4
  // iterators and standard algorithms optimization
  input.erase(remove_if(input.begin(), input.end(),
                        [](char c) { return c < 32 || c > 126; }),
              input.end());

  bool inSpace = false;
  transform(input.begin(), input.end(), input.begin(), [&inSpace](char c) {
    if (isspace(static_cast<unsigned char>(c))) {
      if (!inSpace) {
        inSpace = true;
        return ' ';
      } else {
        return '\0';
      }
    } else {
      inSpace = false;
      if (ispunct(static_cast<unsigned char>(c)) && c != ',')
        return ',';
      return static_cast<char>(tolower(static_cast<unsigned char>(c)));
    }
  });

  size_t prevStart = string::npos, prevLen = 0;
  size_t wordStart = 0;

  for (size_t i = 0; i <= input.size(); ++i) {
    if (i == input.size() || input[i] == ' ') {
      if (wordStart < i) {
        size_t len = i - wordStart;
        bool isDuplicate = false;

        if (prevStart != string::npos && len == prevLen) {
          isDuplicate = true;
          for (size_t j = 0; j < len; ++j) {
            if (input[wordStart + j] != input[prevStart + j]) {
              isDuplicate = false;
              break;
            }
          }
        }

        if (isDuplicate) {
          fill(input.begin() + wordStart, input.begin() + i, '\0');
          if (i < input.size() && input[i] == ' ')
            input[i] = '\0';
        } else {
          prevStart = wordStart;
          prevLen = len;
        }
      }
      wordStart = i + 1;
    }
  }

  input.erase(remove(input.begin(), input.end(), '\0'), input.end());

  return input;
}

int main(int argc, char *argv[]) {
  string input;
  getline(cin, input, '\0');

  if (argc > 1 && string(argv[1]) == "--validate") {
    cout << normalizeText(input) << flush;
  } else {
    double result = test(normalizeText, input, true);
    string timeFile = (argc > 1) ? argv[1] : "benchmark_time.txt";

    ofstream outFile(timeFile, ios::app);
    if (outFile.is_open()) {
      outFile << result << '\t';
      outFile.close();
    } else {
      cerr << "Unable to open file for writing time." << endl;
    }
  }

  return 0;
}