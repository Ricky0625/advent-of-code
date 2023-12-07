#include <iostream>
#include <fstream>
#include <vector>
#include <unordered_map>

#define INPUT_FILE "../input.txt"

bool isSymbol(char ch)
{
    return (!isalnum(ch) && ch != '.');
}

bool hasSymbolInSurroundings(std::vector<std::string> &engineLines, int col, int row)
{
    int maxHeight = engineLines.size();

    // check top-left
    if (col > 0 && row > 0 && isSymbol(engineLines[col - 1][row - 1]))
    {
        // std::cout << "top-left " << engineLines[col][row] << std::endl;
        return true;
    }

    // check top
    if (col > 0 && isSymbol(engineLines[col - 1][row]))
    {
        // std::cout << "top " << engineLines[col][row] << std::endl;
        return true;
    }

    // check top-right
    if (col > 0 && ((size_t)row < engineLines[col].size() - 1) && isSymbol(engineLines[col - 1][row + 1]))
    {
        // std::cout << "top-right " << engineLines[col][row] << std::endl;
        return true;
    }

    // check left
    if (row > 0 && isSymbol(engineLines[col][row - 1]))
    {
        // std::cout << "left " << engineLines[col][row] << std::endl;
        return true;
    }

    // check right
    if ((size_t)row < engineLines[col].size() - 1 && isSymbol(engineLines[col][row + 1]))
    {
        // std::cout << "right " << engineLines[col][row] << std::endl;
        return true;
    }

    // check bottom-left
    if (col < maxHeight - 1 && row > 0 && isSymbol(engineLines[col + 1][row - 1]))
    {
        // std::cout << "bottom-left " << engineLines[col][row] << std::endl;
        return true;
    }

    // check bottom
    if ((col < maxHeight - 1) && isSymbol(engineLines[col + 1][row]))
    {
        // std::cout << "bottom " << engineLines[col][row] << std::endl;
        return true;
    }

    // check bottom right
    if (col < maxHeight - 1 && (size_t)row < engineLines[col + 1].size() - 1 && isSymbol(engineLines[col + 1][row + 1]))
    {
        // std::cout << "bottom-right " << engineLines[col][row] << std::endl;
        return true;
    }

    return false;
}

int getLineSum(std::vector<std::string> &engineLines, int currentIndex)
{
    int sum = 0;
    int number = 0;
    bool hasSymbol = false;
    std::string &currentLine = engineLines[currentIndex];

    for (size_t i = 0; i < currentLine.size(); i++)
    {
        if (isdigit(currentLine[i]))
        {
            if (number == 0)
                number = currentLine[i] - '0';
            else
            {
                number = number * 10 + (currentLine[i] - '0');
            }

            if (!hasSymbol)
                hasSymbol = hasSymbolInSurroundings(engineLines, currentIndex, i);
        }
        else
        {
            if (number != 0 && hasSymbol)
                sum += number;
            number = 0;
            hasSymbol = false;
        }
    }
    return sum;
}

int getEngineParts(std::ifstream &input)
{
    int sum = 0;
    std::vector<std::string> engineLines;
    std::string line;

    while (std::getline(input, line))
        engineLines.push_back(line);

    for (size_t i = 0; i < engineLines.size(); i++)
        sum += getLineSum(engineLines, i);

    return sum;
}

int main()
{
    std::ifstream input;

    input.open(INPUT_FILE);
    if (input.is_open())
        std::cout << "Engine: " << getEngineParts(input) << std::endl;
    else
        std::cerr << "[" << INPUT_FILE << "] not found!" << std::endl;
}