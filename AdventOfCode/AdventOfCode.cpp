#include <string>

#include "TestRunner.hpp"

const std::string FileName = "day8.txt";
constexpr size_t NumberOfTestRuns = 10;

int main (int)
{
    Test::TestConfig config { FileName, NumberOfTestRuns, true, true, true, true };
    Test::RunTests (config);
}