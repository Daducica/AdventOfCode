#include "TestRunner.hpp"

#include <cassert>
#include <functional>
#include <iomanip>
#include <iostream>

#include "GPUSolution.hpp"
#include "MultithreadSolution.hpp"
#include "OOPSolution.hpp"
#include "OriginalSolution.hpp"
#include "ProceduralOptimizedSolution.hpp"
#include "ProceduralSolution.hpp"
#include "Utilities.hpp"

namespace Test
{
	TestConfig::TestConfig (const std::string& fileName, size_t numberOfTestRuns,
				bool shouldRunFullTest, bool shouldMeasureFileRead,
				bool shouldRunVisibilityCountTest, bool shouldRunHighestScenicScoreTest) :
		fileName (fileName),
		numberOfTestRuns (numberOfTestRuns),
		shouldRunFullTest (shouldRunFullTest),
		shouldMeasureFileRead (shouldMeasureFileRead),
		shouldRunVisibilityCountTest (shouldRunVisibilityCountTest),
		shouldRunHighestScenicScoreTest (shouldRunHighestScenicScoreTest)
	{ }


	class TestSolution
	{
		struct TaskResult
		{
			double timeResult;
			uint64_t calculationResult;
		};
		std::optional<double> fullResult;
		std::optional<TaskResult> readResult;
		std::optional<TaskResult> visibilityCountResult;
		std::optional<TaskResult> scenicScoreResult;

		virtual std::string GetTestName () const = 0;
		virtual void RunFullSolution () const = 0;
		virtual size_t RunReadTest () const = 0;
		virtual uint64_t RunVisibilityCountTest () const = 0;
		virtual uint64_t RunScenicScoreTest () const = 0;
		void PrintTimeResultForTask (double taskResult, double benchMark) const;
		void PrintResultForTask (const TestSolution::TaskResult& taskResult, const TestSolution::TaskResult& benchMark) const;
	public:
		void MeasureFullSolutionTest (size_t numberOfTestRuns);
		void MeasureReadTest (size_t numberOfTestRuns);
		void MeasureVisibilityCountTest (size_t numberOfTestRuns);
		void MeasureScenicScoreTest (size_t numberOfTestRuns);

		virtual ~TestSolution ();
		void PrintResults (const TestSolution& benchMark) const;
	};


	void TestSolution::MeasureFullSolutionTest (size_t numberOfTestRuns)
	{
		Utilities::MicroSecTimer timer;
		timer.StartTimer ();

		for (size_t i = 0; i < numberOfTestRuns; ++i)
			RunFullSolution ();

		fullResult = (double)timer.StopTimer () / numberOfTestRuns;
	}


	void TestSolution::MeasureReadTest (size_t numberOfTestRuns)
	{
		Utilities::MicroSecTimer timer;
		timer.StartTimer ();

		uint64_t calculationResult = 0;
		for (size_t i = 0; i < numberOfTestRuns; ++i)
			calculationResult = RunReadTest ();

		readResult = TaskResult { (double)timer.StopTimer () / numberOfTestRuns, calculationResult };
	}


	void TestSolution::MeasureVisibilityCountTest (size_t numberOfTestRuns)
	{
		Utilities::MicroSecTimer timer;
		timer.StartTimer ();

		uint64_t calculationResult = 0;
		for (size_t i = 0; i < numberOfTestRuns; ++i)
			calculationResult = RunVisibilityCountTest ();

		visibilityCountResult = TaskResult { (double)timer.StopTimer () / numberOfTestRuns, calculationResult };
	}


	void TestSolution::MeasureScenicScoreTest (size_t numberOfTestRuns)
	{
		Utilities::MicroSecTimer timer;
		timer.StartTimer ();

		uint64_t calculationResult = 0;
		for (size_t i = 0; i < numberOfTestRuns; ++i)
			calculationResult = RunScenicScoreTest ();

		scenicScoreResult = TaskResult { (double)timer.StopTimer () / (double)numberOfTestRuns, calculationResult };
	}


	TestSolution::~TestSolution () = default;


	void TestSolution::PrintTimeResultForTask (double taskResult, double benchMark) const
	{
		if (benchMark == 0) {
			std::cout << "bm=0\t";
			return;
		}

		const double relativeRunTime = (double)taskResult / benchMark;
		std::cout << relativeRunTime << "x\t";
	}


	void TestSolution::PrintResultForTask (const TestSolution::TaskResult& taskResult, const TestSolution::TaskResult& benchMark) const
	{
		if (taskResult.calculationResult != benchMark.calculationResult) {
			std::cout << "failed\t";
			return;
		}

		PrintTimeResultForTask (benchMark.timeResult, taskResult.timeResult);
	}


