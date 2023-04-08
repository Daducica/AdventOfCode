#ifndef GPU_SOLUTION
#define GPU_SOLUTION

#include <string>
#include <vector>

namespace GPUSolution
{
	std::vector<std::vector<short>> ReadFile (const std::string& fileName);
	int GetNumberOfVisibleTreesInForest (const std::vector<std::vector<short>>& forest);
	int GetHighestScenicScoreInForest (const std::vector<std::vector<short>>& forest);

	void RunGPUSolution (const std::string& fileName);
}

#endif