#define private public
#include "../wheel.h"
typedef std::pair<int, pair<ull, ull> /**/> T;
#define NIL std::make_pair(1 << 30, make_pair(0, 0))
#define INIT NIL
T ancestor_merge(T a, T b) {
  if (a.first == (1 << 30)) {
    return b;
  } else if (b.first == (1 << 30)) {
    return a;
  }
  if (a.first < b.first) {
    ull left = a.second.first;
    ull right = a.second.second + b.second.second - b.second.first;
    return make_pair(a.first, make_pair(left, right));
  } else {
    ull left = a.second.first + b.second.first - a.second.second;
    ull right = b.second.second;
    return make_pair(b.first, make_pair(left, right));
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
    ancestor = make_pair(-1, make_pair(0, 0));
    depth = -1;
    dfs(graph, source);
  }
  void operator()(Graph &graph) {
    for (int i = 0; i < (int)graph.size(); ++i) {
      graph[i].discover_time = -1;
    }
    timestamp = 0;
    for (int source = 0; source < (int)graph.size(); ++source) {
      ancestor = make_pair(-1, make_pair(0, 0));
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
        ancestor = make_pair(depth, make_pair(0, 0));
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
  int N, M, loc;
  int status = scanf("%d%d%d", &N, &M, &loc);
  --loc;
  if (status != 3) {
    exit(0);
  }
  Graph graph(N);
  vector<pair<pair<int, int>, ull> /**/> edges;
  edges.reserve(M);
  // while (M-- > 0) {
  for (int i = 0; i < N - 1; ++i) {
    int u, v;
    ull w;
    cin >> u >> v >> w;
    --u, --v;
    edges.push_back(make_pair(make_pair(u, v), w));
    graph[u].neighbors.push_back(v);
    graph[v].neighbors.push_back(u);
  }
  int source = 0;
  DFS()(graph, source);
  Fenwick tree(N - 1);

  for (int i = 0; i < N; ++i) {
    int index = graph[i].discover_time;
    if (index == 0) {
      continue;
    }
    --index;
    tree.raw_update(index, graph[i].ancestor);
  }

  for (int i = 0; i < (int)edges.size(); ++i) {
    int u = edges[i].first.first;
    int v = edges[i].first.second;
    ull w = edges[i].second;
    int vertex = graph[u].discover_time > graph[v].discover_time ? u : v;
    int dis = graph[vertex].discover_time;
    int fin = graph[vertex].finish_time;
    if (dis != 0) {
      --dis;
      T ref = tree[dis];
      ref.second.second += w;
      tree.raw_update(dis, ref);
    }
    if (fin != N) {
      --fin;
      T ref = tree[fin];
      ref.second.first += w;
      tree.raw_update(fin, ref);
    }
  }
  tree.fast_init();

  while (M-- > 0) {
    int op;
    cin >> op;
    if (op == 0) {
      // move message
      int a, b;
      cin >> a;
      --a;
      b = loc;
      loc = a;
      int beg = graph[a].discover_time;
      int end = graph[b].discover_time;
      if (beg > end)
        std::swap(beg, end);
      std::pair<ull, ull> distance = tree.reduce(beg, end).second;
      cout << distance.first + distance.second << endl;
    } else {
      // change edge
      int i;
      ull new_w;
      cin >> i >> new_w;
      --i;
      int u = edges[i].first.first;
      int v = edges[i].first.second;
      ull w = edges[i].second;
      w = new_w - w;
      edges[i].second = new_w;
      int vertex = graph[u].discover_time > graph[v].discover_time ? u : v;
      int dis = graph[vertex].discover_time;
      int fin = graph[vertex].finish_time;
      if (dis != 0) {
        --dis;
        T ref = tree[dis];
        ref.second.second += w;
        tree.update(dis, ref);
      }
      if (fin != N) {
        --fin;
        T ref = tree[fin];
        ref.second.first += w;
        tree.update(fin, ref);
      }
    }
  }
}


int main() {
  cin.redirect("data.in");
  while (true) {
    workload();
  }
}
