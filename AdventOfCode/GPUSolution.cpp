#include "GPUSolution.hpp"
#include "GPUSolutionCUDA.h"
#include "Utilities.hpp"

namespace GPUSolution
{
	ForestMatrix ReadFile (const std::string& fileName)
	{
		return Utilities::ReadForest (fileName);
	}


	uint64_t GetNumberOfVisibleTreesInForest (const ForestMatrix& forest)
	{
		if (forest.size () == 0)
			return 0;

		return RunVisibleTreeCalculationOnGPU (forest);
	}


	uint64_t GetHighestScenicScoreInForest (const ForestMatrix& /*forest*/)
	{
		// TODO
		return 0;
	}


	void RunGPUSolution (const std::string& fileName)
	{
		const ForestMatrix forest = ReadFile (fileName);
		GetNumberOfVisibleTreesInForest (forest);
		GetHighestScenicScoreInForest (forest);
	}

}