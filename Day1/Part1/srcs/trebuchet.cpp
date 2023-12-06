#include <iostream>
#include <fstream>
#include <vector>

#define INPUT_FILE "../input.txt"

int toDigit(char ch)
{
    return ch - 48;
}

void pushNums(std::string line, std::vector<int> &nums)
{
    nums.clear();
    for (size_t i = 0; i < line.size(); i++)
    {
        if (isdigit(line[i]))
            nums.push_back(toDigit(line[i]));
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