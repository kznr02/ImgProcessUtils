#define BUILD_TEST

#include "utils.h"
#include <algorithm>
#include <iostream>
#include <list>

uint16_t min(uint16_t* src)
{
	std::list<uint16_t> tmp_list = src;
	return std::min_element(std::begin(src), std::end(src))
}
