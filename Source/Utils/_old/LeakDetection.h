#pragma once

#include "DebugOnly.h"
#include "../Containers/StaticClass.h"

namespace ae
{
/// Helps manage memory leaks. Detects memory leaks during debug. Only
/// supports MSVC currently.
class LeakDetection
{
public:
	/// Allows memory leaks to be detected during debug.
	static void enable();
};
extern LeakDetection __LeakDetection;
}

/// Ignore all memory leaks caused by memory allocations within
/// parenthesis. Useful for hiding non-growing "safe" memory leaks,
/// which is sometimes the case when working with third party
/// libraries.
#define IGNORE_MEMLEAK(CODE) \
int __flags; \
DEBUG_ONLY(__flags = _CrtSetDbgFlag(_CRTDBG_REPORT_FLAG); \
_CrtSetDbgFlag(__flags & ~_CRTDBG_ALLOC_MEM_DF);) \
CODE \
DEBUG_ONLY(_CrtSetDbgFlag(__flags);)

