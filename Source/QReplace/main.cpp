#include <RecursiveReplace.h>

#include <QtCore/QCoreApplication>
#include <Utils/Console.h>
#include <Utils/Memory.h>
#include <Utils/RegexSearch.h>

using namespace ae;

int main(int argc, char *argv[])
{
	ae::Memory::enableLeakDetection();

	QCoreApplication a(argc, argv);

	RecursiveReplace r;
	//r.replace("C:/Desktop/Regex");
	r.replace("C:/Desktop/Source/Cpp/AberrantEngine/Source");

	Console::pause();
}
