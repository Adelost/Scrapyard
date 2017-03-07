#pragma once

#define CATCH_CONFIG_RUNNER

#include "External/Catch/include/catch.hpp"

namespace ae
{
/// A simple poxy for Catch Unit Test
/// Catch is (c) Phil Nash - https://github.com/philsquared
class UnitTests
{
public:
	static void run()
	{
		Catch::Session().run();
	}
};
}