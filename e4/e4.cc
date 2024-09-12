import <algorithm>;
import <print>;
import <vector>;

auto partition(std::vector<ssize_t> &vec, const ssize_t &low,
               const ssize_t &high) -> ssize_t {
  auto pivot{vec.at(high)};
  auto i{low - 1};

  for (auto j{low}; j < high; ++j) {
    if (vec.at(j) < pivot) {
      ++i;
      std::swap(vec.at(i), vec.at(j));
    }
  }

  std::swap(vec.at(i + 1), vec.at(high));
  return i + 1;
}

auto quicksort(std::vector<ssize_t> &vec, const ssize_t &low,
               const ssize_t &high) -> void {
  if (low < high) {
    auto partition_index{partition(vec, low, high)};
    quicksort(vec, low, partition_index - 1);
    quicksort(vec, partition_index + 1, high);
  }
}

auto print_array(const std::vector<ssize_t> &vec) -> void {
  for (const auto &v : vec) {
    std::print("{} ", v);
  }
  std::print("\n");
}

int main(int argc, char **argv) {
  std::vector<ssize_t> vec{};
  for (auto i{1}; i < argc; ++i) {
    vec.emplace_back(std::stol(argv[i]));
  }
  quicksort(vec, 0, vec.size() - 1);
  print_array(vec);

  return 0;
}
