#include <iostream>
#include <fstream>
#include <vector>
#include <unordered_map>

#define INPUT_FILE "../input.txt"
typedef std::unordered_map<std::string, int> DigitMap;

/**
 * @brief Convert an ASCII character to its actual numeric form
 */
int toDigit(char ch)
{
    return ch - 48;
}

void pushNums(std::string line, std::vector<int> &nums)
{
    DigitMap digits{
        {"zero", 0},
        {"one", 1},
        {"two", 2},
        {"three", 3},
        {"four", 4},
        {"five", 5},
        {"six", 6},
        {"seven", 7},
        {"eight", 8},
        {"nine", 9},
    };
    const size_t MIN_KEY_LEN = 3;
    const size_t MAX_KEY_LEN = 5;

    std::string subStr;

    nums.clear();
    for (std::string::iterator it = line.begin(); it != line.end(); it++)
    {
        if (isdigit(*it))
        {
            nums.push_back(toDigit(*it));
            continue;
        }

        for (size_t i = MIN_KEY_LEN; i <= MAX_KEY_LEN && it + i <= line.end(); i++)
        {
            subStr = std::string(it, it + i);
            DigitMap::iterator occurrence = digits.find(subStr);
            if (occurrence != digits.end())
            {
                nums.push_back(occurrence->second);
                break;
            }
        }
    }
}

/**
 * @brief Get calibration value.
 * @details
 * According to the subject, the calibration document consists of
 * lines of text. On each line, the calibration value can be found
 * by combining the first digit and last digit to form a single
 * two-digit number.
 * So the idea is, push the digit into a vector and access the
 * first and last digit.
 * First: index 0 * 10
 * Last: index (len - 1)
 * After that convert them into number.
 */
int getCalibrationValue(std::ifstream &input)
{
    int calibrationValue = 0;
    std::string line;
    std::vector<int> nums;

    while (std::getline(input, line))
    {
        pushNums(line, nums);
        if (nums.empty())
            continue;
        calibrationValue += (nums.front() * 10) + nums.back();
    }

    return calibrationValue;
}

int main()
{
    std::ifstream input;

    input.open(INPUT_FILE);
    if (input.is_open())
        std::cout << "Calibration value: " << getCalibrationValue(input) << std::endl;
    else
        std::cerr << "[" << INPUT_FILE << "] not found!" << std::endl;
}