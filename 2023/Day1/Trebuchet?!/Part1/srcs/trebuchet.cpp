#include <iostream>
#include <fstream>
#include <string>

#define INPUT_FILE "../input.txt"

int toDigit(char ch)
{
    return ch - 48;
}

std::string constructStringWithDigitOnly(std::string &line)
{
    std::string digitStr = "";

    for (size_t i = 0; i < line.size(); i++)
    {
        if (isdigit(line[i]))
            digitStr += line[i];
    }
    return digitStr;
}

/**
 * @brief Get calibration value.
 * @details
 * According to the subject, the calibration document consists of
 * lines of text. On each line, the calibration value can be found
 * by combining the first digit and last digit to form a single
 * two-digit number.
 * So the idea is, take all the digit out of the string to construct
 * a new string. This will take O(n). Then get the first and last
 * digit by simply accessing them by index.
 * First: index 0
 * Last: index (len - 1)
 * After that convert them into number.
*/
int getCalibrationValue(std::ifstream &input)
{
    int calibrationValue = 0;
    std::string line;
    std::string digitStr;
    std::string twoDigit = "";

    while (std::getline(input, line))
    {
        digitStr = constructStringWithDigitOnly(line);
        calibrationValue += (toDigit(digitStr[0]) * 10) + toDigit(digitStr[digitStr.size() - 1]);
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