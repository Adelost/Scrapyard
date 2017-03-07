#include <Utils/Array.h>
#include <Utils/Console.h>
#include <Utils/Inspectable.h>
#include <Utils/Math.h>
#include <Utils/Memory.h>
#include <Utils/Format.h>

#include <iostream>
#include <vector>

using namespace ae;

class Example : Inspectable
{
public:
	INSPECTABLE
	("Example",
	 MEMBER_AUTONAMED(Member::Int, someInt)
	 MEMBER_AUTONAMED(Member::Bool, someBool)
	 MEMBER_AUTONAMED(Member::Float, someFloat)
	)

	Example()
	{
		someInt = 42;
		someBool = true;
		someFloat = Math::PI;
	}

private:
	int someInt;
	bool someBool;
	float someFloat;
};

void testContainers()
{
	Array<int> arr;
	arr << 0 << 1 << 2;
	//Print::subtitle("Array");
	std::cout << "Array: " << arr << "\n";

	std::cout << "Array iterator" << arr << std::endl;
	for (int i : arr)
		std::cout << i;
	std::cout << "\n";
}

void testIntrospection()
{
	Example foo;
	std::cout << "Name: " << foo.inspect().name() << "\n";
	std::cout << "Members: ";
	for (auto m : foo.inspect())
		std::cout << m->valueAsString() << " ";
	std::cout << "\n";
}

void testAlgorithms()
{}

class Foo
{
public:
	~Foo()
	{
		std::cout << "Destructor called on this=" << this << '\n';
	}

	const Foo& operator=(const Foo& other)
	{
		std::cout << "Assignment called\n";

		return *this;
	}
};

Foo foo()
{
	return Foo();
}

struct Prop
{
	class
	{
		int value;
	public:
		int & operator = (const int &i)
		{
			return value = i;
		}
		operator int () const
		{
			return value;
		}
	} alpha;

	class
	{
		float value;
	public:
		float & operator = (const float &f)
		{
			return value = f;
		}
		operator float() const
		{
			return value;
		}
	} bravo;
};

int main()
{
	Prop foo;
	foo.alpha = 0;

	Console::printTitle() << Math::PI << " Start " << true;
	Console::printSubtitle() << Format::string("Hello %1 %2 %3 %1")
	                         % "text"
	                         % true
	                         % 42;

	Console::print() << "Hello";
	Console::print() << "Hello " << "this " << 1 << " me " << false;
	Console::print() << "Hello " << "this " << 3.013 << " me";

	Memory::enableLeakDetection();

	//Print::title("Tests");

	//Print::subtitle("Introspection");
	//testIntrospection();

	//Print::subtitle("Array");
	//testContainers();

	Console::pause();

	return 0;
}


