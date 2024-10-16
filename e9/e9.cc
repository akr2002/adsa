#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

// Structure to represent an item with weight and value
struct Item {
  int value;
  int weight;
};

// Comparator function to sort items by value-to-weight ratio in decreasing
// order
bool compare(Item a, Item b) {
  double r1 = (double)a.value / a.weight;
  double r2 = (double)b.value / b.weight;
  return r1 > r2;
}

// Function to solve the Fractional Knapsack problem using the Greedy technique
double fractionalKnapsack(int W, vector<Item> &items) {
  // Sort items by value-to-weight ratio
  sort(items.begin(), items.end(), compare);

  int currentWeight = 0;   // Current weight of the knapsack
  double finalValue = 0.0; // Maximum value in the knapsack

  // Iterate through all items
  for (size_t i = 0; i < items.size(); i++) {
    // If adding the item doesn't exceed capacity, add the entire item
    if (currentWeight + items[i].weight <= W) {
      currentWeight += items[i].weight;
      finalValue += items[i].value;
    }
    // If the item cannot be added entirely, add a fraction of it
    else {
      int remainingWeight = W - currentWeight;
      finalValue +=
          items[i].value * ((double)remainingWeight / items[i].weight);
      break; // Once we fill the knapsack, we stop
    }
  }

  return finalValue;
}

int main() {
  int W = 50; // Capacity of the knapsack

  // Example items (value, weight)
  vector<Item> items = {{60, 10}, {100, 20}, {120, 30}};

  // Solve the Knapsack problem using the Greedy technique
  double maxValue = fractionalKnapsack(W, items);

  // Output the maximum value
  cout << "Maximum value we can obtain = " << maxValue << endl;

  return 0;
}
