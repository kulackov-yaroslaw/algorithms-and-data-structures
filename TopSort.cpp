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

bool HasCycle_DFS(const Graph& graph, std::vector<Status>& visited, int64_t root) {
    visited[root] = Status::IN_PROCESS;
    const auto& adjacent = graph.GetAdjacentVertex(root);
    for (const auto& vertex : adjacent) {
        if (visited[vertex] == Status::IN_PROCESS) {
            return true;
        }
        if (visited[vertex] == Status::NOT_VISITED) {
            if (HasCycle_DFS(graph, visited, vertex)){
                return true;
            }
        }
    }
    visited[root] = Status::FIN_VISITED;
    return false;
}

bool HasCycle(const Graph& graph) {
    int64_t size = graph.GetCountVertex();
    std::vector<Status> visited(size, Status::NOT_VISITED);
    for (int64_t i = 0; i < size; ++i) {
        if (visited[i] == Status::NOT_VISITED) {
            if (HasCycle_DFS(graph, visited, i)){
                return true;
            }
        }
    }
    return false;
}

void TopSort_DFS(const Graph& graph, std::vector<bool>& visited, std::vector<int64_t>& top_sorted, int64_t root) {
    visited[root] = true;
    const auto & agjent = graph.GetAdjacentVertex(root);
    for (const auto & vertex : agjent) {
        if (!visited[vertex]) {
            TopSort_DFS(graph, visited, top_sorted, vertex);
        }
    }
    top_sorted.push_back(root);
}

std::vector<int64_t> TopSort(const Graph& graph) {
    if (HasCycle(graph)) {
        return{};
    }
    const int64_t size = graph.GetCountVertex();
    std::vector<bool> visited(size, false);
    std::vector<int64_t> top_sorted;
    for (int64_t i = 0; i < size; ++i) {
        if (!visited[i]) {
            TopSort_DFS(graph, visited, top_sorted, i);
        }
    }
    return{ top_sorted.rbegin(), top_sorted.rend() };
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
    const std::vector<int64_t> top_sort = TopSort(graph);
    if (top_sort.size() == 0) {
        std::cout << -1;
    }
    else {
        for (auto vert : top_sort) {
            std::cout << vert + 1 << " ";
        }
    }
    return 0;
}