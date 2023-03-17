#ifndef FOREST
#define FOREST

#include <memory>
#include <optional>
#include <string>
#include <vector>

#include "Tree.hpp"

namespace OOPSolution
{
	class Forest;

	class ForestCalculatorInterface
	{
	public:
		virtual int CalculateAndSaveVisibleTreeCount (Forest* forest) = 0;
		virtual int CalculateAndSaveHighestScenicScoreInForest (Forest* forest) = 0;
		virtual ~ForestCalculatorInterface ();
	};

	class Forest
	{
		std::vector<std::vector<Tree>> trees;
		std::optional<int> numberOfVisibleTrees;
		std::optional<int> highestScenicScore;

		std::unique_ptr<ForestCalculatorInterface> calculatorImp;

		void Clear ();

	public:
		Forest (const std::string& fileName, std::unique_ptr<ForestCalculatorInterface> impl);
		int CalculateAndSaveVisibleTreeCount ();
		int CalculateAndSaveHighestScenicScoreInForest ();
		bool IsTreeOnEdge (int i, int j) const;
		int GetWidth() { return trees.empty () ? 0 : trees[0].size (); }
		int GetHeight () { return trees.size (); }
		Tree& GetTree (int i, int j) { return trees[i][j]; }
		const Tree& GetTree (int i, int j) const { return trees[i][j]; }

		static void ReadForest (const std::string& fileName, Forest& forest);
	};
}

#endif
