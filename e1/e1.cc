import <algorithm>;
import <optional>;
import <print>;
import <ranges>;
import <vector>;

auto b_search(const std::vector<ssize_t> &vec, const ssize_t &key) -> bool {
  auto temp{vec};
  std::ranges::sort(temp);
  auto mid{temp.size() / 2};
  auto beg{0ul}, end{temp.size()};
  while (beg <= end) {
    mid = (beg + end) / 2;
    if (temp.at(mid) == key)
      return true;
    else if (key < temp.at(mid)) {
      end = mid - 1;
    } else {
      beg = mid + 1;
    }
  }
  return false;
}

auto l_search(const std::vector<ssize_t> &vec, const ssize_t &key)
    -> std::optional<size_t> {
  auto index{0u};
  for (const auto &e : vec) {
    if (e == key) {
      return index;
    }
    ++index;
  }
  return std::nullopt;
}

int main(int argc, char **argv) {
  std::vector<ssize_t> vec{5,  3, 5, 4,    6,  5,  7,   45, 6,
                           45, 6, 5, 6756, 75, 54, 634, 5,  3};
  auto key{std::stoi(argv[1])};
  // ssize_t key{77};
  std::println("Linear Search");
  std::println("=============");
  auto result{l_search(vec, key)};
  if (result.has_value()) {
    std::println("Key found at index {}", result.value());
  } else
    std::println("Key not found");
  auto b_result{b_search(vec, key)};
  std::println("\nBinary Search");
  std::println("=============");
  b_result ? std::println("Key found") : std::println("Key not found");
  return 0;
}
