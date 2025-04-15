#include <iostream>
#include <string>
#include <sstream>
#include <algorithm>
#include <cctype>

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
    return std::ispunct(static_cast<unsigned char>(c)) && c != ',';
}

std::string normalizeText(const std::string &input)
{
    std::ostringstream result;
    bool inWhitespace = false;

    for (char c : input)
    {
        if (!isPrintable(c))
            continue;

        if (isWhitespace(c))
        {
            if (!inWhitespace)
            {
                result << ' ';
                inWhitespace = true;
            }
        }
        else
        {
            if (isPunctuation(c))
            {
                result << ',';
            }
            else
            {
                result << static_cast<char>(std::tolower(static_cast<unsigned char>(c)));
            }
            inWhitespace = false;
        }
    }

    // usunięcie duplikatów wyrazów
    std::istringstream iss(result.str());
    std::ostringstream finalResult;
    std::string prevWord, word;
    while (iss >> word)
    {
        if (word != prevWord)
        {
            finalResult << word << ' ';
            prevWord = word;
        }
    }

    std::string final = finalResult.str();
    if (!final.empty())
        final.pop_back(); // usuń końcową spację
    return final;
}

int main()
{
    std::string input;
    std::getline(std::cin, input, '\0'); // wczytanie całego pliku do końca
    std::string output = normalizeText(input);
    std::cout << output << std::endl;
    return 0;
}
