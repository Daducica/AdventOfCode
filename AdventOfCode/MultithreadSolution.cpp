#include "MultithreadSolution.hpp"

#include <algorithm>
#include <execution>

#include "Utilities.hpp"

namespace MultithreadSolution
{
    typedef std::vector<std::vector<short>> Forest;
    typedef std::vector<std::vector<bool>> VisibilityCache;

    std::vector<std::vector<short>> ReadFile (const std::string& fileName)
    {
        return Utilities::ReadForest (fileName);
    }

    static bool IsTreeOnEdge (const Forest& forest, int i, int j)
    {
        if (forest.empty ())
            return false;

        return i == 0 || j == 0 || i == forest.size () - 1 || j == forest[0].size () - 1;
    }

    static int CheckVisibilityFromLeft (const Forest& forest, VisibilityCache& visibility)
    {
        const unsigned int width = forest[0].size ();
        const unsigned int height = forest.size ();

        std::vector<int> rowResults (height);

        auto process = [&](const int i) {
            int maxHeightInRow = -1;
            const std::vector<short>& row = forest[i];
            std::vector<bool>& visibilityRow = visibility[i];
            for (unsigned int j = 0; j < width; ++j) {
                const short treeHeight = row[j];
                if (treeHeight > maxHeightInRow) {
                    maxHeightInRow = treeHeight;
                    if (!visibilityRow[j]) {
                        rowResults[i]++;
                        visibilityRow[j] = true;
                    }
                }
            }
        };

        std::vector<int> range (height);
        int index = 0;
        for (int& i : range) {
            i = index++;
        }

        std::for_each (
            std::execution::par,
            range.begin (),
            range.end (),
            process);

        return std::accumulate (rowResults.begin (), rowResults.end (), 0);
    }


    static int CheckVisibilityFromRight (const Forest& forest, VisibilityCache& visibility)
    {
        const unsigned int width = forest[0].size ();
        const unsigned int height = forest.size ();

        std::vector<int> rowResults (height);

        auto process = [&](const int i) {
            int maxHeightInRow = -1;
            const std::vector<short>& row = forest[i];
            std::vector<bool>& visibilityRow = visibility[i];
            for (int j = width - 1; j >= 0; --j) {
                const short treeHeight = row[j];
                if (treeHeight > maxHeightInRow) {
                    maxHeightInRow = treeHeight;
                    if (!visibilityRow[j]) {
                        rowResults[i]++;
                        visibilityRow[j] = true;
                    }
                }
            }
        };

        std::vector<int> range (height);
        int index = 0;
        for (int& i : range) {
            i = index++;
        }

        std::for_each (
            std::execution::par,
            range.begin (),
            range.end (),
            process);

        return std::accumulate (rowResults.begin (), rowResults.end (), 0);
    }


    static int CheckVisibilityFromTop (const Forest& forest, VisibilityCache& visibility)
    {
        const unsigned int width = forest[0].size ();
        const unsigned int height = forest.size ();

        std::vector<int> rowResults (width);

        auto process = [&](const int j) {
            int maxHeightInColumn = -1;
            for (unsigned int i = 0; i < height; ++i) {
                const short treeHeight = forest[i][j];
                if (treeHeight > maxHeightInColumn) {
                    maxHeightInColumn = treeHeight;
                    if (!visibility[i][j]) {
                        rowResults[j]++;
                        visibility[i][j] = true;
                    }
                }
            }
        };

        std::vector<int> range (width);
        int index = 0;
        for (int& i : range) {
            i = index++;
        }

        std::for_each (
            std::execution::par,
            range.begin (),
            range.end (),
            process);

        return std::accumulate (rowResults.begin (), rowResults.end (), 0);
    }


