#pragma once
#include "wheel.h"
#include <queue>
#include <stack>
struct Vertex {
  int color;
  int value;
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
    edges.push_back(Edge(-1, -1));
  }

  struct Edge {
    int next;
    int to;     // vertex
    Edge(int next, int to) : next(next), to(to) {}
  };

  void add_edge(int from, int to) {
    int pre_beg = operator[](from).edge_beg;
    operator[](from).edge_beg = edges.size();
    edges.push_back(Edge(pre_beg, to));
  }

  Edge get_edge(int edge_id) { return edges[edge_id]; }

  vector<Edge> edges;
};
