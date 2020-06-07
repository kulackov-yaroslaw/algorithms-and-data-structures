//
// Created by yaroslaw on 30/05/2020.
//

#include <iostream>
#include <vector>
#include <queue>
#include <cstdint>

class  Graph {
    std::vector<std::vector<int64_t>> adj_list_;
    int64_t count_vertex_;
    int64_t count_edges_;
public:
    Graph(int64_t count_vertex) : count_vertex_(count_vertex),
                                  count_edges_(0),
                                  adj_list_(count_vertex, std::vector<int64_t>()) {}
    void AddEdge(int64_t from, int64_t to) {
        ++count_edges_;
        adj_list_[from].push_back(to);
    }
    const std::vector<int64_t>& GetAdjacentVertex(int64_t vertex) const{
        return adj_list_[vertex];
    }
    int64_t GetCountVertex() const {
        return count_vertex_;
    }
};

std::vector<int64_t> GetShortestPath(const Graph& graph, int64_t from, int64_t to) {
    int64_t size = graph.GetCountVertex();
    std::vector<int64_t> predecessors(size, -1);
    std::vector<bool> visited(size, false);
    std::queue<int64_t> queue_vertex;
    queue_vertex.push(from);
    visited[from] = true;
    while (!queue_vertex.empty()) {
        int current = queue_vertex.front();
        queue_vertex.pop();
        const auto & adjent = graph.GetAdjacentVertex(current);
        for (const auto vert : adjent) {
            if (!visited[vert]) {
                visited[vert] = true;
                predecessors[vert] = current;
                queue_vertex.push(vert);
            }
        }
    }
    if (predecessors[to] == -1) {
        return{};
    }
    std::vector<int64_t> way;
    int64_t vert = to;
    do {
        way.push_back(vert);
        vert = predecessors[vert];
    } while (vert != from);
    way.push_back(from);
    return{ way.rbegin(), way.rend() };
}

int main() {
    int64_t n, m;
    std::cin >> n >> m;
    Graph graph(n);
    int64_t start, finish;
    std::cin >> start >> finish;
    --start;
    --finish;
    for (int64_t i = 0; i < m; ++i) {
        int64_t from, to;
        std::cin >> from >> to;
        --from;
        --to;
        graph.AddEdge(from, to);
        graph.AddEdge(to, from);
    }
    if (start == finish) {
        std::cout << 0 << " " << start + 1;
        return 0;
    }
    const std::vector<int64_t> way = GetShortestPath(graph, start, finish);
    if (way.empty()) {
        std::cout << -1;
    }
    else {
        std::cout << way.size() - 1 << "\n";
        for (auto vert : way) {
            std::cout << vert + 1 << " ";
        }
    }
    return 0;
}