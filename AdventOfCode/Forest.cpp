#include "Forest.hpp"

#include <fstream>

#include "Utilities.hpp"

namespace OOPSolution
{

	ForestCalculatorInterface::~ForestCalculatorInterface () = default;

	Forest::Forest (const std::string& fileName, std::unique_ptr<ForestCalculatorInterface> impl) :
		calculatorImp (impl.release ())
	{
		ReadForest (fileName, *this);
	}


	bool Forest::IsTreeOnEdge (int i, int j) const
	{
		return i == 0 || j == 0 || i == trees.size () - 1 || j == trees[0].size () - 1;
	}


	int Forest::CalculateAndSaveVisibleTreeCount ()
	{
		const int result = calculatorImp->CalculateAndSaveVisibleTreeCount (this);
		numberOfVisibleTrees = result;
		return result;
	}


	int Forest::CalculateAndSaveHighestScenicScoreInForest ()
	{
		const int result = calculatorImp->CalculateAndSaveHighestScenicScoreInForest (this);
		highestScenicScore = result;
		return result;
	}


	void Forest::Clear ()
	{
		if (trees.size () > 0) {
			trees.clear ();
			numberOfVisibleTrees = std::nullopt;
			highestScenicScore = std::nullopt;
		}
	}


	void Forest::ReadForest (const std::string& fileName, Forest& forest)
	{
		std::ifstream fileStream (fileName);
		std::string line;
		forest.Clear ();
		while (std::getline (fileStream, line)) {
			std::vector<Tree> row;
			for (unsigned int i = 0; i < line.size (); i++) {
				row.emplace_back (Tree (Utilities::CharToShort (line[i])));
			}
			forest.trees.push_back (row);
		}
		fileStream.close ();
	}

}
