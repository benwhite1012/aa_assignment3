#include <iostream>
#include <vector>
#include <random>
#include <string>
#include <algorithm>
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

//turn test vector into string for printing
std::string vec_str(const std::vector<int>& vec) {
    std::string result = "[";
    const char* space = "";
    for (int x : vec) {
        result += space + std::to_string(x);
        space = ", ";
    }
    result += "]";
    return result; //return string representation of vector
}

//finds median using native nth_element for test validation
int nth_median(std::vector<int> vector) {
    const std::size_t k = (vector.size() - 1) / 2; //kth element aka the index of the median, if n is even then lower median
    std::nth_element(vector.begin(), vector.begin() + k, vector.end()); //partially sorts v so kth is at correct index
    return vector[k]; //return median or lower median value
}

int main() {
    std::mt19937 rng(23); //random no. generator, fixed seed for reproducibility
    std::vector<int> test = generate_array(1, 100, 15, rng); //generate randomised test array

    int median = nth_median(test); //find median of test array using native nth_element
 
    std::cout << "Test array: " << vec_str(test) << "\n"; //print test array

    int q_median = qselect(test, true); //return median using quick select
    int m_median = mom(test, false); //return median using median of medians
    
    std::cout << ((q_median == median) ? "Success! " : "Failed! ");     
    std::cout << "Expected: " << median << " Quick Select: " << q_median << "\n";

    std::cout << ((m_median == median) ? "Success! " : "Failed! ");
    std::cout << "Expected: " << median << " Median of Medians: " << m_median << "\n";
}