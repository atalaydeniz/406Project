/*

Classified as "Inefficient Parallelization" --> "Small Parallel Region"

*/

#include <iostream>
#include <vector>
#include <omp.h>

bool isReachable(const std::vector<std::vector<int>>& graph, int source, int destination) {
    int numVertices = graph.size();
    std::vector<bool> visited(numVertices, false);
    visited[source] = true;

    bool updated = true;
    while (updated) {
        updated = false;

        for (int i = 0; i < numVertices; ++i) {
            if (visited[i]) {
                #pragma omp parallel for
                for (int j = 0; j < numVertices; ++j) {
                    if (graph[i][j] && !visited[j]) {
                        #pragma omp critical
                        {
                            if (!visited[j]) {
                                visited[j] = true;
                                updated = true;
                            }
                        }
                    }
                }
            }
        }
    }

    return visited[destination];
}

int main() {
    std::vector<std::vector<int>> graph = {};
    for (int i = 0; i < 1000; i++) {
        std::vector<int> c = {};
        for (int j = 0; j < 1000; j++) {
            srand((unsigned) time(NULL));
            int random = rand();
            random = random % 2;
            c.push_back(random);
        }
        graph.push_back(c);
    }

    int source = 0;
    int destination = 3;
    double s = omp_get_wtime();
    bool reachable = isReachable(graph, source, destination);
    double e = omp_get_wtime();
    std::cout << e - s << std::endl;
    std::cout << "Is destination reachable from source? " << (reachable ? "Yes" : "No") << std::endl;

    return 0;
}
