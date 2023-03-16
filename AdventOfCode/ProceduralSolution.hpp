#ifndef PROCEDURAL_SOLUTION
#define PROCEDURAL_SOLUTION

#include <string>
#include <vector>

namespace ProceduralSolution
{
	void RunProceduralSolution (const std::string& fileName);
	int GetNumberOfVisibleTreesInForest (const std::vector<std::vector<short>>& forest);
	int GetHighestScenicScoreInForest (const std::vector<std::vector<short>>& forest);
}

#endif