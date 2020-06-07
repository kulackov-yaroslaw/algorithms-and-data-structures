//
// Created by yaroslaw on 30/05/2020.
//

#include <iostream>
#include <vector>
#include <cstdint>
#include <set>

struct Edge {
    int vert1, vert2;
    int weight;
    Edge(int from, int to, int w) : vert1(from), vert2(to), weight(w) {}
};

class Comp {
public:
    bool operator()(const Edge& lhs, const Edge& rhs) {
        return lhs.weight < rhs.weight;
    }
};

class DSU {
    std::vector<int64_t> set_;
    std::vector<int64_t> range_;
    std::vector<int64_t> weight_;
    int64_t count_set_;
public:
    DSU(int64_t size) : count_set_(size), set_(size), range_(size, 1), weight_(size, 0) {
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
    void Union(int64_t first, int64_t second, int64_t weight) {
        int64_t first_set = GetSet(first);
        int64_t second_set = GetSet(second);
        if (first_set != second_set) {
            if (range_[first_set] == range_[second_set]) {
                set_[second_set] = first_set;
                ++range_[first_set];
                weight_[first_set] += weight;
                weight_[first_set] += weight_[second_set];

            }
            else{
                if (range_[first_set] < range_[second_set]) {
                    set_[first_set] = second_set;
                    weight_[second_set] += weight;
                    weight_[second_set] += weight_[first_set];
                }
                else {
                    set_[second_set] = first_set;
                    weight_[first_set] += weight;
                    weight_[first_set] += weight_[second_set];
                }
            }
            --count_set_;
        }
        else {
            weight_[second_set] += weight;
        }
    }
    int64_t GetCountSet() {
        return count_set_;
    }
    int64_t GetWeight(int64_t vertex) {
        return weight_[GetSet(vertex)];
    }
};

int MinOstovWeight(const std::multiset<Edge, Comp>& edges, int n) {
    int res = 0;
    DSU dsu(n);
    for (auto edge : edges) {
        if (dsu.GetSet(edge.vert1) != dsu.GetSet(edge.vert2)) {
            dsu.Union(edge.vert1, edge.vert2, edge.weight);
        }
    }
    return dsu.GetWeight(0);
}

int main() {
    int n, m;
    std::cin >> n >> m;
    std::multiset<Edge, Comp> edges;
    int from, to, weight;
    for (int i = 0; i < m; ++i) {
        std::cin >> from >> to >> weight;
        edges.insert(Edge(--from, --to, weight));
    }
    std::cout << MinOstovWeight(edges, n);
}