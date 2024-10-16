#include <iostream>
#include <limits.h>
#include <vector>

using namespace std;

const int MAX = 4;       // Maximum number of cities for the example (4 cities)
const int INF = INT_MAX; // Infinity (for large values)

// Distance matrix to store distances between cities
int dist[MAX][MAX] = {
    {0, 10, 15, 20}, // Distances from city 0 to other cities
    {10, 0, 35, 25}, // Distances from city 1 to other cities
    {15, 35, 0, 30}, // Distances from city 2 to other cities
    {20, 25, 30, 0}  // Distances from city 3 to other cities
};

// Memoization table to store subproblem solutions
int dp[MAX][1 << MAX]; // [city][visitedCitiesMask]

// Function to solve TSP using dynamic programming and bitmasking
int tsp(int pos, int visited, int n) {
  // Base case: if all cities have been visited, return to the starting city
  if (visited == (1 << n) - 1) {
    return dist[pos][0]; // Return distance to the start city
  }

  // If the subproblem has already been solved, return the stored result
  if (dp[pos][visited] != -1) {
    return dp[pos][visited];
  }

  int answer = INF;

  // Try all cities and select the one that minimizes the cost
  for (int city = 0; city < n; city++) {
    // If the city has not been visited yet
    if ((visited & (1 << city)) == 0) {
      int newAnswer = dist[pos][city] + tsp(city, visited | (1 << city), n);
      answer = min(answer, newAnswer);
    }
  }

  // Store the result in the memoization table and return
  dp[pos][visited] = answer;
  return answer;
}

int main() {
  int n = MAX; // Number of cities (4 for this example)

  // Initialize the memoization table with -1 (indicating unsolved subproblems)
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < (1 << n); j++) {
      dp[i][j] = -1;
    }
  }

  // Solve the TSP starting from city 0 with only city 0 visited
  int result = tsp(0, 1, n);

  // Output the minimum cost
  cout << "The minimum cost of visiting all cities is: " << result << endl;

  return 0;
}
