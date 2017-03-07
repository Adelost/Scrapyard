#include <Engine/ComponentPool.h>
#include <Engine/Entity.h>
#include <Utils/Algorithm.h>
#include <Utils/Console.h>
#include <Utils/DebugOnly.h>
#include <Utils/DebugOnly.h>
#include <Utils/Math.h>
#include <Utils/Memory.h>
#include <Utils/NativePoolArray.h>
#include <Utils/Array.h>
#include <Utils/PoolPtr.h>
#include <Utils/PoolArray.h>
#include <Utils/StablePoolArray.h>
#include <Utils/StopWatch.h>
#include <Utils/LeakDetection.h>

#include <string>
#include <vector>
#include <vector>

using namespace ae;

RELEASE_ONLY(const int ELEMENT_COUNT = 10000000; const int REPEATS = 10;);
DEBUG_ONLY(const int ELEMENT_COUNT = 5; const int REPEATS = 3;);

/// Template class to create a struct of varying sizes in bytes, with a minimum
///	of 4 bytes. Useful when measuring performance variance of container with
///	different sized elements.
template<int BYTES>
struct Element
{
	Element() {}
	Element(int data)
	{
		this->data = data;
	}
	union
	{
		int data;
		char padding[BYTES];
	};
};

template<class C, class E>
void startElement(C* container, E& element)
{
	container->add(element);
}

template<class C, class E>
void startElement(std::vector<E>* container, E& element)
{
	container->push_back(element);
}

/// Profile the iteration performance of container "T" using element "E".
template<class C, class E>
void add(C& container)
{
	container.reserve(ELEMENT_COUNT);
	StopWatch w;
	for (int i = 0; i < ELEMENT_COUNT; i++)
		startElement<C, E>(&container, E(i));
	w.pause();
	w.printTime("Add");
}

/// Profile the iteration performance of container "T" using element "E".
template<class C, class E>
void iterate(C& container)
{
	int checksum = 0;
	StopWatch w;
	for (E e : container)
		checksum += e.data;
	w.pause();

	// We need to print a checksum as well as time to prevent unused code sections
	// from being optimized away by the compiler.
	std::cout << "Iter:\t" << w.timeMs() << " ms\tchecksum: " << checksum << "\n";
}

template<class C, class E>
void iterate(Array<PoolPtr<E>>& container)
{
	int checksum = 0;
	StopWatch w;
	for (PoolPtr<E> e : container)
		checksum += e->data;
	w.pause();
	std::cout << "Iter:\t" << w.timeMs() << " ms\tchecksum: " << checksum << "\n";
}

template<class C, class E>
void remove(C& container)
{
	// Nothing
}

template<class C, class E>
void remove(PoolArray<E>& container)
{
	StopWatch w;

	w.start();
	Array<int> random;
	for (int i = 0; i < container.count(); i++)
		random.add(i);
	Algorithm::shuffle(random.raw(), random.count());
	w.printTime("Rand");

	PoolArray<E>& c = container;

	w.start();
	for (int i = 0; i < random.count(); i++)
		c.remove(i);
	w.printTime("Remove");
	w.start();
	for (int i = 0; i < random.count(); i++)
		c.add(i);
	w.printTime("Add");

	//c = container;
	//w.start();
	//for (int i = 0; i < random.count() / 2; i++)
	//	c.remove(random[i]);
	//for (int i = 0; i < random.count() / 2; i++)
	//	c.add(i);
	//w.printTime("Remove");

	//c = container;
	//w.start();
	//for (int i = 0; i < random.count(); i++)
	//	c.remove(random[i]);
	//w.printTime("Full remove");

	//std::cout << container << std::endl;
}

template<class C, class E>
void profileContaner(std::string label)
{
	std::cout << label << "\n---\n";

	C container;
	add<C, E>(container);
	container.clear();

	add<C, E>(container);
	container.clear();

	container.reserve(ELEMENT_COUNT);
	StopWatch w;
	for (int i = 0; i < ELEMENT_COUNT; i++)
		startElement<C, E>(&container, E(i));
	w.pause();
	w.printTime("Add");
	container.clear();

	add<C, E>(container);
	container.clear();

	//iterate<C, E>(container);
	//remove<C, E>(container);

	std::cout << "\n";
}

