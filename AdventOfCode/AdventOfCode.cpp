#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cassert>
#include <chrono>

const std::string FileName = "day8.txt";

std::vector<std::vector<int>> ReadForest (const std::string& fileName)
{
    std::ifstream fileStream (fileName);
    std::string line;
    std::vector<std::vector<int>> forest;
    while (std::getline (fileStream, line)) {
        std::vector<int> row;
        for (unsigned int i = 0; i < line.size (); i++) {
            row.push_back (line[i] - '0');
        }
        forest.push_back (row);
    }
    return forest;
}


bool IsTreeOnEdge (const std::vector<std::vector<int>>& forest, int i, int j)
{
    return i == 0 || j == 0 || i == forest.size () - 1 || j == forest[0].size () - 1;
}


bool IsTreeVisibleFromLeft (const std::vector<std::vector<int>>& forest, unsigned int i, unsigned int j)
{
    const int treeHeight = forest[i][j];
    for (unsigned int k = 0; k < i; k++) {
        if (forest[k][j] >= treeHeight) {
            return false;
        }
    }
    return true;
}

bool IsTreeVisibleFromRight (const std::vector<std::vector<int>>& forest, unsigned int i, unsigned int j)
{
    const int treeHeight = forest[i][j];
    for (unsigned int k = forest.size () - 1; k > i; k--) {
        if (forest[k][j] >= treeHeight) {
            return false;
        }
    }
    return true;
}


bool IsTreeVisibleFromTop (const std::vector<std::vector<int>>& forest, unsigned int i, unsigned int j)
{
    const int treeHeight = forest[i][j];
    for (unsigned int k = 0; k < j; k++) {
        if (forest[i][k] >= treeHeight) {
            return false;
        }
    }
    return true;
}


bool IsTreeVisibleFromBottom (const std::vector<std::vector<int>>& forest, unsigned int i, unsigned int j)
{
    const int treeHeight = forest[i][j];
    for (unsigned int k = forest[0].size () - 1; k > j; k--) {
        if (forest[i][k] >= treeHeight) {
            return false;
        }
    }
    return true;
}


bool IsTreeVisible (const std::vector<std::vector<int>>& forest, unsigned int i, unsigned int j)
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


int GetNumberOfVisibleTreesInForest (const std::vector<std::vector<int>>& forest)
{
    int visibleTreeCount = 0;
    for (unsigned int i = 0; i < forest.size (); i++) {
        for (unsigned int j = 0; j < forest[0].size (); j++) {
            if (IsTreeVisible (forest, i, j))
                visibleTreeCount++;
        }
    }
    return visibleTreeCount;
}


int GetNumberOfVisibleTreesToTheLeft (const std::vector<std::vector<int>>& forest, unsigned int i, unsigned int j)
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


int GetNumberOfVisibleTreesToTheRight (const std::vector<std::vector<int>>& forest, unsigned int i, unsigned int j)
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


int GetNumberOfVisibleTreesToTheTop (const std::vector<std::vector<int>>& forest, unsigned int i, unsigned int j)
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


int GetNumberOfVisibleTreesToTheBottom (const std::vector<std::vector<int>>& forest, unsigned int i, unsigned int j)
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


int GetScenicScoreForTree (const std::vector<std::vector<int>>& forest, unsigned int i, unsigned int j)
{
    const int scoreToLeft = GetNumberOfVisibleTreesToTheLeft (forest, i, j);
    const int scoreToRight = GetNumberOfVisibleTreesToTheRight (forest, i, j);
    const int scoreToTop = GetNumberOfVisibleTreesToTheTop (forest, i, j);
    const int scoreToBottom = GetNumberOfVisibleTreesToTheBottom (forest, i, j);
    return scoreToLeft * scoreToRight * scoreToTop * scoreToBottom;
}


int GetHighestScenicScoreInForest (const std::vector<std::vector<int>>& forest)
{
    int maxScore = 0;
    for (unsigned int i = 0; i < forest.size (); i++) {
        for (unsigned int j = 0; j < forest[0].size (); j++) {
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


int main (int)
{
    const auto startTime = std::chrono::steady_clock::now ();

    const std::vector<std::vector<int>> forest = ReadForest (FileName);

    const int numberOfVisibleTrees = GetNumberOfVisibleTreesInForest (forest);
    std::cout << numberOfVisibleTrees << std::endl;
    assert (numberOfVisibleTrees == 1792);

    const int highestScenicScore = GetHighestScenicScoreInForest (forest);
    std::cout << highestScenicScore << std::endl;
    assert (highestScenicScore == 334880);

    const auto endTime = std::chrono::steady_clock::now ();
    const auto runTime = std::chrono::duration_cast<std::chrono::milliseconds>(endTime - startTime).count (); 
    std::cout << runTime << std::endl;
    assert (runTime < 200);

    return 0;
}