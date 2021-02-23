
#pragma once


#ifdef NDEBUG
#define ASSERT(x) x
#define ASSERT_MSG(x, msg) x
#else
#define ASSERT(x) if (!(x)) __debugbreak()
#define ASSERT_MSG(x, msg) if (!(x)){ \
std::cout << msg << std::endl;                \
__debugbreak();}
#endif
