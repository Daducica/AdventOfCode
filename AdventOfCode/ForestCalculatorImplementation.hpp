#ifndef FOREST_CALCULATOR_IMPLEMENTATION
#define FOREST_CALCULATOR_IMPLEMENTATION

#include "Forest.hpp"

namespace OOPSolution
{
	class ForestCalculatorImplementation : public ForestCalculatorInterface {
		Forest* forest;

		uint64_t CheckAndSaveVisibilityFromLeft ();
		uint64_t CheckAndSaveVisibilityFromRight ();
		uint64_t CheckAndSaveVisibilityFromTop ();
		uint64_t CheckAndSaveVisibilityFromBottom ();

		uint64_t GetNumberOfVisibleTreesToTheLeft (size_t row, size_t col);
		uint64_t GetNumberOfVisibleTreesToTheRight (size_t row, size_t col);
		uint64_t GetNumberOfVisibleTreesToTheTop (size_t row, size_t col);
		uint64_t GetNumberOfVisibleTreesToTheBottom (size_t row, size_t col);
		uint64_t GetScenicScoreForTree (size_t row, size_t col);
	public:
		virtual uint64_t CalculateAndSaveVisibleTreeCount (Forest* forest) override;
		virtual uint64_t CalculateAndSaveHighestScenicScoreInForest (Forest* forest) override;
	};


}

#endif