//#include <Components/AllComponents.h>
//#include <Components/Graphic.h>
//#include <Engine/ComponentPool.h>
//#include <Engine/Entity.h>
//#include <Utils/Algorithm.h>
//#include <Utils/Console.h>
//#include <Utils/DebugOnly.h>
//#include <Utils/DebugOnly.h>
//#include <Utils/Math.h>
//#include <Utils/Memory.h>
//#include <Utils/NativePoolArray.h>
//#include <Utils/PoolAlloc.h>
//#include <Utils/PoolArray.h>
//#include <Utils/StablePoolArray.h>
//#include <Utils/StopWatch.h>
//
//#include <string>
//#include <vector>
//#include <vector>
//
//RELEASE_ONLY(const int ELEMENT_COUNT = 100000000; const int REPEATS = 1;);
//DEBUG_ONLY(const int ELEMENT_COUNT = 8; const int REPEATS = 3;);
//
///// Template class to create a struct of varying sizes in bytes, with a minimum
//	of 4 bytes. Useful when measuring performance variance of container with
//	different sized elements.
//template<int BYTES>
//struct Element
//{
//	Element() {}
//	Element(int data)
//	{
//		this->data = data;
//	}
//	union
//	{
//		int data;
//		char padding[BYTES];
//	};
//};
//
//template<class C, class E>
//void addElement(C& container, E& element)
//{
//	container.add(element);
//}
//
//template<class C, class E>
//void addElement(std::vector<E>& container, E& element)
//{
//	container.push_back(element);
//}
//
///// Profile the iteration performance of container "T" using element "E".
//template<class C, class E>
//void add(C& container)
//{
//	container.reserve(ELEMENT_COUNT);
//	StopWatch w;
//	for (int i = 0; i < ELEMENT_COUNT; i++)
//		addElement<C, E>(container, E(i));
//	w.printTime("Add");
//}
//
///// Profile the iteration performance of container "T" using element "E".
//template<class C, class E>
//void iterate(C& container)
//{
//	int checksum = 0;
//	StopWatch w;
//	for (E e : container)
//		checksum += e.data;
//	w.pause();
//
//	// We need to print a checksum as well as time to prevent unused code sections
//	// from being optimized away by the compiler.
//	std::cout << "Iter:\t" << w.timeMs() << " ms\tchecksum: " << checksum << "\n";
//}
//
//template<class C, class E>
//void iterate(Array<PoolAlloc<E>>& container)
//{
//	int checksum = 0;
//	StopWatch w;
//	for (PoolAlloc<E> e : container)
//		checksum += e->data;
//	w.pause();
//	std::cout << "Iter:\t" << w.timeMs() << " ms\tchecksum: " << checksum << "\n";
//}
//
//template<class C, class E>
//void remove(C& container)
//{
//	// Nothing
//}
//
//template<class C, class E>
//void remove(PoolArray<E>& container)
//{
//	StopWatch w;
//
//	w.start();
//	Array<int> random;
//	for (int i = 0; i < container.count(); i++)
//		random.add(i);
//	Algorithm::shuffle(random.elements(), random.count());
//	w.printTime("Rand");
//
//	PoolArray<E>& c = container;
//
//	w.start();
//	for (int i = 0; i < random.count(); i++)
//		c.remove(i);
//	w.printTime("Remove");
//	w.start();
//	for (int i = 0; i < random.count(); i++)
//		c.add(i);
//	w.printTime("Add");
//
//	//c = container;
//	//w.start();
//	//for (int i = 0; i < random.count() / 2; i++)
//	//	c.remove(random[i]);
//	//for (int i = 0; i < random.count() / 2; i++)
//	//	c.add(i);
//	//w.printTime("Remove");
//
//	//c = container;
//	//w.start();
//	//for (int i = 0; i < random.count(); i++)
//	//	c.remove(random[i]);
//	//w.printTime("Full remove");
//
//	//std::cout << container << std::endl;
//}
//
//template<class C, class E>
//void profileContaner(std::string label)
//{
//	std::cout << label << "\n---\n";
//
//	C container;
//	add<C, E>(container);
//	iterate<C, E>(container);
//	remove<C, E>(container);
//
//	std::cout << "\n";
//}
//
//template<class E>
//void profilePointerOverhead(std::string label)
//{
//	std::cout << label << "\n---\n";
//
//	Array<E> elements;
//	elements.reserve(ELEMENT_COUNT);
//	for (int i = 0; i < ELEMENT_COUNT; i++)
//		elements.add(E(i));
//	Array<E*> container;
//	container.reserve(ELEMENT_COUNT);
//
//	StopWatch w;
//	w.start();
//	for (int i = 0; i < ELEMENT_COUNT; i++)
//		container.add(&elements[i]);
//	w.printTime("Add");
//
//	int checksum = 0;
//	w.start();
//	for (E* e : container)
//		checksum += (*e).data;
//	w.pause();
//	std::cout << "Iter:\t" << w.timeMs() << " ms\tchecksum: " << checksum << "\n";
//}
//
///// Profile the performance of various containers using element "E".
//template<class E>
//void profileElement()
//{
//	//profileContaner<std::vector<E>, E>("Vector");
//	profileContaner<Array<E>, E>("Array");
//	//
//	//profileContaner<NativePoolArray<E>, E>("NativePoolArray");
//	profileContaner<PoolArray<E>, E>("PoolArray");
//	//profileContaner<StablePoolArray<E>, E>("StablePoolArray");
//	//PoolAlloc<E>::Reserve(ELEMENT_COUNT);
//	//profileContaner<Array<PoolAlloc<E>>, E>("PoolAlloc");
//	//profilePointerOverhead<E>("Pointer Overhead");
//}
//
//int main()
//{
//	Memory::enableLeakDetection();
//
//	profileElement<Element<4>>();
//
//	Array<int> foo;
//	Algorithm::sort(foo.elements(), foo.count());
//
//	Console::pressToContinue();
//
//	return 0;
//}