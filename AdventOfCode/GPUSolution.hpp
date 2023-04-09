#ifndef GPU_SOLUTION
#define GPU_SOLUTION

#include <string>
#include <vector>

namespace GPUSolution
{
	std::vector<std::vector<short>> ReadFile (const std::string& fileName);
	uint64_t GetNumberOfVisibleTreesInForest (const std::vector<std::vector<short>>& forest);
	uint64_t GetHighestScenicScoreInForest (const std::vector<std::vector<short>>& forest);

	void RunGPUSolution (const std::string& fileName);
}

#endif