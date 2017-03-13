#pragma once

namespace ae
{
/// Disallows creating instances of any inheriting class. This is
/// useful if you only want to allow static methods on a class.
class StaticClass
{
private:
	StaticClass() = delete;
};
}

