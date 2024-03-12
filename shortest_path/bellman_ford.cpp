#include "shortest_path.h"

vector<int> bellman_ford(vector<vector<int>> graph, int src)
{
    int V = graph.size();
    vector<int> dist(V);
    dist = graph[src];
    for (int i = 0; i < V; i++)
        for (int j = 0; j < V; j++)
            for (int k = 0; k < V; k++)
                if (dist[j] != M && graph[j][k] != M && dist[j] + graph[j][k] < dist[k])
                    dist[k] = dist[j] + graph[j][k];
    return dist;
}