	void TestSolution::PrintResults (const TestSolution& benchMark) const
	{
		std::cout << GetTestName () << "\t";
		if (fullResult.has_value () && benchMark.fullResult.has_value ()) {
			PrintTimeResultForTask (benchMark.fullResult.value (), fullResult.value ());
		}
		if (readResult.has_value () && benchMark.readResult.has_value ()) {
			PrintResultForTask (readResult.value (), benchMark.readResult.value ());
		}
		if (visibilityCountResult.has_value () && benchMark.visibilityCountResult.has_value ()) {
			PrintResultForTask (visibilityCountResult.value (), benchMark.visibilityCountResult.value ());
		}
		if (scenicScoreResult.has_value () && benchMark.scenicScoreResult.has_value ()) {
			PrintResultForTask (scenicScoreResult.value (), benchMark.scenicScoreResult.value ());
		}
		std::cout << std::endl;
	}


	class TestOriginalSolution : public TestSolution
	{
		const std::string testName = "Original";
		const std::string fileName;
		std::vector<std::vector<int>> testData;
	public:
		TestOriginalSolution (const std::string& fileName);
		virtual std::string GetTestName () const override;
		virtual void RunFullSolution () const override;
		virtual size_t RunReadTest () const override;
		virtual uint64_t RunVisibilityCountTest () const override;
		virtual uint64_t RunScenicScoreTest () const override;
	};


	TestOriginalSolution::TestOriginalSolution (const std::string& fileName) :
		fileName (fileName),
		testData (OriginalSolution::ReadFile (fileName))
	{
	}


	std::string TestOriginalSolution::GetTestName () const
	{
		return testName;
	}


	void TestOriginalSolution::RunFullSolution () const
	{
		OriginalSolution::RunOriginalSolution (fileName);
	}


	size_t TestOriginalSolution::RunReadTest () const
	{
		std::vector<std::vector<int>> result = OriginalSolution::ReadFile (fileName);
		if (result.empty ())
			return 0;
		return result.size () * result[0].size ();
	}


	uint64_t TestOriginalSolution::RunVisibilityCountTest () const
	{
		return OriginalSolution::CalculateVisibilityCount (testData);
	}

	
	uint64_t TestOriginalSolution::RunScenicScoreTest () const
	{
		return OriginalSolution::CalculateHighestScenicScore (testData);
	}


	class TestProceduralSolution : public TestSolution
	{
		const std::string testName = "Procedural";
		const std::string fileName;
		std::vector<std::vector<short>> testData;
	public:
		TestProceduralSolution (const std::string& fileName);
		virtual std::string GetTestName () const override;
		virtual void RunFullSolution () const override;
		virtual size_t RunReadTest () const override;
		virtual uint64_t RunVisibilityCountTest () const override;
		virtual uint64_t RunScenicScoreTest () const override;
	};


	TestProceduralSolution::TestProceduralSolution (const std::string& fileName) :
		fileName (fileName),
		testData (ProceduralSolution::ReadFile (fileName))
	{
	}


	std::string TestProceduralSolution::GetTestName () const
	{
		return testName;
	}


	void TestProceduralSolution::RunFullSolution () const
	{
		ProceduralSolution::RunProceduralSolution (fileName);
	}


	size_t TestProceduralSolution::RunReadTest () const
	{
		std::vector<std::vector<short>> result = ProceduralSolution::ReadFile (fileName);
		if (result.empty ())
			return 0;
		return result.size () * result[0].size ();
	}


	uint64_t TestProceduralSolution::RunVisibilityCountTest () const
	{
		return ProceduralSolution::GetNumberOfVisibleTreesInForest (testData);
	}


	uint64_t TestProceduralSolution::RunScenicScoreTest () const
	{
		return ProceduralSolution::GetHighestScenicScoreInForest (testData);
	}


	class TestOptimizedSolution : public TestSolution
	{
		const std::string testName = "Optimized";
		const std::string fileName;
		std::vector<std::vector<short>> testData;
	public:
		TestOptimizedSolution (const std::string& fileName);
		virtual std::string GetTestName () const override;
		virtual void RunFullSolution () const override;
		virtual size_t RunReadTest () const override;
		virtual uint64_t RunVisibilityCountTest () const override;
		virtual uint64_t RunScenicScoreTest () const override;
	};


