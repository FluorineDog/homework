#include "../wheel.h"
#define clz(x) __builtin_clz(x)
typedef long long T;
#define NIL (1 << 30)
#define INIT NIL
#define FUNC(a, b) std::min(a, b)
// #include "monoid_tree.h"
#include "../fenwick_tree/fenwick.h"
struct Data {
  int father;
  int max;
  int min;
  int up_gap;
  int down_gap;
  Data(int father, int value)
      : father(father), max(value), min(value), up_gap(0), down_gap(0) {}
  Data append_up(const Data &v) const {
    Data tmp(v);
    tmp.max = std::max(max, v.max);
    tmp.min = std::min(min, v.min);
    tmp.up_gap = std::max(std::max(tmp.up_gap, up_gap), max - v.min);
    tmp.down_gap = std::max(std::max(tmp.down_gap, down_gap), v.max - min);
    return tmp;
  }
  int blend_source(const Data &v) {
    return std::max(std::max(up_gap, v.down_gap), max - v.min);
  }
};

struct Vertex {
  int ancestor_depth;
  int price;
  int depth;
  vector<Data> jmpTable;
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
    ancestor_depth = -1;
    depth = -1;
    dfs(graph, source, -1);
  }
  void operator()(Graph &graph) {
    for (int i = 0; i < (int)graph.size(); ++i) {
      graph[i].discover_time = -1;
    }
    timestamp = 0;
    for (int source = 0; source < (int)graph.size(); ++source) {
      depth = -1;
      ancestor_depth = -1;
      dfs(graph, source, -1);
    }
  }

private:
  void dfs(Graph &graph, int source, int parent) {
    ++depth;
    if (graph[source].discover_time == -1) {
      Vertex &vertex = graph[source];
      vertex.discover_time = timestamp++;
      vertex.depth = depth;
      vertex.ancestor_depth = ancestor_depth;
      vertex.jmpTable.reserve(32 - clz(depth));
      {
        Data acc = Data(parent, vertex.price);
        vertex.jmpTable.push_back(acc);
        // [beg 2^k] = [beg 2^--k] * [beg double 2^--k]
        int cur_beg = acc.father;
        int k = 0;
        while (cur_beg != -1 && graph[cur_beg].depth - (1 << k) >= -1) {
          acc = acc.append_up(graph[cur_beg].jmpTable[k]);
          vertex.jmpTable.push_back(acc);
          ++k;
          cur_beg = acc.father;
        }
      }
      for (int i = 0; i < (int)vertex.neighbors.size(); ++i) {
        ancestor_depth = depth;
        dfs(graph, vertex.neighbors[i], source);
      }
      vertex.finish_time = timestamp;
    }
    --depth;
  }

private:
  int ancestor_depth;
  int depth;
  int timestamp;
};

void workload() {
  int N;
  {
    int status = scanf("%d", &N);
    if (status != 1) {
      exit(0);
    }
  }
  Graph graph(N);
  for (int i = 0; i < N; ++i) {
    cin >> graph[i].price;
  }
  for (int i = 0; i < N - 1; ++i) {
    int u, v;
    cin >> u >> v;
    --u, --v;
    graph[u].neighbors.push_back(v);
    graph[v].neighbors.push_back(u);
  }
  DFS()(graph, 0);
  Fenwick tree(N);
  for (int i = 1; i < N; ++i) {
    tree.raw_update(graph[i].discover_time - 1, graph[i].ancestor_depth);
  }
  tree.fast_init();
  int Q;
  cin >> Q;
  while (Q-- > 0) {
    int m, n;
    cin >> m >> n;
    m--, n--;
    Data left = graph[m].jmpTable[0];
    Data right = graph[n].jmpTable[0];
    int m_depth = graph[m].depth;
    int n_depth = graph[n].depth;

    int common_depth;
    int a = graph[m].discover_time;
    int b = graph[n].discover_time;
    if (a > b) {
      std::swap(a, b);
    }
    common_depth = tree.reduce(a, b);
    while (m_depth > common_depth) {
      int k = 31 - clz(m_depth - common_depth);
      // extend 2^k
      left = left.append_up(graph[left.father].jmpTable[k]);
      m_depth -= 1 << k;
    }
    while (n_depth > common_depth) {
      int k = 31 - clz(n_depth - common_depth);
      // extend 2^k
      right = right.append_up(graph[right.father].jmpTable[k]);
      n_depth -= 1 << k;
    }
    cout << right.blend_source(left) << endl;
  }
}

int main() {
  cin.redirect("data.in");
  workload();
}