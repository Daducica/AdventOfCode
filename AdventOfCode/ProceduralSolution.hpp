#ifndef PROCEDURAL_SOLUTION
#define PROCEDURAL_SOLUTION

#include <string>
#include <vector>

namespace ProceduralSolution
{
	std::vector<std::vector<short>> ReadFile (const std::string& fileName);
	uint64_t GetNumberOfVisibleTreesInForest (const std::vector<std::vector<short>>& forest);
	uint64_t GetHighestScenicScoreInForest (const std::vector<std::vector<short>>& forest);

	void RunProceduralSolution (const std::string& fileName);
}

#endif