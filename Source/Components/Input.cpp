#include "Input.h"

namespace sys
{
InputSystem Input;
InputSystem::ButtonSystem Button;

bool InputSystem::ButtonSystem::isPressed(std::string name)
{
	return sys::Input.button(name);
}

bool InputSystem::ButtonSystem::pressed(std::string name)
{
	return sys::Input.buttonDown(name);
}

bool InputSystem::ButtonSystem::released(std::string name)
{
	return sys::Input.buttonUp(name);
}

void InputSystem::ButtonSystem::update()
{
	sys::Input.update();
}

void InputSystem::ButtonSystem::set(std::string name, bool pressed)
{
	sys::Input.setButton(name, pressed);
}
}
