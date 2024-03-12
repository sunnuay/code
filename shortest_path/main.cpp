#include "shortest_path.h"

void print(vector<int> dist)
{
    for (int i = 0; i < dist.size(); i++)
    {
        if (dist[i] == M)
            cout << "∞ ";
        else
            cout << dist[i] << " ";
    }
    cout << endl;
}

int main()
{
    vector<vector<int>> graph = {{0, -2, 1, M, M},
                                 {M, 0, M, M, -1},
                                 {M, M, 0, -5, M},
                                 {M, M, M, 0, 0},
                                 {M, M, M, M, 0}};

    vector<int> dist_dijkstra = dijkstra(graph, 0);
    vector<int> dist_bellman_ford = bellman_ford(graph, 0);
    vector<vector<int>> dist_floyd_warshall = floyd_warshall(graph);

    print(dist_dijkstra);
    cout << endl;
    print(dist_bellman_ford);
    cout << endl;
    for (int i = 0; i < graph.size(); i++)
        print(dist_floyd_warshall[i]);
    return 0;
}