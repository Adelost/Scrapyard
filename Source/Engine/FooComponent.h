#pragma once

#include <Engine/Component.h>

namespace Component
{
	/// Example of a created component, used for testing purposes

	class Foo : public ae::Component<Foo>
	{
	public:
		int foo;
	};
}
