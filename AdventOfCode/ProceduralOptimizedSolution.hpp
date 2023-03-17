#ifndef PROCEDURAL_OPTIMIZED_SOLUTION
#define PROCEDURAL_OPTIMIZED_SOLUTION

#include <string>
#include <vector>

namespace OptimizedProceduralSolution
{
	void RunOptimizedProceduralSolution (const std::string& fileName,
								bool shouldRunVisibilityCountTest,
								bool shouldRunHighestScenicScoreTest);
	int GetNumberOfVisibleTreesInForest (const std::vector<std::vector<short>>& forest);
	int GetHighestScenicScoreInForest (const std::vector<std::vector<short>>& forest);
}

#endif