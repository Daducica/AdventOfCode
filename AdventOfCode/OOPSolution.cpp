#include "OOPSolution.hpp"

#include <cassert>
#include <fstream>
#include <optional>
#include <vector>

#include "Forest.hpp"
#include "ForestCalculatorImplementation.hpp"

namespace OOPSolution
{


	void RunOOPSolution (const std::string& fileName, bool shouldRunVisibilityCountTest, bool shouldRunHighestScenicScoreTest)
	{
		Forest forest (fileName, std::make_unique<ForestCalculatorImplementation> ());

		if (shouldRunVisibilityCountTest) {
			const int numberOfVisibleTrees = forest.CalculateAndSaveVisibleTreeCount ();
			if (fileName == "day8.txt")
				assert (numberOfVisibleTrees == 1792);
		}

		if (shouldRunHighestScenicScoreTest) {
			const int highestScenicScore = forest.CalculateAndSaveHighestScenicScoreInForest ();
			if (fileName == "day8.txt")
				assert (highestScenicScore == 334880);
		}
	}
}