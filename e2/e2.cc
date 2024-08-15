import <algorithm>;
import <print>;
import <vector>;

auto sort(std::vector<ssize_t> &vec) -> void {
  for (auto i{0u}; i < vec.size(); ++i) {
    for (auto j{0u}; j < vec.size() - 1; ++j) {
      if (vec.at(j) > vec.at(j + 1)) {
        std::swap(vec.at(j), vec.at(j + 1));
      }
    }
  }
}

int main(int argc, char **argv) {
  std::vector<ssize_t> vec{};
  for (ssize_t i{1}; i < argc; ++i) {
    vec.emplace_back(std::stol(argv[i]));
  }
  sort(vec);
  for (const auto &v : vec) {
    std::print("{} ", v);
  }
  std::print("\n");
  return 0;
}
