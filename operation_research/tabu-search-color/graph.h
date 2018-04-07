#pragma once
#include <queue>
#include <stack>
#include "wheel.h"
struct Vertex {
  int color;
  int edge_beg;
  Vertex() : edge_beg(0), color(-1) {}
};

class Graph : public vector<Vertex> {
 public:
  Graph(int V, int E = 0) {
    this->resize(V);
    edges.reserve(E + 1);
    edges.push_back(Edge(-1, -1));
  }

  struct Edge {
    int next;
    int to;  // vertex
    Edge(int next, int to) : next(next), to(to) {}
  };

  void add_edge(int from, int to) {
    int pre_beg = operator[](from).edge_beg;
    operator[](from).edge_beg = edges.size();
    edges.push_back(Edge(pre_beg, to));
  }

  Edge get_edge(int edge_id) { return edges[edge_id]; }
  // Edge edge_begin(int id) { return get_edge((*this)[id].edge_beg); }
  Edge edge_begin(Vertex& v) { return get_edge(v.edge_beg); }
  Edge edge_next(Edge& e) { return get_edge(e.next); }
  bool edge_valid(Edge& e) { return e.next != -1; }
  vector<Edge> edges;
};
