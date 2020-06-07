//
// Created by yaroslaw on 30/05/2020.
//

#include <iostream>
#include <vector>
#include <cstdint>

const int64_t inf = 100000;

struct Edge {
    int64_t from_, to_;
    int64_t weight_;
    Edge(int64_t from, int64_t to, int64_t weight) :
            from_(from),
            to_(to),
            weight_(weight){}
};

class Graph {
    std::vector<std::vector<int64_t>> matrix_;
    int64_t count_vertex_;
    int64_t count_edges_;
public:
    Graph(int64_t n) :
            count_vertex_(n),
            count_edges_(0),
            matrix_(n, std::vector<int64_t>(n)) {}
    void AddEdge(const Edge& edge) {
        matrix_[edge.from_][edge.to_] = edge.weight_;
        ++count_edges_;
    }
    const std::vector<int64_t>& VertexDistances(int64_t vertex) const {
        return matrix_[vertex];
    }
    int64_t GetCountVertex() const {
        return count_vertex_;
    }
    int64_t GetCountEdges() const {
        return count_edges_;
    }
};

std::vector<int64_t> FindCycle(const Graph& graph) {
    const int64_t size = graph.GetCountVertex();
    std::vector<int64_t> predecessors(size);
    std::vector<int64_t> distances(size, 0);
    int vertex_reacheble_from_cycle;
    for (int64_t i = 0; i < size; ++i) {
        vertex_reacheble_from_cycle = -1;
        for (int64_t root = 0; root < size; ++root) {
            const std::vector<int64_t>& vertex_distances = graph.VertexDistances(root);
            for (int64_t neighbour = 0; neighbour < size; ++neighbour) {
                if (distances[root] != inf && vertex_distances[neighbour] != inf && distances[neighbour] > distances[root] + vertex_distances[neighbour]) {
                    distances[neighbour] = distances[root] + vertex_distances[neighbour];
                    predecessors[neighbour] = root;
                    vertex_reacheble_from_cycle = neighbour;
                }
            }
        }
    }
    if (vertex_reacheble_from_cycle == -1) {
        return{};
    }
    for (int64_t i = 0; i < size; ++i) {
        vertex_reacheble_from_cycle = predecessors[vertex_reacheble_from_cycle];
    }
    int64_t vertex_in_cycle = vertex_reacheble_from_cycle;
    std::vector<int64_t> cycle;
    int64_t temp_vertex = vertex_in_cycle;
    do {
        cycle.push_back(temp_vertex);
        temp_vertex = predecessors[temp_vertex];
    } while (temp_vertex != vertex_in_cycle);
    cycle.push_back(temp_vertex);
    return{ cycle.rbegin(), cycle.rend() };
}

int main() {
    int64_t n;
    std::cin >> n;
    Graph graph(n);
    for (int64_t i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            int64_t from, to, weight;
            std::cin >> weight;
            graph.AddEdge(Edge(i, j, weight));
        }
    }
    std::vector<int64_t> cycle = FindCycle(graph);
    int64_t count_cycle_vertex_count = cycle.size();
    if (count_cycle_vertex_count == 0) {
        std::cout << "NO";
    }
    else{
        std::cout << "YES\n" << count_cycle_vertex_count << "\n";
        for (int64_t i = 0; i < count_cycle_vertex_count; ++i) {
            std::cout << cycle[i] + 1 << " ";
        }
    }
    return 0;
}