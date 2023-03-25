#ifndef ORIGINAL_SOLUTION
#define ORIGINAL_SOLUTION

#include <string>
#include <vector>

namespace OriginalSolution
{
	std::vector<std::vector<int>> ReadFile (const std::string& fileName);
	int CalculateVisibilityCount (const std::vector<std::vector<int>>& m);
	int CalculateHighestScenicScore (const std::vector<std::vector<int>>& m);

	void RunOriginalSolution (const std::string& fileName);
}

#endif