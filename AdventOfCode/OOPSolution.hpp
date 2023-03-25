#ifndef OOP_SOLUTION
#define OOP_SOLUTION

#include <string>

#include "Forest.hpp"

namespace OOPSolution
{
	Forest ReadFile (const std::string& fileName);
	int GetNumberOfVisibleTreesInForest (Forest& forest);
	int GetHighestScenicScoreInForest (Forest& forest);

	void RunOOPSolution (const std::string& fileName);
}

#endif