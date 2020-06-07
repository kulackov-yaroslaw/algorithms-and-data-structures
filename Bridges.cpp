//
// Created by yaroslaw on 30/05/2020.
//

#include <iostream>
#include <cstdint>
#include <vector>
#include <algorithm>
#include <set>
#include <map>

class AdjGraph{
    std::vector<std::vector<uint64_t>> adj_list_;
    uint64_t count_vertex_, count_edges_;
public:
    AdjGraph(const uint64_t count_vertex){
        count_vertex_ = count_vertex;
        count_edges_ = 0;
        adj_list_.resize(count_vertex, std::vector<uint64_t>());
    }
    void AddEdge(const uint64_t from, const uint64_t to){
        adj_list_[from].push_back(to);
        count_edges_++;
    }
    std::vector<uint64_t> GetAdgacentVertex(const uint64_t vertex) const {
        return adj_list_[vertex];
    }
    uint64_t GetCountVertex()const{
        return count_vertex_;
    }
};

struct Edge {
    uint64_t from, to;
    Edge(int vertex_from, uint64_t vertex_to) :from(vertex_from), to(vertex_to) {}
    bool operator<(const Edge & rhs) const{
        if (from == rhs.from) {
            return to < rhs.to;
        }
        else {
            return from < rhs.from;
        }
    }
};

struct Status {
    std::vector<bool> visited;
    std::vector<uint64_t> time_in;
    std::vector<uint64_t> time_up;
    std::vector<bool> multiple_edge;
    uint64_t time;
    Status(uint64_t n, uint64_t m) : visited(n, false),
                                     multiple_edge(m, false),
                                     time_in(n),
                                     time_up(n),
                                     time(0){}

};

void GetBridgeDfs(const AdjGraph &graph,
                  Status & status,
                  const std::map<Edge, uint64_t> & map_edges,
                  std::set<uint64_t> & numbers_bridge_edges,
                  uint64_t root, uint64_t ancestor) {
    status.visited[root] = true;
    status.time_in[root] = status.time;
    status.time_up[root] = status.time;
    status.time++;
    for (auto neighbor : graph.GetAdgacentVertex(root)) {
        if (neighbor == ancestor) continue;
        if (!status.visited[neighbor]) {
            GetBridgeDfs(graph, status, map_edges, numbers_bridge_edges, neighbor, root);
            status.time_up[root] = std::min(status.time_up[root], status.time_up[neighbor]);
            if (status.time_up[neighbor] > status.time_in[root] &&
                !status.multiple_edge[map_edges.find(Edge(root, neighbor))->second]) {
                numbers_bridge_edges.insert(map_edges.find(Edge(root, neighbor))->second);
            }
        }
        else {
            status.time_up[root] = std::min(status.time_up[root], status.time_in[neighbor]);
        }
    }
}


std::set<uint64_t> GetBridges(const AdjGraph &graph, const std::map<Edge, uint64_t> & map_edges, Status & status) {
    const uint64_t size = graph.GetCountVertex();
    std::set<uint64_t> numbers_bridge_edges;

    for (uint64_t root = 0; root < size; ++root) {
        if (!status.visited[root]) {
            GetBridgeDfs(graph, status, map_edges, numbers_bridge_edges, root, -1);
        }
    }

    return numbers_bridge_edges;
}

int main() {
    uint64_t n, m;
    std::cin >> n >> m;
    std::map<Edge, uint64_t> map_edges;
    AdjGraph graph(n);
    Status status(n, m);
    for (uint64_t i = 0; i < m; ++i) {
        uint64_t from, to;
        std::cin >> from >> to;
        --from;
        --to;
        if (map_edges.find(Edge(from, to)) != map_edges.end()) {
            status.multiple_edge[map_edges.find(Edge(from, to))->second] = true;
            continue;
        }
        if (map_edges.find(Edge(to, from)) != map_edges.end()) {
            status.multiple_edge[map_edges.find(Edge(to, from))->second] = true;
            continue;
        }
        map_edges[Edge(from, to)] = i;
        map_edges[Edge(to, from)] = i;
        graph.AddEdge(from, to);
        graph.AddEdge(to, from);
    }
    const std::set<uint64_t> numbers_bridge_edges = GetBridges(graph, map_edges, status);
    std::cout << numbers_bridge_edges.size() << "\n";
    for (auto bridge : numbers_bridge_edges) {
        std::cout << bridge + 1 << " ";
    }
    return 0;
}