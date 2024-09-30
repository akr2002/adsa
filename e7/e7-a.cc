import <print>;
import <queue>;
import <vector>;

template <typename T> using adj_list_t = std::vector<std::vector<T>>;

class Graph {
private:
  ssize_t vertices{};
  adj_list_t<ssize_t> adj{};

public:
  Graph(const ssize_t &v) : vertices(v), adj(v) {}

  auto add_edge(const ssize_t &u, const ssize_t &v) -> void {
    adj[u].emplace_back(v);
    adj[v].emplace_back(u);
  }

  auto BFS(const ssize_t &start) -> void {
    std::vector<bool> visited(vertices, false);
    std::queue<ssize_t> q{};

    visited[start] = true;
    q.push(start);

    while (!q.empty()) {
      auto current{q.front()};
      q.pop();
      std::print("{} ", current);

      for (const auto &neighbor : adj[current]) {
        if (!visited[neighbor]) {
          visited[neighbor] = true;
          q.push(neighbor);
        }
      }
    }
  }
};

int main() {
  Graph g(6);

  g.add_edge(0, 1);
  g.add_edge(0, 2);
  g.add_edge(1, 3);
  g.add_edge(1, 4);
  g.add_edge(2, 5);

  std::println("Breadth-First Search starting from vertex 0");
  g.BFS(0);
  std::print("\n");

  return 0;
}
