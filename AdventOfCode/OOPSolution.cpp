#include "OOPSolution.hpp"

#include <cassert>
#include <fstream>
#include <optional>
#include <vector>

#include "ForestCalculatorImplementation.hpp"

namespace OOPSolution
{
	Forest ReadFile (const std::string& fileName)
	{
		return Forest (fileName, std::make_unique<ForestCalculatorImplementation> ());
	}


	int GetNumberOfVisibleTreesInForest (Forest& forest)
	{
		return forest.CalculateAndSaveVisibleTreeCount ();
	}


	int GetHighestScenicScoreInForest (Forest& forest)
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