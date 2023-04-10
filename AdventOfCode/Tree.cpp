#include "Tree.hpp"

namespace OOPSolution
{
	Tree::Tree (TreeHeight height) :
		height (height)
	{
	}


	TreeHeight Tree::GetHeight () const
	{
		return height;
	}


	bool Tree::IsVisibleFromAnyDirection () const
	{
		if (visibleFromLeft.has_value () && visibleFromLeft.value () == true)
			return true;

		if (visibleFromRight.has_value () && visibleFromRight.value () == true)
			return true;

		if (visibleFromTop.has_value () && visibleFromTop.value () == true)
			return true;

		if (visibleFromBottom.has_value () && visibleFromBottom.value () == true)
			return true;

		return false;
	}


	void Tree::SetVisibleFromLeft (bool value)
	{
		visibleFromLeft = value;
	}


	void Tree::SetVisibleFromRight (bool value)
	{
		visibleFromRight = value;
	}


	void Tree::SetVisibleFromTop (bool value)
	{
		visibleFromTop = value;
	}


	void Tree::SetVisibleFromBottom (bool value)
	{
		visibleFromBottom = value;
	}


	void Tree::SetScenicScore (uint64_t value)
	{
		scenicScore = value;
	}
}