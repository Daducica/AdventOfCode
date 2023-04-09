#ifndef OOP_SOLUTION
#define OOP_SOLUTION

#include <string>

#include "Forest.hpp"

namespace OOPSolution
{
	Forest ReadFile (const std::string& fileName);
	uint64_t GetNumberOfVisibleTreesInForest (Forest& forest);
	uint64_t GetHighestScenicScoreInForest (Forest& forest);

	void RunOOPSolution (const std::string& fileName);
}

#endif