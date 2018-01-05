#include "../wheel.h"
#define clz(x) __builtin_clz(x)
typedef int T;
#define NIL (1 << 30)
#define INIT NIL
#define FUNC(a, b) std::min(a, b)
// #include "monoid_tree.h"
#include "../fenwick_tree/fenwick.h"
typedef Fenwick MonoidTree;

struct Data {
  int father;
  int max;
  int min;
  int up_gap;
  int down_gap;
  Data(int father = -1, int value = -1)
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
struct DataArray{
  Data data[20];
  Data& operator[](int index){
    return data[index];
  }
};

struct Vertex {
  int ancestor_depth;
  int price;
  int depth;
  // vector<Data> jmpTable;
  int discover_time;
  int finish_time;
  int edge_beg;
  // vector<int> neighbors;
  Vertex() : edge_beg(0) {}
};
// typedef vector<Vertex> Graph;

class Graph : public vector<Vertex> {
public:
  Graph(int V, int E = 0)  {
    this->resize(V);
    edges.reserve(E + 1);
    edges.push_back(Edge(-1, -1));
    jmpTable.resize(V);
  }
  struct Edge {
    int next;
    int to;
    Edge(int next, int to) : next(next), to(to) {}
  };
  void add_edge(int from, int to) {
    int pre_beg = operator[](from).edge_beg;
    operator[](from).edge_beg = edges.size();
    edges.push_back(Edge(pre_beg, to));
  }
  Edge get_edge(int edge_id) { return edges[edge_id]; }
  vector<DataArray> jmpTable;

private:
  vector<Edge> edges;
};

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
      {
        Data acc = Data(parent, vertex.price);
        // [beg 2^k] = [beg 2^--k] * [beg double 2^--k]
        int k = 0;
        graph.jmpTable[source][k] = acc;
        int cur_beg = acc.father;
        while (cur_beg != -1 && graph[cur_beg].depth - (1 << k) >= -1) {
          acc = acc.append_up(graph.jmpTable[cur_beg][k]);
          ++k;
          graph.jmpTable[source][k] = acc;
          cur_beg = acc.father;
        }
      }
      for (Graph::Edge edge = graph.get_edge(vertex.edge_beg); edge.to != -1;
           edge = graph.get_edge(edge.next)) {
        ancestor_depth = depth;
        dfs(graph, edge.to, source);
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
    graph.add_edge(u, v);
    graph.add_edge(v, u);
  }
  DFS()(graph, 0);
  MonoidTree tree(N);
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
    Data left = graph.jmpTable[m][0];
    Data right = graph.jmpTable[n][0];
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
      left = left.append_up(graph.jmpTable[left.father][k]);
      m_depth -= 1 << k;
    }
    while (n_depth > common_depth) {
      int k = 31 - clz(n_depth - common_depth);
      // extend 2^k
      right = right.append_up(graph.jmpTable[right.father][k]);
      n_depth -= 1 << k;
    }
    // cout << right.blend_source(left) << endl;
    printf("%d\n", right.blend_source(left));
  }
}

int main() {
  cin.redirect("data.in");
  workload();
}
