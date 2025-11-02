#include <iostream>
#include <vector>
#include "median.hpp"

int main() {
    std::vector<int> numbers = {10}; //test array

    int q_median = qselect(numbers); //return median using quick select
    std::cout << "Quick Select: " << q_median << "\n";

    int m_median = mom(numbers); //return median using median of medians
    std::cout << "Median of Medians: " << m_median << "\n";
}