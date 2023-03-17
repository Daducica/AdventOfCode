#ifndef FOREST_CALCULATOR_IMPLEMENTATION
#define FOREST_CALCULATOR_IMPLEMENTATION

#include "Forest.hpp"

namespace OOPSolution
{
	class ForestCalculatorImplementation : public ForestCalculatorInterface {
		Forest* forest;

		int CheckAndSaveVisibilityFromLeft () const;
		int CheckAndSaveVisibilityFromRight () const;
		int CheckAndSaveVisibilityFromTop () const;
		int CheckAndSaveVisibilityFromBottom () const;

		int GetNumberOfVisibleTreesToTheLeft (unsigned int i, unsigned int j) const;
		int GetNumberOfVisibleTreesToTheRight (unsigned int i, unsigned int j) const;
		int GetNumberOfVisibleTreesToTheTop (unsigned int i, unsigned int j) const;
		int GetNumberOfVisibleTreesToTheBottom (unsigned int i, unsigned int j) const;
		int GetScenicScoreForTree (unsigned int i, unsigned int j) const;
	public:
		virtual int CalculateAndSaveVisibleTreeCount (Forest* forest) override;
		virtual int CalculateAndSaveHighestScenicScoreInForest (Forest* forest) override;
	};


}

#endif
