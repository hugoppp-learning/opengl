#ifndef OPENGLTEST_ASSERT_H
#define OPENGLTEST_ASSERT_H

#ifdef NDEBUG
#define ASSERT(x) x
#else
#define ASSERT(x) if (!(x)) __debugbreak()
#endif

#endif //OPENGLTEST_ASSERT_H

