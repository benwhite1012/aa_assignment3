// median.cpp
#include <string>
#include <vector>
#include <iostream>
#include <random>
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

    int l = 0; //left most index
    int r = n - 1; //right most index

    if (l == r) {
        return vec[l]; //if only one element, return it
    }

    //pick pivot at random
    std::mt19937 rng(23); //random no. generator, fixed seed for reproducibility
    std::uniform_int_distribution<std::size_t> dist(l, r); //defines a range between l and r
    int p_index = dist(rng); //generates a random pivot index
    int p = vec[p_index]; //retrieves pivot value

    return p; //return the pivot value for testing
}

//median of medians
int mom(std::vector<int>& vec) {
    std::ignore = vec;
    return -1; //placeholder
}