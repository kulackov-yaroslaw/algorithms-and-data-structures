//
// Created by yaroslaw on 30/05/2020.
//
#include <vector>
#include <cstdint>

void GoDfs(const std::vector<std::vector<int64_t>> &adj_list, std::vector<int64_t> &formation, std::vector<int8_t> & color, int64_t v) {
    color[v] = 1;
    for (auto u : adj_list[v]) {
        if (color[u] == 0) {
            GoDfs(adj_list, formation, color, u);
        }
    }
    formation.push_back(v);
    color[v] = 2;
}

std::vector<int64_t> Dfs(const std::vector<std::vector<int64_t>> &adj_list) {
    const int64_t size = adj_list.size();
    std::vector<int8_t> color(size, 0);
    std::vector<int64_t> formation;
    for (int64_t i = 0; i < size; ++i) {
        if (!color[i]) {
            GoDfs(adj_list, formation, color, i);
        }
    }
    return formation;
}