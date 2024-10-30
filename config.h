#ifndef CONFIG_H
#define CONFIG_H

// Include standard headers for necessary constants
#include <climits>   // For SIZE_MAX and other limits
#include <cstdint>   // For uint64_t and other fixed-width integers

// Define SIZE_MAX if not already defined
#ifndef SIZE_MAX
#define SIZE_MAX (~(size_t)0)
#endif

// Define UINT64_MAX if not already defined
#ifndef UINT64_MAX
#define UINT64_MAX (~(uint64_t)0)
#endif

// Additional standard limit macros (optional)
#ifndef INT_MAX
#define INT_MAX (~(int)0)
#endif

#ifndef INT_MIN
#define INT_MIN (int)((unsigned int)0x80000000)
#endif

#endif // CONFIG_H
