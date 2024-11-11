#include <print>
#include <vector>

template <typename T> using heap_t = std::vector<T>;

auto swap(ssize_t &a, ssize_t &b) -> void {
  auto temp{b};
  b = a;
  a = temp;
}

auto heapify(heap_t<ssize_t> &heap, const size_t &i) -> void {
  const auto size{heap.size()};
  auto largest{i};
  const auto left{2 * i + 1};
  const auto right{2 * i + 2};

  if (left < size && heap[left] > heap[largest])
    largest = left;

  if (right < size && heap[right] > heap[largest])
    largest = right;

  if (largest != i) {
    swap(heap[i], heap[largest]);
    heapify(heap, largest);
  }
}

auto insert(heap_t<ssize_t> &heap, const ssize_t &data) -> void {
  ssize_t size = heap.size();
  heap.emplace_back(data);
  if (size == 0)
    return;

  for (auto i{(size / 2) - 1}; i >= 0; --i)
    heapify(heap, i);
}

auto remove_node(heap_t<ssize_t> &heap, const ssize_t &data) -> void {
  ssize_t size = heap.size();
  auto i{0zu};
  for (i = 0; i < size; ++i)
    if (data == heap[i])
      break;

  if (i == size)
    return;

  swap(heap[i], heap[size - 1]);
  heap.pop_back();

  for (auto i{(size / 2) - 1}; i >= 0; --i)
    heapify(heap, i);
}

auto print_heap(const heap_t<ssize_t> &heap) -> void {
  for (const auto &node : heap)
    std::print("{} ", node);

  std::print("\n");
}

int main() {
  heap_t<ssize_t> heap{};

  insert(heap, 12);
  insert(heap, 18);
  insert(heap, 13);
  insert(heap, 62);
  insert(heap, 5);

  std::print("Heap: ");
  print_heap(heap);

  remove_node(heap, 12);

  std::print("After removing 12: ");
  print_heap(heap);

  return 0;
}
