#include <iostream>
#include <string>
#include <vector>
#include <set>
#include "List.h"
#include "Random.h"
#include "Console.h"

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
    Bar::foo();
    ae::List<int> list = {1, 2, 3, 4, 5};
    list = list.filter([](int element) {
        return element > 2;
    });
//    list = list.filtert([&](int element) {
//        return element > 2;
//    });
    list = list.filter([](int element) {
        return element > 2;
    });
    ae::List<float> strList = list.mapi<float>([](int element, int index) {
        return element * ae::Random::nextFloat();
    });
//    std::set<int> mapped = list.reduce(std::set<int>(), [](std::set<int> prev, int curr) {
//        prev.insert(curr);
//        return prev;
//    });
    int mapped = list.reduce(0, [](int prev, int curr) {
        return prev + curr;
    });

    int mappede = list.sum();

    for (int element: list) {

    }

    std::string foo = strList.toString();
//    list.toString();
    return 0;
}


void fooasd() {
    std::cout << "Hello";
}
