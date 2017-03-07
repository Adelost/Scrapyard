#include <iostream>
#include <string>
#include <vector>
#include "Array.h"

void fooasd();

int main() {
    std::string foo = "ads";
    ae::Array<int> bar = {1,2,3,4};
//    ae::Array<int> foo = {1,2,3,4};
//    foo.addAll(&bar[0], bar.count());
    std::vector<int> v = {1,2,3,4};
    auto glambda = []() { return "Lambda"; };
    std::cout << "Hello, World!" << glambda() << std::endl;
    fooasd();
    return 0;
}

void fooasd() {
    std::cout << "Hello";
}
