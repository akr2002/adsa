#include <climits>
#include <iostream>
#include <queue>
#include <vector>

using namespace std;

// Structure to represent an edge in the graph
struct Edge {
  int vertex;
  int weight;
};

// Custom comparator to order the priority queue based on shortest distance
struct Compare {
  bool operator()(pair<int, int> const &p1, pair<int, int> const &p2) {
    return p1.second > p2.second;
  }
};

// Dijkstra's algorithm function to compute the shortest paths
void dijkstra(const vector<vector<Edge>> &graph, int source) {
  int V = graph.size();

  // Distance vector to store the shortest distance from the source to each
  // vertex
  vector<int> dist(V, INT_MAX);

  // Priority queue to process vertices, where the pair stores (vertex,
  // distance)
  priority_queue<pair<int, int>, vector<pair<int, int>>, Compare> pq;

  // Distance to the source is zero
  dist[source] = 0;

  // Push the source into the priority queue
  pq.push({source, 0});

  // Process the graph
  while (!pq.empty()) {
    int u = pq.top().first; // Get the vertex with the smallest distance
    pq.pop();

    // Traverse all adjacent vertices of the current vertex
    for (const Edge &edge : graph[u]) {
      int v = edge.vertex;
      int weight = edge.weight;

      // If there is a shorter path to v through u
      if (dist[u] + weight < dist[v]) {
        dist[v] = dist[u] + weight; // Update distance to v
        pq.push({v, dist[v]});      // Push v into the priority queue
      }
    }
  }

  // Output the shortest distance from the source to all vertices
  cout << "Vertex\tDistance from Source (0)" << endl;
  for (int i = 0; i < V; i++) {
    cout << i << "\t" << dist[i] << endl;
  }
}

int main() {
  // Example graph: Number of vertices = 5
  // Graph representation:
  // (0)---10---(1)
  //  | \       / |
  //  6  5    15  2
  //  |   \   /   |
  // (3)---4-(2)---(4)

  int V = 5; // Number of vertices

  // Constructing the graph as an adjacency list
  vector<vector<Edge>> graph(V);

  // Adding edges (u, v, w) where u and v are vertices and w is the weight
  graph[0].push_back({1, 10});
  graph[0].push_back({3, 6});
  graph[0].push_back({2, 5});

  graph[1].push_back({0, 10});
  graph[1].push_back({2, 15});
  graph[1].push_back({4, 2});

  graph[2].push_back({0, 5});
  graph[2].push_back({1, 15});
  graph[2].push_back({3, 4});
  graph[2].push_back({4, 12});

  graph[3].push_back({0, 6});
  graph[3].push_back({2, 4});

  graph[4].push_back({1, 2});
  graph[4].push_back({2, 12});

  int source = 0; // Starting node (source vertex)

  // Run Dijkstra's algorithm from the source
  dijkstra(graph, source);

  return 0;
}
