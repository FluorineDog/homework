#include "../wheel.h"
typedef std::pair<int, int> T;
#define NIL std::make_pair(1 << 30, -1)
T ancestor_merge(T a, T b) { return a.first < b.first ? a : b; }
#define func(a, b) ancestor_merge(a, b)
#include "monoid_tree.h"
#include <stack>

struct Vertex {
  int ancestor;
  int depth;
  int discover_time;
  int finish_time;
  vector<int> edges;
};

typedef vector<Vertex> Graph;
class DFS {
public:
  DFS() {}
  void operator()(Graph &graph, int source) {
    for (int i = 0; i < (int)graph.size(); ++i) {
      graph[i].discover_time = -1;
    }
    timestamp = 0;
    ancestor = 0;
    depth = -1;
    dfs(graph, source);
  }

private:
  void dfs(Graph &graph, int source) {
    ++depth;
    if (graph[source].discover_time == -1) {
      // dupplicate
      return;
    }
    Vertex &vertex = graph[source];
    vertex.discover_time = timestamp++;
    for (int i = 0; i < (int)vertex.edges.size(); ++i) {
      ancestor = source;
      dfs(graph, vertex.edges[i]);
    }
    vertex.finish_time = timestamp;
    --depth;
  }

private:
  int depth;
  int timestamp;
  int ancestor;
};

void workload() {
  int N;
  int status = scanf("%d", &N);
  if (status != 1) {
    exit(0);
  }
  Graph graph(N);
  for (int k = 0; k < N; ++k) {
    int vertex;
    int edge_count;
    scanf(" %d:(%d)", &vertex, &edge_count);
    --vertex;
    graph[vertex].edges.reserve(edge_count);
    for (int i = 0; i < edge_count; ++i) {
      int edge;
      scanf("%d", &edge);
      --edge;
      graph[vertex].edges.push_back(edge);
    }
  }
  DFS()(graph, 0);
  MonoidTree tree(N - 1);
  for (int i = 1; i < N; ++i) {
    tree[i - 1] = std::make_pair(graph[i].depth, graph[i].ancestor);
  }
  tree.fast_init();
  int K;
	scanf("%d", &K);
  vector<int> record(N);
  while (K-- > 0) {
    int a, b;
    scanf(" (%d %d)", &a, &b);
    --a;
    --b;
		int beg = graph[a].discover_time;
		int end = graph[b].discover_time;
		if(beg > end) std::swap(beg, end);
    int ancestor = tree.reduce(beg, end).second;
    record[ancestor]++;
  }

  for (int i = 0; i < N; ++i) {
    if (record[i]) {
      printf("%d:%d\n", i + 1, record[i]);
    }
  }
}

int main() {
  cin.redirect("data.in");
  while (true) {
    workload();
  }
}
