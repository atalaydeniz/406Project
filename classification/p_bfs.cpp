/*

Classified as "Inefficient Parallelization" --> "Underparallelization"
              "Micro-Architectural" --> "Data Locality"

*/

#include <iostream>
#include <vector>
#include <queue>
#include <omp.h>

void parallelBFS_Inefficient(std::vector<std::vector<int>>& graph, int startNode) {
    int numNodes = graph.size();
    std::vector<bool> visited(numNodes, false);
    std::queue<int> bfsQueue;

    visited[startNode] = true;
    bfsQueue.push(startNode);

    while (!bfsQueue.empty()) {
        int currentNode = bfsQueue.front();
        bfsQueue.pop();

        // Process the current node
        std::cout << "Visited Node: " << currentNode << std::endl;

        // Explore neighbors of the current node in parallel
        #pragma omp parallel for
        for (int i = 0; i < numNodes; i++) {
            if (graph[currentNode][i] && !visited[i]) {
                #pragma omp critical
                {
                    visited[i] = true;
                    bfsQueue.push(i);
                }
            }
        }
    }
}

int main() {
    std::vector<std::vector<int>> graph = {
        {1,0,0,0,0,0,1,1,1,1,0,1,1,0,1,0,1,1,1,1,1,1,0,0,1},
        {1,0,0,1,1,1,1,0,0,1,0,0,0,1,1,0,1,0,0,1,1,0,0,0,0},
        {0,0,0,0,0,1,1,0,0,0,0,0,1,0,1,0,0,0,0,0,1,0,0,0,0},
        {1,1,0,1,0,1,0,1,1,0,1,0,1,0,0,1,1,0,1,0,0,1,0,1,0},
        {1,1,0,1,1,1,1,0,1,0,1,1,1,1,1,0,0,1,1,0,1,0,1,1,1},
        {0,1,0,0,0,1,0,0,0,1,0,1,0,1,1,0,1,1,1,1,1,1,1,1,1},
        {0,0,0,0,0,0,0,0,1,0,0,0,0,1,0,1,0,0,1,0,0,0,1,1,0},
        {0,1,1,0,0,1,0,0,0,0,0,1,0,1,1,1,1,0,0,1,1,0,1,0,1},
        {0,0,1,1,1,1,0,1,1,1,0,0,0,0,1,0,1,0,0,0,0,0,0,0,0},
        {1,1,0,0,0,1,0,1,1,0,1,1,0,0,1,0,0,1,0,1,0,1,0,0,1},
        {0,1,0,0,1,0,1,1,1,1,1,1,1,1,1,0,1,1,0,1,0,1,0,1,1},
        {1,0,1,0,1,1,0,0,0,0,1,0,1,1,1,1,0,0,0,1,1,0,0,1,1},
        {1,0,0,0,1,1,1,1,1,0,1,0,1,0,0,0,1,0,0,0,0,0,0,1,1},
        {1,1,1,0,1,1,0,1,1,1,0,1,0,1,0,1,0,1,0,0,1,0,0,0,1},
        {1,1,0,0,0,0,1,1,0,1,0,0,1,0,0,0,1,0,1,0,1,1,1,0,1},
        {1,0,1,1,0,1,0,0,0,1,0,0,1,1,0,1,1,1,0,0,1,1,1,0,0},
        {0,1,1,0,1,1,0,0,1,0,0,0,0,1,1,1,0,0,0,0,0,0,0,1,1},
        {1,1,1,1,1,0,0,1,0,0,0,0,0,1,0,0,0,1,1,0,0,0,1,1,1},
        {0,0,1,1,0,0,1,1,0,0,1,1,0,1,1,1,1,1,0,1,1,0,1,1,0},
        {1,1,0,0,0,0,0,1,1,1,1,1,1,1,1,1,0,1,0,1,1,1,1,0,0},
        {0,1,0,0,1,1,1,1,1,1,0,1,1,1,0,0,1,1,0,0,1,1,1,0,1},
        {1,0,0,1,1,0,0,1,0,0,0,0,0,0,0,0,1,0,0,0,1,0,1,0,1},
        {1,0,1,0,0,0,0,1,0,1,1,0,1,0,1,0,1,1,1,1,1,0,1,1,1},
        {0,1,0,0,1,0,0,0,1,1,0,0,1,0,1,1,0,0,0,0,0,0,1,0,1},
        {1,1,1,1,1,1,1,1,0,1,1,0,1,0,0,1,1,1,1,1,0,1,1,0,0}

    };

    int startNode = 0;

    double s = omp_get_wtime();    
    parallelBFS_Inefficient(graph, startNode);
    double e = omp_get_wtime();
    std::cout << e - s << std::endl;
    return 0;
}
