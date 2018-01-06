// #define HIGH_IO_PERFORMANCE
#include "../wheel.h"
#define ull int
#include "graph.h"
int main() {
  cin.redirect("data.in");
  int M, N;
  cin >> N >> M;
  Graph graph(N + 1);
  while (M-- > 0) {
    int u, v, w;
    cin >> u >> v >> w;
    graph.add_edge(u, v, w);
  }
  graph.spfa(1);
  ull first = graph[N].value;
  // for (int i = 1; i <= N; ++i) {
  //   graph[i].value = 1 << 30;
  // }
  // graph.spfa(N);
  // ull second = graph[1].value;
  // cout << std::max(first, second) << endl;
  cout << first << endl;
  return 0;
}
