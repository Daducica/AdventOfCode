#include "TestRunner.hpp"

#include <functional>
#include "OOPSolution.hpp"
#include "OriginalSolution.hpp"
#include "ProceduralSolution.hpp"
#include "Utilities.hpp"

namespace Test
{
	typedef std::function<void (const std::string&)> TestFunction;

	static void RunTest (const std::string& fileName, unsigned int numberOfTestRuns,
						 const std::string& message, const TestFunction& function)
	{
		Utilities::Timer timer;
		timer.StartTimer ();

		for (unsigned int i = 0; i < numberOfTestRuns; ++i)
			function (fileName);

		timer.StopTimer (message);
	}



	void RunTests (const std::string& fileName, unsigned int numberOfTestRuns)
	{
		RunTest (fileName, numberOfTestRuns, "The original solution finished in\t",
				 &OriginalSolution::RunOriginalSolution);
		RunTest (fileName, numberOfTestRuns, "The original solution finished in\t",
				 &OriginalSolution::RunOriginalSolution);
		RunTest (fileName, numberOfTestRuns, "The original solution finished in\t",
				 &OriginalSolution::RunOriginalSolution);
		RunTest (fileName, numberOfTestRuns, "The original solution finished in\t",
				 &OriginalSolution::RunOriginalSolution);
		RunTest (fileName, numberOfTestRuns, "The original solution finished in\t",
				 &OriginalSolution::RunOriginalSolution);

		RunTest (fileName, numberOfTestRuns, "The original solution finished in\t",
				 &OriginalSolution::RunOriginalSolution);
		RunTest (fileName, numberOfTestRuns, "The procedural solution finished in\t",
				 &ProceduralSolution::RunProceduralSolution);
		RunTest (fileName, numberOfTestRuns, "The OOP solution finished in\t\t",
				 &OOPSolution::RunOOPSolution);
	}
}
