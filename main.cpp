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

//runs a single test case
bool run_test(std::vector<int> test_array, const std::string& test_name, bool random) {  
    int expected = nth_median(test_array); //get expected median using nth_element
    int result = qselect(test_array, random); //get median using with specified pivot selection method
    bool passed = (result == expected); //check if test passed
    
    //print test name and result
    std::cout << "  " << (passed ? "[PASS]" : "[FAIL]") << " " << test_name;
    if (!passed) {
        std::cout << " - Expected: " << expected << ", Got: " << result;
    }
    std::cout << "\n";
    
    return passed; //return whether test passed
}

//runs tests for a given pivot selection method
std::tuple<int, int> tests(bool random, std::mt19937& rng) {

    //print which pivot selection method is being tested
    if (random) {
        std::cout << "Running tests with randomised pivot selection...\n";
    } else {
        std::cout << "Running tests with deterministic pivot selection...\n";
    }
    
    int total_tests = 0; //count total tests
    int passed_tests = 0; //count passed tests

    //function to tally test results
    auto tally = [&](bool passed) {
        ++total_tests;
        if (passed) ++passed_tests;
    };

    //run fixed test cases for edge cases
    tally(run_test(generate_array(1, 100, 1, rng), "Single element array", random));
    tally(run_test(generate_array(1, 100, 2, rng), "Two element array", random));
    tally(run_test(generate_array(1, 100, 3, rng), "Three element array", random));
    tally(run_test({4,4,4,4,4,4,4,4,4}, "Identical elements", random));
    tally(run_test({1,2,3,4,5,6,7,8,9,10}, "Already sorted ascending", random));
    tally(run_test({10,9,8,7,6,5,4,3,2,1}, "Already sorted descending", random));
    tally(run_test(generate_array(1, 1000, 10000, rng), "Large random array (10000 elements)", random));

    return {passed_tests, total_tests}; //return number of passed tests and total tests
}

int main() {
    std::mt19937 rng(23); //random no. generator, fixed seed for reproducibility

    //run tests for both pivot selection methods
    auto [pass_r, total_r] = tests(true, rng);
    auto [pass_d, total_d] = tests(false, rng);

    //print summary of test results
    if (pass_r == total_r) {std::cout << "Success! ";} else std::cout << "Failed! ";
    std::cout << pass_r << " out of " << total_r << " randomised pivot selection tests passed.\n";

    if (pass_d == total_d) {std::cout << "Success! ";} else std::cout << "Failed! ";
    std::cout << pass_d << " out of " << total_d << " deterministic pivot selection tests passed.\n";

}