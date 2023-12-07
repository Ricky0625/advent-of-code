#include <iostream>
#include <fstream>
#include <vector>
#include <unordered_map>

#define INPUT_FILE "../input.txt"
#define R "red"
#define G "green"
#define B "blue"

typedef std::unordered_map<std::string, int> ColorCount;

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

void resetColorCount(ColorCount &count)
{
    count = {
        {R, 0},
        {G, 0},
        {B, 0}
    };
}

int getId(std::string &line)
{
    const std::string delimeter = ": ";
    size_t delimeterPos = line.find(delimeter);

    if (delimeterPos == std::string::npos)
        return -1;
    
    std::vector<std::string> vect;
    std::string idStr = line.substr(0, delimeterPos);
    line = line.substr(delimeterPos + delimeter.size());

    splitStr(idStr, vect, " ");
    return atoi((vect.back()).c_str());
}

void getColorCount(std::string &attempts, ColorCount &counts)
{
    (void)counts;
    std::vector<std::string> allAttempts;
    std::vector<std::string> currentAttemptColors;
    std::vector<std::string> colorStats;
    int value;

    splitStr(attempts, allAttempts, "; ");
    for (size_t i = 0; i < allAttempts.size(); i++)
    {
        splitStr(allAttempts[i], currentAttemptColors, ", ");
        for (size_t j = 0; j < currentAttemptColors.size(); j++)
        {
            splitStr(currentAttemptColors[j], colorStats, " ");
            value = std::stoi(colorStats.front());
            if (counts[colorStats.back()] < value)
                counts[colorStats.back()] = value;
        }
    }
}

int getPower(ColorCount &counts)
{
    return (counts[R] * counts[G] * counts[B]);
}

int getSumOfIds(std::ifstream &input)
{
    int currentId;
    std::string line;
    ColorCount counts;
    int sum = 0;

    resetColorCount(counts);
    while (std::getline(input, line))
    {
        currentId = getId(line);
        if (currentId == -1)
            continue;
        getColorCount(line, counts);
        sum += getPower(counts);
        resetColorCount(counts);
    }
    return sum;
}

int main()
{
    std::ifstream input;

    input.open(INPUT_FILE);
    if (input.is_open())
        std::cout << "Sum of IDs: " << getSumOfIds(input) << std::endl;
    else
        std::cerr << "[" << INPUT_FILE << "] not found!" << std::endl;
}