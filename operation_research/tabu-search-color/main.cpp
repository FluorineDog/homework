#include <cassert>
#include <iostream>
#include <random>
#include <set>
#include <string>
#include "graph.h"
#include "cost_engine.h"
using std::set;
using std::string;


// #include "heap_del.h"
bool search(Graph& g, int color_count, std::default_random_engine& e);

int main() {
  const char* filename = "data/DSJC125.1.col";
  const int preset_color_count = 5;

  cin.redirect(filename);
  char ch;
  int vertex_count, edge_count;
  while (true) {
    cin >> ch;
    if (ch == 'c') {
      // commnets
      cin.skipline();
    } else if (ch == 'p') {
      // presentation
      char tmp[20];
      cin >> tmp >> vertex_count >> edge_count;
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

  graph = graph.optimize();
  std::default_random_engine e(67);
  graph.set_color_count(preset_color_count);

  CostEngine eng(graph);
  
  // set by random
  // for (int k = vertex_count; k-- > 0;) {
  //   cout << "searching " << k << endl;
  //   std::default_random_engine e(67);
  //   search(graph, vertex_count, e);
  // }

  return 0;
}

