#include "../wheel.h"
typedef std::pair<int, int> T;
#define NIL std::make_pair(1 << 30, -1)
#define INIT NIL
T ancestor_merge(T a, T b) { return a.first < b.first ? a : b; }
#define FUNC(a, b) ancestor_merge(a, b)
#include "monoid_tree.h"
// #include "../fenwick_tree/fenwick.h"
#include <stack>
#define T std::pair<int, int> 

struct Vertex {
  // int ancestor;
  // int ancestor_depth;
  T ancestor;
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
    ancestor = make_pair(-1, -1);
    depth = -1;
    dfs(graph, source);
  }

private:
  void dfs(Graph &graph, int source) {
    ++depth;
    if (graph[source].discover_time == -1) {
      Vertex &vertex = graph[source];
      vertex.discover_time = timestamp++;
      vertex.ancestor = ancestor;
      for (int i = 0; i < (int)vertex.edges.size(); ++i) {
        ancestor = make_pair(depth, source);
        dfs(graph, vertex.edges[i]);
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
  int N;
  int status = scanf("%d", &N);
  if (status != 1) {
    exit(0);
  }
  Graph graph(N);
  vector<bool> possible_root(N);
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
      possible_root[edge] = true;
    }
  }
  int source = 0;
  for (; source < N; ++source) {
    if (!possible_root[source]) {
      break;
    }
  }
  DFS()(graph, source);
  // MonoidTree tree(N - 1);
  MonoidTree tree(N - 1);
  for (int i = 0; i < N; ++i) {
    int index = graph[i].discover_time;
    if (index == 0) {
      continue;
    }
    --index;
    tree.raw_update(index, graph[i].ancestor);
    // cerr << index << "**" << tree[index].first << "**" << tree[index].second + 1
        //  << endl;
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
    if (beg > end)
      std::swap(beg, end);
    int ancestor = tree.reduce(beg, end).second;
    // cerr << beg << "*" << end << "*" << ancestor + 1 << endl;
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
