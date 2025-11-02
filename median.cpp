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

    std::mt19937 rng(23); //random no. generator, fixed seed for reproducibility

    //recursive quick sort pattern
    while (true) {
        if (l == r) {return vec[l];} //if only one element remaining in partition, return it

        //pick pivot at random
        std::uniform_int_distribution<std::size_t> dist(l, r); //defines a range within the current partiton (between l and r)
        int p_index = dist(rng); //generates a random pivot index
        int p = vec[p_index]; //retrieves pivot value


        std::swap(vec[p_index], vec[r]); //move pivot to end of partition
        int less_index = l;  //index to track where to place elements less than pivot

        for (int i = l; i < r; ++i) { //start at left most index, loop through until right most index of partition
            if (vec[i] < p) {
                std::swap(vec[i], vec[less_index]); //put current element on the less than p side (left side of partition)
                ++less_index; //increment index
            }
        } 

        std::swap(vec[less_index], vec[r]); //move pivot in between the elements that were less than and greater than it

        //to do:
        //1. since p is now at its correct index we can check where k is in relation to it 
        //2. then update l and r accordingly to continue search on one side, or return p value (if p=k)
        //3. update return statment

    }

    return -1; //placeholder
}

//median of medians
int mom(std::vector<int>& vec) {
    std::ignore = vec;
    return -1; //placeholder
}