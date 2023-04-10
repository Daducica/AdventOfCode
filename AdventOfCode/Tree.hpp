#ifndef TREE
#define TREE

#include <optional>
#include <string>

#include "Tree.hpp"
#include "Types.hpp"

namespace OOPSolution
{
	class Tree
	{
		TreeHeight height;
		std::optional<bool> visibleFromLeft;
		std::optional<bool> visibleFromRight;
		std::optional<bool> visibleFromTop;
		std::optional<bool> visibleFromBottom;
		std::optional<uint64_t>  scenicScore;

	public:
		Tree (TreeHeight height);
		TreeHeight GetHeight () const;
		bool IsVisibleFromAnyDirection () const;

		void SetVisibleFromLeft (bool value);
		void SetVisibleFromRight (bool value);
		void SetVisibleFromTop (bool value);
		void SetVisibleFromBottom (bool value);

		void SetScenicScore (uint64_t value);
	};

}

#endif
