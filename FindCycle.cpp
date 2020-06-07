//
// Created by yaroslaw on 30/05/2020.
//

#include <iostream>
#include <vector>
#include <cstdint>


enum class Status  { NOT_VISITED = 0, IN_PROCESS = 1, FIN_VISITED = 2 };

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

int64_t FindVertexInCycle(const Graph& graph, std::vector<Status>& visited, std::vector<int64_t>& predeccors, int64_t root) {
    visited[root] = Status::IN_PROCESS;
    const auto& adjacent = graph.GetAdjacentVertex(root);
    for (const auto& vertex : adjacent) {
        if (visited[vertex] == Status::IN_PROCESS) {
            predeccors[vertex] = root;
            return root;
        }
        if (visited[vertex] == Status::NOT_VISITED) {
            predeccors[vertex] = root;
            int64_t vertex_in_cycle = FindVertexInCycle(graph, visited, predeccors, vertex);
            if (vertex_in_cycle != -1){
                return vertex_in_cycle;
            }
        }
    }
    visited[root] = Status::FIN_VISITED;
    return -1;
}

std::vector<int64_t> GetCycle(const Graph& graph) {
    const int64_t size = graph.GetCountVertex();
    std::vector<Status> visited(size, Status::NOT_VISITED);
    std::vector<int64_t> predecessors(size, -1);
    int64_t vertex_in_cycle = -1;
    for (int64_t i = 0; i < size; ++i) {
        if (visited[i] == Status::NOT_VISITED) {
            vertex_in_cycle = FindVertexInCycle(graph, visited, predecessors, i);
            if (vertex_in_cycle != -1) {
                break;
            }
        }
    }
    if (vertex_in_cycle != -1) {
        std::vector<int64_t> cycle;
        int64_t cur_vertex = vertex_in_cycle;
        cycle.push_back(vertex_in_cycle);
        while (predecessors[cur_vertex] != vertex_in_cycle) {
            cur_vertex = predecessors[cur_vertex];
            cycle.push_back(cur_vertex);
        }
        return{ cycle.rbegin(), cycle.rend() };
    }
    return{};
}

int main() {
    int64_t n, m;
    std::cin >> n >> m;
    Graph graph(n);
    for (int64_t i = 0; i < m; ++i) {
        int64_t from, to;
        std::cin >> from >> to;
        --from;
        --to;
        graph.AddEdge(from, to);

    }
    const std::vector<int64_t> cycle = GetCycle(graph);
    if (cycle.empty()) {
        std::cout << "NO";
    }
    else {
        std::cout << "YES" << "\n";
        for (auto vert : cycle) {
            std::cout << vert + 1 << " ";
        }
    }
    return 0;
}