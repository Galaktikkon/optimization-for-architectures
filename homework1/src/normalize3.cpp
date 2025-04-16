using namespace std;

#include <iostream>
#include <string>
#include <sstream>
#include <algorithm>
#include <cctype>
#include <fstream>
#include "test.h"

bool isPrintable(char c)
{
    return c >= 32 && c <= 126;
}

bool isWhitespace(char c)
{
    return c == ' ' || c == '\t' || c == '\n';
}

bool isPunctuation(char c)
{
    return ispunct(static_cast<unsigned char>(c)) && c != ',';
}

string normalizeText(const string &input)
{
    string result = "";

    // Ad 1
    // Preallocation optimization
    result.reserve(input.size());

    bool inWhitespace = false;

    for (char c : input)
    {
        if (!isPrintable(c))
            continue;

        if (isWhitespace(c))
        {
            if (!inWhitespace)
            {
                result += ' ';
                inWhitespace = true;
            }
        }
        else
        {
            if (isPunctuation(c))
            {
                result += ',';
            }
            else
            {
                result += static_cast<char>(tolower(c));
            }
            inWhitespace = false;
        }
    }

    string prevWord = "", word = "", tempResult = "";

    // Ad 1
    // Preallocation optimization
    prevWord.reserve(result.size());
    word.reserve(result.size());
    tempResult.reserve(result.size());

    for (size_t i = 0; i < result.size(); ++i)
    {
        if (result[i] == ' ')
        {
            if (!word.empty() && word != prevWord)
            {
                tempResult += word + ' ';
                prevWord = word;
            }
            word.clear();
        }
        else
        {
            word += result[i];
        }
    }
    if (!word.empty() && word != prevWord)
    {
        tempResult += word + ' ';
    }
    result = tempResult;

    return result;
}

int main(int argc, char *argv[])
{
    string input;
    getline(cin, input, '\0');

    double result = test(normalizeText, input, true);

    string timeFile = (argc > 1) ? argv[1] : "benchmark_time.txt";

    std::ofstream outFile(timeFile, ios::app);
    if (outFile.is_open())
    {
        outFile << result << '\t';
        outFile.close();
    }
    else
    {
        std::cerr << "Unable to open file for writing time." << std::endl;
    }

    return 0;
}
