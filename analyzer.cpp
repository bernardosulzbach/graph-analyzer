#include <algorithm>
#include <cstdint>
#include <iostream>
#include <limits>
#include <vector>

/**
 * The specialized node type used in Tarjan's algorithm.
 */
typedef struct TarjanNode {
  int64_t id;
  int64_t index;
  int64_t link;
  bool stack;
  std::vector<int64_t> outgoing;

  TarjanNode(int64_t node_id, const std::vector<bool> &relations) {
    id = node_id;
    index = undefined_index;
    link = 0;
    stack = false;
    for (int64_t i = 0; i < relations.size(); i++) {
      if (relations[i]) {
        outgoing.push_back(i);
      }
    }
  }

  static const int64_t undefined_index = std::numeric_limits<int64_t>::min();

} TarjanNode;

static void read_graph_line(std::vector<std::vector<bool>> &matrix) {
  std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '(');
  int64_t n;
  std::cin >> n;
  while (true) {
    // Consume all whitespace.
    std::cin >> std::ws;
    if (std::cin.peek() == ')') {
      // Got a closing parenthesis, stop.
      break;
    }
    int64_t x;
    std::cin >> x;
    matrix[n][x] = true;
  }
}

static void read_graph(std::vector<std::vector<bool>> &matrix) {
  for (int64_t i = 0; i < matrix.size(); i++) {
    read_graph_line(matrix);
  }
}

static std::vector<TarjanNode>
derive_nodes(const std::vector<std::vector<bool>> &matrix) {
  std::vector<TarjanNode> nodes;
  for (int64_t i = 0; i < matrix.size(); i++) {
    nodes.push_back(TarjanNode(i, matrix[i]));
  }
  return nodes;
}

static void tarjan_start(std::vector<std::vector<int64_t>> &components,
                         std::vector<TarjanNode> &nodes,
                         std::vector<TarjanNode *> &node_stack,
                         TarjanNode &node, int64_t &index) {
  node.index = index;
  node.link = index;
  index++;
  node_stack.push_back(&node);
  node.stack = true;
  for (int64_t out : node.outgoing) {
    TarjanNode &next = nodes[out];
    if (next.index == TarjanNode::undefined_index) {
      tarjan_start(components, nodes, node_stack, next, index);
      node.link = std::min(node.link, next.link);
    } else if (next.stack) {
      // As the next node is on the stack too, it is in this component.
      node.link = std::min(node.link, next.index);
    }
  }
  // If we have a new component, add it to the vector.
  if (node.link == node.index) {
    std::vector<int64_t> component;
    TarjanNode &removed = *node_stack.back();
    do {
      removed = *node_stack.back();
      node_stack.pop_back();
      removed.stack = false;
      component.push_back(removed.id);
    } while (removed.id != node.id);
    components.push_back(component);
  }
}

/**
 * An implementation of Tarjan's algorithm.
 */
static std::vector<std::vector<int64_t>>
derive_components(std::vector<std::vector<bool>> &matrix) {
  std::vector<std::vector<int64_t>> components;
  std::vector<TarjanNode> nodes = derive_nodes(matrix);
  std::vector<TarjanNode *> node_stack;
  int64_t index = 0;
  // Prevent value copies from the base vector.
  for (TarjanNode &node : nodes) {
    // If we have not yet connected this node, try to do it.
    if (node.index == TarjanNode::undefined_index) {
      tarjan_start(components, nodes, node_stack, node, index);
    }
  }
  for (std::vector<int64_t> &component : components) {
    std::sort(component.begin(), component.end());
  }
  std::sort(components.begin(), components.end());
  return components;
}

static void print_components(std::vector<std::vector<bool>> &matrix) {
  std::vector<std::vector<int64_t>> components = derive_components(matrix);
  std::cout << "Components: ";
  std::cout << "{ ";
  bool first_component = true;
  for (std::vector<int64_t> component : components) {
    if (!first_component) {
      std::cout << ", ";
    }
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
    first_component = false;
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
