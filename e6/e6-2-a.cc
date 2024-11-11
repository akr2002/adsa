#include <algorithm>
#include <print>
#include <vector>

// A structure to represent an edge
struct Edge {
  int u, v, weight;
};

// Comparator function to sort edges by weight
auto compare(Edge a, Edge b) -> bool { return a.weight < b.weight; }

// Disjoint Set (Union-Find) to manage connected components
class DisjointSet {
  std::vector<int> parent, rank;

public:
  DisjointSet(int n) {
    parent.resize(n);
    rank.resize(n, 0);
    for (int i = 0; i < n; i++)
      parent[i] = i; // Each vertex is its own parent initially
  }

  // Find function with path compression
  auto find(int u) -> int {
    if (u != parent[u])
      parent[u] = find(parent[u]);
    return parent[u];
  }

  // Union function by rank
  auto unite(int u, int v) -> void {
    int rootU = find(u);
    int rootV = find(v);

    if (rootU != rootV) {
      if (rank[rootU] < rank[rootV]) {
        parent[rootU] = rootV;
      } else if (rank[rootU] > rank[rootV]) {
        parent[rootV] = rootU;
      } else {
        parent[rootV] = rootU;
        rank[rootU]++;
      }
    }
  }
};

// Kruskal's Algorithm to find the Minimum Spanning Tree
void kruskalMST(std::vector<Edge> &edges, int V) {
  // Sort the edges by increasing weight
  std::sort(edges.begin(), edges.end(), compare);

  DisjointSet ds(V);     // Create a disjoint set for V vertices
  std::vector<Edge> mst; // std::vector to store the edges of the MST
  int mstWeight = 0;     // Total weight of the MST

  for (auto edge : edges) {
    int u = edge.u;
    int v = edge.v;

    // Check if the current edge forms a cycle
    if (ds.find(u) != ds.find(v)) {
      // If not, add it to the MST
      mst.push_back(edge);
      mstWeight += edge.weight;

      // Union the sets
      ds.unite(u, v);
    }
  }

  // Print the MST
  std::println("Edges in the Minimum Spanning Tree:");
  for (auto edge : mst) {
    std::println("{} - {}: {}", edge.u, edge.v, edge.weight);
  }
  std::println("Total weight of the MST: {}", mstWeight);
}

int main() {
  int V = 5; // Number of vertices
  std::vector<Edge> edges;

  // Add edges to the graph (u, v, weight)
  edges.push_back({0, 1, 1});
  edges.push_back({0, 2, 3});
  edges.push_back({1, 2, 2});
  edges.push_back({1, 3, 4});
  edges.push_back({2, 3, 5});
  edges.push_back({3, 4, 6});

  // Function to find and print the MST
  kruskalMST(edges, V);

  return 0;
}
