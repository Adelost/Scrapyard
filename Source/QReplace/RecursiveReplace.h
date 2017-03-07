#pragma once

#include <Utils/Algorithm.h>
#include <Utils/Array.h>
#include <Utils/Console.h>
#include <Utils/Format.h>
#include <Utils/RegexSearch.h>
#include <Utils/StringRef.h>
#include <Utils/CppParser.h>

#include <QString>
#include <QTextStream>
#include <QDir>
#include <QRegularExpression>

#include <regex>
#include <iostream>


using namespace ae;

//class QRegexReplace
//{
//public:
//	QRegexReplace(QString pattern, QString text)
//	{
//		m_regex.setPattern(".*/\\*[\\S\\s]*?\\*/");
//		m_iterator = m_regex.globalMatch(text);
//		m_text = text;
//	}
//
//private:
//	QString m_text;
//	QRegularExpression m_regex;
//	QRegularExpressionMatchIterator m_iterator;
//	int m_prefixStart;
//
//public:
//	class Match
//	{
//	public:
//		Match(QRegexReplace& host) : m_host(host), m_match(host.m_iterator.peekNext()) {}
//		QString match(int i)
//		{
//			return m_match.captured(i);
//		}
//		QString prefix()
//		{
//			int last = m_match.lastCapturedIndex();
//			int s = m_match.capturedStart();
//			int e = m_match.capturedEnd();
//			int l = m_match.capturedLength();
//			QString str = m_host.m_text.mid(s, l);
//			return "";
//		}
//		QString suffix()
//		{
//			return "";
//		}
//
//	private:
//		QRegexReplace& m_host;
//		QRegularExpressionMatch m_match;
//	};
//
//	#pragma region Iterator
//	class Iterator
//	{
//	public:
//		Iterator(QRegexReplace& host) : m_host(host) {}
//		bool operator!=(const Iterator& other) const
//		{
//			return m_host.m_iterator.hasNext();
//		}
//		const Iterator& operator++()
//		{
//			m_host.m_iterator.next();
//			m_host.
//
//			return *this;
//		}
//		Match operator*() const
//		{
//			return Match(m_host);
//		}
//
//	private:
//		QRegexReplace& m_host;
//	};
//
//	Iterator begin()
//	{
//		return Iterator(*this);
//	}
//	Iterator end()
//	{
//		return Iterator(*this);
//	}
//	#pragma endregion
//};



class RecursiveReplace
{
public:
	RecursiveReplace()
	{
		m_depth = 0;
	}

	void replace(std::string path)
	{
		m_path = path;

		search(QString(path.c_str()));
	}

	void search(QString path)
	{
		QDir dir(path);
		QFileInfoList list = dir.entryInfoList();
		for (int iList = 0; iList < list.count(); iList++)
		{
			QFileInfo info = list[iList];
			QString fileName = info.fileName();

			QString sFilePath = info.filePath();
			if (info.isDir())
			{
				// recursive
				if (!Algorithm::any(fileName, "..", ".", "GeneratedFiles"))
				{
					//printFolder(info.fileName());

					m_depth++;
					search(sFilePath);
					m_depth--;
				}
			}
			else if (Algorithm::any(info.suffix(), "h", "hpp", "cpp"))
			{
				//printFile(fileName);
				QFile f(info.absoluteFilePath());
				f.open(QFile::ReadWrite | QFile::Text);
				QTextStream in(&f);

				std::string s = in.readAll().toStdString();

				CppParser parse(s);
				//Console::print() << "=======";
			}
		}
	}

	void printDepth()
	{
		for (int i = 0; i < m_depth; i++)
			std::cout << " ";
	}

	void printFolder(QString name)
	{
		//std::string content;
		//TextSearcher search(&content, 0, content.length());

		//search.between("/**", "*/").


		printDepth();
		Console::print() << "[" << name.toStdString() << "]";
	}

	void printFile(QString name)
	{
		printDepth();
		Console::print() << name.toStdString();
	}

	bool tokenFound(const std::string& content, int index, const std::string& token)
	{
		int length = token.length();

		if (content.length() < index + length)
			return false;

		for (int i = 0; i < length; i++)
		{
			if (content[index + i] != token[i])
				return false;
		}

		m_tokenEnd = index + length;

		return true;
	}

private:
	std::string m_path;
	int m_depth;
	int m_tokenEnd;
};