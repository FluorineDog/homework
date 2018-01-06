#define HIGH_IO_PERFORMANCE
#include "graph.h"
int main() {
  cin.redirect("data.in");
  Graph graph(50001);
  // acc[0, t)
  for (int i = 0; i < 50000; ++i) {
    graph.add_edge(i, i + 1, 1);
    graph.add_edge(i + 1, i, 0);
  }
  int M; 
  cin >> M;
  while (M-- > 0) {
		int beg, end;
		ull count;
		cin >> beg >> end >> count;
		end++;
		graph.add_edge(end, beg, -count);
  }
	graph.spfa(50000);
	cout << -graph[0].value << endl;
}