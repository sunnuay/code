#include "shortest_path.h"

vector<vector<int>> floyd_warshall(vector<vector<int>> graph)
{
    int V = graph.size();
    vector<vector<int>> dist(V, vector<int>(V));
    dist = graph;
    for (int k = 0; k < V; k++)
        for (int i = 0; i < V; i++)
            for (int j = 0; j < V; j++)
                if (dist[i][k] != M && dist[k][j] != M && dist[i][k] + dist[k][j] < dist[i][j])
                    dist[i][j] = dist[i][k] + dist[k][j];
    return dist;
}