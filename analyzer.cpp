#include <vector>
#include <iostream>
#include <cstdint>

static void read_graph_line(std::vector<std::vector<bool>> &matrix) {
  char ignored;
  std::cin >> ignored;
  int64_t n;
  std::cin >> n;
  int64_t x;
  while (std::cin >> x) {
    matrix[n][x] = true;
  }
}

static void read_graph(std::vector<std::vector<bool>> &matrix) {
  for (int64_t i = 0; i < matrix.size(); i++) {
    read_graph_line(matrix);
  }
}

int main(void) {
  // Discard the opening parenthesis.
  char ignored;
  std::cin >> ignored;
  // Create the adjacency matrix.
  int64_t n;
  std::cin >> n;
  std::vector<bool> row(n, false);
  std::vector<std::vector<bool>> matrix(n, row);
  read_graph(matrix);
  matrix.reserve(n);
  return 0;
}
