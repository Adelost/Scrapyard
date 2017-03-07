#include <iostream>
#include <string>
#include <vector>
#include "List.h"


std::string join(ae::List<int> list, std::string separator = ",") {
    if (list.isEmpty()) {
        return "";
    }
    std::string joined = "";
    for (int i = 0; i < list.size() - 1; i += 1) {
        joined += std::to_string(list[i]);
        joined += separator;
    }
    joined += std::to_string(list.last());
    return joined;
}

std::string toString(ae::List<int> list) {
    return "[" + join(list, ", ") + "]";
}


int main() {
    ae::List<int> a = {1, 2, 3, 4, 5};
    std::string foo = join(a);
    return 0;
}


void fooasd() {
    std::cout << "Hello";
}
