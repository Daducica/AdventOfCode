#ifndef PROCEDURAL_SOLUTION
#define PROCEDURAL_SOLUTION

#include <string>
#include <vector>

namespace ProceduralSolution
{
	std::vector<std::vector<short>> ReadFile (const std::string& fileName);
	int GetNumberOfVisibleTreesInForest (const std::vector<std::vector<short>>& forest);
	int GetHighestScenicScoreInForest (const std::vector<std::vector<short>>& forest);

	void RunProceduralSolution (const std::string& fileName);
}

#endif