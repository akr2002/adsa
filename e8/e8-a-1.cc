#include <limits>
#include <print>
#include <queue>
#include <vector>

struct Edge {
  ssize_t vertex{};
  ssize_t weight{};
};

struct Compare {
  auto operator()(std::pair<ssize_t, ssize_t> const &p1,
                  std::pair<ssize_t, ssize_t> const &p2) -> bool {
    return p1.second > p2.second;
  }
};

auto dijkstra(const std::vector<std::vector<Edge>> &graph,
              ssize_t source) -> void {
  auto V{graph.size()};

  std::vector<ssize_t> dist(V, std::numeric_limits<ssize_t>::max());

  std::priority_queue<std::pair<ssize_t, ssize_t>,
                      std::vector<std::pair<ssize_t, ssize_t>>, Compare>
      pq{};

  dist[source] = 0;

  pq.push({source, 0});

  while (!pq.empty()) {
    auto u{pq.top().first};
    pq.pop();

    for (const auto &edge : graph[u]) {
      auto v{edge.vertex};
      auto weight{edge.weight};

      if (dist[u] + weight < dist[v]) {
        dist[v] = dist[u] + weight;
        pq.push({v, dist[v]});
      }
    }
  }

  std::println("Vertex\tDistance from Source (0)");
  for (auto i{0u}; i < V; ++i) {
    std::println("{}\t{}", i, dist[i]);
  }
}

int main() {

  const ssize_t V{5};

  std::vector<std::vector<Edge>> graph(V);

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

  ssize_t source{};

  dijkstra(graph, source);

  return 0;
}
