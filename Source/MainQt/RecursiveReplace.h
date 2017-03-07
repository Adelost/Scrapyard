#pragma once

#include <Utils/Console.h>

#include <iostream>

class RecursiveReplace
{
public:
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

			QString sFilePath = info.filePath();
			if (info.isDir())
			{
				// recursive
				if (info.fileName() != ".." && info.fileName() != ".")
				{
					search(sFilePath);
				}

				std::cout << info.fileName().toStdString() << std::endl;
			}
			else
			{
				// Do something with the file here
			}
		}
	}

private:
	std::string m_path;
};

void recurseDirectory(const QString& sDir)
{
	QDir dir(sDir);
	QFileInfoList list = dir.entryInfoList();
	for (int iList = 0; iList < list.count(); iList++)
	{
		QFileInfo info = list[iList];

		QString sFilePath = info.filePath();
		if (info.isDir())
		{
			// recursive
			if (info.fileName() != ".." && info.fileName() != ".")
			{
				recurseDirectory(sFilePath);
			}

			std::cout << info.fileName().toStdString() << std::endl;
		}
		else
		{
			// Do something with the file here
		}
	}
}