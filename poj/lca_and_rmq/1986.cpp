#include "../wheel.h"
typedef std::pair<int, pair<int, int> /**/> T;
#define NIL std::make_pair(1 << 30, make_pair(-1, -1))
#define INIT NIL
T ancestor_merge(T a, T b) {
  if (a.first < b.first) {
    int left = a.second.first;
    int right = a.second.second + b.second.second - b.second.first;
    return make_pair(a.first, make_pair(left, right));
  } else {
    int left = a.second.first + b.second.first - a.second.second;
    int right = b.second.second;
    return make_pair(a.first, make_pair(left, right));
  }
}
#define FUNC(a, b) ancestor_merge(a, b)
// #include "monoid_tree.h"
#include "../fenwick_tree/fenwick.h"
#include <stack>

struct Vertex {
  // int ancestor;
  // int ancestor_depth;
  T ancestor;
  int discover_time;
  int finish_time;
  vector<int> neighbors;
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
    ancestor = make_pair(-1, make_pair(-1, -1));
    depth = -1;
    dfs(graph, source);
  }
  void operator()(Graph &graph) {
    for (int i = 0; i < (int)graph.size(); ++i) {
      graph[i].discover_time = -1;
    }
    timestamp = 0;
    for (int source = 0; source < graph.size(); ++source) {
      ancestor = make_pair(-1, make_pair(-1, -1));
      depth = -1;
      dfs(graph, source);
    }
  }

private:
  void dfs(Graph &graph, int source) {
    ++depth;
    if (graph[source].discover_time == -1) {
      Vertex &vertex = graph[source];
      vertex.discover_time = timestamp++;
      vertex.ancestor = ancestor;
      for (int i = 0; i < (int)vertex.neighbors.size(); ++i) {
        ancestor = make_pair(depth, make_pair(0,0));
        dfs(graph, vertex.neighbors[i]);
      }
      vertex.finish_time = timestamp;
    }
    --depth;
  }

private:
  T ancestor;
  int depth;
  int timestamp;
};

void workload() {
  int N, M;
  int status = scanf("%d%d", &N, &M);
  if (status != 2) {
    exit(0);
  }
  Graph graph(N);
  vector<pair<pair<int, int>, ull> /**/> edges;
  edges.reserve(M);
  while (M-- > 0) {
    int u, v;
    ull w;
    cin >> u >> v >> w;
    edges.push_back(make_pair(make_pair(u, v), w));
    graph[u].neighbors.push_back(v);
    graph[v].neighbors.push_back(u);
  }
  int source = 0;
  DFS()(graph, source);
  // MonoidTree tree(N - 1);
  Fenwick tree(N - 1);
  for (int i = 0; i < N; ++i) {
    int index = graph[i].discover_time;
    if (index == 0) {
      continue;
    }
    --index;
    tree.raw_update(index, graph[i].ancestor);
  }

  tree.fast_init();
  int K;
  // scanf("%d", &K);
  K = cin.getInt();
  vector<int> record(N);
  while (K-- > 0) {
    int a, b;
    // scanf(" (%d %d)", &a, &b);
    a = cin.getInt();
    b = cin.getInt();
    --a;
    --b;
    int beg = graph[a].discover_time;
    int end = graph[b].discover_time;
    if (beg > end)
      std::swap(beg, end);
    int ancestor = tree.reduce(beg, end).second;
    // cerr << beg << "*" << end << "*" << ancestor + 1 << endl;
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
