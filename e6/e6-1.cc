import <limits>;
import <memory>;
import <print>;
import <queue>;
import <utility>;
import <vector>;

class Graph {
private:
  std::vector<std::pair<ssize_t, ssize_t>> *adj{};
  ssize_t vertices{};

public:
  Graph() = default;
  Graph(const ssize_t &vertices)
      : vertices(vertices),
        adj(new std::vector<std::pair<ssize_t, ssize_t>>[vertices]) {}
  ~Graph() { delete[] adj; }

  auto add_edge(const ssize_t &u, const ssize_t &v,
                const ssize_t &weight) -> void {
    /* adj->at(v) = std::make_pair(u, weight); */
    /* adj->at(u) = std::make_pair(v, weight); */
    adj[v].emplace_back(std::make_pair(u, weight));
    adj[u].emplace_back(std::make_pair(v, weight));
  }

  auto prim_mst() -> void {
    // store vertices
    std::priority_queue<std::pair<ssize_t, ssize_t>,
                        std::vector<std::pair<ssize_t, ssize_t>>,
                        std::greater<std::pair<ssize_t, ssize_t>>>
        pq{};

    // store minimum weght edge to vertex
    std::vector<ssize_t> key(vertices, std::numeric_limits<ssize_t>::max());

    // track if vector is in mst
    std::vector<bool> in_mst(vertices, false);

    // store parent of each vertex
    std::vector<ssize_t> parent(vertices, -1);

    // start from vertex 0
    pq.push(std::make_pair(0, 0));
    key[0] = 0;

    while (!pq.empty()) {
      auto u{pq.top().second};
      pq.pop();

      // include the vetex in the mst
      in_mst[u] = true;

      // loop through all adj vertices of the current vertex
      for (const auto &it : adj[u]) {
        const auto &[v, weight] = it;

        // if v is not in mst and the weight of u-v is smaller than the current
        // key of v
        if (!in_mst[v] && key[v] > weight) {
          // update key value and parent index
          key[v] = weight;
          pq.push(std::make_pair(key[v], v));
          parent[v] = u;
        }
      }
    }

    // print mst edges and their weights
    std::println("Edge \tWeight");
    for (auto i{1}; i < vertices; ++i)
      std::println("{} - {} \t {}", parent[i], i, key[i]);
  }
};

int main() {
  ssize_t vertices{5};
  Graph g(vertices);

  g.add_edge(0, 1, 2);
  g.add_edge(0, 3, 6);
  g.add_edge(1, 2, 3);
  g.add_edge(1, 3, 8);
  g.add_edge(1, 4, 5);
  g.add_edge(2, 4, 7);
  g.add_edge(3, 4, 9);

  g.prim_mst();

  return 0;
}
