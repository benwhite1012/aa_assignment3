// median.cpp
#include <string>
#include <vector>
#include <iostream>
#include "median.hpp"

//quick select
int qselect(std::vector<int>& vec) {
    //if array is empty throw error
    if (vec.empty()) {
        throw std::invalid_argument("vector must not be empty");
    }

    const int n = vec.size(); //length of vector
    const int k = (n - 1) / 2; //kth element aka the index of the median, if n is even then lower median
    std::ignore = k;

    if (n == 1) {
        return vec[k]; //if only one element, return it
    }

    return -1; //placeholder
}

//median of medians
int mom(std::vector<int>& vec) {
    std::ignore = vec;
    return -1; //placeholder
}