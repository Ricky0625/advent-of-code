#include <iostream>
#include <fstream>
#include <vector>
#include <set>

#define INPUT_FILE "../input.txt"

void splitStr(const std::string &str, std::vector<std::string> &vect, const std::string &delimeter)
{
    size_t pos = str.find(delimeter);
    size_t initialPos = 0;

    vect.clear();
    while (pos != std::string::npos)
    {
        std::string substring = str.substr(initialPos, pos - initialPos);
        if (!substring.empty())
            vect.push_back(substring);
        initialPos = pos + delimeter.size();
        pos = str.find(delimeter, initialPos);
    }

    std::string lastSubstring = str.substr(initialPos, std::min(pos, str.size()) - initialPos + 1);
    if (!lastSubstring.empty())
        vect.push_back(lastSubstring);
}

int getCardPoints(std::string &line)
{
    int points = 0;
    size_t pointsStart = line.find(": ");

    std::vector<std::string> twoPart;
    std::vector<std::string> entries;
    std::vector<std::string> answers;
    std::set<std::string> answerSet;
    std::string pointsStr = line.substr(pointsStart);

    splitStr(pointsStr, twoPart, " | ");
    splitStr(twoPart[0], entries, " ");
    splitStr(twoPart[1], answers, " ");

    for (size_t i = 0; i < answers.size(); i++)
        answerSet.insert(answers[i]);
    
    for (size_t i = 0; i < entries.size(); i++)
    {
        if (answerSet.find(entries[i]) != answerSet.end())
            (points == 0 ? ++points : points *= 2);
    }
    return points;
}

int getAllPoints(std::ifstream &input)
{
    int sum = 0;
    std::string line;

    while (getline(input, line))
        sum += getCardPoints(line);
    return sum;
}

int main()
{
    std::ifstream input;

    input.open(INPUT_FILE);
    if (input.is_open())
        std::cout << getAllPoints(input) << std::endl;
    else
        std::cerr << "[" << INPUT_FILE << "] not found!" << std::endl;
}