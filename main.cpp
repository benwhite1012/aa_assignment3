#include <iostream>
#include "median.hpp"

int main() {
    std::cout << "main() success \n";
    std::string text = "hello";
    if (median(text) == 5) {
        std::cout << "median() success \n";
    } else {
        std::cout << "median() failed \n";
    }
}