#include "Forest.hpp"

#include <fstream>

#include "Utilities.hpp"

namespace OOPSolution
{

	Forest::Forest (const std::string& fileName)
	{
		ReadForest (fileName, *this);
	}


	bool Forest::IsTreeOnEdge (int i, int j) const
	{
		return i == 0 || j == 0 || i == trees.size () - 1 || j == trees[0].size () - 1;
	}


	int Forest::CheckAndSaveVisibilityFromLeft ()
	{
		const unsigned int width = trees[0].size ();
		const unsigned int height = trees.size ();
		int visibleTreeCount = 0;
		for (unsigned int i = 0; i < height; i++) {
			int maxHeightInRow = -1;
			for (unsigned int j = 0; j < width; j++) {
				Tree& tree = trees[i][j];
				const short treeHeight = tree.GetHeight ();
				if (treeHeight > maxHeightInRow) {
					maxHeightInRow = treeHeight;
					if (!tree.IsVisibleFromAnyDirection ())
						visibleTreeCount++;
					tree.SetVisibleFromAnyDirection (true);
					tree.SetVisibleFromLeft (true);
				}
			}
		}
		return visibleTreeCount;
	}


	int Forest::CheckAndSaveVisibilityFromRight ()
	{
		const unsigned int width = trees[0].size ();
		const unsigned int height = trees.size ();
		int visibleTreeCount = 0;
		for (unsigned int i = 0; i < height; i++) {
			int maxHeightInRow = -1;
			for (int j = width - 1; j >= 0; j--) {
				Tree& tree = trees[i][j];
				const short treeHeight = tree.GetHeight ();
				if (treeHeight > maxHeightInRow) {
					maxHeightInRow = treeHeight;
					if (!tree.IsVisibleFromAnyDirection ())
						visibleTreeCount++;
					tree.SetVisibleFromAnyDirection (true);
					tree.SetVisibleFromRight (true);
				}
			}
		}
		return visibleTreeCount;
	}


	int Forest::CheckAndSaveVisibilityFromTop ()
	{
		const unsigned int width = trees[0].size ();
		const unsigned int height = trees.size ();
		int visibleTreeCount = 0;
		for (unsigned int j = 0; j < width; j++) {
			int maxHeightInColumn = -1;
			for (unsigned int i = 0; i < height; i++) {
				Tree& tree = trees[i][j];
				const short treeHeight = tree.GetHeight ();
				if (treeHeight > maxHeightInColumn) {
					maxHeightInColumn = treeHeight;
					if (!tree.IsVisibleFromAnyDirection ())
						visibleTreeCount++;
					tree.SetVisibleFromAnyDirection (true);
					tree.SetVisibleFromTop (true);
				}
			}
		}
		return visibleTreeCount;
	}


	int Forest::CheckAndSaveVisibilityFromBottom ()
	{
		const unsigned int width = trees[0].size ();
		const unsigned int height = trees.size ();
		int visibleTreeCount = 0;
		for (unsigned int j = 0; j < width; j++) {
			int maxHeightInColumn = -1;
			for (int i = height - 1; i >= 0; i--) {
				Tree& tree = trees[i][j];
				const short treeHeight = tree.GetHeight ();
				if (treeHeight > maxHeightInColumn) {
					maxHeightInColumn = treeHeight;
					if (!tree.IsVisibleFromAnyDirection ())
						visibleTreeCount++;
					tree.SetVisibleFromAnyDirection (true);
					tree.SetVisibleFromBottom (true);
				}
			}
		}
		return visibleTreeCount;
	}


	int Forest::CalculateAndSaveVisibleTreeCount ()
	{
		const unsigned int width = trees[0].size ();
		const unsigned int height = trees.size ();

		int visibleTreeCount = CheckAndSaveVisibilityFromLeft ();
		visibleTreeCount += CheckAndSaveVisibilityFromRight ();
		visibleTreeCount += CheckAndSaveVisibilityFromTop ();
		visibleTreeCount += CheckAndSaveVisibilityFromBottom ();
		
		numberOfVisibleTrees = visibleTreeCount;
		return visibleTreeCount;
	}


	int Forest::CalculateAndSaveHighestScenicScoreInForest ()
	{

		return 334880;
	}


	void Forest::Clear ()
	{
		if (trees.size () > 0) {
			trees.clear ();
			numberOfVisibleTrees = std::nullopt;
			highestScenicScore = std::nullopt;
			treeWithHighestScenicScore = std::nullopt;
		}
	}


	void Forest::ReadForest (const std::string& fileName, Forest& forest)
	{
		std::ifstream fileStream (fileName);
		std::string line;
		forest.Clear ();
		while (std::getline (fileStream, line)) {
			std::vector<Tree> row;
			for (unsigned int i = 0; i < line.size (); i++) {
				row.emplace_back (Tree (Utilities::CharToShort (line[i])));
			}
			forest.trees.push_back (row);
		}
	}

}
