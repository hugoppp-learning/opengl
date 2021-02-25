
#pragma once

#include <iostream>

#ifdef NDEBUG
#define ASSERT(x) x
#define ASSERT_MSG(x, msg) x
#else
#define ASSERT(x) if (!(x)) __debugbreak()
#define ASSERT_MSG(x, msg) if (!(x)){                                                           \
std::cout                                                                                       \
<< "\nERROR: Assert failed in '"  << __FUNCTION__ << "' in file\n"                              \
<<  __FILE__ << ":" << __LINE__ << "\n'"                                                        \
<< msg << "'"<< std::endl;                                                                      \
__debugbreak();}
#endif
