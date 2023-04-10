#ifndef PROCEDURAL_OPTIMIZED_SOLUTION
#define PROCEDURAL_OPTIMIZED_SOLUTION

#include <string>

#include "Types.hpp"

namespace OptimizedProceduralSolution
{
	ForestMatrix ReadFile (const std::string& fileName);
	uint64_t GetNumberOfVisibleTreesInForest (const ForestMatrix& forest);
	uint64_t GetHighestScenicScoreInForest (const ForestMatrix& forest);

	void RunOptimizedProceduralSolution (const std::string& fileName);
}

#endif