#include <iostream>
#include <vector>
#include <queue>
#include <omp.h>

void BFS(int start_vertex, const std::vector<std::vector<int>>& adjacency_list, std::vector<bool>& visited) {
    std::queue<int> q;
    q.push(start_vertex);
    visited[start_vertex] = true;

    while (!q.empty()) {
        int current_vertex = q.front();
        q.pop();

        #pragma omp parallel for
        for (int i = 0; i < adjacency_list[current_vertex].size(); ++i) {
            int neighbor = adjacency_list[current_vertex][i];
            if (!visited[neighbor]) {
                visited[neighbor] = true;
                q.push(neighbor);
            }
        }
    }
}

void printBFS(const std::vector<std::vector<int>>& adjacency_list) {
    int num_vertices = adjacency_list.size();
    std::vector<bool> visited(num_vertices, false);

    for (int i = 0; i < num_vertices; ++i) {
        if (!visited[i]) {
            BFS(i, adjacency_list, visited);
        }
    }

    std::cout << "Breadth-First Search traversal: ";
    for (int i = 0; i < num_vertices; ++i) {
        std::cout << i << " ";
    }
    std::cout << std::endl;
}

int main() {
    std::vector<std::vector<int>> adjacency_list = {
        {1, 2},     // Node 0 is connected to nodes 1 and 2
        {2, 3},     // Node 1 is connected to nodes 2 and 3
        {3},        // Node 2 is connected to node 3
        {0, 2}      // Node 3 is connected to nodes 0 and 2
    };

    printBFS(adjacency_list);

    return 0;
}
