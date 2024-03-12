#include "shortest_path.h"

vector<int> dijkstra(vector<vector<int>> graph, int src)
{
    int V = graph.size();
    vector<int> dist(V, M);
    vector<bool> visited(V, false);
    dist[src] = 0;
    for (int i = 0; i < V; i++)
    {
        int j = -1;
        for (int temp = 0; temp < V; temp++)
            if (!visited[temp])
                if (j == -1 || dist[temp] <= dist[j])
                    j = temp;
        visited[j] = true;
        for (int k = 0; k < V; k++)
            if (!visited[k] && graph[j][k] != M && dist[j] + graph[j][k] < dist[k])
                dist[k] = dist[j] + graph[j][k];
    }
    return dist;
}