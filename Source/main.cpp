#include <iostream>
#include <string>
#include <vector>
#include <set>
#include "Utils/List.h"
#include "Utils/Random.h"
#include "Utils/Console.h"
#include "Utils/Math.h"
#include "Utils/Algorithm.h"

class Bar {
public:
    class Car {
    public:
        Car() {
            std::cout << "Foo";
        }
    };

    static Car foo() {
        return Car();
    }
};


int main() {
    using namespace std;
    using namespace ae;


//    List<int> list = List<int>::range(0, 10, 1);
    List<double> list = List<double>::range(0, 1, 0.01);
    list.shuffle();
    list.sort();
    std::string str = list.toString();
    return 0;

//    list = list.filter([](int n) {
//        return Math::isPrime(n);
//    });
//    const string& listStr = list.toString();
//    List<int> mapped = list.mapi([&](int element, int i) {
//        return element * Random::nextFloat() + list[i];
//    });
//    list.eachi([&](int element, int i) {
//        return element * Random::nextFloat() + list[i];
//    });
//    list.reduce<set<int>>(set<int>(), [](set<int> prev, int curr) {
//        prev.insert(curr);
//        return prev;
//    });
//
//    int summed = list.sum();

//    string foo = mapped.toString();
//    list.toString();
    return 0;
}


void fooasd() {
    std::cout << "Hello";
}
