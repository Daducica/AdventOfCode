#ifndef TEST_RUNNER
#define TEST_RUNNER

#include <string>

namespace Test
{
	struct TestConfig {
		const std::string fileName;
		const size_t numberOfTestRuns;
		const bool shouldRunFullTest;
		const bool shouldMeasureFileRead;
		const bool shouldRunVisibilityCountTest;
		const bool shouldRunHighestScenicScoreTest;

		TestConfig (const std::string& fileName, size_t numberOfTestRuns,
					bool shouldRunFullTest, bool shouldMeasureFileRead,
					bool shouldRunVisibilityCountTest, bool shouldRunHighestScenicScoreTest);
	};

	void RunTests (const TestConfig& config);
}

#endif