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

		int GetNumberOfVisibleTreesToTheLeft (unsigned int i, unsigned int j) const;
		int GetNumberOfVisibleTreesToTheRight (unsigned int i, unsigned int j) const;
		int GetNumberOfVisibleTreesToTheTop (unsigned int i, unsigned int j) const;
		int GetNumberOfVisibleTreesToTheBottom (unsigned int i, unsigned int j) const;
		int GetScenicScoreForTree (unsigned int i, unsigned int j) const;

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
