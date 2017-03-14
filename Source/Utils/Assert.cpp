#include "Assert.h"

#include <cstdio> // fprintf


int XAssert::onFailure(bool condition, const char* file, int line,
                       const char* msg)
{
	// Prints info to console
	fprintf(stderr,
	        "=========================\n Warning: Assertion Failed\n Info: %s\n File: %s(%d)\n",
	        msg, file, line);

	// Return either "Break" or "Continue" to break or continue execution after
	// a failed assert. Continue is useful when performing unit tests.
	return BREAK;
}
