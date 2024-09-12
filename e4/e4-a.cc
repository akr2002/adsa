import <print>;
import <vector>;

auto merge(std::vector<ssize_t> &vec, const ssize_t &left, const ssize_t &mid,
           const ssize_t &right) -> void {
  const auto n1{mid - left + 1};
  const auto n2{right - mid};

  std::vector<ssize_t> L{}, R{};
  for (ssize_t i{}; i < n1; ++i) {
    L.insert(L.begin(), vec.at(left + i));
  }
  for (ssize_t i{}; i < n2; ++i) {
    R.insert(R.begin(), vec.at(mid + 1 + i));
  }

  ssize_t i{}, j{}, k{left};

  while (i < n1 && j < n2) {
    if (L.at(i) <= R.at(j)) {
      vec.at(k) = L.at(i);
      ++i;
    } else {
      vec.at(k) = R.at(j);
      ++j;
    }
    ++k;
  }

  while (i < n1) {
    vec.at(k) = L.at(i);
    ++i;
    ++k;
  }

  while (j < n2) {
    vec.at(k) = R.at(j);
    ++j;
    ++k;
  }
}

auto mergesort(std::vector<ssize_t> &vec, const ssize_t &left,
               const ssize_t &right) -> void {
  if (left < right) {
    auto mid{left + (right - left) / 2};

    mergesort(vec, left, mid);
    mergesort(vec, mid + 1, right);
    merge(vec, left, mid, right);
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
  mergesort(vec, 0, vec.size() - 1);
  print_array(vec);

  return 0;
}
