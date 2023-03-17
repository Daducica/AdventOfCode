#ifndef TREE
#define TREE

#include <optional>
#include <string>
#include <vector>

#include "Tree.hpp"

namespace OOPSolution
{
	class Tree
	{
		short height;
		std::optional<bool> visibleFromLeft;
		std::optional<bool> visibleFromRight;
		std::optional<bool> visibleFromTop;
		std::optional<bool> visibleFromBottom;
		std::optional<bool> visibleFromAnyDirection;
		std::optional<int>  scenicScore;

	public:
		Tree (short height);
		short GetHeight () const { return height; }
		std::optional<bool> IsVisibleFromAnyDirection () const { return visibleFromAnyDirection; }
		void SetVisibleFromAnyDirection (bool value) { visibleFromAnyDirection = value; }
		void SetVisibleFromLeft (bool value) { visibleFromLeft = value; }
		void SetVisibleFromRight (bool value) { visibleFromRight = value; }
		void SetVisibleFromTop (bool value) { visibleFromTop = value; }
		void SetVisibleFromBottom (bool value) { visibleFromBottom = value; }
		void SetScenicScore (int value) { scenicScore = value; }
	};

}

#endif