    static int CheckVisibilityFromBottom (const Forest& forest, VisibilityCache& visibility)
    {
        const unsigned int width = forest[0].size ();
        const unsigned int height = forest.size ();

        std::vector<int> rowResults (width);

        auto process = [&](const int j) {
            int maxHeightInColumn = -1;
            for (int i = height - 1; i >= 0; --i) {
                const short treeHeight = forest[i][j];
                if (treeHeight > maxHeightInColumn) {
                    maxHeightInColumn = treeHeight;
                    if (!visibility[i][j]) {
                        rowResults[j]++;
                        visibility[i][j] = true;
                    }
                }
            }
        };

        std::vector<int> range (width);
        int index = 0;
        for (int& i : range) {
            i = index++;
        }

        std::for_each (
            std::execution::par,
            range.begin (),
            range.end (),
            process);

        return std::accumulate (rowResults.begin (), rowResults.end (), 0);
    }


    int GetNumberOfVisibleTreesInForest (const Forest& forest)
    {
        const unsigned int height = forest.size ();
        if (height == 0)
            return 0;

        const unsigned int width = forest[0].size ();

        std::vector<bool> row (width, false);
        VisibilityCache visibility (height, row);

        int visibleTreeCount = CheckVisibilityFromLeft (forest, visibility);
        visibleTreeCount += CheckVisibilityFromRight (forest, visibility);
        visibleTreeCount += CheckVisibilityFromTop (forest, visibility);
        visibleTreeCount += CheckVisibilityFromBottom (forest, visibility);

        return visibleTreeCount;
    }


    static int GetNumberOfVisibleTreesToTheLeft (const Forest& forest, unsigned int i, unsigned int j)
    {
        int treeCount = 0;
        const int treeHeight = forest[i][j];
        for (int k = i - 1; k >= 0; k--) {
            treeCount++;
            if (forest[k][j] >= treeHeight)
                break;
        }
        return treeCount;
    }


    static int GetNumberOfVisibleTreesToTheRight (const Forest& forest, unsigned int i, unsigned int j)
    {
        int treeCount = 0;
        const int treeHeight = forest[i][j];
        for (unsigned int k = i + 1; k < forest.size (); k++) {
            treeCount++;
            if (forest[k][j] >= treeHeight)
                break;
        }
        return treeCount;
    }


    static int GetNumberOfVisibleTreesToTheTop (const Forest& forest, unsigned int i, unsigned int j)
    {
        int treeCount = 0;
        const int treeHeight = forest[i][j];
        for (int k = j - 1; k >= 0; k--) {
            treeCount++;
            if (forest[i][k] >= treeHeight)
                break;
        }
        return treeCount;
    }


    static int GetNumberOfVisibleTreesToTheBottom (const Forest& forest, unsigned int i, unsigned int j)
    {
        int treeCount = 0;
        const int treeHeight = forest[i][j];
        for (unsigned int k = j + 1; k < forest[0].size (); k++) {
            treeCount++;
            if (forest[i][k] >= treeHeight)
                break;
        }
        return treeCount;
    }


    static int GetScenicScoreForTree (const Forest& forest, unsigned int i, unsigned int j)
    {
        const int scoreToLeft = GetNumberOfVisibleTreesToTheLeft (forest, i, j);
        const int scoreToRight = GetNumberOfVisibleTreesToTheRight (forest, i, j);
        const int scoreToTop = GetNumberOfVisibleTreesToTheTop (forest, i, j);
        const int scoreToBottom = GetNumberOfVisibleTreesToTheBottom (forest, i, j);
        return scoreToLeft * scoreToRight * scoreToTop * scoreToBottom;
    }


    int GetHighestScenicScoreInForest (const Forest& forest)
    {
        const unsigned int height = forest.size ();
        if (height == 0)
            return 0;

        int maxScore = 0;
        const unsigned int width = forest[0].size ();
        for (unsigned int i = 0; i < height; ++i) {
            for (unsigned int j = 0; j < width; ++j) {
                if (IsTreeOnEdge (forest, i, j)) {
                    continue;
                }
                const int scenicScore = GetScenicScoreForTree (forest, i, j);
                if (scenicScore > maxScore)
                    maxScore = scenicScore;
            }
        }
        return maxScore;
    }


    void RunMultithreadSolution (const std::string& fileName)
    {
        const Forest forest = ReadFile (fileName);
        GetNumberOfVisibleTreesInForest (forest);
        GetHighestScenicScoreInForest (forest);
    }

}