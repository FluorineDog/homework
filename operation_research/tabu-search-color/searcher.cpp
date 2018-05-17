#include "TabuSearch.h"
int main(int argc, char* argv[]) {
  if (argc != 3) {
    cin.redirect("data/DSJC500.5.col");
    preset_color_count = 49;
  } else {
    cin.redirect(argv[1]);
    preset_color_count = strtol(argv[2], nullptr, 10);
  }

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

  return 0;
}