
import <array>;
import <limits>;
import <print>;

ssize_t MAX{4};
auto inf{std::numeric_limits<ssize_t>::max()};

template <typename T, std::size_t Row, std::size_t Col>
using matrix_2d_t = std::array<std::array<T, Col>, Row>;

matrix_2d_t<ssize_t, MAX, MAX> dist{
    {{0, 10, 15, 20}, {10, 0, 35, 25}, {15, 35, 0, 30}, {20, 25, 30, 0}}};

matrix_2d_t<ssize_t, MAX, 1 << MAX> dp{}; // [city][visited_cities_mask]

auto tsp(ssize_t pos, ssize_t visited, ssize_t n) -> ssize_t {
  if (visited == (1 << n) - 1) {
    return dist[pos][0];
  }

  if (dp[pos][visited] == -1) {
    return dp[pos][visited];
  }

  auto answer{inf};

  for (ssize_t city{}; city < n; ++city) {
    if ((visited & (1 << city)) == 0) {
      auto new_answer{dist[pos][city] + tsp(city, visited | (1 << city), n)};
      answer = std::min(answer, new_answer);
    }
  }

  dp[pos][visited] = answer;
  return answer;
}

int main() {
  auto n{MAX};

  for (ssize_t i{0}; i < n; ++i) {
    for (ssize_t j{0}; j < (1 << n); ++j) {
      dp[i][j] = -1;
    }
  }

  auto result{tsp(0, 1, n)};

  std::println("The minimum cost of visiting all cities is: {}", result);

  return 0;
}
