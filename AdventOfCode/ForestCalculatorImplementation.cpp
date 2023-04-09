#include "ForestCalculatorImplementation.hpp"

namespace OOPSolution
{

	int ForestCalculatorImplementation::CheckAndSaveVisibilityFromLeft () const
	{
		const unsigned int width = forest->GetWidth ();
		const unsigned int height = forest->GetHeight ();
		int visibleTreeCount = 0;
		for (unsigned int i = 0; i < height; i++) {
			int maxHeightInRow = -1;
			for (unsigned int j = 0; j < width; j++) {
				Tree& tree = forest->GetTree (i, j);
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


	int ForestCalculatorImplementation::CheckAndSaveVisibilityFromRight () const
	{
		const unsigned int width = forest->GetWidth ();
		const unsigned int height = forest->GetHeight ();
		int visibleTreeCount = 0;
		for (unsigned int i = 0; i < height; i++) {
			int maxHeightInRow = -1;
			for (int j = width - 1; j >= 0; j--) {
				Tree& tree = forest->GetTree (i, j);
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


	int ForestCalculatorImplementation::CheckAndSaveVisibilityFromTop () const
	{
		const unsigned int width = forest->GetWidth ();
		const unsigned int height = forest->GetHeight ();
		int visibleTreeCount = 0;
		for (unsigned int j = 0; j < width; j++) {
			int maxHeightInColumn = -1;
			for (unsigned int i = 0; i < height; i++) {
				Tree& tree = forest->GetTree (i, j);
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


	int ForestCalculatorImplementation::CheckAndSaveVisibilityFromBottom () const
	{
		const unsigned int width = forest->GetWidth ();
		const unsigned int height = forest->GetHeight ();

		if (height == 0 || width == 0)
			return 0;

		int visibleTreeCount = 0;
		for (unsigned int j = 0; j < width; j++) {
			int maxHeightInColumn = -1;
			for (int i = height - 1; i >= 0; i--) {
				Tree& tree = forest->GetTree (i, j);
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


	int ForestCalculatorImplementation::CalculateAndSaveVisibleTreeCount (Forest* forestIn)
	{
		forest = forestIn;

		const unsigned int width = forest->GetWidth ();
		const unsigned int height = forest->GetHeight ();

		int visibleTreeCount = CheckAndSaveVisibilityFromLeft ();
		visibleTreeCount += CheckAndSaveVisibilityFromRight ();
		visibleTreeCount += CheckAndSaveVisibilityFromTop ();
		visibleTreeCount += CheckAndSaveVisibilityFromBottom ();

		return visibleTreeCount;
	}


	int ForestCalculatorImplementation::GetNumberOfVisibleTreesToTheLeft (unsigned int i, unsigned int j) const
	{
		int treeCount = 0;
		const int treeHeight = forest->GetTree (i, j).GetHeight ();
		for (int k = i - 1; k >= 0; k--) {
			treeCount++;
			if (forest->GetTree (k, j).GetHeight () >= treeHeight)
				break;
		}
		return treeCount;
	}


	int ForestCalculatorImplementation::GetNumberOfVisibleTreesToTheRight (unsigned int i, unsigned int j) const
	{
		int treeCount = 0;
		const int treeHeight = forest->GetTree (i, j).GetHeight ();
		for (unsigned int k = i + 1; k < forest->GetHeight (); k++) {
			treeCount++;
			if (forest->GetTree (k, j).GetHeight () >= treeHeight)
				break;
		}
		return treeCount;
	}


	int ForestCalculatorImplementation::GetNumberOfVisibleTreesToTheTop (unsigned int i, unsigned int j) const
	{
		int treeCount = 0;
		const int treeHeight = forest->GetTree (i, j).GetHeight ();
		for (int k = j - 1; k >= 0; k--) {
			treeCount++;
			if (forest->GetTree (i, k).GetHeight () >= treeHeight)
				break;
		}
		return treeCount;
	}


	int ForestCalculatorImplementation::GetNumberOfVisibleTreesToTheBottom (unsigned int i, unsigned int j) const
	{
		int treeCount = 0;
		const int treeHeight = forest->GetTree (i, j).GetHeight ();
		for (unsigned int k = j + 1; k < forest->GetWidth (); k++) {
			treeCount++;
			if (forest->GetTree (i, k).GetHeight () >= treeHeight)
				break;
		}
		return treeCount;
	}


	int ForestCalculatorImplementation::GetScenicScoreForTree (unsigned int i, unsigned int j) const
	{
		const int scoreToLeft = GetNumberOfVisibleTreesToTheLeft (i, j);
		const int scoreToRight = GetNumberOfVisibleTreesToTheRight (i, j);
		const int scoreToTop = GetNumberOfVisibleTreesToTheTop (i, j);
		const int scoreToBottom = GetNumberOfVisibleTreesToTheBottom (i, j);
		return scoreToLeft * scoreToRight * scoreToTop * scoreToBottom;
	}


	int ForestCalculatorImplementation::CalculateAndSaveHighestScenicScoreInForest (Forest* forestIn)
	{
		forest = forestIn;
		int maxScore = 0;
		const unsigned int width = forest->GetWidth ();
		for (unsigned int i = 0; i < forest->GetHeight (); i++) {
			for (unsigned int j = 0; j < width; j++) {
				if (forest->IsTreeOnEdge (i, j)) {
					continue;
				}
				const int scenicScore = GetScenicScoreForTree (i, j);
				forest->GetTree (i, j).SetScenicScore (scenicScore);
				if (scenicScore > maxScore)
					maxScore = scenicScore;
			}
		}
		return maxScore;
	}
}