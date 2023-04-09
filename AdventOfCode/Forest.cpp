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
		if (trees.empty ())
			return false;

		return i == 0 || j == 0 || i == trees.size () - 1 || j == trees[0].size () - 1;
	}


	bool Forest::IsWithinBounds (int i, int j) const
	{
		return i >= 0 && j >= 0 && i < trees.size () && trees.size () > 0 && j < trees[0].size ();
	}


	int Forest::GetWidth () const
	{
		return trees.empty () ? 0 : trees[0].size ();
	}


	int Forest::GetHeight () const
	{
		return trees.size ();
	}


	Tree& Forest::GetTree (int i, int j)
	{
		if (!IsWithinBounds (i, j))
			Utilities::PrintIndexOutOfBondsMessage (i, j, GetHeight (), GetWidth ());
		return trees[i][j];
	}


	const Tree& Forest::GetTree (int i, int j) const
	{
		if (!IsWithinBounds (i, j))
			Utilities::PrintIndexOutOfBondsMessage (i, j, GetHeight (), GetWidth ());
		return trees[i][j];
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
		if (!fileStream.good ()) {
			Utilities::PrintFileNotFoundMessage (fileName);
			return;
		}
		forest.Clear ();

		std::string line;
		std::getline (fileStream, line);
		const unsigned int width = line.size ();
		do {
			if (line.size () != width) {
				Utilities::PrintBadLineLengthMessage (forest.trees.size () + 1, fileName);
				return;
			}
			std::vector<Tree> row;
			for (unsigned int i = 0; i < line.size (); i++) {
				row.emplace_back (Tree (Utilities::CharDigitToShort (line[i])));
			}
			forest.trees.emplace_back (row);
		} while (std::getline (fileStream, line));
	}

}
