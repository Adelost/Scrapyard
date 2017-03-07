#pragma once

#include <string>

namespace ae
{
/// References a substring of a std::string.
/// 
/// - Designed to improve performance of substring handling 
///   when manipulating strings.
/// - Calling toString() returns a copy of the referenced
///   substring.
class StringRef
{
public:
	StringRef()
	{
		m_start = 0;
		m_length = 0;
	}
	StringRef(const StringRef& other)
	{
		*this = other;
	}
	StringRef(std::string* source)
	{
		*this = source;
	}
	StringRef(std::string* source, int start, int length)
	{
		setSource(source, start, length);
	}

	StringRef& operator=(const StringRef& other)
	{
		setSource(other);

		return *this;
	}
	StringRef& operator=(const std::string* other)
	{
		setSource(other);

		return *this;
	}
	/// Returns a copy of the referenced substring.
	std::string toString() const
	{
		return m_source->substr(m_start, m_length);
	}
	/// Compares this StringRef with other StringRef. 0 = "String < "
	int compare(const StringRef& other) const
	{
		return m_source->compare(m_start, m_length, *other.m_source, other.m_start, other.m_length);
	}
	int compare(const std::string& other) const
	{
		return m_source->compare(m_start, m_length, other);
	}

	void setSource(const StringRef& source)
	{
		setSource(source.m_source, source.m_start, source.m_length);
	}
	/// Overrides the source with the specified text. Useful when
	/// staging changes to a source text without affecting the source.
	void setText(std::string& text)
	{
		m_localSource = text;
		setSource(&m_localSource);
	}
	void setSource(const std::string* source)
	{
		m_source = source;
		m_start = 0;
		m_length = source->length();
	}
	void setSource(const std::string* source, int start, int length)
	{
		m_source = source;
		m_start = start;
		m_length = length;
	}
	void setStart(int start)
	{
		m_start = start;
	}
	void setEnd(int end)
	{
		m_length = end - m_start;
	}
	int length()
	{
		return m_length;
	}
	void setLength(int length)
	{
		m_length = length;
	}
	bool isEmpty()
	{
		return length() == 0;
	}

private:
	std::string m_localSource;
	const std::string* m_source;
	int m_start;
	int m_length;
};

bool operator==(const StringRef& left, const StringRef& right)
{
	return left.compare(right) == 0;
}

bool operator!=(const StringRef& left, const StringRef& right)
{
	return left.compare(right) != 0;
}

bool operator==(const StringRef& left, const std::string& right)
{
	return left.compare(right) == 0;
}

bool operator!=(const StringRef& left, const std::string& right)
{
	return left.compare(right) != 0;
}

bool operator==(const std::string& left, const StringRef& right)
{
	return right.compare(left) == 0;
}

bool operator!=(const std::string& left, const StringRef& right)
{
	return right.compare(left) != 0;
}

bool operator<(const StringRef& left, const StringRef& right)
{
	return left.compare(right) < 0;
}

bool operator>(const StringRef& left, const StringRef& right)
{
	return left.compare(right) > 0;
}

bool operator<(const std::string& left, const StringRef& right)
{
	return right.compare(left) > 0;
}

bool operator>(const std::string& left, const StringRef& right)
{
	return right.compare(left) < 0;
}

bool operator<(const StringRef& left, const std::string& right)
{
	return left.compare(right) < 0;
}

bool operator>(const StringRef& left, const std::string& right)
{
	return left.compare(right) > 0;
}
}