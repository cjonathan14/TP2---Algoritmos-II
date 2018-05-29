/*
		UTILS.CC
*/

#include "utils.h"

#include <cstdlib>

bool is_pow_2 (size_t n) 
{
	return (n&(n-1))==0 ? true : false;
}
