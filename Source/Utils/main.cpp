#include <iostream>
#include <string>
#include <vector>
#include <set>
#include "List.h"
#include "Random.h"
#include "Console.h"
#include "Math.h"

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

    List<int> list = List<int>::range(1000);
    list = list.filter([](int n) {
        return Math::isPrime(n);
    });
    const string& listStr = list.toString();
    List<int> mapped = list.mapi([&](int element, int i) {
        return element * Random::nextFloat() + list[i];
    });
    list.eachi([&](int element, int i) {
        return element * Random::nextFloat() + list[i];
    });
//    set<int> uniques(list.begin(), list.end());
//    uniques = list.reduce<set<int>>(set<int>(), [](set<int> prev, int curr) {
//        prev.insert(curr);
//        return prev;
//    });
//    set<int> uniques;
    list.reduce<set<int>>(set<int>(), [](set<int> prev, int curr) {
        prev.insert(curr);
        return prev;
    });
//    int reduced = list.reduce(0, [](int prev, int curr) {
//        return prev + curr;
//    });

    int summed = list.sum();

    string foo = mapped.toString();
//    list.toString();
    return 0;
}


void fooasd() {
    std::cout << "Hello";
}
