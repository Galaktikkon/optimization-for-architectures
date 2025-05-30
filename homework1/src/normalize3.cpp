using namespace std;

#include "test.h"
#include <algorithm>
#include <cctype>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

string normalizeText(string &input) {

  bool inWhitespace = false;

  // Ad 3
  // Inplace transformation optimization
  for (size_t i = 0; i < input.size(); ++i) {
    if (input[i] < 32 || input[i] > 126) {
      input[i] = '\0';
    } else if (isspace(static_cast<unsigned char>(input[i]))) {
      if (!inWhitespace) {
        input[i] = ' ';
        inWhitespace = true;
      } else {
        input[i] = '\0';
      }
    } else {
      if (ispunct(static_cast<unsigned char>(input[i])) && input[i] != ',') {
        input[i] = ',';
      } else {
        input[i] =
            static_cast<char>(tolower(static_cast<unsigned char>(input[i])));
      }
      inWhitespace = false;
    }
  }

  input.erase(remove(input.begin(), input.end(), '\0'), input.end());

  size_t prevStart = string::npos, prevLen = 0;
  size_t wordStart = 0;

  // Ad 3
  // Inplace transformation optimization
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
          for (size_t j = wordStart; j < i; ++j)
            input[j] = '\0';
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
