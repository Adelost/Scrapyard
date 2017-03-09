#include <iostream>
#include <string>
#include <vector>
#include "List.h"
#include "Random.h"
#include "Console.h"

class Bar {
public:
    class Car {
    public:
        Car(){
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

//    list = list.each([](int element) {
//    });
    ae::write() << "1" << 2 << 3 << 4;
    list = list.filter([](int element, int index) {
        return element > 2;
    });
    ae::List<float> strList = list.map<float>([](int element) {
        return element * ae::Random::nextFloat();
    });

    std::string foo = strList.toString();
//    list.toString();
    return 0;
}


void fooasd() {
    std::cout << "Hello";
}
