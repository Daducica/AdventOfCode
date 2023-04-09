#ifndef GPU_SOLUTION_CUDA
#define GPU_SOLUTION_CUDA

#include <vector>

namespace GPUSolution
{
	uint64_t RunVisibleTreeCalculationOnGPU (const std::vector<std::vector<short>>& forest);
}


#endif