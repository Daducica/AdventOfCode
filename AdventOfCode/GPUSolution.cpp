#include "GPUSolution.hpp"
#include "GPUSolutionCUDA.h"
#include "Utilities.hpp"

namespace GPUSolution
{
	typedef std::vector<std::vector<short>> Forest;

	std::vector<std::vector<short>> ReadFile (const std::string& fileName)
	{
		return Utilities::ReadForest (fileName);
	}


	uint64_t GetNumberOfVisibleTreesInForest (const std::vector<std::vector<short>>& forest)
	{
		if (forest.size () == 0)
			return 0;

		return RunVisibleTreeCalculationOnGPU (forest);
	}


	uint64_t GetHighestScenicScoreInForest (const std::vector<std::vector<short>>& /*forest*/)
	{
		// TODO
		return 0;
	}


	void RunGPUSolution (const std::string& fileName)
	{
		const Forest forest = ReadFile (fileName);
		GetNumberOfVisibleTreesInForest (forest);
		GetHighestScenicScoreInForest (forest);
	}

}