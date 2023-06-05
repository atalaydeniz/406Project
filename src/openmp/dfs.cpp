#include <iostream>
#include <vector>
#include <stack>
#include <omp.h>

void DFS(int start_vertex, const std::vector<std::vector<int>>& adjacency_list, std::vector<bool>& visited) {
    std::stack<int> s;
    s.push(start_vertex);
    visited[start_vertex] = true;

    while (!s.empty()) {
        int current_vertex = s.top();
        s.pop();

        #pragma omp parallel for
        for (int i = 0; i < adjacency_list[current_vertex].size(); ++i) {
            int neighbor = adjacency_list[current_vertex][i];
            if (!visited[neighbor]) {
                visited[neighbor] = true;
                s.push(neighbor);
            }
        }
    }
}

void printDFS(const std::vector<std::vector<int>>& adjacency_list) {
    int num_vertices = adjacency_list.size();
    std::vector<bool> visited(num_vertices, false);

    for (int i = 0; i < num_vertices; ++i) {
        if (!visited[i]) {
            DFS(i, adjacency_list, visited);
        }
    }

    std::cout << "Depth-First Search traversal: ";
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

    printDFS(adjacency_list);

    return 0;
}
