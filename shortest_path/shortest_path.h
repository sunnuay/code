#define M 0x7fffffff
#include <vector>
#include <iostream>
using namespace std;

vector<int> dijkstra(vector<vector<int>> graph, int src);
vector<int> bellman_ford(vector<vector<int>> graph, int src);
vector<vector<int>> floyd_warshall(vector<vector<int>> graph);