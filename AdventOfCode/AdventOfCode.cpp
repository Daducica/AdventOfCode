#include <string>

#include "TestRunner.hpp"

const std::string FileName = "day8.txt";
constexpr unsigned int NumberOfTestRuns = 10;

int main (int)
{
    Test::TestConfig config { FileName, NumberOfTestRuns, true, true, true, true};
    Test::RunTests (config);
}