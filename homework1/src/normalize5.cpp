using namespace std;

#include "test.h"
#include <algorithm>
#include <cctype>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string.h>
#include <string>

// Ad 5
// Bare metal optimization
char *normalizeTextC(char *input, size_t len, size_t &outLen) {
  char *buffer = new char[len + 1];
  size_t pos = 0;
  bool inSpace = false;

  for (size_t i = 0; i < len; ++i) {
    unsigned char c = input[i];

    if (c < 32 || c > 126)
      continue;

    if (isspace(c)) {
      if (!inSpace) {
        buffer[pos++] = ' ';
        inSpace = true;
      }
    } else {
      inSpace = false;
      if (ispunct(c) && c != ',')
        buffer[pos++] = ',';
      else
        buffer[pos++] = tolower(c);
    }
  }

  buffer[pos] = '\0';

  char *output = new char[pos + 1];
  size_t outPos = 0;

  const char *prev = nullptr;
  size_t prevLen = 0;

  size_t i = 0;
  while (i < pos) {
    while (i < pos && buffer[i] == ' ')
      ++i;
    size_t start = i;
    while (i < pos && buffer[i] != ' ')
      ++i;

    size_t lenWord = i - start;
    if (lenWord == 0)
      continue;

    if (!prev || lenWord != prevLen ||
        memcmp(buffer + start, prev, lenWord) != 0) {
      memcpy(output + outPos, buffer + start, lenWord);
      outPos += lenWord;
      output[outPos++] = ' ';

      prev = buffer + start;
      prevLen = lenWord;
    }
  }

  delete[] buffer;
  if (outPos > 0 && output[outPos - 1] == ' ')
    --outPos;
  output[outPos] = '\0';
  outLen = outPos;
  return output;
}

std::string normalizeText(std::string &input) {
  size_t outLen = 0;
  char *raw = new char[input.size() + 1];
  memcpy(raw, input.c_str(), input.size());
  raw[input.size()] = '\0';

  char *result = normalizeTextC(raw, input.size(), outLen);

  std::string output(result, outLen);
  delete[] result;
  delete[] raw;

  return output;
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
