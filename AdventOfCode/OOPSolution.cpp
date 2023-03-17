#include "OOPSolution.hpp"

#include <cassert>
#include <fstream>
#include <optional>
#include <vector>

#include "Forest.hpp"

namespace OOPSolution
{


	void RunOOPSolution (const std::string& fileName, bool shouldRunVisibilityCountTest, bool shouldRunHighestScenicScoreTest)
	{
		Forest forest (fileName);

		if (shouldRunVisibilityCountTest) {
			const int numberOfVisibleTrees = forest.CalculateAndSaveVisibleTreeCount ();
			assert (numberOfVisibleTrees == 1792);
		}

		if (shouldRunHighestScenicScoreTest) {
			const int highestScenicScore = forest.CalculateAndSaveHighestScenicScoreInForest ();
			assert (highestScenicScore == 334880);
		}
	}
}