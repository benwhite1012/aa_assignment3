// median.cpp
#include <string>
#include <vector>
#include <iostream>
#include <random>
#include "median.hpp"

//helper function for randomised pivot selection
int random_p(int l, int r, std::mt19937& rng) {
    std::uniform_int_distribution<int> dist(l, r); //defines a range within the current partiton (between l and r)
    return dist(rng); //generates a random pivot index within partition
}

//helper function for deterministic pivot selection
int deterministic_p(std::vector<int>& v, int l, int r) {
    auto d = v; //vector copy
    std::ignore = l;
    std::ignore = r;
    return 1; //placeholder, should return a deterministic pivot index using median of medians
}

//quick select
int qselect(std::vector<int>& vec, bool random) {
    //if array is empty throw error
    if (vec.empty()) {
        throw std::invalid_argument("vector must not be empty");
    }

    auto v = vec; //vector copy

    const int n = v.size(); //length of vector
    const int k = (n - 1) / 2; //kth element aka the index of the median, if n is even then lower median 

    int l = 0; //left most index
    int r = n - 1; //right most index

    std::mt19937 rng(23); //random no. generator, fixed seed for reproducibility

    //recursive quick sort pattern
    while (true) {
        if (l == r) {return v[l];} //if only one element remaining in partition, return it

        int p_index = 1; //pivot index
        
        if (random) {
            p_index = random_p(l, r, rng); //get randomised pivot index
        }
        else {
            p_index = deterministic_p(v, l, r); //get deterministic pivot index
        }

        int p = v[p_index]; //get pivot value

        std::swap(v[p_index], v[r]); //move pivot to end of partition
        int less_index = l;  //index to track where to place elements less than pivot

        for (int i = l; i < r; ++i) { //start at left most index, loop through until right most index of partition
            if (v[i] < p) {
                std::swap(v[i], v[less_index]); //put current element on the less than p side (left side of partition)
                ++less_index; //increment index
            }
        } 

        std::swap(v[less_index], v[r]); //move pivot in between the elements that were less than and greater than it

        //since p is now at its correct index we can check where k is in relation to it
        //then update l and r accordingly to continue search on one side, or return p value (if p=k)

        if (k == less_index) {return v[less_index];} //found median, return the pivot value

        else if (k < less_index) {r = less_index - 1;} //k is on left side of p, update r so we search only the left side of the pivot

        else {l = less_index + 1;} //k is on the right side of p, update l so we only search the right side of the pivot

    }
}

//median of medians
int mom(std::vector<int>& vec, bool random) {
    return qselect(vec, random);
}