#include "TestRunner.hpp"

#include <functional>
#include "OOPSolution.hpp"
#include "OriginalSolution.hpp"
#include "ProceduralSolution.hpp"
#include "Utilities.hpp"

namespace Test
{
	typedef std::function<void (const std::string&, bool, bool)> TestFunction;

	static void RunTest (const std::string& message, const TestFunction& function, const TestConfig& config)
	{
		Utilities::Timer timer;
		timer.StartTimer ();

		for (unsigned int i = 0; i < config.numberOfTestRuns; ++i)
			function (config.fileName, config.shouldRunVisibilityCountTest, config.shouldRunHighestScenicScoreTest);

		timer.StopTimer (message);
	}



	void RunTests (const TestConfig& config)
	{
		RunTest ("The original solution finished in\t",
				 &OriginalSolution::RunOriginalSolution, config);
		RunTest ("The original solution finished in\t",
				 &OriginalSolution::RunOriginalSolution, config);
		RunTest ("The original solution finished in\t",
				 &OriginalSolution::RunOriginalSolution, config);
		RunTest ("The original solution finished in\t",
				 &OriginalSolution::RunOriginalSolution, config);
		RunTest ("The original solution finished in\t",
				 &OriginalSolution::RunOriginalSolution, config);

		RunTest ("The original solution finished in\t", &OriginalSolution::RunOriginalSolution, config);
		RunTest ("The procedural solution finished in\t", &ProceduralSolution::RunProceduralSolution, config);
		RunTest ("The OOP solution finished in\t\t", &OOPSolution::RunOOPSolution, config);
	}
}
