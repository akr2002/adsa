#include <iostream>
#include <vector>
#include <ranges>
#include <concepts>
#include <algorithm>

// Concept to ensure elements are sortable
template <typename T>
concept Sortable = requires(T a, T b) {
    { a < b } -> std::convertible_to<bool>;
};

// Merge function to merge two sorted halves
template <Sortable T>
void merge(std::vector<T>& vec, int left, int mid, int right) {
    std::vector<T> leftHalf(vec.begin() + left, vec.begin() + mid + 1);
    std::vector<T> rightHalf(vec.begin() + mid + 1, vec.begin() + right + 1);

    int i = 0, j = 0, k = left;

    while (i < leftHalf.size() && j < rightHalf.size()) {
        if (leftHalf[i] <= rightHalf[j]) {
            vec[k++] = leftHalf[i++];
        } else {
            vec[k++] = rightHalf[j++];
        }
    }

    // Copy any remaining elements
    std::ranges::copy(leftHalf | std::views::drop(i), vec.begin() + k);
    std::ranges::copy(rightHalf | std::views::drop(j), vec.begin() + k);
}

// Recursive MergeSort function
template <Sortable T>
void mergeSort(std::vector<T>& vec, int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;

        mergeSort(vec, left, mid);
        mergeSort(vec, mid + 1, right);
        merge(vec, left, mid, right);
    }
}

int main() {
    std::vector<int> vec = {38, 27, 43, 3, 9, 82, 10};

    mergeSort(vec, 0, vec.size() - 1);

    for (const auto& elem : vec) {
        std::cout << elem << " ";
    }

    return 0;
}

