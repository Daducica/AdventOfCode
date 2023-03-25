#ifndef TEST_RUNNER
#define TEST_RUNNER

#include <string>

namespace Test
{
	struct TestConfig {
		const std::string fileName;
		const unsigned int numberOfTestRuns;
		const bool shouldRunFullTest;
		const bool shouldMeasureFileRead;
		const bool shouldRunVisibilityCountTest;
		const bool shouldRunHighestScenicScoreTest;

		TestConfig () = delete;
	};

	void RunTests (const TestConfig& config);
}

#endif