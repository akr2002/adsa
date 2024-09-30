import <print>;
import <vector>;

template <typename T> using adj_list_t = std::vector<std::vector<T>>;

class Graph {
private:
  ssize_t vertices{};
  adj_list_t<ssize_t> adj{};

  auto DFS_util(const ssize_t &node, std::vector<bool> &visited) -> void {
    visited[node] = true;
    std::print("{} ", node);

    for (const auto &neighbor : adj[node]) {
      if (!visited[neighbor]) {
        DFS_util(neighbor, visited);
      }
    }
  }

public:
  Graph(const ssize_t &v) : vertices(v), adj(v) {}

  auto add_edge(const ssize_t &u, const ssize_t &v) -> void {
    adj[u].emplace_back(v);
    adj[v].emplace_back(u);
  }

  auto DFS(const ssize_t &start) -> void {
    std::vector<bool> visited(vertices, false);
    DFS_util(start, visited);
  }
};

int main() {
  Graph g(6);

  g.add_edge(0, 1);
  g.add_edge(0, 2);
  g.add_edge(1, 3);
  g.add_edge(1, 4);
  g.add_edge(2, 5);

  std::println("Depth-First Search starting from vertex 0");
  g.DFS(0);
  std::print("\n");

  return 0;
}
