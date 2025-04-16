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
    return ispunct(c) && c != ',';
}

string normalizeText(const string &input)
{
    string result = "";
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
                result += tolower(c);
            }
            inWhitespace = false;
        }
    }

    string prevWord = "", word = "", tempResult = "";
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
