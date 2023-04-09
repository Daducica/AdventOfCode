#include "ForestCalculatorImplementation.hpp"

namespace OOPSolution
{

	uint64_t ForestCalculatorImplementation::CheckAndSaveVisibilityFromLeft () const
	{
		const size_t width = forest->GetWidth ();
		const size_t height = forest->GetHeight ();
		uint64_t visibleTreeCount = 0;
		for (size_t row = 0; row < height; row++) {
			int maxHeightInRow = -1;
			for (size_t col = 0; col < width; col++) {
				Tree& tree = forest->GetTree (row, col);
				const short treeHeight = tree.GetHeight ();
				if (treeHeight > maxHeightInRow) {
					maxHeightInRow = treeHeight;
					if (!tree.IsVisibleFromAnyDirection ())
						visibleTreeCount++;
					tree.SetVisibleFromLeft (true);
				}
			}
		}
		return visibleTreeCount;
	}


	uint64_t ForestCalculatorImplementation::CheckAndSaveVisibilityFromRight () const
	{
		const size_t width = forest->GetWidth ();
		const size_t height = forest->GetHeight ();
		uint64_t visibleTreeCount = 0;
		for (size_t row = 0; row < height; row++) {
			int maxHeightInRow = -1;
			for (std::int32_t col = std::int32_t (width - 1); col >= 0; col--) {
				Tree& tree = forest->GetTree (row, col);
				const short treeHeight = tree.GetHeight ();
				if (treeHeight > maxHeightInRow) {
					maxHeightInRow = treeHeight;
					if (!tree.IsVisibleFromAnyDirection ())
						visibleTreeCount++;
					tree.SetVisibleFromRight (true);
				}
			}
		}
		return visibleTreeCount;
	}


	uint64_t ForestCalculatorImplementation::CheckAndSaveVisibilityFromTop () const
	{
		const size_t width = forest->GetWidth ();
		const size_t height = forest->GetHeight ();
		uint64_t visibleTreeCount = 0;
		for (size_t col = 0; col < width; col++) {
			int maxHeightInColumn = -1;
			for (size_t row = 0; row < height; row++) {
				Tree& tree = forest->GetTree (row, col);
				const short treeHeight = tree.GetHeight ();
				if (treeHeight > maxHeightInColumn) {
					maxHeightInColumn = treeHeight;
					if (!tree.IsVisibleFromAnyDirection ())
						visibleTreeCount++;
					tree.SetVisibleFromTop (true);
				}
			}
		}
		return visibleTreeCount;
	}


	uint64_t ForestCalculatorImplementation::CheckAndSaveVisibilityFromBottom () const
	{
		const size_t width = forest->GetWidth ();
		const size_t height = forest->GetHeight ();

		if (height == 0 || width == 0)
			return 0;

		uint64_t visibleTreeCount = 0;
		for (size_t col = 0; col < width; col++) {
			int maxHeightInColumn = -1;
			for (std::int32_t row = std::int32_t (height - 1); row >= 0; row--) {
				Tree& tree = forest->GetTree (row, col);
				const short treeHeight = tree.GetHeight ();
				if (treeHeight > maxHeightInColumn) {
					maxHeightInColumn = treeHeight;
					if (!tree.IsVisibleFromAnyDirection ())
						visibleTreeCount++;
					tree.SetVisibleFromBottom (true);
				}
			}
		}
		return visibleTreeCount;
	}


	uint64_t ForestCalculatorImplementation::CalculateAndSaveVisibleTreeCount (Forest* forestIn)
	{
		forest = forestIn;

		const size_t width = forest->GetWidth ();
		const size_t height = forest->GetHeight ();

		uint64_t visibleTreeCount = CheckAndSaveVisibilityFromLeft ();
		visibleTreeCount += CheckAndSaveVisibilityFromRight ();
		visibleTreeCount += CheckAndSaveVisibilityFromTop ();
		visibleTreeCount += CheckAndSaveVisibilityFromBottom ();

		return visibleTreeCount;
	}


	uint64_t ForestCalculatorImplementation::GetNumberOfVisibleTreesToTheTop (size_t row, size_t col) const
	{
		uint64_t treeCount = 0;
		const int treeHeight = forest->GetTree (row, col).GetHeight ();
		for (std::int32_t index = std::int32_t (row - 1); index >= 0; index--) {
			treeCount++;
			if (forest->GetTree (index, col).GetHeight () >= treeHeight)
				break;
		}
		return treeCount;
	}


	uint64_t ForestCalculatorImplementation::GetNumberOfVisibleTreesToTheBottom (size_t row, size_t col) const
	{
		uint64_t treeCount = 0;
		const int treeHeight = forest->GetTree (row, col).GetHeight ();
		for (size_t index = row + 1; index < forest->GetHeight (); index++) {
			treeCount++;
			if (forest->GetTree (index, col).GetHeight () >= treeHeight)
				break;
		}
		return treeCount;
	}


	uint64_t ForestCalculatorImplementation::GetNumberOfVisibleTreesToTheLeft (size_t row, size_t col) const
	{
		uint64_t treeCount = 0;
		const int treeHeight = forest->GetTree (row, col).GetHeight ();
		for (std::int32_t index = std::int32_t (col - 1); index >= 0; index--) {
			treeCount++;
			if (forest->GetTree (row, index).GetHeight () >= treeHeight)
				break;
		}
		return treeCount;
	}


	uint64_t ForestCalculatorImplementation::GetNumberOfVisibleTreesToTheRight (size_t row, size_t col) const
	{
		uint64_t treeCount = 0;
		const int treeHeight = forest->GetTree (row, col).GetHeight ();
		for (size_t index = col + 1; index < forest->GetWidth (); index++) {
			treeCount++;
			if (forest->GetTree (row, index).GetHeight () >= treeHeight)
				break;
		}
		return treeCount;
	}


	uint64_t ForestCalculatorImplementation::GetScenicScoreForTree (size_t row, size_t col) const
	{
		const uint64_t scoreToLeft = GetNumberOfVisibleTreesToTheLeft (row, col);
		const uint64_t scoreToRight = GetNumberOfVisibleTreesToTheRight (row, col);
		const uint64_t scoreToTop = GetNumberOfVisibleTreesToTheTop (row, col);
		const uint64_t scoreToBottom = GetNumberOfVisibleTreesToTheBottom (row, col);
		return scoreToLeft * scoreToRight * scoreToTop * scoreToBottom;
	}


	uint64_t ForestCalculatorImplementation::CalculateAndSaveHighestScenicScoreInForest (Forest* forestIn)
	{
		forest = forestIn;
		uint64_t maxScore = 0;
		const size_t width = forest->GetWidth ();
		for (size_t row = 0; row < forest->GetHeight (); row++) {
			for (size_t col = 0; col < width; col++) {
				if (forest->IsTreeOnEdge (row, col)) {
					continue;
				}
				const uint64_t scenicScore = GetScenicScoreForTree (row, col);
				forest->GetTree (row, col).SetScenicScore (scenicScore);
				if (scenicScore > maxScore)
					maxScore = scenicScore;
			}
		}
		return maxScore;
	}
}