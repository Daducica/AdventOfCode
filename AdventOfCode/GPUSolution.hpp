#ifndef GPU_SOLUTION
#define GPU_SOLUTION

#include <string>

#include "Types.hpp"

namespace GPUSolution
{
	ForestMatrix ReadFile (const std::string& fileName);
	uint64_t GetNumberOfVisibleTreesInForest (const ForestMatrix& forest);
	uint64_t GetHighestScenicScoreInForest (const ForestMatrix& forest);

	void RunGPUSolution (const std::string& fileName);
}

#endif