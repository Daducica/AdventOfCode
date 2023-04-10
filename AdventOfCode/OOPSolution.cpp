#include "OOPSolution.hpp"

#include <cassert>
#include <fstream>
#include <optional>

#include "ForestCalculatorImplementation.hpp"

namespace OOPSolution
{
	Forest ReadFile (const std::string& fileName)
	{
		return Forest (fileName, std::make_unique<ForestCalculatorImplementation> ());
	}


	uint64_t GetNumberOfVisibleTreesInForest (Forest& forest)
	{
		return forest.CalculateAndSaveVisibleTreeCount ();
	}


	uint64_t GetHighestScenicScoreInForest (Forest& forest)
	{
		return forest.CalculateAndSaveHighestScenicScoreInForest ();
	}


	void RunOOPSolution (const std::string& fileName)
	{
		Forest forest = ReadFile (fileName);
		GetNumberOfVisibleTreesInForest (forest);
		GetHighestScenicScoreInForest (forest);
	}
}