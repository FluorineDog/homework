#include "../wheel.h"
#include <queue>
#include <stack>
struct Vertex {
  ull value;
  int edge_beg;
  int visited;
  int in_queue;
  Vertex() : value(1LL << 30), edge_beg(0), visited(0), in_queue(0) {}
};

class Graph : public vector<Vertex> {
public:
  Graph(int V, int E = 0) {
    this->resize(V);
    edges.reserve(E + 1);
    edges.push_back(Edge(-1, -1, 0));
    // jmpTable.resize(V);
  }

  struct Edge {
    ull value;
    int next;
    int to;
    Edge(int next, int to, ull value) : value(value), next(next), to(to) {}
  };

  void add_edge(int from, int to, ull weight) {
    int pre_beg = operator[](from).edge_beg;
    operator[](from).edge_beg = edges.size();
    edges.push_back(Edge(pre_beg, to, weight));
  }

  Edge get_edge(int edge_id) { return edges[edge_id]; }

  bool spfa(int source) {
    Graph &graph = *this;
    graph[source].value = 0;
    graph[source].in_queue = 1;
    std::stack<int> q;
    q.push(source);
    while (!q.empty()) {
      int from = q.top();
      q.pop();
      Vertex &u = graph[from];
      // u.visited++;
      u.in_queue = 0;
      for (Edge edge = get_edge(u.edge_beg); edge.to != -1;
           edge = get_edge(edge.next)) {
        Vertex &v = graph[edge.to];
        ull new_value = u.value + edge.value;
        if (new_value < v.value) {
          v.visited++;
          if (v.visited >= (int)graph.size()) {
            return false;
          }
          v.value = new_value;
          if (!v.in_queue) {
            q.push(edge.to);
            v.in_queue = 1;
          }
        }
      }
    }
    return true;
  }

private:
  vector<Edge> edges;
};
