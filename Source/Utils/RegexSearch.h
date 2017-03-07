#pragma once

#include <string>
#include <regex>
class RegexSearch
{
public:
	RegexSearch()
	{
		m_hasMatch = false;
	}
	RegexSearch(std::string regex)
	{
		m_hasMatch = false;
		setRegex(regex);
	}
	RegexSearch(std::string input, std::string regex)
	{
		m_hasMatch = false;
		setInput(input);
		setRegex(regex);
	}

	void setInput(std::string input)
	{
		m_input = input;
	}

	void setRegex(std::string regex)
	{
		m_regex = regex;
	}

	bool hasMatch()
	{
		if(m_hasMatch)
			next();

		if (std::regex_search(m_input, m_smatch, m_regex))
		{
			m_hasMatch = true;
			m_match = m_smatch[0];
			int index = m_smatch.position();

			return true;
		}
		
		m_output += m_input; 

		return false;
	}

	/// Replaces the current match with specified text.
	void replace(std::string text)
	{
		m_match = text;
	}

	/// Returns the full match.
	std::string match()
	{
		return match(0);
	}


	/// Returns specified capture group. "0" for full match, "1" for first
	/// capture group, "2" for second, and so on.
	std::string match(int index)
	{
		std::string match = m_smatch[index];

		return match;
	}

	/// Reformats the current match. Use "$0" for full match, "$1" for first
	/// capture group, "$2" for second, and so on.
	void format(std::string format)
	{
		m_match = m_smatch.format(format);
	}

	std::string output()
	{
		return m_output;
	}


private:
	/// Go to next match.
	void next()
	{
		m_output += m_smatch.prefix();
		m_output += m_match;
		m_input = m_smatch.suffix();
	}

	bool m_hasMatch = true;
	std::string m_input;
	std::string m_output;
	std::string m_match;
	std::smatch m_smatch;
	std::regex m_regex;
};