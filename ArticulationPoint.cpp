//
// Created by yaroslaw on 30/05/2020.
//

#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdint>
#include <set>

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

struct Status {
    int time;
    std::vector<int64_t> time_in;
    std::vector<int64_t> time_up;
    std::vector<bool> visited;
    std::set<int64_t> articulation_points;
    Status(int64_t n) :
            time(0),
            time_in(n),
            time_up(n),
            visited(n, false)
    {}
};

void DFS(const Graph& graph, Status& status, int64_t root, bool is_root = false) {
    status.time_in[root] = status.time;
    status.time_up[root] = status.time;
    status.time++;
    status.visited[root] = true;
    const auto adjasent = graph.GetAdjacentVertex(root);
    int64_t count_children_trees = 0;
    for (const auto& neighbor : adjasent) {
        if (!status.visited[neighbor]) {
            ++count_children_trees;
            DFS(graph, status, neighbor);
            status.time_up[root] = std::min(status.time_up[neighbor], status.time_up[root]);
            if (status.time_up[neighbor] >= status.time_in[root] && !is_root) {
                status.articulation_points.insert(root);
            }
        }
        else {
            status.time_up[root] = std::min(status.time_in[neighbor], status.time_up[root]);

        }
    }
    if (is_root && count_children_trees >= 2) {
        status.articulation_points.insert(root);
    }

}

std::set<int64_t> GetArticulationPoints(const Graph& graph) {
    const int64_t size = graph.GetCountVertex();
    Status status(size);
    for (int i = 0; i < size; ++i) {
        if (!status.visited[i]) {
            DFS(graph, status, i, true);
        }
    }
    return status.articulation_points;
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
        graph.AddEdge(to, from);

    }
    const std::set<int64_t> articulation_points = GetArticulationPoints(graph);
    std::cout << articulation_points.size() << "\n";
    for (auto point : articulation_points) {
        std::cout << point + 1 << "\n";
    }
    return 0;
}