	TestOptimizedSolution::TestOptimizedSolution (const std::string& fileName) :
		fileName (fileName),
		testData (OptimizedProceduralSolution::ReadFile (fileName))
	{
	}


	std::string TestOptimizedSolution::GetTestName () const
	{
		return testName;
	}


	void TestOptimizedSolution::RunFullSolution () const
	{
		OptimizedProceduralSolution::RunOptimizedProceduralSolution (fileName);
	}


	size_t TestOptimizedSolution::RunReadTest () const
	{
		std::vector<std::vector<short>> result = OptimizedProceduralSolution::ReadFile (fileName);
		if (result.empty ())
			return 0;
		return result.size () * result[0].size ();
	}


	uint64_t TestOptimizedSolution::RunVisibilityCountTest () const
	{
		return OptimizedProceduralSolution::GetNumberOfVisibleTreesInForest (testData);
	}


	uint64_t TestOptimizedSolution::RunScenicScoreTest () const
	{
		return OptimizedProceduralSolution::GetHighestScenicScoreInForest (testData);
	}


	class TestOOPSolution : public TestSolution
	{
		const std::string testName = "OOP\t";
		const std::string fileName;
		OOPSolution::Forest testData;
	public:
		TestOOPSolution (const std::string& fileName);
		virtual std::string GetTestName () const override;
		virtual void RunFullSolution () const override;
		virtual size_t RunReadTest () const override;
		virtual uint64_t RunVisibilityCountTest () const override;
		virtual uint64_t RunScenicScoreTest () const override;
	};


	TestOOPSolution::TestOOPSolution (const std::string& fileName) :
		fileName (fileName),
		testData (OOPSolution::ReadFile (fileName))
	{
	}


	std::string TestOOPSolution::GetTestName () const
	{
		return testName;
	}


	void TestOOPSolution::RunFullSolution () const
	{
		OOPSolution::RunOOPSolution (fileName);
	}


	size_t TestOOPSolution::RunReadTest () const
	{
		OOPSolution::Forest result = OOPSolution::ReadFile (fileName);
		return result.GetWidth () * result.GetHeight ();
	}


	uint64_t TestOOPSolution::RunVisibilityCountTest () const
	{
		return OOPSolution::GetNumberOfVisibleTreesInForest (const_cast<OOPSolution::Forest&> (testData));
	}


	uint64_t TestOOPSolution::RunScenicScoreTest () const
	{
		return OOPSolution::GetHighestScenicScoreInForest (const_cast<OOPSolution::Forest&> (testData));
	}


	class TestMultithreadSolution : public TestSolution
	{
		const std::string testName = "Multithread";
		const std::string fileName;
		std::vector<std::vector<short>> testData;
	public:
		TestMultithreadSolution (const std::string& fileName);
		virtual std::string GetTestName () const override;
		virtual void RunFullSolution () const override;
		virtual size_t RunReadTest () const override;
		virtual uint64_t RunVisibilityCountTest () const override;
		virtual uint64_t RunScenicScoreTest () const override;
	};


	TestMultithreadSolution::TestMultithreadSolution (const std::string& fileName) :
		fileName (fileName),
		testData (MultithreadSolution::ReadFile (fileName))
	{
	}


	std::string TestMultithreadSolution::GetTestName () const
	{
		return testName;
	}


	void TestMultithreadSolution::RunFullSolution () const
	{
		MultithreadSolution::RunMultithreadSolution (fileName);
	}


	size_t TestMultithreadSolution::RunReadTest () const
	{
		std::vector<std::vector<short>> result = MultithreadSolution::ReadFile (fileName);
		if (result.empty ())
			return 0;
		return result.size () * result[0].size ();
	}


	uint64_t TestMultithreadSolution::RunVisibilityCountTest () const
	{
		return MultithreadSolution::GetNumberOfVisibleTreesInForest (testData);
	}


	uint64_t TestMultithreadSolution::RunScenicScoreTest () const
	{
		return MultithreadSolution::GetHighestScenicScoreInForest (testData);
	}


	class TestGPUSolution : public TestSolution
	{
		const std::string testName = "GPU\t";
		const std::string fileName;
		std::vector<std::vector<short>> testData;
	public:
		TestGPUSolution (const std::string& fileName);
		virtual std::string GetTestName () const override;
		virtual void RunFullSolution () const override;
		virtual size_t RunReadTest () const override;
		virtual uint64_t RunVisibilityCountTest () const override;
		virtual uint64_t RunScenicScoreTest () const override;
	};


	TestGPUSolution::TestGPUSolution (const std::string& fileName) :
		fileName (fileName),
		testData (GPUSolution::ReadFile (fileName))
	{
	}


