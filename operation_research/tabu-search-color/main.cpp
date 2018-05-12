#include <cassert>
#include <iostream>
#include <random>
#include <set>
#include <string>
#include "graph.h"
using std::set;
using std::string;

constexpr int COLOR = 10;

// #include "heap_del.h"
bool search(Graph g, int color_count, std::default_random_engine& e);

int main() {
  const char* filename = "data/DSJC125.1.col";

  cin.redirect(filename);
  char ch;
  int vertex_count, edge_count;
  while (true) {
    cerr << "hh";
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

  // Graph graph(vertex_count, edge_count * 2);
  // for (int i = 0; i < edge_count; ++i) {
  //   while (getchar() != 'e') {
  //   }
  //   int from, to;
  //   cin >> from >> to;
  //   --from;
  //   --to;
  //   graph.add_edge(from, to);
  //   graph.add_edge(to, from);
  // }

  // graph = graph.optimize();
  // std::default_random_engine e(67);
  // search(graph, 0, e);
  
  // set by random
  // for (int k = vertex_count; k-- > 0;) {
  //   cout << "searching " << k << endl;
  //   std::default_random_engine e(67);
  //   search(graph, vertex_count, e);
  // }

  return 0;
}

bool search(Graph g, int color_count, std::default_random_engine& e) {
  // using set
  for (auto& v : g) {
    v.color = e() % color_count;
  }

  // vector<set<int, int>> vertex_colors;

  for (int from = 0; from < g.size(); ++from) {
    auto& v = g[from];
    for(auto to: g.get_edges(from)){
      cout << "e " << from << " " << to << endl;
    }
    // for (auto edge = g.edge_begin(v); g.edge_valid(edge);g.edge_next(edge)) {
    //   auto& to_vertex = graph[edge.to];
    //   vertex_colors[vertex_id].insert(to_vertex.color);
    // }
  }
  return false;
}
