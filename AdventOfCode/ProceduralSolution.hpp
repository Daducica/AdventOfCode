#ifndef PROCEDURAL_SOLUTION
#define PROCEDURAL_SOLUTION

#include <string>

#include "Types.hpp"

namespace ProceduralSolution
{
	ForestMatrix ReadFile (const std::string& fileName);
	uint64_t GetNumberOfVisibleTreesInForest (const ForestMatrix& forest);
	uint64_t GetHighestScenicScoreInForest (const ForestMatrix& forest);

	void RunProceduralSolution (const std::string& fileName);
}

#endif