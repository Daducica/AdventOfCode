#include "ProceduralSolution.hpp"

#include <cassert>
#include "Utilities.hpp"

namespace ProceduralSolution
{
    std::vector<std::vector<short>> ReadFile (const std::string& fileName)
    {
        return Utilities::ReadForest (fileName);
    }


    static bool IsTreeOnEdge (const std::vector<std::vector<short>>& forest, int i, int j)
    {
        if (forest.empty ())
            return false;

        return i == 0 || j == 0 || i == forest.size () - 1 || j == forest[0].size () - 1;
    }


    static bool IsTreeVisibleFromLeft (const std::vector<std::vector<short>>& forest, unsigned int i, unsigned int j)
    {
        const int treeHeight = forest[i][j];
        for (unsigned int k = 0; k < i; k++) {
            if (forest[k][j] >= treeHeight) {
                return false;
            }
        }
        return true;
    }

    static bool IsTreeVisibleFromRight (const std::vector<std::vector<short>>& forest, unsigned int i, unsigned int j)
    {
        const int treeHeight = forest[i][j];
        for (unsigned int k = forest.size () - 1; k > i; k--) {
            if (forest[k][j] >= treeHeight) {
                return false;
            }
        }
        return true;
    }


    static bool IsTreeVisibleFromTop (const std::vector<std::vector<short>>& forest, unsigned int i, unsigned int j)
    {
        const int treeHeight = forest[i][j];
        for (unsigned int k = 0; k < j; k++) {
            if (forest[i][k] >= treeHeight) {
                return false;
            }
        }
        return true;
    }


    static bool IsTreeVisibleFromBottom (const std::vector<std::vector<short>>& forest, unsigned int i, unsigned int j)
    {
        const int treeHeight = forest[i][j];
        for (unsigned int k = forest[0].size () - 1; k > j; k--) {
            if (forest[i][k] >= treeHeight) {
                return false;
            }
        }
        return true;
    }


    static bool IsTreeVisible (const std::vector<std::vector<short>>& forest, unsigned int i, unsigned int j)
    {
        if (IsTreeOnEdge (forest, i, j))
            return true;

        if (IsTreeVisibleFromLeft (forest, i, j))
            return true;

        if (IsTreeVisibleFromRight (forest, i, j))
            return true;

        if (IsTreeVisibleFromTop (forest, i, j))
            return true;

        if (IsTreeVisibleFromBottom (forest, i, j))
            return true;

        return false;
    }


    static int  GetEdgeTreeCount (const std::vector<std::vector<short>>& forest)
    {
        const unsigned int width = forest[0].size ();
        const unsigned int height = forest.size ();
        return 2 * width + 2 * height * 2 - 4;
    }


    int GetNumberOfVisibleTreesInForest (const std::vector<std::vector<short>>& forest)
    {
        if (forest.empty ())
            return 0;

        int visibleTreeCount = 0;
        const unsigned int width = forest[0].size ();
        for (unsigned int i = 0; i < forest.size (); i++) {
            for (unsigned int j = 0; j < width; j++) {
                if (IsTreeVisible (forest, i, j))
                    visibleTreeCount++;
            }
        }
        return visibleTreeCount;
    }


    static int GetNumberOfVisibleTreesToTheLeft (const std::vector<std::vector<short>>& forest, unsigned int i, unsigned int j)
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


    static int GetNumberOfVisibleTreesToTheRight (const std::vector<std::vector<short>>& forest, unsigned int i, unsigned int j)
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


    static int GetNumberOfVisibleTreesToTheTop (const std::vector<std::vector<short>>& forest, unsigned int i, unsigned int j)
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


    static int GetNumberOfVisibleTreesToTheBottom (const std::vector<std::vector<short>>& forest, unsigned int i, unsigned int j)
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


    static int GetScenicScoreForTree (const std::vector<std::vector<short>>& forest, unsigned int i, unsigned int j)
    {
        const int scoreToLeft = GetNumberOfVisibleTreesToTheLeft (forest, i, j);
        const int scoreToRight = GetNumberOfVisibleTreesToTheRight (forest, i, j);
        const int scoreToTop = GetNumberOfVisibleTreesToTheTop (forest, i, j);
        const int scoreToBottom = GetNumberOfVisibleTreesToTheBottom (forest, i, j);
        return scoreToLeft * scoreToRight * scoreToTop * scoreToBottom;
    }


    int GetHighestScenicScoreInForest (const std::vector<std::vector<short>>& forest)
    {
        if (forest.empty ())
            return 0;

        int maxScore = 0;
        const unsigned int width = forest[0].size ();
        for (unsigned int i = 0; i < forest.size (); i++) {
            for (unsigned int j = 0; j < width; j++) {
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


    void RunProceduralSolution (const std::string& fileName)
    {
        const std::vector<std::vector<short>> forest = ReadFile (fileName);
        ProceduralSolution::GetNumberOfVisibleTreesInForest (forest);
        ProceduralSolution::GetHighestScenicScoreInForest (forest);
    }

}