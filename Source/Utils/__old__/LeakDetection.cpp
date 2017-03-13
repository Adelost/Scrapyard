#include "LeakDetection.h"

#include "DebugOnly.h"
#include "../Containers/StaticInit.h"
#include "../Console.h"
#include <crtdbg.h> // _CrtSetDbgFlag

namespace ae
{
void LeakDetection::enable()
{
	DEBUG_ONLY(_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);)
	Console::print() << "Memory leak detection is enable.";
}
}
