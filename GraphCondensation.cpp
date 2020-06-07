//
// Created by yaroslaw on 30/05/2020.
//

#include <iostream>
#include <vector>
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
    const int64_t size = graph.GetCountVertex();
    std::vector<bool> visited(size, 0);
    std::vector<int64_t> top_sorted;
    for (int64_t i = 0; i < size; ++i) {
        if (!visited[i]) {
            TopSort_DFS(graph, visited, top_sorted, i);
        }
    }
    return{ top_sorted.rbegin(), top_sorted.rend() };
}

struct Components {
    int64_t count_components_;
    std::vector<int64_t> affiliation_;
    Components(int64_t size) : count_components_(0),
                               affiliation_(size){}
};

void FindComponent_DFS(const Graph& graph, std::vector<bool>& visited, Components& components, int64_t root) {
    const int64_t number_component = components.count_components_ - 1;
    components.affiliation_[root] = number_component;
    visited[root] = true;
    const auto& adjasent = graph.GetAdjacentVertex(root);
    for (const auto neighbour : adjasent) {
        if (!visited[neighbour]) {
            FindComponent_DFS(graph, visited, components, neighbour);
        }
    }
}

Components GetComponent_TopSorted(const Graph& graph) {
    const int64_t size = graph.GetCountVertex();
    const std::vector<int64_t> top_sorted = TopSort(graph);
    Graph reverse_graph(size);
    for (int64_t vertex = 0; vertex < size; ++vertex) {
        const auto& adjasent = graph.GetAdjacentVertex(vertex);
        for (const auto neighbour : adjasent) {
            reverse_graph.AddEdge(neighbour, vertex);
        }
    }
    std::vector<bool> visited(size, false);
    Components components(size);
    for (int64_t i = 0; i < size; ++i) {
        if (!visited[top_sorted[i]]) {
            ++components.count_components_;
            FindComponent_DFS(reverse_graph, visited, components, top_sorted[i]);
        }
    }
    return components;
}

int main() {
    int64_t n, m;
    std::cin >> n >> m;
    Graph graph(n);
    for (int64_t i = 0; i < m; ++i) {
        int64_t from, to;
        std::cin >> from >> to;
        graph.AddEdge(--from, --to);
    }
    const Components components = GetComponent_TopSorted(graph);
    std::cout << components.count_components_ << "\n";
    for (int64_t i = 0; i < n; ++i) {
        std::cout << components.affiliation_[i] + 1 << " ";
    }

    return 0;
}