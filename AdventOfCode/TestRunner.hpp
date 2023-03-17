#ifndef TEST_RUNNER
#define TEST_RUNNER

#include <string>

namespace Test
{
	struct TestConfig {
		const std::string fileName;
		const unsigned int numberOfTestRuns;
		bool shouldRunVisibilityCountTest;
		bool shouldRunHighestScenicScoreTest;

		TestConfig () = delete;
	};

	void RunTests (const TestConfig& config);
}

#endif