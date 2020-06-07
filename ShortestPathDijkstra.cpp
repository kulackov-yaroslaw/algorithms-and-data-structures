//
// Created by yaroslaw on 30/05/2020.
//

#include <iostream>
#include <cstdint>
#include <vector>
#include <algorithm>
#include <set>
#include <queue>
#include <map>

const int64_t inf = 2009000999;

struct Edge {
    int64_t from_, to_;
    int64_t weight_;
    Edge(int64_t from, int64_t to, int64_t weight) :
            from_(from),
            to_(to),
            weight_(weight){}
};
class Graph {
    std::vector<std::vector<Edge>> adj_list_;
    int64_t count_vertex_;
    int64_t count_edges_;
public:
    Graph(int64_t n) : count_vertex_(n),
                       count_edges_(0),
                       adj_list_(n, std::vector<Edge>()){}
    void AddEdge(Edge edge) {
        adj_list_[edge.from_].push_back(edge);
        count_edges_++;
    }
    std::vector<Edge> GetAdjacentEdges(int64_t vertex) const {
        return adj_list_[vertex];
    }
    int64_t GetCountVertex() const{
        return count_vertex_;
    }
};

struct Data {
    int64_t num_, dist_;
    Data(int64_t num, int64_t dist) : num_(num), dist_(dist){}
    bool operator<(const Data& rhs) const {
        return dist_ > rhs.dist_;
    }
};

std::vector<int64_t> GetDistances(const Graph& graph, int64_t root) {
    const int64_t size = graph.GetCountVertex();
    std::vector <bool> visited(size, false);
    std::vector<int64_t> distances(size, inf);
    std::priority_queue<Data> heap;
    distances[root] = 0;
    heap.push(Data(root, 0));

    while (true) {
        while (!heap.empty() && visited[heap.top().num_]) {
            heap.pop();
        }
        if (heap.empty()) {
            break;
        }
        const int64_t curVertex = heap.top().num_;
        visited[curVertex] = true;
        const auto& adjacentVertices = graph.GetAdjacentEdges(curVertex);
        for (const auto& edge : adjacentVertices) {
            if (distances[edge.from_] + edge.weight_ < distances[edge.to_]) {
                distances[edge.to_] = distances[edge.from_] + edge.weight_;
                heap.push(Data(edge.to_, distances[edge.to_]));
            }
        }
    }
    return distances;
}

void ProcessGraph() {
    int64_t n, m;
    std::cin >> n >> m;
    Graph graph(n);
    for (int64_t i = 0; i < m; ++i) {
        int from, to, weight;
        std::cin >> from >> to >> weight;
        graph.AddEdge(Edge(from, to, weight));
        graph.AddEdge(Edge(to, from, weight));

    }
    int64_t root;
    std::cin >> root;
    std::vector<int64_t> distances = GetDistances(graph, root);
    for (auto dist : distances) {
        std::cout << dist << " ";
    }
    std::cout << "\n";
}

int main() {
    int64_t num;
    std::cin >> num;
    for (int64_t i = 0; i < num; ++i) {
        ProcessGraph();
    }
    return 0;
}