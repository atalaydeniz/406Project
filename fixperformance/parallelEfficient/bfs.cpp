/*

Compilation: g++ -fopenmp -o code bfs.cpp
Run: ./code

*/

#include <iostream>
#include <vector>
#include <queue>
#include <omp.h>

void parallelBFS_Efficient(std::vector<std::vector<int>>& graph, int startNode) {
    int numNodes = graph.size();
    std::vector<bool> visited(numNodes, false);
    std::queue<int> bfsQueue;

    visited[startNode] = true;
    bfsQueue.push(startNode);

    while (!bfsQueue.empty()) {
        int levelSize = bfsQueue.size();

        // Process the nodes at the current level in parallel
        #pragma omp parallel for
        for (int i = 0; i < levelSize; i++) {
            int currentNode;
            
            #pragma omp critical
            {
                currentNode = bfsQueue.front();
                bfsQueue.pop();
            }

            // Process the current node
            std::cout << "Visited Node: " << currentNode << std::endl;

            // Explore neighbors of the current node
            for (int j = 0; j < numNodes; j++) {
                if (graph[currentNode][j] && !visited[j]) {
                    #pragma omp critical
                    {
                        visited[j] = true;
                        bfsQueue.push(j);
                    }
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
    parallelBFS_Efficient(graph, startNode);
    double e = omp_get_wtime();
    std::cout << e - s << std::endl;
    return 0;
}
