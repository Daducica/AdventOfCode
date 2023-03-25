#ifndef PROCEDURAL_OPTIMIZED_SOLUTION
#define PROCEDURAL_OPTIMIZED_SOLUTION

#include <string>
#include <vector>

namespace OptimizedProceduralSolution
{
	std::vector<std::vector<short>> ReadFile (const std::string& fileName);
	int GetNumberOfVisibleTreesInForest (const std::vector<std::vector<short>>& forest);
	int GetHighestScenicScoreInForest (const std::vector<std::vector<short>>& forest);

	void RunOptimizedProceduralSolution (const std::string& fileName);
}

#endif