	std::string TestGPUSolution::GetTestName () const
	{
		return testName;
	}


	void TestGPUSolution::RunFullSolution () const
	{
		GPUSolution::RunGPUSolution (fileName);
	}


	size_t TestGPUSolution::RunReadTest () const
	{
		std::vector<std::vector<short>> result = GPUSolution::ReadFile (fileName);
		if (result.empty ())
			return 0;
		return result.size () * result[0].size ();
	}


	uint64_t TestGPUSolution::RunVisibilityCountTest () const
	{
		return GPUSolution::GetNumberOfVisibleTreesInForest (testData);
	}


	uint64_t TestGPUSolution::RunScenicScoreTest () const
	{
		return GPUSolution::GetHighestScenicScoreInForest (testData);
	}


	static void RunFullTest (size_t numberOfTestRuns, std::vector<TestSolution*> testSolutions)
	{
		for (TestSolution* testSolution : testSolutions)
			testSolution->MeasureFullSolutionTest (numberOfTestRuns);
	}


	static void RunReadTest (size_t numberOfTestRuns, std::vector<TestSolution*> testSolutions)
	{
		for (TestSolution* testSolution : testSolutions)
			testSolution->MeasureReadTest (numberOfTestRuns);
	}


	static void RunVisibilityCountTest (size_t numberOfTestRuns, std::vector<TestSolution*> testSolutions)
	{
		for (TestSolution* testSolution : testSolutions)
			testSolution->MeasureVisibilityCountTest (numberOfTestRuns);
	}


	static void RunScenicScoreTest (size_t numberOfTestRuns, std::vector<TestSolution*> testSolutions)
	{
		for (TestSolution* testSolution : testSolutions)
			testSolution->MeasureScenicScoreTest (numberOfTestRuns);
	}


	void PrintResults (const TestConfig& config, const std::vector<TestSolution*>& testSolutions, size_t benchMarkIndex)
	{
		std::cout << std::fixed;
		std::cout << std::setprecision (2);

		std::string header = "\t\t";

		if (config.shouldRunFullTest)
			header.append ("Full\t");
		if (config.shouldMeasureFileRead)
			header.append ("Read\t");
		if (config.shouldRunVisibilityCountTest)
			header.append ("VisC\t");
		if (config.shouldRunHighestScenicScoreTest)
			header.append ("Scenic\t");

		std::cout << "Filename = " << config.fileName << "\n"
			<< "LoopCount = " << config.numberOfTestRuns << "\n"
			<< "If the result is incorrect, \"failed\" is written into the table instead of the speed result.\n\n"
			<< header << "\n"
			<< "---------------------------------------------\n";

		assert (testSolutions.size () >= benchMarkIndex);

		const TestSolution* benchMarkSolution = testSolutions[benchMarkIndex];

		assert (benchMarkSolution != nullptr);

		for (const TestSolution* testSolution : testSolutions) {
			testSolution->PrintResults (*benchMarkSolution);
		}
	}


	void RunTests (const TestConfig& config)
	{
		if (config.numberOfTestRuns == 0) {
			std::cout << "Number of test runs cannot be 0.\n";
			return;
		}

		{ // warmup
			OriginalSolution::RunOriginalSolution (config.fileName);
			OriginalSolution::RunOriginalSolution (config.fileName);
			OriginalSolution::RunOriginalSolution (config.fileName);
		}

		TestOriginalSolution originalSolution (config.fileName);
		TestProceduralSolution proceduralSolution (config.fileName);
		TestOptimizedSolution optimizedSolution (config.fileName);
		TestOOPSolution oopSolution (config.fileName);
		TestMultithreadSolution multithreadSolution (config.fileName);
		TestGPUSolution gpuSolution (config.fileName);

		std::vector<TestSolution*> testSolutions {
			&originalSolution,
			&proceduralSolution,
			&optimizedSolution,
			&oopSolution,
			&multithreadSolution,
			&gpuSolution
		};

		if (config.shouldRunFullTest)
			RunFullTest (config.numberOfTestRuns, testSolutions);
		if (config.shouldMeasureFileRead)
			RunReadTest (config.numberOfTestRuns, testSolutions);
		if (config.shouldRunVisibilityCountTest)
			RunVisibilityCountTest (config.numberOfTestRuns, testSolutions);
		if (config.shouldRunHighestScenicScoreTest)
			RunScenicScoreTest (config.numberOfTestRuns, testSolutions);

		PrintResults (config, testSolutions, 0);
	}
}
