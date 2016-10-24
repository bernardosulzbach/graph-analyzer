#include <cstdint>
#include <iostream>
#include <vector>

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

static std::vector<std::vector<int64_t>>
derive_components(std::vector<std::vector<bool>> &matrix) {
  std::vector<std::vector<int64_t>> components;
  return components;
}

static void print_components(std::vector<std::vector<bool>> &matrix) {
  std::cout << "Components: ";
  std::vector<std::vector<int64_t>> components = derive_components(matrix);
  std::cout << "{ ";
  for (std::vector<int64_t> component : components) {
    std::cout << "{";
    bool first_node = true;
    for (int64_t node : component) {
      if (!first_node) {
        std::cout << ", ";
      }
      std::cout << node;
      first_node = false;
    }
    std::cout << "}";
  }
  std::cout << " }";
  std::cout << '\n';
}

static void print_topological_sort(std::vector<std::vector<bool>> &matrix) {
  return;
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
  print_components(matrix);
  print_topological_sort(matrix);
  return 0;
}
