//
// Created by yaroslaw on 30/05/2020.
//

#include <iostream>
#include <stdint.h>
#include <vector>
#include <algorithm>
#include <set>
#include <map>

const int64_t inf = 10000000000;


class Graph {
    std::vector<std::vector<int64_t>> matrix_;
    int64_t count_vertex_;
public:
    Graph(int64_t n) : count_vertex_(n),
                       matrix_(n, std::vector<int64_t>(n)){}
    void AddEdge(int64_t from, int64_t to, int64_t weight) {
        matrix_[from][to] = weight;
    }
    std::vector<std::vector<int64_t>> GetMatrix() const {
        return matrix_;
    }
    int64_t GetCountVertex() const{
        return count_vertex_;
    }
};

int64_t GetMinPath(const Graph& graph, int64_t from, int64_t to) {
    std::vector<std::vector<int64_t>> matrix = graph.GetMatrix();
    const int64_t size = graph.GetCountVertex();
    for (int64_t k = 0; k < size; ++k) {
        for (int64_t i = 0; i < size; ++i) {
            for (int64_t j = 0; j < size; ++j) {
                if (matrix[i][j] > matrix[i][k] + matrix[k][j]) {
                    matrix[i][j] = matrix[i][k] + matrix[k][j];
                }
            }
        }
    }
    if (matrix[from][to] == inf) {
        return -1;
    }
    return matrix[from][to];
}

int main() {
    int64_t n, s, t;
    std::cin >> n >> s >> t;
    Graph graph(n);
    for (int64_t i = 0; i < n; ++i){
        for (int64_t j = 0; j < n; ++j) {
            int64_t weight;
            std::cin >> weight;
            if (weight == -1) {
                weight = inf;
            }
            graph.AddEdge(i, j, weight);
        }
    }
    std::cout << GetMinPath(graph, --s, --t);
    return 0;
}