#pragma once

/// Make sure the code inputed as argument is only run once.
#define CALL_ONCE(CODE) \
{ \
	static bool first = true; \
	if(first) \
	{ \
		first = false; \
		CODE\
	} \
}