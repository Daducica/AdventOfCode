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


	bool Forest::IsTreeOnEdge (size_t row, size_t col) const
	{
		if (trees.empty ())
			return false;

		return row == 0 || col == 0 || row == trees.size () - 1 || col == trees[0].size () - 1;
	}


	bool Forest::IsWithinBounds (size_t row, size_t col) const
	{
		return row < trees.size () && trees.size () > 0 && col < trees[0].size ();
	}


	size_t Forest::GetWidth () const
	{
		return trees.empty () ? 0 : trees[0].size ();
	}


	size_t Forest::GetHeight () const
	{
		return trees.size ();
	}


	Tree& Forest::GetTree (size_t row, size_t col)
	{
		if (!IsWithinBounds (row, col))
			Utilities::PrintIndexOutOfBondsMessage (row, col, GetHeight (), GetWidth ());
		return trees[row][col];
	}


	const Tree& Forest::GetTree (size_t row, size_t col) const
	{
		if (!IsWithinBounds (row, col))
			Utilities::PrintIndexOutOfBondsMessage (row, col, GetHeight (), GetWidth ());
		return trees[row][col];
	}


	uint64_t Forest::CalculateAndSaveVisibleTreeCount ()
	{
		const uint64_t result = calculatorImp->CalculateAndSaveVisibleTreeCount (this);
		numberOfVisibleTrees = result;
		return result;
	}


	uint64_t Forest::CalculateAndSaveHighestScenicScoreInForest ()
	{
		const uint64_t result = calculatorImp->CalculateAndSaveHighestScenicScoreInForest (this);
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
		const size_t width = (size_t) line.size ();
		do {
			if (line.size () != width) {
				Utilities::PrintBadLineLengthMessage (forest.trees.size () + 1, fileName);
				return;
			}
			std::vector<Tree> rowVector;
			for (size_t row = 0; row < line.size (); row++) {
				rowVector.emplace_back (Tree (Utilities::CharDigitToShort (line[row])));
			}
			forest.trees.emplace_back (rowVector);
		} while (std::getline (fileStream, line));
	}

}
