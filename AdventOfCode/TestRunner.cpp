#include "TestRunner.hpp"

#include <functional>
#include <iomanip>
#include <iostream>

#include "OOPSolution.hpp"
#include "OriginalSolution.hpp"
#include "ProceduralOptimizedSolution.hpp"
#include "ProceduralSolution.hpp"
#include "Utilities.hpp"

namespace Test
{
	typedef std::function<void (const std::string&)> TestFunction;

	static int RunTestAndMeasureAverageDuration (const TestFunction& function, const TestConfig& config)
	{
		Utilities::MilliSecTimer timer;
		timer.StartTimer ();

		for (unsigned int i = 0; i < config.numberOfTestRuns; ++i)
			function (config.fileName);

		return timer.StopTimer () / config.numberOfTestRuns;
	}


	struct TestItem
	{
		const TestFunction function;
		const std::string name;
		std::optional<int> result;

		TestItem (const TestFunction& function, const std::string& name) :
			function (function),
			name (name)
		{
		}
	};


	void PrintResults (int benchMark, const std::vector<TestItem>& results)
	{
		std::cout << std::fixed;
		std::cout << std::setprecision (2);

		for (const TestItem& testItem : results) {
			if (testItem.result.has_value ()) {
				const double relativeRunTime = (double)benchMark / testItem.result.value ();
				std::cout << testItem.name << "\t" << relativeRunTime << "x\n";
			}
		}
	}


	void RunTests (const TestConfig& config)
	{
		int benchMark = RunTestAndMeasureAverageDuration (&OriginalSolution::RunOriginalSolution, config);

		std::vector<TestItem> functionsToTest {
			{ &OriginalSolution::RunOriginalSolution, "Original"},
			{ &ProceduralSolution::RunProceduralSolution,  "Procedural"},
			{ &OptimizedProceduralSolution::RunOptimizedProceduralSolution, "Optimized"},
			{ &OOPSolution::RunOOPSolution,  "OOP\t"}
		};

		for (TestItem& testItem : functionsToTest) {
			testItem.result = RunTestAndMeasureAverageDuration (testItem.function, config);
		}

		std::cout << "Filename=" << config.fileName << "\n"
				  << "LoopCount=" << config.numberOfTestRuns << "\n"
				  << "Benchmark=" << benchMark << "ms\n"
				  << "---------------------------------------------\n";
		PrintResults (benchMark, functionsToTest);
	}
}
