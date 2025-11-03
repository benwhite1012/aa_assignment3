#include <iostream>
#include <vector>
#include <random>
#include "median.hpp"

//generates a random array of n integers between f and l
std::vector<int> generate_array(int f, int l, int n, std::mt19937& rng){
    std::uniform_int_distribution<int> dist(f, l); //defines a range between f and l
    std::vector<int> test;

    //generates n random integers within range and adds to vector
    for (int i = 0; i < n; ++i) {
        test.push_back(dist(rng)); 
    }

    return test; //return generated vector
}

int main() {
    std::mt19937 rng(23); //random no. generator, fixed seed for reproducibility
    std::vector<int> test = generate_array(1, 100, 15, rng); //generate randomised test array

    //print test array
    std::cout << "Test array: [";
    const char* space = "";
    for (int x : test) {
        std::cout << space << x;
        space = ", ";
    }
    std::cout << "]\n";

    int q_median = qselect(test, true); //return median using quick select
    std::cout << "Quick Select: " << q_median << "\n";

    int m_median = mom(test, false); //return median using median of medians
    std::cout << "Median of Medians: " << m_median << "\n";
}