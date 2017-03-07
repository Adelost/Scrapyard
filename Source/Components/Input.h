#pragma once

#include <Engine/Component.h>

#include <unordered_map>
#include <vector>
#include <string>

namespace sys
{
class InputSystem
{
public:
	class ButtonSystem
	{
	public:
		void update();
		//! Returns true if button currently is pressed.
		bool isPressed(std::string name);
		//! Returns true if button was pressed during the current frame.
		bool pressed(std::string name);
		//! Returns true if button was released during the current frame.
		bool released(std::string name);
		void set(std::string name, bool pressed);
	};

private:
	struct Button
	{
		Button()
		{
			state = false;
			up  = false;
			down = false;
		}

		bool state;
		bool up;
		bool down;
	};

public:
	InputSystem()
	{
		//button("Up");
		//button("Down");
		//button("Left");
		//button("Right");
	}
	//! Returns true while the virtual button identified by name is held
	//! down.
	bool button(std::string name)
	{
		return m_buttons[name].state;
	}
	//! Returns true the first frame the button is released.
	bool buttonUp(std::string name)
	{
		return m_buttons[name].up;
	}
	//! Returns true the first frame the button is pressed.
	bool buttonDown(std::string name)
	{
		return m_buttons[name].down;
	}

	void setButton(std::string name, bool pressed)
	{
		Button& b = m_buttons[name];
		if (pressed && !b.state)
		{
			b.state = pressed;
			setButtonDown(name);
		}
		else if (!pressed && b.state)
		{
			b.state = pressed;
			setButtonUp(name);
		}
	}

	void update()
	{
		// Reset button changes
		for (std::string& name : changedButton)
		{
			Button& b = m_buttons[name];
			b.down = false;
			b.up = false;
		}
		changedButton.clear();
	}

private:
	void setButtonDown(std::string name)
	{
		m_buttons[name].down = true;
		addChange(name);
	}
	void setButtonUp(std::string name)
	{
		m_buttons[name].up = true;
		addChange(name);
	}
	void addChange(std::string name)
	{
		changedButton.push_back(name);
	}

	std::vector<std::string> changedButton;
	std::unordered_map<std::string, Button> m_buttons;
};
extern InputSystem Input;
extern InputSystem::ButtonSystem Button;
}
