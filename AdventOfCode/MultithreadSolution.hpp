#ifndef MULTITHREAD_SOLUTION
#define MULTITHREAD_SOLUTION

#include <string>

#include "Types.hpp"

namespace MultithreadSolution
{
	ForestMatrix ReadFile (const std::string& fileName);
	uint64_t GetNumberOfVisibleTreesInForest (const ForestMatrix& forest);
	uint64_t GetHighestScenicScoreInForest (const ForestMatrix& forest);

	void RunMultithreadSolution (const std::string& fileName);
}

#endif