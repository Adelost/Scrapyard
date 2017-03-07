#pragma once

#include <Engine/Component.h>

using namespace ae;

namespace Fruits
{
	class Apple : public Component<Apple> {};
	class Banana : public Component<Banana> {};
	class Citrus : public Component<Citrus> {};
	class Durian : public Component<Durian> {};
	class Eggplant : public Component<Eggplant> {};
	class Fig : public Component<Fig> {};
	class Grapes : public Component<Grapes> {};
}

