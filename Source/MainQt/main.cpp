#include "Preincludes.h"
#include "Preforwards.h"
#include "MainWindow.h"
#include "RecursiveReplace.h"

#include <Utils/Memory.h>

void foo();

int main(int argc, char *argv[])
{
	// Detect memory leaks
	ae::Memory::enableLeakDetection();

	RecursiveReplace r;
	r.replace("C:/Desktop/Regex");

	// Startup program
	QApplication a(argc, argv);
	MainWindow w;
	w.show();
	return a.exec();
}

#include "Preincludes.h"
#include "Preforwards.h"
#include <iostream>
#include <string>
#include <QRegularExpression>


void foo()
{
	std::string in = "/*\naaa\naaaaaaaaa\naaaaaaaaa\naaaaaaaaaaaaa\naaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa\naaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa\naaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa\naaaaaaaaaaaaaaaaa\naaaaaaaaa\naaaaaaaaaaaaa\naaaaaaaaa\naaaaaaaaaaaaaaaaaa\naaaaaaaaa\naaaaaaaaaaaaa\naaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa\naaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa\naaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa\naaaaaaaaaaaaaaaaa\naaaaaaaaa\naaaaaaaaa\naaaaaaaaa\n*/";

	QRegularExpression re(".*/\\*(\n|.)*?\\*/");
	QRegularExpressionMatchIterator it = re.globalMatch(QString(in.c_str()));
	while (it.hasNext())
	{
		QRegularExpressionMatch match = it.next();
		QString word = match.captured(0);
	}
}
