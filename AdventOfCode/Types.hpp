#ifndef TYPES
#define TYPES

#include <vector>

typedef std::int_fast8_t					 TreeHeight;

typedef std::vector<TreeHeight>				 ForestRow;
typedef std::vector<std::vector<TreeHeight>> ForestMatrix;

typedef std::vector<bool>					 VisibilityCacheRow;
typedef std::vector<std::vector<bool>>		 VisibilityCache;

#endif
