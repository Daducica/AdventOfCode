#include "TestRunner.hpp"

#include <cassert>
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
	class TestSolution
	{
		std::optional<int> fullResult;
		std::optional<int> readResult;
		std::optional<int> visibilityCountResult;
		std::optional<int> scenicScoreResult;

		virtual std::string GetTestName () const = 0;
		virtual void RunFullSolution () const = 0;
		virtual void RunReadTest () const = 0;
		virtual void RunVisibilityCountTest () const = 0;
		virtual void RunScenicScoreTest () const = 0;
	public:
		void MeasureFullSolutionTest (int numberOfTestRuns);
		void MeasureReadTest (int numberOfTestRuns);
		void MeasureVisibilityCountTest (int numberOfTestRuns);
		void MeasureScenicScoreTest (int numberOfTestRuns);

		virtual ~TestSolution ();
		void PrintResults (const TestSolution& benchMark) const;
	};


	void TestSolution::MeasureFullSolutionTest (int numberOfTestRuns)
	{
		Utilities::MilliSecTimer timer;
		timer.StartTimer ();

		for (unsigned int i = 0; i < numberOfTestRuns; ++i)
			RunFullSolution ();

		fullResult = timer.StopTimer () / numberOfTestRuns;
	}


	void TestSolution::MeasureReadTest (int numberOfTestRuns)
	{
		Utilities::MilliSecTimer timer;
		timer.StartTimer ();

		for (unsigned int i = 0; i < numberOfTestRuns; ++i)
			RunReadTest ();

		readResult = timer.StopTimer () / numberOfTestRuns;
	}


	void TestSolution::MeasureVisibilityCountTest (int numberOfTestRuns)
	{
		Utilities::MilliSecTimer timer;
		timer.StartTimer ();

		for (unsigned int i = 0; i < numberOfTestRuns; ++i)
			RunVisibilityCountTest ();

		visibilityCountResult = timer.StopTimer () / numberOfTestRuns;
	}


	void TestSolution::MeasureScenicScoreTest (int numberOfTestRuns)
	{
		Utilities::MilliSecTimer timer;
		timer.StartTimer ();

		for (unsigned int i = 0; i < numberOfTestRuns; ++i)
			RunScenicScoreTest ();

		scenicScoreResult = timer.StopTimer () / numberOfTestRuns;
	}


	TestSolution::~TestSolution () = default;


	void TestSolution::PrintResults (const TestSolution& benchMark) const
	{
		std::cout << GetTestName () << "\t";
		if (fullResult.has_value () && benchMark.fullResult.has_value ()) {
			const double relativeRunTime = (double)benchMark.fullResult.value () / fullResult.value ();
			std::cout << relativeRunTime << "x\t";
		}
		if (readResult.has_value () && benchMark.readResult.has_value ()) {
			const double relativeRunTime = (double)benchMark.readResult.value () / readResult.value ();
			std::cout << relativeRunTime << "x\t";
		}
		if (visibilityCountResult.has_value () && benchMark.visibilityCountResult.has_value ()) {
			const double relativeRunTime = (double)benchMark.visibilityCountResult.value () / visibilityCountResult.value ();
			std::cout << relativeRunTime << "x\t";
		}
		if (scenicScoreResult.has_value () && benchMark.scenicScoreResult.has_value ()) {
			const double relativeRunTime = (double)benchMark.scenicScoreResult.value () / scenicScoreResult.value ();
			std::cout << relativeRunTime << "x\t";
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
		virtual void RunReadTest () const override;
		virtual void RunVisibilityCountTest () const override;
		virtual void RunScenicScoreTest () const override;
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


	void TestOriginalSolution::RunReadTest () const
	{
		OriginalSolution::ReadFile (fileName);
	}


	void TestOriginalSolution::RunVisibilityCountTest () const
	{
		OriginalSolution::CalculateVisibilityCount (testData);
	}

	
	void TestOriginalSolution::RunScenicScoreTest () const
	{
		OriginalSolution::CalculateHighestScenicScore (testData);
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
		virtual void RunReadTest () const override;
		virtual void RunVisibilityCountTest () const override;
		virtual void RunScenicScoreTest () const override;
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


	void TestProceduralSolution::RunReadTest () const
	{
		ProceduralSolution::ReadFile (fileName);
	}


	void TestProceduralSolution::RunVisibilityCountTest () const
	{
		ProceduralSolution::GetNumberOfVisibleTreesInForest (testData);
	}


	void TestProceduralSolution::RunScenicScoreTest () const
	{
		ProceduralSolution::GetNumberOfVisibleTreesInForest (testData);
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
		virtual void RunReadTest () const override;
		virtual void RunVisibilityCountTest () const override;
		virtual void RunScenicScoreTest () const override;
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


	void TestOptimizedSolution::RunReadTest () const
	{
		OptimizedProceduralSolution::ReadFile (fileName);
	}


	void TestOptimizedSolution::RunVisibilityCountTest () const
	{
		OptimizedProceduralSolution::GetNumberOfVisibleTreesInForest (testData);
	}


	void TestOptimizedSolution::RunScenicScoreTest () const
	{
		OptimizedProceduralSolution::GetNumberOfVisibleTreesInForest (testData);
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
		virtual void RunReadTest () const override;
		virtual void RunVisibilityCountTest () const override;
		virtual void RunScenicScoreTest () const override;
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


	void TestOOPSolution::RunReadTest () const
	{
		OOPSolution::ReadFile (fileName);
	}


	void TestOOPSolution::RunVisibilityCountTest () const
	{
		OOPSolution::GetNumberOfVisibleTreesInForest (const_cast<OOPSolution::Forest&> (testData));
	}


	void TestOOPSolution::RunScenicScoreTest () const
	{
		OOPSolution::GetNumberOfVisibleTreesInForest (const_cast<OOPSolution::Forest&> (testData));
	}


	static void RunFullTest (int numberOfTestRuns, std::vector<TestSolution*> testSolutions)
	{
		for (TestSolution* testSolution : testSolutions)
			testSolution->MeasureFullSolutionTest (numberOfTestRuns);
	}


	static void RunReadTest (int numberOfTestRuns, std::vector<TestSolution*> testSolutions)
	{
		for (TestSolution* testSolution : testSolutions)
			testSolution->MeasureReadTest (numberOfTestRuns);
	}


	static void RunVisibilityCountTest (int numberOfTestRuns, std::vector<TestSolution*> testSolutions)
	{
		for (TestSolution* testSolution : testSolutions)
			testSolution->MeasureVisibilityCountTest (numberOfTestRuns);
	}


	static void RunScenicScoreTest (int numberOfTestRuns, std::vector<TestSolution*> testSolutions)
	{
		for (TestSolution* testSolution : testSolutions)
			testSolution->MeasureScenicScoreTest (numberOfTestRuns);
	}


	void PrintResults (const TestConfig& config, const std::vector<TestSolution*>& testSolutions, unsigned int benchMarkIndex)
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
			<< "LoopCount = " << config.numberOfTestRuns << "\n\n"
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
		TestOriginalSolution originalSolution (config.fileName);
		TestProceduralSolution proceduralSolution (config.fileName);
		TestOptimizedSolution optimizedSolution (config.fileName);
		TestOOPSolution oopSolution (config.fileName);

		std::vector<TestSolution*> testSolutions {
			&originalSolution,
			&proceduralSolution,
			&optimizedSolution,
			&oopSolution
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
