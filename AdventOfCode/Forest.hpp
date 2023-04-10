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
		virtual uint64_t CalculateAndSaveVisibleTreeCount (Forest* forest) = 0;
		virtual uint64_t CalculateAndSaveHighestScenicScoreInForest (Forest* forest) = 0;
		Tree& GetTree (Forest& forest, size_t row, size_t col);
		virtual ~ForestCalculatorInterface ();
	};


	class Forest
	{
		friend ForestCalculatorInterface;

		std::vector<std::vector<Tree>> trees;
		std::optional<uint64_t> numberOfVisibleTrees;
		std::optional<uint64_t> highestScenicScore;

		std::unique_ptr<ForestCalculatorInterface> calculatorImp;

		void Clear ();
		Tree& GetTree (size_t row, size_t col);

	public:
		Forest (const std::string& fileName, std::unique_ptr<ForestCalculatorInterface> impl);
		uint64_t CalculateAndSaveVisibleTreeCount ();
		uint64_t CalculateAndSaveHighestScenicScoreInForest ();
		bool IsTreeOnEdge (size_t row, size_t col) const;
		bool IsWithinBounds (size_t row, size_t col) const;
		size_t GetWidth () const;
		size_t GetHeight () const;
		const Tree& GetTree (size_t row, size_t col) const;
		std::optional<uint64_t> GetNumberOfVisibleTrees () const;
		std::optional<uint64_t> GetHighestScenicScore () const;

		static void ReadForest (const std::string& fileName, Forest& forest);
	};
}

#endif
