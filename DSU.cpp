//
// Created by yaroslaw on 30/05/2020.
//

#include <iostream>
#include <vector>
#include <cstdint>

class DSU {
    std::vector<int64_t> set_;
    std::vector<int64_t> range_;
    int count_set_;
public:
    DSU(int64_t size) : count_set_(size), set_(size), range_(size, 1) {
        for (int64_t i = 0; i < size; ++i) {
            set_[i] = i;
        }
    }
    int64_t GetSet(int64_t vertex) {
        if (set_[vertex] == vertex) {
            return vertex;
        }
        int64_t set = GetSet(set_[vertex]);
        set_[vertex] = set;
        return set;
    }
    void Union(int64_t first, int64_t second) {
        int64_t first_set = GetSet(first);
        int64_t second_set = GetSet(second);
        if (first_set != second_set) {
            if (range_[first_set] == range_[second_set]) {
                set_[second_set] = first_set;
                ++range_[first_set];
            }
            else{
                if (range_[first_set] < range_[second_set]) {
                    set_[first_set] = second_set;
                }
                else {
                    set_[second_set] = first_set;
                }
            }
            --count_set_;
        }
    }
    int64_t GetCountSet() {
        return count_set_;
    }
};