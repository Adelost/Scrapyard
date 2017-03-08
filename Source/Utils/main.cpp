#include <iostream>
#include <string>
#include <vector>
#include "List.h"
#include "Random.h"

int main() {
    ae::List<int> list = {1, 2, 3, 4, 5};
    list = list.filter([](int element) {
        return element > 2;
    });
    list = list.filter([](int element, int index) {
        return element > 2;
    });
    list;
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
