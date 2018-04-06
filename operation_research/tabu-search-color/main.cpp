#include <cassert>
#include <iostream>
#include <random>
#include <string>
#include "graph.h"
using std::string;

constexpr int COLOR = 10;

int main() {
  std::default_random_engine e(67);
  
  // Graph
  cin.redirect("data/DSJC125.1.col");
  char ch;
  int vertex_count, edge_count;
  while (true) {
    cin >> ch;
    if (ch == 'c') {
      // commnets
      cin.skipline();
    } else if (ch == 'p') {
      // presentation
      cin >> vertex_count >> edge_count;
      break;
    } else {
      assert(false);
    }
  }

  Graph graph(vertex_count, edge_count * 2);
  for (int i = 0; i < edge_count; ++i) {
    while (getchar() != 'e') {
    }
    int from, to;
    cin >> from >> to;
    --from;
    --to;
    graph.add_edge(from, to);
    graph.add_edge(to, from);
  }

  
  return 0;
}
