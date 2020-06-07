//
// Created by yaroslaw on 30/05/2020.
//

#include <iostream>
#include <vector>
#include <cstdint>

const int64_t inf = 30000;

struct Edge {
    int64_t from_, to_;
    int64_t weight_;
    Edge(int64_t from, int64_t to, int64_t weight) :
            from_(from),
            to_(to),
            weight_(weight){}
};

class Graph {
    std::vector<Edge> edges_;
    int64_t count_vertex_;
    int64_t count_edges_;
public:
    Graph(int64_t n) :
            count_vertex_(n),
            count_edges_(0),
            edges_() {}
    void AddEdge(const Edge& edge) {
        edges_.push_back(edge);
    }
    const std::vector<Edge>& GetEdges() const {
        return edges_;
    }
    int64_t GetCountVertex() const {
        return count_vertex_;
    }
    int64_t GetCountEdges() const {
        return count_edges_;
    }
};

std::vector<int64_t> GetDistances(const Graph& graph, int64_t root) {
    const int64_t size = graph.GetCountVertex();
    std::vector<int64_t> distances(size, inf);
    distances[root] = 0;
    const std::vector<Edge>& edges = graph.GetEdges();
    for (int64_t i = 0; i < size; ++i) {
        for (const auto& edge : edges) {
            if (distances[edge.from_] != inf && distances[edge.to_] > distances[edge.from_] + edge.weight_) {
                distances[edge.to_] = distances[edge.from_] + edge.weight_;
            }
        }
    }
    return distances;
}

int main() {
    int64_t n, m;
    std::cin >> n >> m;
    Graph graph(n);
    for (int64_t i = 0; i < m; ++i) {
        int64_t from, to, weight;
        std::cin >> from >> to >> weight;
        graph.AddEdge(Edge(--from, --to, weight));
    }
    std::vector<int64_t> distances = GetDistances(graph, 0);
    for (int64_t i = 0; i < n; ++i) {
        std::cout << distances[i] << " ";
    }
    return 0;
}