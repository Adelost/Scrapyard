#pragma once

#include "Time.h"

#include <Engine/Component.h>
#include <Utils/Console.h>

using namespace ae;

namespace com
{
	class Alpha : public Component<Alpha>
	{
	public:
		Alpha(int id) : Component<Alpha>(id)
		{
			a = id;
		}

		int a;
	};

	class Beta : public Component<Beta>
	{
	public:
		Beta(int id) :  Component<Beta>(id), cAlpha(id)
		{
			/*b = id;
			Console::print() << "Beta: " << b << ", Alpha: " << cAlpha->a;
			Console::print() << "Delta time: " << sys::Time.delta();
			sys::Time.delta();
			sys::Time.delta();*/
		}
		Dependency<Alpha> cAlpha;

		int b;
	};
}



