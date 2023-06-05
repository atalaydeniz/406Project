#include <iostream>
#include <vector>
#include <queue>
#include <omp.h>

void explore(int vertex, const std::vector<std::vector<int>>& adjacency_list, std::vector<bool>& visited) {
    visited[vertex] = true;
    #pragma omp parallel for
    for (int i = 0; i < adjacency_list[vertex].size(); ++i) {
        int neighbor = adjacency_list[vertex][i];
        if (!visited[neighbor]) {
            explore(neighbor, adjacency_list, visited);
        }
    }
}

bool isReachable(int start_vertex, int target_vertex, const std::vector<std::vector<int>>& adjacency_list) {
    int num_vertices = adjacency_list.size();
    std::vector<bool> visited(num_vertices, false);
    explore(start_vertex, adjacency_list, visited);

    return visited[target_vertex];
}

int main() {
    std::vector<std::vector<int>> adjacency_list = {
        {1, 2},     // Node 0 is connected to nodes 1 and 2
        {2, 3},     // Node 1 is connected to nodes 2 and 3
        {3},        // Node 2 is connected to node 3
        {0, 2}      // Node 3 is connected to nodes 0 and 2
    };

    int start_vertex = 0;
    int target_vertex = 3;

    bool reachable = isReachable(start_vertex, target_vertex, adjacency_list);

    if (reachable)
        std::cout << "There is a path from vertex " << start_vertex << " to vertex " << target_vertex << std::endl;
    else
        std::cout << "There is no path from vertex " << start_vertex << " to vertex " << target_vertex << std::endl;

    return 0;
}
