// ISC License (ISC)
//
// Copyright (c) 2016, Bernardo Sulzbach (mafagafogigante@gmail.com)
//
// Permission to use, copy, modify, and/or distribute this software for any
// purpose with or without fee is hereby granted, provided that the above
// copyright notice and this permission notice appear in all copies.
//
// Author: Bernardo Sulzbach (mafagafogigante@gmail.com)

#include <algorithm>
#include <cstdint>
#include <iostream>
#include <limits>
#include <vector>

using std::vector;
using std::cout;

/**
 * The specialized node type used in Tarjan's algorithm.
 */
typedef struct TarjanNode {
  int64_t id;
  int64_t index;
  int64_t link;
  bool stack;
  vector<int64_t> outgoing;

  TarjanNode(int64_t node_id, const vector<bool> &relations) {
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

static void read_graph_line(vector<vector<bool>> &matrix) {
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

static void read_graph(vector<vector<bool>> &matrix) {
  for (int64_t i = 0; i < matrix.size(); i++) {
    read_graph_line(matrix);
  }
}

static vector<TarjanNode> derive_nodes(const vector<vector<bool>> &matrix) {
  vector<TarjanNode> nodes;
  for (int64_t i = 0; i < matrix.size(); i++) {
    nodes.push_back(TarjanNode(i, matrix[i]));
  }
  return nodes;
}

static void tarjan_start(vector<vector<int64_t>> &components,
                         vector<TarjanNode> &nodes, vector<size_t> &node_stack,
                         TarjanNode &node, int64_t &index) {
  node.index = index;
  node.link = index;
  index++;
  node_stack.push_back(node.id);
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
    vector<int64_t> component;
    while (true) {
      TarjanNode &removed = nodes[node_stack.back()];
      node_stack.pop_back();
      removed.stack = false;
      component.push_back(removed.id);
      if (removed.id == node.id) {
        break;
      }
    }
    components.push_back(component);
  }
}

/**
 * An implementation of Tarjan's algorithm.
 */
static vector<vector<int64_t>> derive_components(vector<vector<bool>> &matrix) {
  vector<vector<int64_t>> components;
  vector<TarjanNode> nodes = derive_nodes(matrix);
  vector<size_t> node_stack;
  int64_t index = 0;
  // Prevent value copies from the base vector.
  for (TarjanNode &node : nodes) {
    // If we have not yet connected this node, try to do it.
    if (node.index == TarjanNode::undefined_index) {
      tarjan_start(components, nodes, node_stack, node, index);
    }
  }
  for (vector<int64_t> &component : components) {
    std::sort(component.begin(), component.end());
  }
  std::sort(components.begin(), components.end());
  return components;
}

static void print_components(vector<vector<bool>> &matrix) {
  vector<vector<int64_t>> components = derive_components(matrix);
  cout << "Components: ";
  cout << "{ ";
  bool first_component = true;
  for (vector<int64_t> component : components) {
    if (!first_component) {
      cout << ", ";
    }
    cout << "{";
    bool first_node = true;
    for (int64_t node : component) {
      if (!first_node) {
        cout << ", ";
      }
      cout << node;
      first_node = false;
    }
    cout << "}";
    first_component = false;
  }
  cout << " }";
  cout << '\n';
}

static bool topological_sort_step(vector<vector<bool>> &matrix,
                                  vector<int> &tags, vector<int64_t> &stack,
                                  int64_t i) {
  if (tags[i] == 1) {
    // Found a cycle, return warning that this is not a DAG.
    return false;
  }
  if (tags[i] == 2) {
    return true;
  }
  tags[i] = 1;
  for (int64_t j = 0; j < matrix.size(); j++) {
    if (matrix[i][j]) {
      if (!topological_sort_step(matrix, tags, stack, j)) {
        return false;
      }
    }
  }
  tags[i] = 2;
  stack.push_back(i);
  return true;
}

static bool topological_sort(vector<vector<bool>> &matrix,
                             vector<int64_t> &output) {
  vector<int64_t> stack;
  vector<int> tags(matrix.size(), 0);
  for (int64_t i = 0; i < matrix.size(); i++) {
    if (tags[i] == 0) {
      if (!topological_sort_step(matrix, tags, stack, i)) {
        return false;
      }
    }
  }
  while (!stack.empty()) {
    output.push_back(stack.back());
    stack.pop_back();
  }
  return true;
}

static void print_topological_sort(vector<vector<bool>> &matrix) {
  vector<int64_t> output;
  bool is_dag = topological_sort(matrix, output);
  if (!is_dag) {
    cout << "No topological ordering (there are directed cycles)" << '\n';
    return;
  }
  bool first_node = true;
  for (int64_t node : output) {
    if (!first_node) {
      cout << ", ";
    }
    cout << node;
    first_node = false;
  }
  cout << '\n';
}

int main(void) {
  // Discard the opening parenthesis.
  char ignored;
  std::cin >> ignored;
  // Create the adjacency matrix.
  int64_t n;
  std::cin >> n;
  vector<bool> row(n, false);
  vector<vector<bool>> matrix(n, row);
  read_graph(matrix);
  print_components(matrix);
  print_topological_sort(matrix);
  return 0;
}
