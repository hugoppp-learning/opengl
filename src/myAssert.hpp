
#pragma once

#ifdef NDEBUG
#define ASSERT(x) x
#else
#define ASSERT(x) if (!(x)) __debugbreak()
#endif
