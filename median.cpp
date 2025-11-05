// median.cpp
#include <string>
#include <vector>
#include <iostream>
#include <random>
#include <algorithm> //only included for sort() for arrays of size <=5 in deterministic pivot selection
#include "median.hpp"

//problem: find the median (or lower median if even number of elements) of an unsorted array of integers
//solution: without fully sorting the array, use quick select with either a randomised or deterministic pivot selection to find the median efficiently

//function for selecting randomised pivot selection
int random_p(int l, int r, std::mt19937& rng) {
    std::uniform_int_distribution<int> dist(l, r); //defines a range within the current partiton (between l and r)
    return dist(rng); //generates a random pivot index within partition
}

//function for selecting a deterministic pivot selection using median of medians
int deterministic_p(std::vector<int>& v, int l, int r) {
    const int n = r - l + 1; //length of current partition

    //short cut to find the median directly if partition has length <= 5
    if (n <= 5) {
        std::vector<int> small(v.begin() + l, v.begin() + r + 1); //create a vector of current partition
        std::sort(small.begin(), small.end()); //sort vector
        int median_val = small[(n - 1) / 2];  //get median value (lower median if even number of elements)

        //find index of median_val in original vector and return it
        for (int i = l; i <= r; ++i) {
            if (v[i] == median_val) return i; //return index of median
        }
        throw std::logic_error("median of medians not found in small partition (n<=5)"); //should never reach here
    }

    std::vector<int> medians; //vector to hold medians of each group of 5

    //find median of each group of 5
    for (int start = l; start <= r; start += 5) { //loop through current partition in groups of 5
        const int end = std::min(start + 4, r); //end index of current group of 5
        std::vector<int> group(v.begin() + start, v.begin() + end + 1); //create group of up to 5 elements
        std::sort(group.begin(), group.end()); //sort group of 5 to find median
        medians.push_back(group[(int(group.size()) - 1) / 2]); //add lower median to medians vector
    }

    //recursively call mom to find median of medians
    int median_of_medians = mom(medians);

    //find index of median_of_medians in original vector and return it
    for (int i = l; i <= r; ++i) {
        if (v[i] == median_of_medians) { //if median value matched, return index of it
            return i; //return pivot index
        }
    }
    
    throw std::logic_error("median of medians not found in partition"); //should never reach here
}

//quick select
int qselect(std::vector<int>& vec, bool random) {
    //if array is empty throw error
    if (vec.empty()) {
        throw std::invalid_argument("vector must not be empty");
    }

    const int n = vec.size(); //length of vector
    const int k = (n - 1) / 2; //kth element aka the index of the median, if n is even then lower median 

    int l = 0; //left most index
    int r = n - 1; //right most index

    std::mt19937 rng(23); //random no. generator, fixed seed for reproducibility

    //recursive quick sort pattern
    while (true) {
        if (l == r) {return vec[l];} //if only one element remaining in partition, return it

        int p_index; //pivot index
        
        if (random) {
            p_index = random_p(l, r, rng); //get randomised pivot index
        }
        else {
            p_index = deterministic_p(vec, l, r); //get deterministic pivot index
        }

        int p = vec[p_index]; //get pivot value

        std::swap(vec[p_index], vec[r]); //move pivot to end of partition
        int less_index = l;  //index to track where to place elements less than pivot

        for (int i = l; i < r; ++i) { //start at left most index, loop through until right most index of partition
            if (vec[i] < p) {
                std::swap(vec[i], vec[less_index]); //put current element on the less than p side (left side of partition)
                ++less_index; //increment index
            }
        } 

        std::swap(vec[less_index], vec[r]); //move pivot in between the elements that were less than and greater than it

        //since p is now at its correct index we can check where k is in relation to it
        //then update l and r accordingly to continue search on one side, or return p value (if p=k)

        if (k == less_index) {return vec[less_index];} //found median, return the pivot value

        else if (k < less_index) {r = less_index - 1;} //k is on left side of p, update r so we search only the left side of the pivot

        else {l = less_index + 1;} //k is on the right side of p, update l so we only search the right side of the pivot

    }
}
//qselect() with median of medians pivot selection
int mom(std::vector<int>& vec) {
    return qselect(vec, false); //call qselect with deterministic pivot selection
}