#include "ProceduralOptimizedSolution.hpp"

#include <cassert>
#include "Utilities.hpp"

namespace OptimizedProceduralSolution
{
    ForestMatrix ReadFile (const std::string& fileName)
    {
        return Utilities::ReadForest (fileName);
    }


    static bool IsTreeOnEdge (const ForestMatrix& forest, size_t i, size_t j)
    {
        if (forest.empty ())
            return false;

        return i == 0 || j == 0 || i == forest.size () - 1 || j == forest[0].size () - 1;
    }

    static uint64_t CheckVisibilityFromLeft (const ForestMatrix& forest, VisibilityCache& visibility)
    {
        const size_t width = forest[0].size ();
        const size_t height = forest.size ();
        uint64_t visibleTreeCount = 0;
        for (size_t row = 0; row < height; ++row) {
            TreeHeight maxHeightInRow = -1;
            for (size_t col = 0; col < width; ++col) {
                const TreeHeight treeHeight = forest[row][col];
                if (treeHeight > maxHeightInRow) {
                    maxHeightInRow = treeHeight;
                    if (!visibility[row][col]) {
                        ++visibleTreeCount;
                        visibility[row][col] = true;
                    }
                }
            }
        }
        return visibleTreeCount;
    }


    static uint64_t CheckVisibilityFromRight (const ForestMatrix& forest, VisibilityCache& visibility)
    {
        const size_t width = forest[0].size ();
        const size_t height = forest.size ();
        uint64_t visibleTreeCount = 0;
        for (size_t row = 0; row < height; ++row) {
            TreeHeight maxHeightInRow = -1;
            for (std::int32_t col = std::int32_t (width - 1); col >= 0; --col) {
                const TreeHeight treeHeight = forest[row][col];
                if (treeHeight > maxHeightInRow) {
                    maxHeightInRow = treeHeight;
                    if (!visibility[row][col]) {
                        ++visibleTreeCount;
                        visibility[row][col] = true;
                    }
                }
            }
        }
        return visibleTreeCount;
    }


    static uint64_t CheckVisibilityFromTop (const ForestMatrix& forest, VisibilityCache& visibility)
    {
        const size_t width = forest[0].size ();
        const size_t height = forest.size ();
        uint64_t visibleTreeCount = 0;
        for (size_t col = 0; col < width; ++col) {
            TreeHeight maxHeightInColumn = -1;
            for (size_t row = 0; row < height; ++row) {
                const TreeHeight treeHeight = forest[row][col];
                if (treeHeight > maxHeightInColumn) {
                    maxHeightInColumn = treeHeight;
                    if (!visibility[row][col]) {
                        ++visibleTreeCount;
                        visibility[row][col] = true;
                    }
                }
            }
        }
        return visibleTreeCount;
    }


    static uint64_t CheckVisibilityFromBottom (const ForestMatrix& forest, VisibilityCache& visibility)
    {
        const size_t width = forest[0].size ();
        const size_t height = forest.size ();
        uint64_t visibleTreeCount = 0;
        for (size_t col = 0; col < width; ++col) {
            TreeHeight maxHeightInColumn = -1;
            for (std::int32_t row = std::int32_t (height - 1); row >= 0; --row) {
                const TreeHeight treeHeight = forest[row][col];
                if (treeHeight > maxHeightInColumn) {
                    maxHeightInColumn = treeHeight;
                    if (!visibility[row][col]) {
                        ++visibleTreeCount;
                        visibility[row][col] = true;
                    }
                }
            }
        }
        return visibleTreeCount;
    }


    uint64_t GetNumberOfVisibleTreesInForest (const ForestMatrix& forest)
    {
        if (forest.empty ())
            return 0;

        const size_t width = forest[0].size ();
        const size_t height = forest.size ();

        VisibilityCacheRow row (width, false);
        VisibilityCache visibility (height, row);

        uint64_t visibleTreeCount = CheckVisibilityFromLeft (forest, visibility);
        visibleTreeCount += CheckVisibilityFromRight (forest, visibility);
        visibleTreeCount += CheckVisibilityFromTop (forest, visibility);
        visibleTreeCount += CheckVisibilityFromBottom (forest, visibility);

        return visibleTreeCount;
    }


    static uint64_t GetNumberOfVisibleTreesToTheTop (const ForestMatrix& forest, size_t row, size_t col)
    {
        uint64_t treeCount = 0;
        const TreeHeight treeHeight = forest[row][col];
        for (std::int32_t index = std::int32_t (row - 1); index >= 0; index--) {
            treeCount++;
            if (forest[index][col] >= treeHeight)
                break;
        }
        return treeCount;
    }


    static uint64_t GetNumberOfVisibleTreesToTheBottom (const ForestMatrix& forest, size_t row, size_t col)
    {
        uint64_t treeCount = 0;
        const TreeHeight treeHeight = forest[row][col];
        for (size_t index = row + 1; index < forest.size (); index++) {
            treeCount++;
            if (forest[index][col] >= treeHeight)
                break;
        }
        return treeCount;
    }


    static uint64_t GetNumberOfVisibleTreesToTheLeft (const ForestMatrix& forest, size_t row, size_t col)
    {
        uint64_t treeCount = 0;
        const TreeHeight treeHeight = forest[row][col];
        for (std::int32_t index = std::int32_t (col - 1); index >= 0; index--) {
            treeCount++;
            if (forest[row][index] >= treeHeight)
                break;
        }
        return treeCount;
    }


    static uint64_t GetNumberOfVisibleTreesToTheRight (const ForestMatrix& forest, size_t row, size_t col)
    {
        uint64_t treeCount = 0;
        const TreeHeight treeHeight = forest[row][col];
        for (size_t index = col + 1; index < forest[0].size (); index++) {
            treeCount++;
            if (forest[row][index] >= treeHeight)
                break;
        }
        return treeCount;
    }


    static uint64_t GetScenicScoreForTree (const ForestMatrix& forest, size_t row, size_t col)
    {
        const uint64_t scoreToLeft = GetNumberOfVisibleTreesToTheLeft (forest, row, col);
        const uint64_t scoreToRight = GetNumberOfVisibleTreesToTheRight (forest, row, col);
        const uint64_t scoreToTop = GetNumberOfVisibleTreesToTheTop (forest, row, col);
        const uint64_t scoreToBottom = GetNumberOfVisibleTreesToTheBottom (forest, row, col);
        return scoreToLeft * scoreToRight * scoreToTop * scoreToBottom;
    }


    uint64_t GetHighestScenicScoreInForest (const ForestMatrix& forest)
    {
        if (forest.empty ())
            return 0;

        uint64_t maxScore = 0;
        const size_t width = forest[0].size ();
        for (size_t row = 0; row < forest.size (); ++row) {
            for (size_t col = 0; col < width; ++col) {
                if (IsTreeOnEdge (forest, row, col)) {
                    continue;
                }
                const uint64_t scenicScore = GetScenicScoreForTree (forest, row, col);
                if (scenicScore > maxScore)
                    maxScore = scenicScore;
            }
        }
        return maxScore;
    }


    void RunOptimizedProceduralSolution (const std::string& fileName)
    {
        const ForestMatrix forest = ReadFile (fileName);
        GetNumberOfVisibleTreesInForest (forest);
        GetHighestScenicScoreInForest (forest);
    }

}