template<class E>
void profilePointerOverhead(std::string label)
{
	std::cout << label << "\n---\n";

	Array<E> elements;
	elements.reserve(ELEMENT_COUNT);
	for (int i = 0; i < ELEMENT_COUNT; i++)
		elements.add(E(i));
	Array<E*> container;
	container.reserve(ELEMENT_COUNT);

	StopWatch w;
	w.start();
	for (int i = 0; i < ELEMENT_COUNT; i++)
		container.add(&elements[i]);
	w.printTime("Add");

	int checksum = 0;
	w.start();
	for (E* e : container)
		checksum += (*e).data;
	w.pause();
	std::cout << "Iter:\t" << w.timeMs() << " ms\tchecksum: " << checksum << "\n";
}

/// Profile the performance of various containers using element "E".
template<class E>
void profileElement()
{
	profileContaner<Array<E>, E>("Array");
	profileContaner<std::vector<E>, E>("Vector");
	profileContaner<Array<E>, E>("Array");
	profileContaner<std::vector<E>, E>("Vector");

	//profileContaner<PoolArray<E>, E>("PoolArray");
	//profileContaner<StablePoolArray<E>, E>("StablePoolArray");
	//PoolAlloc<E>::Reserve(ELEMENT_COUNT);
	//profileContaner<Array<PoolAlloc<E>>, E>("PoolAlloc");
	//profilePointerOverhead<E>("Pointer Overhead");
}

class IAaa
{
public:
	virtual int& get() = 0;
};

class Aaa : public IAaa
{
public:
	Aaa(int i)
	{
		m_i = i;
	}

	int& get()
	{
		return m_i;
	}

	int& getR()
	{
		return m_i;
	}

private:
	int m_i;
};


class Bbb
{
public:
	Bbb(int i)
	{
		m_i = i;
	}

	int& get()
	{
		return m_i;
	}

private:
	int m_i;
	int m_i2;
};


void virtualOverhead()
{
	StopWatch w;
	int total;

	Array<Aaa> a;
	for (int i = 0; i < ELEMENT_COUNT; i++)
		a << Aaa(i);

	Array<Bbb> b;
	for (int i = 0; i < ELEMENT_COUNT; i++)
		b << Bbb(i);

	{
		Array<IAaa*> pa;
		for (int i = 0; i < ELEMENT_COUNT; i++)
			pa << &a[i];

		total = 0;
		w.start();
		for (int x = 0; x < REPEATS; x++)
		{
			for (auto i : pa)
				total += i->get();
		}
		w.pause();
		w.printTime("Virtual");
		Console::print() << "checksum " << total;
	}

	{
		Array<Aaa*> pa;
		for (int i = 0; i < ELEMENT_COUNT; i++)
			pa << &a[i];

		total = 0;
		w.start();
		for (int x = 0; x < REPEATS; x++)
		{
			for (auto i : pa)
				total += i->get();
		}

		w.pause();
		w.printTime("Direct");
		Console::print() << "checksum " << total;
	}

	{
		Array<Aaa*> pa;
		for (int i = 0; i < ELEMENT_COUNT; i++)
			pa << &a[i];

		total = 0;
		w.start();
		for (int x = 0; x < REPEATS; x++)
		{
			for (auto i : pa)
				total += i->getR();
		}

		w.pause();
		w.printTime("Direct");
		Console::print() << "checksum " << total;
	}

	{
		Array<Bbb*> pb;
		for (int i = 0; i < ELEMENT_COUNT; i++)
			pb << &b[i];

		total = 0;
		w.start();
		for (int x = 0; x < REPEATS; x++)
		{
			for (auto i : pb)
				total += i->get();
		}
		w.pause();
		w.printTime("Normal");
		Console::print() << "checksum " << total;
	}
}

int main()
{
	LeakDetection::enable();
	virtualOverhead();

	//profileElement<Element<4>>();


	//StopWatch w;
	//int total;

	//// ----

	//std::vector<Element<4>> v;
	//v.reserve(ELEMENT_COUNT);

	//w.start();
	//for (int i = 0; i < ELEMENT_COUNT; i++)
	//	v.push_back(i);
	//w.pause();
	//w.printTime("Vector time");

	//total = 0;
	//w.start();
	//for (auto i : v)
	//	total += i.data;
	//w.pause();
	//w.printTime("Vector loop");

	//Console::print() << "checksum " << total;


	//// ----

	//Array<Element<4>> a;
	//a.reserve(ELEMENT_COUNT);

	//w.start();
	//for (int i = 0; i < ELEMENT_COUNT; i++)
	//	a.add(i);
	//w.pause();
	//w.printTime("Arr time");

	//total = 0;
	//w.start();
	//for (auto i : a)
	//	total += i.data;
	//w.pause();
	//w.printTime("Arr loop");

	//Console::print() << "checksum " << total;

	//// ----

	Console::pause();

	return 0;
}