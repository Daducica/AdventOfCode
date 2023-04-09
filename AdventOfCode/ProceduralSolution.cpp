#include "ProceduralSolution.hpp"

#include <cassert>
#include "Utilities.hpp"

namespace ProceduralSolution
{
    std::vector<std::vector<short>> ReadFile (const std::string& fileName)
    {
        return Utilities::ReadForest (fileName);
    }


    static bool IsTreeOnEdge (const std::vector<std::vector<short>>& forest, size_t row, size_t col)
    {
        if (forest.empty ())
            return false;

        return row == 0 || col == 0 || row == forest.size () - 1 || col == forest[0].size () - 1;
    }


    static bool IsTreeVisibleFromTop (const std::vector<std::vector<short>>& forest, size_t row, size_t col)
    {
        const int treeHeight = forest[row][col];
        for (size_t index = 0; index < row; index++) {
            if (forest[index][col] >= treeHeight) {
                return false;
            }
        }
        return true;
    }

    static bool IsTreeVisibleFromBottom (const std::vector<std::vector<short>>& forest, size_t row, size_t col)
    {
        const int treeHeight = forest[row][col];
        for (size_t index = forest.size () - 1; index > row; index--) {
            if (forest[index][col] >= treeHeight) {
                return false;
            }
        }
        return true;
    }


    static bool IsTreeVisibleFromLeft (const std::vector<std::vector<short>>& forest, size_t row, size_t col)
    {
        const int treeHeight = forest[row][col];
        for (size_t index = 0; index < col; index++) {
            if (forest[row][index] >= treeHeight) {
                return false;
            }
        }
        return true;
    }


    static bool IsTreeVisibleFromRight (const std::vector<std::vector<short>>& forest, size_t row, size_t col)
    {
        const int treeHeight = forest[row][col];
        for (size_t index = forest[0].size () - 1; index > col; index--) {
            if (forest[row][index] >= treeHeight) {
                return false;
            }
        }
        return true;
    }


    static bool IsTreeVisible (const std::vector<std::vector<short>>& forest, size_t row, size_t col)
    {
        if (IsTreeOnEdge (forest, row, col))
            return true;

        if (IsTreeVisibleFromLeft (forest, row, col))
            return true;

        if (IsTreeVisibleFromRight (forest, row, col))
            return true;

        if (IsTreeVisibleFromTop (forest, row, col))
            return true;

        if (IsTreeVisibleFromBottom (forest, row, col))
            return true;

        return false;
    }


    uint64_t GetNumberOfVisibleTreesInForest (const std::vector<std::vector<short>>& forest)
    {
        if (forest.empty ())
            return 0;

        uint64_t visibleTreeCount = 0;
        const size_t width = forest[0].size ();
        for (size_t row = 0; row < forest.size (); row++) {
            for (size_t col = 0; col < width; col++) {
                if (IsTreeVisible (forest, row, col))
                    visibleTreeCount++;
            }
        }
        return visibleTreeCount;
    }


    static uint64_t GetNumberOfVisibleTreesToTheTop (const std::vector<std::vector<short>>& forest, size_t row, size_t col)
    {
        uint64_t treeCount = 0;
        const int treeHeight = forest[row][col];
        for (std::int32_t index = std::int32_t (row - 1); index >= 0; index--) {
            treeCount++;
            if (forest[index][col] >= treeHeight)
                break;
        }
        return treeCount;
    }


    static uint64_t GetNumberOfVisibleTreesToTheBottom (const std::vector<std::vector<short>>& forest, size_t row, size_t col)
    {
        uint64_t treeCount = 0;
        const int treeHeight = forest[row][col];
        for (size_t index = row + 1; index < forest.size (); index++) {
            treeCount++;
            if (forest[index][col] >= treeHeight)
                break;
        }
        return treeCount;
    }


    static uint64_t GetNumberOfVisibleTreesToTheLeft (const std::vector<std::vector<short>>& forest, size_t row, size_t col)
    {
        uint64_t treeCount = 0;
        const int treeHeight = forest[row][col];
        for (std::int32_t index = std::int32_t (col - 1); index >= 0; index--) {
            treeCount++;
            if (forest[row][index] >= treeHeight)
                break;
        }
        return treeCount;
    }


    static uint64_t GetNumberOfVisibleTreesToTheRight (const std::vector<std::vector<short>>& forest, size_t row, size_t col)
    {
        uint64_t treeCount = 0;
        const int treeHeight = forest[row][col];
        for (size_t index = col + 1; index < forest[0].size (); index++) {
            treeCount++;
            if (forest[row][index] >= treeHeight)
                break;
        }
        return treeCount;
    }


    static uint64_t GetScenicScoreForTree (const std::vector<std::vector<short>>& forest, size_t row, size_t col)
    {
        const uint64_t scoreToLeft = GetNumberOfVisibleTreesToTheLeft (forest, row, col);
        const uint64_t scoreToRight = GetNumberOfVisibleTreesToTheRight (forest, row, col);
        const uint64_t scoreToTop = GetNumberOfVisibleTreesToTheTop (forest, row, col);
        const uint64_t scoreToBottom = GetNumberOfVisibleTreesToTheBottom (forest, row, col);
        return scoreToLeft * scoreToRight * scoreToTop * scoreToBottom;
    }


    uint64_t GetHighestScenicScoreInForest (const std::vector<std::vector<short>>& forest)
    {
        if (forest.empty ())
            return 0;

        uint64_t maxScore = 0;
        const size_t width = forest[0].size ();
        for (size_t row = 0; row < forest.size (); row++) {
            for (size_t col = 0; col < width; col++) {
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


    void RunProceduralSolution (const std::string& fileName)
    {
        const std::vector<std::vector<short>> forest = ReadFile (fileName);
        ProceduralSolution::GetNumberOfVisibleTreesInForest (forest);
        ProceduralSolution::GetHighestScenicScoreInForest (forest);
    }

}