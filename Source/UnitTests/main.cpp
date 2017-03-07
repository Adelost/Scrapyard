#include <Utils/Console.h>
#include <boost/any.hpp>
using namespace ae;
using namespace std;
#include <vector>

class Person
{
public:
	Person(string name)
	{
		m_name = new string(name);
	}
	~Person()
	{
		delete m_name;
	}
	Person(Person&& other)
	{
		*this = other;

	}
	void printName()
	{
		cout << *m_name;
	}
	string* name() const
	{
		return m_name;
	}

private:
	string* m_name;
};

class A
{
public:
	~A()
	{
		print() << "A destroyed";
	}
};
class B : public A
{
public:
	~B()
	{
		print() << "B destroyed";
	}
};

////User always calls this method, general method for distance()
//
//// User needs to satisfy the following 2 criteria:
//// For random access iterator, second iterator position must come
//// after first iterator position/
//// For all other kind of iterator, second iterator must be reachable from first iterator
//// Both of the iterator must refer to the same container, otherwise result is undefined
//template <typename Iterator>
//typename std::iterator_traits<Iterator>::difference_type
//distance(Iterator pos1, Iterator pos2)
//{
//	return distance(pos1, pos2,
//	                std::iterator_traits<Iterator>
//	                ::iterator_category());
//}
//
////Core implementation ..... distance() for random access iterators
//template <typename RandomAccessIterator>
//typename std::iterator_traits<RandomAccessIterator>::difference_type
//// Note the return type above, it solely depends on Iterators declared typedefs,
//// no so called INT/SHORT here
//distance(RandomAccessIterator first_position, RandomAccessIterator second_position,
//         std::random_access_iterator_tag)
//{
//	return second_position - first_position;
//}
//
//
////distance() for input, forward, and bidirectional iterators
//// Keep in mind that here we are using only Input iterator tags, so
//// forward and bidirectional iterator will also be in this bucket, because we
//// used Inheritance while declare forward and bidirectional iterator tags.
//
//template <typename InputIterator>
//typename std::iterator_traits<lnputIterator>::difference_type
//// Note the return type here, truly generic
//distance(Inputlterator first_position, InputIterator second_position,
//         std::input_iterator_tag)
//{
//	// note the type of the temp variable here, truly generic
//	typename std::iterator_traits<lnputIterator>::difference_type diff;
//	for (diff = 0; first_position != second_position; ++first_position, ++diff)
//	{
//		;
//	}
//	return diff;
//}


template <class T>
void f(T var) {
    bool advanced = policy_trait<T>::advanced;
    if ( advanced )
        cout << "Do it fancy!" << endl;
    else
        cout << "KISS." << endl;
}



#include <initializer_list>

#include <initializer_list>
int main()
{
	std::vector<int> v = {0, 1, 2, 3, 4};
	std::vector<int> v = {0, 1, 2, 3, 4};

	//Array<int> b = {0, 1, 2, 3, 4};
	Array<int> a = "fo";
	a = "ar";
	a = {0, 1, 2, 3, 4};
	//a.addAll(a);

	/*for(auto i : a)
	{
	}*/



	//v._Grow_to(41);


	a << 0 << 1 << 2;

	boost::any x;
	x = "hello";
	print() << boost::any_cast<const char*>(x);

	Console::pause();
}

////#include "TestUtils.h"
////#include "TestSimulation.h"
//
//#include <Utils/Console.h>
//#include <Utils/LeakDetection.h>
////#include <Utils/UnitTest.h>
////
//#include <utility>
//#include <iostream>
////#include <vector>
////#include <array>
////#include <Utils/Forward.h>
//
////template <class... Args>
////void place(Args&& ... args)
////{
////	print() << "hell" ;
////
//////	Fuu(args...);
////}
//
//using namespace ae;
//
//
//
//
//// Quick overview
//
//void test()
//{
//
//}
//
//int main()
//{
//	LeakDetection::enable();
//	//UnitTests::run();
//
//	Array<int> a;
//	a << 0 << 1 << 2;
//	std::cout << "foo";
//
//
//	/*std::vector<int> v;
//
//
//	{
//
//		{
//			Array<int> b(std::move(a));
//			print() << b[0];
//		}
//
//	}*/
//
//	//f(Array<int>());
//
//	//std::array<int, 5> arr;
//
//
//	//print() << "Array: " << sizeof(ar);
//	//print() << "Vector: " << sizeof(myvector);
//	//myvector.
//	//auto it = myvector.emplace ( myvector.begin()+1, 100 );
//
//
//	//place(0, 1);
//
//
//	//
//
//	Console::pressToContinue();
//	return 0;
//}
//
////#include <Utils/tests.h>
////#include <Utils/Console.h>
////#include <Utils/LeakDetection.h>
////
////int main()
////{
////	using namespace ae;
////	LeakDetection::enable();
////	runTests();
////	Console::pressToContinue();
////	return 0;
////}