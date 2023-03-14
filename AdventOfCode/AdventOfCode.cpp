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


int GetNumberOfVisibleTreesInForest (const std::vector<std::vector<int>>& forest)
{
    int visibleTreeCount = 0;
    for (unsigned int i = 0; i < forest.size (); i++) {
        for (unsigned int j = 0; j < forest[0].size (); j++) {
            if (i == 0 || j == 0 || i == forest.size () - 1 || j == forest[0].size () - 1) {
                visibleTreeCount++;
                continue;
            }
            bool v = true;
            for (unsigned int k = 0; k < i; k++) {
                if (forest[k][j] >= forest[i][j]) {
                    v = false;
                    break;
                }
            }
            if (v) {
                visibleTreeCount++;
                continue;
            }
            v = true;
            for (unsigned int k = forest.size () - 1; k > i; k--) {
                if (forest[k][j] >= forest[i][j]) {
                    v = false;
                    break;
                }
            }
            if (v) {
                visibleTreeCount++;
                continue;
            }
            v = true;
            for (unsigned int k = 0; k < j; k++) {
                if (forest[i][k] >= forest[i][j]) {
                    v = false;
                    break;
                }
            }
            if (v) {
                visibleTreeCount++;
                continue;
            }
            v = true;
            for (unsigned int k = forest[0].size () - 1; k > j; k--) {
                if (forest[i][k] >= forest[i][j]) {
                    v = false;
                    break;
                }
            }
            if (v)
                visibleTreeCount++;
        }
    }
    return visibleTreeCount;
}


int GetHighestScenicScoreInForest (const std::vector<std::vector<int>>& forest)
{
    int maxScore = 0;
    for (unsigned int i = 0; i < forest.size (); i++) {
        for (unsigned int j = 0; j < forest[0].size (); j++) {
            if (i == 0 || j == 0 || i == forest.size () - 1 || j == forest[0].size () - 1) {
                continue;
            }
            int lss1 = 0;
            for (int k = i - 1; k >= 0; k--) {
                lss1++;
                if (forest[k][j] >= forest[i][j])
                    break;
            }
            int lss2 = 0;
            for (unsigned int k = i + 1; k < forest.size (); k++) {
                lss2++;
                if (forest[k][j] >= forest[i][j])
                    break;
            }
            int lss3 = 0;
            for (int k = j - 1; k >= 0; k--) {
                lss3++;
                if (forest[i][k] >= forest[i][j])
                    break;
            }
            int lss4 = 0;
            for (unsigned int k = j + 1; k < forest[0].size (); k++) {
                lss4++;
                if (forest[i][k] >= forest[i][j])
                    break;
            }
            int ss = lss1 * lss2 * lss3 * lss4;
            if (ss > maxScore)
                maxScore = ss;
        }
    }
    return maxScore;
}


int main (int argc, char** argv)
{
    const auto startTime = std::chrono::steady_clock::now ();

    const std::vector<std::vector<int>> m = ReadForest (FileName);

    const int vt = GetNumberOfVisibleTreesInForest (m);
    std::cout << vt << std::endl;
    assert (vt == 1792);

    const int mss = GetHighestScenicScoreInForest (m);
    std::cout << mss << std::endl;
    assert (mss == 334880);

    const auto endTime = std::chrono::steady_clock::now ();
    const auto runTime = std::chrono::duration_cast<std::chrono::milliseconds>(endTime - startTime).count (); 
    std::cout << runTime << std::endl;
    assert (runTime < 200);

    return 0;
}