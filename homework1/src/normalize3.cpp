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

string normalizeText(string &input)
{

    bool inWhitespace = false;

    // Ad 2
    // Inplace transformation optimization
    for (size_t i = 0; i < input.size(); ++i)
    {
        if (!isPrintable(input[i]))
        {
            input[i] = '\0';
        }
        else if (isWhitespace(input[i]))
        {
            if (!inWhitespace)
            {
                input[i] = ' ';
                inWhitespace = true;
            }
            else
            {
                input[i] = '\0';
            }
        }
        else
        {
            if (isPunctuation(input[i]))
            {
                input[i] = ',';
            }
            else
            {
                input[i] = static_cast<char>(tolower(input[i]));
            }
            inWhitespace = false;
        }
    }

    // Ad 1
    // Preallocation optimization
    string prevWord = "";
    prevWord.reserve(input.size());
    size_t wordStart = 0;

    // Ad 2
    // Inplace transformation optimization
    for (size_t i = 0; i <= input.size(); ++i)
    {
        if (i == input.size() || input[i] == ' ')
        {
            if (wordStart < i) // there is a word
            {
                string_view word(&input[wordStart], i - wordStart);
                if (word != prevWord)
                {
                    prevWord = word;
                }
                else
                {
                    // Replace duplicate word with '\0'
                    for (size_t j = wordStart; j < i; ++j)
                        input[j] = '\0';
                }
            }
            wordStart = i + 1;
        }
    }

    input.erase(remove(input.begin(), input.end(), '\0'), input.end());

    return input;
}

int main(int argc, char *argv[])
{
    string input;
    getline(cin, input, '\0');

    double result = test(normalizeText, input, true);

    string timeFile = (argc > 1) ? argv[1] : "benchmark_time.txt";

    ofstream outFile(timeFile, ios::app);
    if (outFile.is_open())
    {
        outFile << result << '\t';
        outFile.close();
    }
    else
    {
        cerr << "Unable to open file for writing time." << endl;
    }

    return 0;
}
