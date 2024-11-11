#include <algorithm>
#include <print>
#include <ranges>
#include <vector>

struct Item {
  ssize_t value{};
  ssize_t weight{};
};

auto compare(const Item &a, const Item &b) -> bool {
  auto r1{static_cast<double>(a.value) / a.weight};
  auto r2{static_cast<double>(b.value) / b.weight};
  return r1 > r2;
}

auto fractional_knapsack(ssize_t W, std::vector<Item> &items) -> double {
  std::ranges::sort(items, compare);

  ssize_t current_weight{};
  double final_value{};

  for (auto &item : items) {
    if (current_weight + item.weight <= W) {
      current_weight += item.weight;
      final_value += item.value;
    } else {
      auto remainig_weight{W - current_weight};
      final_value +=
          item.value * (static_cast<double>(remainig_weight) / item.weight);
      break;
    }
  }
  return final_value;
}

int main() {
  const ssize_t W{50};

  std::vector<Item> items{{60, 10}, {100, 20}, {120, 30}};
  auto max_value{fractional_knapsack(W, items)};
  std::println("Maximum value we can obtain = {}", max_value);
  return 0;
}
