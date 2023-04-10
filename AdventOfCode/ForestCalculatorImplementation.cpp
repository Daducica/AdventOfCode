#include "ForestCalculatorImplementation.hpp"

#include "Types.hpp"

namespace OOPSolution
{

	uint64_t ForestCalculatorImplementation::CheckAndSaveVisibilityFromLeft ()
	{
		const size_t width = forest->GetWidth ();
		const size_t height = forest->GetHeight ();
		uint64_t visibleTreeCount = 0;
		for (size_t row = 0; row < height; row++) {
			TreeHeight maxHeightInRow = -1;
			for (size_t col = 0; col < width; col++) {
				Tree& tree = GetTree (*forest, row, col);
				const TreeHeight treeHeight = tree.GetHeight ();
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


	uint64_t ForestCalculatorImplementation::CheckAndSaveVisibilityFromRight ()
	{
		const size_t width = forest->GetWidth ();
		const size_t height = forest->GetHeight ();
		uint64_t visibleTreeCount = 0;
		for (size_t row = 0; row < height; row++) {
			TreeHeight maxHeightInRow = -1;
			for (std::int32_t col = std::int32_t (width - 1); col >= 0; col--) {
				Tree& tree = GetTree (*forest, row, col);
				const TreeHeight treeHeight = tree.GetHeight ();
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


	uint64_t ForestCalculatorImplementation::CheckAndSaveVisibilityFromTop ()
	{
		const size_t width = forest->GetWidth ();
		const size_t height = forest->GetHeight ();
		uint64_t visibleTreeCount = 0;
		for (size_t col = 0; col < width; col++) {
			TreeHeight maxHeightInColumn = -1;
			for (size_t row = 0; row < height; row++) {
				Tree& tree = GetTree (*forest, row, col);
				const TreeHeight treeHeight = tree.GetHeight ();
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


	uint64_t ForestCalculatorImplementation::CheckAndSaveVisibilityFromBottom ()
	{
		const size_t width = forest->GetWidth ();
		const size_t height = forest->GetHeight ();

		if (height == 0 || width == 0)
			return 0;

		uint64_t visibleTreeCount = 0;
		for (size_t col = 0; col < width; col++) {
			TreeHeight maxHeightInColumn = -1;
			for (std::int32_t row = std::int32_t (height - 1); row >= 0; row--) {
				Tree& tree = GetTree (*forest, row, col);
				const TreeHeight treeHeight = tree.GetHeight ();
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

		if (forest->GetNumberOfVisibleTrees ().has_value ())
			return forest->GetNumberOfVisibleTrees ().value ();

		const size_t width = forest->GetWidth ();
		const size_t height = forest->GetHeight ();

		uint64_t visibleTreeCount = CheckAndSaveVisibilityFromLeft ();
		visibleTreeCount += CheckAndSaveVisibilityFromRight ();
		visibleTreeCount += CheckAndSaveVisibilityFromTop ();
		visibleTreeCount += CheckAndSaveVisibilityFromBottom ();

		return visibleTreeCount;
	}


	uint64_t ForestCalculatorImplementation::GetNumberOfVisibleTreesToTheTop (size_t row, size_t col)
	{
		uint64_t treeCount = 0;
		const TreeHeight treeHeight = GetTree (*forest, row, col).GetHeight ();
		for (std::int32_t index = std::int32_t (row - 1); index >= 0; index--) {
			treeCount++;
			if (GetTree (*forest, index, col).GetHeight () >= treeHeight)
				break;
		}
		return treeCount;
	}


	uint64_t ForestCalculatorImplementation::GetNumberOfVisibleTreesToTheBottom (size_t row, size_t col)
	{
		uint64_t treeCount = 0;
		const TreeHeight treeHeight = GetTree (*forest, row, col).GetHeight ();
		for (size_t index = row + 1; index < forest->GetHeight (); index++) {
			treeCount++;
			if (GetTree (*forest, index, col).GetHeight () >= treeHeight)
				break;
		}
		return treeCount;
	}


	uint64_t ForestCalculatorImplementation::GetNumberOfVisibleTreesToTheLeft (size_t row, size_t col)
	{
		uint64_t treeCount = 0;
		const TreeHeight treeHeight = GetTree (*forest, row, col).GetHeight ();
		for (std::int32_t index = std::int32_t (col - 1); index >= 0; index--) {
			treeCount++;
			if (GetTree (*forest, row, index).GetHeight () >= treeHeight)
				break;
		}
		return treeCount;
	}


	uint64_t ForestCalculatorImplementation::GetNumberOfVisibleTreesToTheRight (size_t row, size_t col)
	{
		uint64_t treeCount = 0;
		const TreeHeight treeHeight = GetTree (*forest, row, col).GetHeight ();
		for (size_t index = col + 1; index < forest->GetWidth (); index++) {
			treeCount++;
			if (GetTree (*forest, row, index).GetHeight () >= treeHeight)
				break;
		}
		return treeCount;
	}


	uint64_t ForestCalculatorImplementation::GetScenicScoreForTree (size_t row, size_t col)
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

		if (forest->GetHighestScenicScore ().has_value ())
			return forest->GetHighestScenicScore ().value ();

		uint64_t maxScore = 0;
		const size_t width = forest->GetWidth ();
		for (size_t row = 0; row < forest->GetHeight (); row++) {
			for (size_t col = 0; col < width; col++) {
				if (forest->IsTreeOnEdge (row, col)) {
					continue;
				}
				const uint64_t scenicScore = GetScenicScoreForTree (row, col);
				GetTree (*forest, row, col).SetScenicScore (scenicScore);
				if (scenicScore > maxScore)
					maxScore = scenicScore;
			}
		}
		return maxScore;
	}
}