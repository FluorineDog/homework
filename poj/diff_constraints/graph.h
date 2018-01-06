#include "../wheel.h"
#include <queue>
struct Vertex {
  ull value;
  int edge_beg;
  int visited;
  Vertex() : value(1 << 30), edge_beg(0), visited(0) {}
};

class Graph : public vector<Vertex> {
public:
  Graph(int V, int E = 0) {
    this->resize(V);
    edges.reserve(E + 1);
    edges.push_back(Edge(-1, -1));
    // jmpTable.resize(V);
  }

  struct Edge {
    int next;
    int value;
    int to;
    Edge(int next, int to) : next(next), to(to) {}
  };

  void add_edge(int from, int to) {
    int pre_beg = operator[](from).edge_beg;
    operator[](from).edge_beg = edges.size();
    edges.push_back(Edge(pre_beg, to));
  }

  Edge get_edge(int edge_id) { return edges[edge_id]; }

  bool spfa(int source) {
    Graph &graph = *this;
    graph[source].value = 0;
    std::queue<int> q;
    while (!q.empty()) {
      int from = q.front();
      q.pop();
      Vertex &u = graph[from];
      u.visited++;
      if (u.visited == graph.size()) {
        return false;
      }
      for (Edge edge = get_edge(from); edge.to != -1;
           edge = get_edge(edge.next)) {
        Vertex &v = graph[edge.to];
        ull new_value = u.value + edge.value;
        if (v.value < new_value) {
          v.value = new_value;
          q.push(edge.to);
        }
      }
    }
    return true;
  }

private:
  vector<Edge> edges;
};
