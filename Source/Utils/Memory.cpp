#include "Memory.h"

#include <cstring> // memcpy, memmove

namespace ae
{
	void Memory::copyRaw(const void* source, void* destination, int bytes)
	{
		memcpy(destination, source, bytes);
	}

	void Memory::moveRaw(const void* source, void* destination, int bytes)
	{
		memmove(destination, source, bytes);
	}

	void Memory::deallocate(void* data)
	{
		free(data);
	}
}
