#include <iostream>
#include <vector>
#include <random>
#include <string>
#include <algorithm>
#include <tuple>
#include <chrono>
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
bool run_test(std::vector<int> test_array, const std::string& test_name, bool random, bool print) {  
    int expected = nth_median(test_array); //get expected median using nth_element
    int result = qselect(test_array, random); //get median using with specified pivot selection method
    bool passed = (result == expected); //check if test passed
    
    //print test name and result
    if (print) {
        std::cout << "  " << (passed ? "[PASS]" : "[FAIL]") << " " << test_name;
        if (!passed) {
            std::cout << " - Expected: " << expected << ", Got: " << result;
        }
        std::cout << "\n";
    }
    
    return passed; //return whether test passed
}

//runs tests for a given pivot selection method
std::tuple<int, int, double> tests(bool random, std::mt19937& rng) {

    auto start = std::chrono::high_resolution_clock::now(); //start timer

    //print which pivot selection method is being tested
    if (random) {
        std::cout << "Running edge case tests with randomised pivot selection...\n";
    } else {
        std::cout << "Running edge case tests with deterministic pivot selection...\n";
    }
    
    int total_tests = 0; //count total tests
    int passed_tests = 0; //count passed tests

    //function to tally test results
    auto tally = [&](bool passed) {
        ++total_tests;
        if (passed) ++passed_tests;
    };

    //run fixed test cases for edge cases
    tally(run_test(generate_array(1, 100, 1, rng), "Single element array", random, true));
    tally(run_test(generate_array(1, 100, 2, rng), "Two element array", random, true));
    tally(run_test(generate_array(1, 100, 3, rng), "Three element array", random, true));
    tally(run_test({-1,-2,5,-3,-6,-10}, "Negative elements", random, true));
    tally(run_test({4,4,4,4,4,4,4,4,4}, "Identical elements", random, true));
    tally(run_test({1,2,3,4,5,6,7,8,9,10}, "Already sorted ascending", random, true));
    tally(run_test({10,9,8,7,6,5,4,3,2,1}, "Already sorted descending", random, true));
    tally(run_test(generate_array(1, 1000, 10000, rng), "Large random array (10,000 elements)", random, true));

    //run 10,000 random test cases
    for (int i = 0; i < 10000; ++i) {
        int n = rng() % 1000 + 1; //random array size between 1 and 1000
        std::vector<int> test_array = generate_array(-1000, 1000, n, rng); //generate random array up to size n with elements between -1000 and 1000
        tally(run_test(test_array, "random_test", random, false)); //run test without printing individual results
    }

    auto end =  std::chrono::high_resolution_clock::now(); //end timer
    std::chrono::duration<double> elapsed = end - start; //calculate elapsed time

    return {passed_tests, total_tests, elapsed.count()}; //return number of passed tests, total tests and elapsed time
}

int main() {
    std::mt19937 rng(23); //random no. generator, fixed seed for reproducibility

    //run tests for both pivot selection methods
    auto [pass_r, total_r, time_r] = tests(true, rng);
    std::cout << "\n";
    auto [pass_d, total_d, time_d] = tests(false, rng);
    std::cout << "\n";

    //print summary of test results
    if (pass_r == total_r) {std::cout << "Success! ";} else std::cout << "Failed! ";
    std::cout << pass_r << " out of " << total_r << " randomised pivot selection tests passed.\n";

    if (pass_d == total_d) {std::cout << "Success! ";} else std::cout << "Failed! ";
    std::cout << pass_d << " out of " << total_d << " deterministic pivot selection tests passed.\n\n";

    std::cout << "Randomised qselect test time: " << time_r << " seconds\n";
    std::cout << "MoM qselect test time: " << time_d << " seconds\n";

}