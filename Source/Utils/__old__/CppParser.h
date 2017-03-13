#pragma once

#include <Utils/StringRef.h>
#include <Utils/Array.h>

#include <regex>

namespace ae
{
class CppParser
{
public:
	CppParser(const std::string& source)
	{
		m_index = 0;
		m_source = source;
		m_hasNext = true;

		startElement();
		parseNext();
	}
	void parseNext()
	{
		while (hasNext())
		{
			findTokenStart();

			bool tokenMatch = true;

			char start = m_source[m_index];

			// Strings
			if (token("\""))
			{
				endElement();
				startElement();

				findEnd("\"");
				endElement();
				
				//Console::print() << "S: " << last().toString();

				startElement();
			}
			//// Comments
			//else if (token("/**"))
			//{
			//	endElement();
			//	startElement();

			//	// findEnd("\\*/");
			//	findEnd("\n");
			//	m_index--;
			//	endElement();
			//	m_index++;

			//	Console::print() << "C: " << last().toString();

			//	startElement();
			//}
			else if (token("///"))
			{
				endElement();
				startElement();

				// findEnd("\\*/");
				findEnd("\n");
				m_index--;
				endElement();
				m_index++;

				Console::print() << "C: " << last().toString();

				startElement();
			}
			// Comments
			else if (token("//"))
			{
				endElement();
				startElement();
				findEnd("\n");
				endElement();
				startElement();
			}
			else
			{
				if (hasNext())
					m_index++;
			}

		}
		endElement();
	}

	void findTokenStart()
	{
		find("\\S");
	}

	bool hasNext()
	{
		return m_hasNext;
	}

	void find(std::string regex)
	{
		std::regex re(regex);
		std::cmatch m;

		if (std::regex_search(&m_source[m_index], m, re))
		{
			int pos = m.position();
			m_index += pos;

			return;
		}

		m_hasNext = false;
	}

	void findEnd(std::string regex)
	{
		m_index++;

		std::regex re(regex);
		std::cmatch m;

		if (std::regex_search(&m_source[m_index], m, re))
		{
			int pos = m.position();
			m_index += pos + m.length();

			return;
		}

		m_hasNext = false;
	}

	char get()
	{
		m_source[m_index];
	}

	void next()
	{
		m_index++;
	}

	void foo()
	{
		std::string prefix;

		if (prefix == "\"")
		{
		}
		if (prefix == "\"")
		{
		}
	}

	bool token(const std::string& token)
	{
		int length = token.length();

		if (m_index + length > (int)m_source.length())
			return false;

		return m_source.compare(m_index, length, token) == 0;
	}


	StringRef& last()
	{
		return m_elements.last();
	}

private:
	void startElement()
	{
		m_elements.add(StringRef(&m_source, m_index, 0));
	}

	void endElement()
	{
		auto& e = last();
		e.setEnd(m_index);

		std::string str = e.toString();

		if (e.isEmpty())
			m_elements.removeLast();
	}

	int m_index;
	std::string m_source;
	Array<StringRef> m_elements;
	bool m_hasNext;
};
}