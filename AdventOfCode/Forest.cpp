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


	int Forest::GetNumberOfVisibleTreesToTheLeft (unsigned int i, unsigned int j) const
	{
		int treeCount = 0;
		const int treeHeight = trees[i][j].GetHeight ();
		for (int k = i - 1; k >= 0; k--) {
			treeCount++;
			if (trees[k][j].GetHeight () >= treeHeight)
				break;
		}
		return treeCount;
	}


	int Forest::GetNumberOfVisibleTreesToTheRight (unsigned int i, unsigned int j) const
	{
		int treeCount = 0;
		const int treeHeight = trees[i][j].GetHeight ();
		for (unsigned int k = i + 1; k < trees.size (); k++) {
			treeCount++;
			if (trees[k][j].GetHeight () >= treeHeight)
				break;
		}
		return treeCount;
	}


	int Forest::GetNumberOfVisibleTreesToTheTop (unsigned int i, unsigned int j) const
	{
		int treeCount = 0;
		const int treeHeight = trees[i][j].GetHeight ();
		for (int k = j - 1; k >= 0; k--) {
			treeCount++;
			if (trees[i][k].GetHeight () >= treeHeight)
				break;
		}
		return treeCount;
	}


	int Forest::GetNumberOfVisibleTreesToTheBottom (unsigned int i, unsigned int j) const
	{
		int treeCount = 0;
		const int treeHeight = trees[i][j].GetHeight ();
		for (unsigned int k = j + 1; k < trees[0].size (); k++) {
			treeCount++;
			if (trees[i][k].GetHeight () >= treeHeight)
				break;
		}
		return treeCount;
	}


	int Forest::GetScenicScoreForTree (unsigned int i, unsigned int j) const
	{
		const int scoreToLeft = GetNumberOfVisibleTreesToTheLeft (i, j);
		const int scoreToRight = GetNumberOfVisibleTreesToTheRight (i, j);
		const int scoreToTop = GetNumberOfVisibleTreesToTheTop (i, j);
		const int scoreToBottom = GetNumberOfVisibleTreesToTheBottom (i, j);
		return scoreToLeft * scoreToRight * scoreToTop * scoreToBottom;
	}

	int Forest::CalculateAndSaveHighestScenicScoreInForest ()
	{
		int maxScore = 0;
		const unsigned int width = trees[0].size ();
		for (unsigned int i = 0; i < trees.size (); i++) {
			for (unsigned int j = 0; j < width; j++) {
				if (IsTreeOnEdge (i, j)) {
					continue;
				}
				const int scenicScore = GetScenicScoreForTree (i, j);
				trees[i][j].SetScenicScore (scenicScore);
				if (scenicScore > maxScore)
					maxScore = scenicScore;
			}
		}
		return maxScore;
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
