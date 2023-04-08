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


	int GetNumberOfVisibleTreesInForest (const std::vector<std::vector<short>>& forest)
	{
		return RunVisibleTreeCalculationOnGPU (forest);
	}


	int GetHighestScenicScoreInForest (const std::vector<std::vector<short>>& forest)
	{
		// TODO
		return 0;
	}


	void RunGPUSolution (const std::string& fileName)
	{
		const Forest forest = ReadFile (fileName);
		//GetNumberOfVisibleTreesInForest (forest);
		GetHighestScenicScoreInForest (forest);
	}

}