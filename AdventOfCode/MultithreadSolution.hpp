#ifndef MULTITHREAD_SOLUTION
#define MULTITHREAD_SOLUTION

#include <string>
#include <vector>

namespace MultithreadSolution
{
	std::vector<std::vector<short>> ReadFile (const std::string& fileName);
	int GetNumberOfVisibleTreesInForest (const std::vector<std::vector<short>>& forest);
	int GetHighestScenicScoreInForest (const std::vector<std::vector<short>>& forest);

	void RunMultithreadSolution (const std::string& fileName);
}



#endif