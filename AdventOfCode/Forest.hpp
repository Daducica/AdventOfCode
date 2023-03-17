#ifndef FOREST
#define FOREST

#include <optional>
#include <string>
#include <vector>

#include "Tree.hpp"

namespace OOPSolution
{
	class Forest
	{
		std::vector<std::vector<Tree>> trees;
		std::optional<int> numberOfVisibleTrees;
		std::optional<int> highestScenicScore;
		std::optional<Tree*> treeWithHighestScenicScore;

		int CheckAndSaveVisibilityFromLeft ();
		int CheckAndSaveVisibilityFromRight ();
		int CheckAndSaveVisibilityFromTop ();
		int CheckAndSaveVisibilityFromBottom ();

		void Clear ();

	public:
		Forest (const std::string& fileName);
		int CalculateAndSaveVisibleTreeCount ();
		int CalculateAndSaveHighestScenicScoreInForest ();
		bool IsTreeOnEdge (int i, int j) const;

		static void ReadForest (const std::string& fileName, Forest& forest);
	};
}

#endif
