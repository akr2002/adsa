import <algorithm>;
import <print>;
import <vector>;

auto print(const std::vector<ssize_t> &vec) -> void {
  for (const auto &v : vec) {
    std::print("{} ", v);
  }
  std::print("\n");
}

auto ins_sort(std::vector<ssize_t> vec) -> void {
  auto i{1};
  auto j{i - 1};
  for (i = 1; i < vec.size(); ++i) {
    auto var{vec.at(i)};
    for (j = i - 1; j >= 0; --j) {
      if (vec.at(j) > var) {
        std::swap(vec.at(j + 1), vec.at(j));
      } else
        break;
    }
    vec.at(j + 1) = var;
  }
  std::print("Insertion sort: ");
  print(vec);
}

auto sel_sort(std::vector<ssize_t> vec) -> void {
  for (auto i{0u}; i < vec.size() - 1; ++i) {
    auto min_index{i};
    for (auto j{i + 1}; j < vec.size(); ++j) {
      if (vec.at(j) < vec.at(min_index)) {
        min_index = j;
      }
    }
    std::swap(vec.at(min_index), vec.at(i));
  }
  std::print("Selection sort: ");
  print(vec);
}

int main(int argc, char **argv) {
  std::vector<ssize_t> vec{};
  for (ssize_t i{1}; i < argc; ++i) {
    vec.emplace_back(std::stol(argv[i]));
  }
  sel_sort(vec);
  ins_sort(vec);
  return 0;
}
